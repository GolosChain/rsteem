/// Runnung example:
///     ./plugin_test --log_level=test_suite --run_test=white_options_postfix

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "database_fixture.hpp"
#include "comment_reward.hpp"
#include "options_postfix.hpp"


using namespace golos::test;


struct whitelist_key {
    std::string key = "history-whitelist-ops";
};


BOOST_FIXTURE_TEST_CASE(white_options_postfix, options_fixture) {
    init_plugin<test_options_postfix<combine_postfix<whitelist_key>>>();

    size_t _chacked_ops_count = 0;
    for (const auto &co : _db_init._added_ops) {
        auto iter = _finded_ops.find(co.first);
        bool is_finded = (iter not_eq _finded_ops.end());
        BOOST_CHECK(is_finded);
        if (is_finded) {
            BOOST_CHECK_EQUAL(iter->second, co.second);
            if (iter->second == co.second) {
                ++_chacked_ops_count;
            }
        } else {
            BOOST_TEST_MESSAGE("Operation \"" + co.second + "\" by \"" + co.first + "\" is not found");
        }
    }
    BOOST_CHECK_EQUAL(_chacked_ops_count, _db_init._added_ops.size());
}