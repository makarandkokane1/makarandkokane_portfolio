
/*-------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <algorithm>

//-------------------------------------------------------------------------------------------------

#include "mkMemoryRawArrays.h"

//-------------------------------------------------------------------------------------------------

template<typename ElementType>
mkUtilities::array<ElementType>::array (
    const array& in_src
    ) :
    m_rawPtr (nullptr),
    m_size (0)
{
    cleanup ();

    if (in_src.m_size <= 0)
        return;

    create (in_src.m_size, in_src.m_rawPtr[0]);

    for (std::size_t i = 0; i < m_size; i++)
        m_rawPtr[i] = in_src.m_rawPtr[i];
}

//-------------------------------------------------------------------------------------------------

template<typename ElementType>
ElementType& mkUtilities::array<ElementType>::get (const size_t& in_index)
{
    if (in_index >= m_size)
    {
        throw 0;
    }

    return m_rawPtr[in_index];
}

//-------------------------------------------------------------------------------------------------

template<typename ElementType>
void mkUtilities::array<ElementType>::realloc (
    const std::size_t& in_newSize,
    const ElementType& in_initialValue)
{
    ElementType* l_rawPtr (nullptr);
    std::size_t  l_size (0);

    if (in_newSize > 0)
    {
        try
        {
            l_rawPtr = new ElementType[in_newSize] {in_initialValue};

            l_size = in_newSize;

            for (auto i = 0; i < l_size; i++)
            {
                if (i < m_size)
                    l_rawPtr[i] = m_rawPtr[i];
                else
                    l_rawPtr[i] = in_initialValue;
            }
                
        }
        catch (std::bad_alloc& e)
        {
            throw e;
        }
    }

    cleanup ();

    m_rawPtr = l_rawPtr;
    m_size = l_size;
}

//-------------------------------------------------------------------------------------------------

template<typename ElementType>
mkUtilities::array<ElementType>::array (
    const std::size_t& in_initialSize,
    const ElementType& in_initialValue) :
    m_rawPtr (nullptr),
    m_size (0)
{
    if (in_initialSize <= 0)
        return;

    create (in_initialSize, in_initialValue);
}

//-------------------------------------------------------------------------------------------------

template<typename ElementType>
void mkUtilities::array<ElementType>::create (
    const std::size_t& in_initialSize,
    const ElementType& in_initialValue)
{
    try
    {
        m_rawPtr = new ElementType[in_initialSize] {in_initialValue};

        m_size = in_initialSize;

        std::fill_n (m_rawPtr, m_size, in_initialValue);
    }
    catch (std::bad_alloc& e)
    {
        throw e;
    }
}

//-------------------------------------------------------------------------------------------------

template<typename ElementType>
void mkUtilities::array<ElementType>::cleanup ()
{
    if (m_rawPtr)
    {
        delete [] m_rawPtr;
        m_rawPtr = nullptr;
        m_size = 0;
    }
}

//-------------------------------------------------------------------------------------------------

template<typename ElementType>
mkUtilities::array<ElementType>::~array ()
{
    cleanup ();
}

//-------------------------------------------------------------------------------------------------

class TestClass
{
public:

    TestClass (const int& in_data) : m_data (in_data) {}

    const TestClass& operator = (const TestClass& in_src)
    {
        m_data = in_src.m_data;
        return *this;
    }

    TestClass (const TestClass& in_src) : m_data (in_src.m_data)
    {        
    }

    void set (const int& in) { m_data = in; }

    int get () const { return m_data; }

private:

    TestClass ();

    int m_data;
};

//-------------------------------------------------------------------------------------------------

void mkUtilities::unittests_rawArrays ()
{
    try
    {
        TestClass element (7);
        mkUtilities::array<TestClass> obj (100000000000L, element);
    }
    catch (std::bad_alloc& e)
    {
        std::cout << "Failed to allocate memory.";
    }

    TestClass element (6);
    mkUtilities::array<TestClass> obj (5, element);

    mkUtilities::array<TestClass> obj2 = obj;

    mkUtilities::array<TestClass> obj3[2] {obj, obj};

    for (auto i = 0; i < obj2.size (); i++)
    {
        TestClass& t = obj2.get (i);
        t.set (i);
    }

    try
    {
        for (auto i = 0; i <= obj2.size (); i++)
        {
            auto t = obj2.get (i);
        }
    }
    catch (const int& e)
    {
        std::cout << "Out of memory bounds.";
    }

    obj2.realloc (8, element);

    for (auto i = 0; i < obj2.size (); i++)
    {
        TestClass& t = obj2.get (i);
        std::cout << t.get () << " ";
    }
}

//-------------------------------------------------------------------------------------------------
