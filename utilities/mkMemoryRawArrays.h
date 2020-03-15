
/*-------------------------------------------------------------------------------------------------

Simple utilities for raw memory management.
Trade-off: Chooses safety over performance.

-------------------------------------------------------------------------------------------------*/

#ifndef _mkMemoryRawArrays
#define _mkMemoryRawArrays

//-------------------------------------------------------------------------------------------------

#include <cstddef>
#include <new>

//-------------------------------------------------------------------------------------------------

namespace mkUtilities
{
    //---------------------------------------------------------------------------------------------

    // Unlike std::array, mkUtilities::array uses dynamic allocation.

    template<typename ElementType>
    class array
    {

    public:

        array (const std::size_t& in_initialSize,
            const ElementType& in_initialValue);

        array (const array& in_src);

        void realloc (const std::size_t& in_newSize,
            const ElementType& in_initialValue);

        virtual ~array ();

        inline std::size_t size () const { return m_size; }

        ElementType& get (const size_t& in_index);

    private:

        array ();

        void create (const std::size_t& in_initialSize,
            const ElementType& in_initialValue);

        void cleanup ();

        ElementType* m_rawPtr;
        std::size_t  m_size;
    };

    //---------------------------------------------------------------------------------------------

    void unittests_rawArrays ();

    //---------------------------------------------------------------------------------------------
};

//-------------------------------------------------------------------------------------------------

#endif

//-------------------------------------------------------------------------------------------------
