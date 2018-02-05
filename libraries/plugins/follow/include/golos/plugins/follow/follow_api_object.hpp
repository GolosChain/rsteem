#ifndef GOLOS_FOLLOW_API_OBJECT_HPP
#define GOLOS_FOLLOW_API_OBJECT_HPP

#include <golos/plugins/social_network/api_object/comment_api_object.hpp>
#include <golos/plugins/follow/follow_objects.hpp>
#include "follow_forward.hpp"
namespace golos {
    namespace plugins {
        namespace follow {
            using golos::protocol::account_name_type;

            struct feed_entry {
                account_name_type author;
                std::string permlink;
                std::vector<account_name_type> reblog_by;
                time_point_sec reblog_on;
                uint32_t entry_id = 0;
            };

            struct comment_feed_entry {
                social_network::comment_api_object comment;
                std::vector<account_name_type> reblog_by;
                time_point_sec reblog_on;
                uint32_t entry_id = 0;
            };

            struct blog_entry {
                account_name_type author;
                account_name_type permlink;
                account_name_type blog;
                time_point_sec reblog_on;
                uint32_t entry_id = 0;
            };

            struct comment_blog_entry {
                social_network::comment_api_object comment;
                std::string blog;
                time_point_sec reblog_on;
                uint32_t entry_id = 0;
            };

            struct account_reputation {
                account_name_type account;
                golos::protocol::share_type reputation;
            };

            struct follow_api_object {
                account_name_type follower;
                account_name_type following;
                std::vector<follow_type> what;
            };

            struct reblog_count {
                account_name_type author;
                uint32_t count;
            };
            struct follow_count_api_obj {
                follow_count_api_obj() {}
                follow_count_api_obj(const std::string& acc,
                    uint32_t followers,
                    uint32_t followings,
                    uint32_t lim)
                     : account(acc),
                     follower_count(followers),
                     following_count(followings),
                     limit(lim) {
                }

                follow_count_api_obj(const follow_count_api_obj &o) :
                        account(o.account),
                        follower_count(o.follower_count),
                        following_count(o.following_count),
                        limit(o.limit) {
                }
                string account;
                uint32_t follower_count = 0;
                uint32_t following_count = 0;
                uint32_t limit = 1000;
            };

            typedef std::vector<std::pair<account_name_type, uint32_t>> blog_authors_r;
        }}}

FC_REFLECT((golos::plugins::follow::feed_entry), (author)(permlink)(reblog_by)(reblog_on)(entry_id));

FC_REFLECT((golos::plugins::follow::comment_feed_entry), (comment)(reblog_by)(reblog_on)(entry_id));

FC_REFLECT((golos::plugins::follow::blog_entry), (author)(permlink)(blog)(reblog_on)(entry_id));

FC_REFLECT((golos::plugins::follow::comment_blog_entry), (comment)(blog)(reblog_on)(entry_id));

FC_REFLECT((golos::plugins::follow::account_reputation), (account)(reputation));

FC_REFLECT((golos::plugins::follow::follow_api_object), (follower)(following)(what));

FC_REFLECT((golos::plugins::follow::reblog_count), (author)(count));

FC_REFLECT((golos::plugins::follow::follow_count_api_obj), (account)(follower_count)(following_count)(limit));


#endif //GOLOS_FOLLOW_API_OBJECT_HPP
