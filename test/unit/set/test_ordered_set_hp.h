/*
    This file is a part of libcds - Concurrent Data Structures library

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2016

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CDSUNIT_SET_TEST_ORDERED_SET_HP_H
#define CDSUNIT_SET_TEST_ORDERED_SET_HP_H

#include "test_set_hp.h"

namespace cds_test {

    class container_ordered_set_hp: public container_set_hp
    {
        typedef container_set_hp base_class;

    protected:
        template <typename Set>
        void test( Set& s )
        {
            // Precondition: set is empty
            // Postcondition: set is empty

            base_class::test( s );

            ASSERT_TRUE( s.empty() );
            ASSERT_CONTAINER_SIZE( s, 0 );

            typedef typename Set::value_type value_type;

            size_t const nSetSize = kSize;
            std::vector< value_type > data;
            std::vector< size_t> indices;
            data.reserve( kSize );
            indices.reserve( kSize );
            for ( size_t key = 0; key < kSize; ++key ) {
                data.push_back( value_type( static_cast<int>(key) ) );
                indices.push_back( key );
            }
            shuffle( indices.begin(), indices.end() );

            for ( auto i : indices ) {
                ASSERT_TRUE( s.insert( data[i] ));
            }
            ASSERT_FALSE( s.empty() );
            ASSERT_CONTAINER_SIZE( s, nSetSize );

            typedef typename Set::guarded_ptr guarded_ptr;
            guarded_ptr gp;

            // extract_min
            size_t nCount = 0;
            int nKey = -1;
            while ( !s.empty() ) {
                gp = s.extract_min();
                ASSERT_FALSE( !gp );
                EXPECT_EQ( nKey + 1, gp->key());
                ++nCount;
                nKey = gp->key();
            }
            gp.release();
            EXPECT_EQ( nCount, nSetSize );

            ASSERT_TRUE( s.empty() );
            ASSERT_CONTAINER_SIZE( s, 0 );

            // extract_max
            for ( auto i : indices ) {
                ASSERT_TRUE( s.insert( data[i] ) );
            }
            ASSERT_FALSE( s.empty() );
            ASSERT_CONTAINER_SIZE( s, nSetSize );

            nCount = 0;
            nKey = nSetSize;
            while ( !s.empty() ) {
                gp = s.extract_max();
                ASSERT_FALSE( !gp );
                EXPECT_EQ( nKey - 1, gp->key());
                ++nCount;
                nKey = gp->key();
            }
            gp.release();
            EXPECT_EQ( nCount, nSetSize );

            ASSERT_TRUE( s.empty() );
            ASSERT_CONTAINER_SIZE( s, 0 );
        }
    };
} // namespace cds_test

#endif // CDSUNIT_SET_TEST_ORDERED_SET_HP_H
