/**
 * @file win32_SmartPointer.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#define __WIN32_SMARTPOINTER_H__

/**
 * @brief The 'SmartPointer' class.
 *
 * @tparam ComClass
 */
template <class ComClass>
class SmartPointer
{
public:
    /**
     * @brief Default-construct a new 'SmartPointer' object.
     *
     */
    SmartPointer() noexcept {}
    /**
     * @brief Copy-Construct a new 'SmartPointer' object.
     *
     * @param obj
     */
    SmartPointer(ComClass* obj) : ptr(obj)
    {
        if (ptr)
            ptr->AddRef();
    }
    /**
     * @brief Move-Construct a new 'SmartPointer' object.
     *
     * @param other
     */
    SmartPointer(SmartPointer& other) : ptr(other.ptr)
    {
        if (ptr)
            ptr->AddRef();
    }
    /**
     * @brief Destroy the 'SmartPointer' object.
     *
     */
    ~SmartPointer()
    {
        release();
    }

    /**
     * @brief Conversion operator.
     *
     * @return ComClass*
     */
    operator ComClass*() CONST noexcept
    {
        return ptr;
    }

    /**
     * @brief Conversion operator.
     *
     * @return ComClass&
     */
    ComClass& operator*() CONST noexcept
    {
        return *ptr;
    }

    /**
     * @brief Conversion operator.
     *
     * @return ComClass*
     */
    ComClass* operator->() CONST noexcept
    {
        return ptr;
    }

    /**
     * @brief Copy operator (pass-by-value).
     *
     * @param newPtr
     * @return SmartPointer&
     */
    SmartPointer& operator= (ComClass* const newPtr)
    {
        if (newPtr != nullptr)
            newPtr->AddRef();
        release();
        ptr = newPtr;
        return *this;
    }

    /**
     * @brief Copy operator (const pass-by-reference).
     *
     * @param newPtr
     * @return SmartPointer&
     */
    SmartPointer& operator= (const ComClass& newPtr)
    {
        return operator= (newPtr.ptr);
    }

    /**
     * @brief Release and nullify this pointer, and return it's memory address.
     *
     * @return ComClass**
     */
    ComClass** resetAndGetAddress()
    {
        release();
        ptr = nullptr;
        return &ptr;
    }

    /**
     * @brief
     *
     * @param classUUID
     * @param dwClsContext
     * @return HRESULT
     */
    HRESULT CoCreateInstance(REFCLSID classUUID, DWORD dwClsContext = CLSCTX_INPROC_SERVER)
    {
        // This *must* call the global function, not the local.
        // Consider overriding the return type def if any clashes...
        // (see JUCE Com Pointer)
        HRESULT hr = ::CoCreateInstance(
            classUUID,
            nullptr,
            dwClsContext,
            __uuidof(ComClass),
            (void**) resetAndGetAddress()
        );
        // assert(hr != CO_E_NOTINITIALIZED);
        return (hr != CO_E_NOTINITIALIZED) ? hr : CO_E_NOTINITIALIZED;
    }

    /**
     * @brief Query the interface to the underlying object.
     *
     * @tparam otherComClass
     * @param classUUID
     * @param destObj
     * @return HRESULT
     */
    template <class otherComClass>
    HRESULT QueryInterface(REFCLSID classUUID, SmartPointer<otherComClass>& destObj) CONST
    {
        if (ptr == nullptr)
            return E_POINTER;

        return ptr->QueryInterface(classUUID, (void**) destObj.resetAndGetAddress());
    }

    /**
     * @brief Query the interface to the underlying object.
     *
     * @tparam otherComClass
     * @param destObj
     * @return HRESULT
     */
    template <class otherComClass>
    HRESULT QueryInterface (SmartPointer<otherComClass>& destObj) CONST
    {
        return this->QueryInterface(__uuidof(otherComClass), destObj);
    }

    /**
     * @brief Get an interface to the underlying object.
     *
     * @tparam otherComClass
     * @return SmartPointer<otherComClass>
     */
    template <class otherComClass>
    SmartPointer<otherComClass> getInterface() CONST
    {
        SmartPointer<otherComClass> destObj;

        if (QueryInterface(destObj) == S_OK)
            return destObj;

        return nullptr;
    }
private:

    /**
     * @brief Call the templated object's underlying 'Release()' method, which
     * must be implemented.
     *
     */
    void release()
    {
        if (ptr != nullptr) ptr->Release();
    }

    /**
     * @brief Conversion operator (innaccessible).
     *
     * @return ComClass**
     */
    ComClass** operator&() noexcept {/* (innaccessible) */}

    /** @brief The underlying pointer member. */
    ComClass* ptr = nullptr;
};

/**
 * @brief The 'SmartPointerHelperBase' class.
 *
 * @tparam First
 * @tparam ComClasses
 */
template <class First, class... ComClasses>
class SmartPointerHelperBase : public First, public ComClasses...
{
public:
    /**
     * @brief Construct a new 'SmartPointerHelperBase' object.
     *
     * @param initRef
     */
    SmartPointerHelperBase(unsigned int initRef) : refCount(initRef) {}
    /**
     * @brief Destroy the 'SmartPointerHelperBase' object.
     *
     */
    virtual ~SmartPointerHelperBase() = default;

    /**
     * @brief Add a new reference to the pointer, increasing the counter by one.
     *
     * @return ULONG
     */
    ULONG STDMETHODCALLTYPE AddRef()
    {
        return ++refCount;
    }
    /**
     * @brief Release a reference to the pointer, decreasing the counter by one.
     *
     * @return ULONG
     */
    ULONG STDMETHODCALLTYPE Release()
    {
        auto r = --refCount;

        if (r == 0)
            delete this;

        return r;
    }

protected:

    /**
     * @brief The underlying reference counter to the pointer.
     *
     */
    ULONG refCount;

    /**
     * @brief Add a new reference to the pointer (increasing the counter by one),
     * and attempt to cast to type 'T'. The returned 'HRESULT' can be checked
     * so that any unsuccessful casts might then be freed with the 'Release()'
     * method.
     *
     * @tparam Type
     * @param result
     * @return HRESULT
     */
    template <class Type>
    HRESULT STDMETHODCALLTYPE castToType(void** result)
    {
        this->AddRef();
        *result = dynamic_cast<Type*>(this);

        return S_OK;
    }

    /**
     * @brief
     *
     * @param refId
     * @param result
     * @return HRESULT
     */
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID refId, void** result)
    {
        if (refId == __uuidof (IUnknown))
            return castToType<First> (result);

        *result = nullptr;

        return E_NOINTERFACE;
    }
};

template <class... ComClasses>
class SmartPointerHelper : public SmartPointerHelperBase<ComClasses...>
{
public:
    explicit SmartPointerHelper(unsigned int initRef = 1) : SmartPointerHelperBase<ComClasses...>(initRef) {}

    /**
     * @brief
     *
     * @param refId
     * @param result
     * @return HRESULT
     */
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID refId, void** result)
    {
        const std::tuple<IID, void*> bases[]
        {
            std::make_tuple (__uuidof(ComClasses), static_cast<void*> (static_cast<ComClasses*> (this)))...
        };

        // Query a ranged 'for' loop (each 'base' in the 'bases' tuple array)
        for (const auto& base : bases)
        {
            if (refId == std::get<0> (base))
            {
                this->AddRef();
                *result = std::get<1> (base);

                return S_OK;
            }
        }

        return SmartPointerHelperBase<ComClasses...>::QueryInterface (refId, result);
    }
};

/**
 * @brief
 *
 * @tparam ComClass
 * @param ptr
 */
template <class ComClass>
void SafeRelease(ComClass** ptr)
{
    if (*ptr)
    {
        (*ptr)->Release();
        *ptr = nullptr;
    }
}
