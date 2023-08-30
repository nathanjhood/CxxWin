/***************************************************************************//**
 * @file win32_PlatformDefs.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-30
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

#pragma once

//==============================================================================
/** This is a shorthand macro for deleting a class's copy constructor and
    copy assignment operator.

    For example, instead of
    @code
    class MyClass
    {
        etc..

    private:
        MyClass (const MyClass&);
        MyClass& operator= (const MyClass&);
    };@endcode

    ..you can just write:

    @code
    class MyClass
    {
        etc..

    private:
        __DECLARE_NON_COPYABLE (MyClass)
    };@endcode
*/
#define __DECLARE_NON_COPYABLE(className) \
    className (const className&) = delete;\
    className& operator= (const className&) = delete;

/** This is a shorthand macro for deleting a class's move constructor and
    move assignment operator.
*/
#define __DECLARE_NON_MOVEABLE(className) \
    className (className&&) = delete;\
    className& operator= (className&&) = delete;

/** This is a shorthand way of writing both a __DECLARE_NON_COPYABLE and
    __LEAK_DETECTOR macro for a class.
*/
#define __DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(className) \
    __DECLARE_NON_COPYABLE(className) \
    __LEAK_DETECTOR(className)

/** This macro can be added to class definitions to disable the use of new/delete to
    allocate the object on the heap, forcing it to only be used as a stack or member variable.
*/
#define __PREVENT_HEAP_ALLOCATION \
   private: \
    static void* operator new (size_t) = delete; \
    static void operator delete (void*) = delete;
