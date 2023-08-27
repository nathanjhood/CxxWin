/***************************************************************************//**
 * @file SmartPtr.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-24
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

#ifndef _CXX_WIN_SMARTPTR_H_
#define _CXX_WIN_SMARTPTR_H_

template <class T>
class SmartPointer
{
public:
    /**
     * @brief Construct a new Smart Pointer object
     *
     * @param p
     */
    SmartPointer(T *p) : ptr(p)
    {

    }
    /**
     * @brief Copy-Construct a new Smart Pointer object
     *
     * @param other
     */
    SmartPointer(SmartPointer& other) : ptr(other.ptr)
    {

    }
    /**
     * @brief Move-Construct a new Smart Pointer object
     *
     * @param other
     */
    SmartPointer(SmartPointer&& other) noexcept : ptr() // initialize via default constructor, C++11 only
    {
        swap(*this, other);
    }
    /**
     * @brief Destroy the Smart Pointer object
     *
     */
    ~SmartPointer()
    {
        Release(ptr);
    }

    /**
     * @brief
     *
     * @param other
     * @return SmartPointer&
     */
    inline SmartPointer& operator=(const SmartPointer& other)
    {
        SmartPointer temp(other);
        Swap(*this, temp);
        return *this;
    }

    inline void Release()
    {
        if (ptr)
        {
            delete ptr;
        }
    }

    /**
     * @brief
     *
     * @param first
     * @param second
     */
    friend void Swap(const SmartPointer& first, const SmartPointer& second) // nothrow
    {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.ptr, second.ptr);
    }

private:
    T* ptr;
};

template <class T>
void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

#endif
