#define BOOST_TEST_MODULE ipfilter_test_module

#include <boost/test/unit_test.hpp>

#include "library.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ipfilter_test_suite)

BOOST_AUTO_TEST_CASE(ipfilter_test) {
    IPPool ip_pool = { IP(1, 2, 34, 76), IP(1, 1, 3, 6), IP(20, 2, 3, 7), IP(20, 2, 3, 100), IP(5, 250, 167, 7) };
    IPPool ip_pool_sample = { IP(20, 2, 3, 100), IP(20, 2, 3, 7), IP(5, 250, 167, 7), IP(1, 2, 34, 76), IP(1, 1, 3, 6) };

    sort_ip_pool(ip_pool);
    BOOST_CHECK(equal(ip_pool.cbegin(), ip_pool.cend(), ip_pool_sample.cbegin()));

    ip_pool_sample = { IP(1, 2, 34, 76), IP(1, 1, 3, 6) };
    BOOST_CHECK(equal(ip_pool_sample.cbegin(), ip_pool_sample.cend(), filter(ip_pool, 1).cbegin()));

    ip_pool_sample = { IP(20, 2, 3, 100), IP(20, 2, 3, 7) };
    BOOST_CHECK(equal(ip_pool_sample.cbegin(), ip_pool_sample.cend(), filter(ip_pool, 20, 2, 3).cbegin()));

    ip_pool_sample = { IP(20, 2, 3, 100), IP(20, 2, 3, 7), IP(1, 1, 3, 6) };
    BOOST_CHECK(equal(ip_pool_sample.cbegin(), ip_pool_sample.cend(), filter_any(ip_pool, 3).cbegin()));
}

BOOST_AUTO_TEST_SUITE_END()
