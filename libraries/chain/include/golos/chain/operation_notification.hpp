#pragma once

#include <golos/protocol/operations/operations.hpp>

#include <golos/chain/steem_object_types.hpp>

namespace golos {
    namespace chain {

        struct operation_notification {
            operation_notification(const protocol::operation &o) : op(o) {
            }

            transaction_id_type trx_id;
            uint32_t block = 0;
            uint32_t trx_in_block = 0;
            uint16_t op_in_trx = 0;
            uint64_t virtual_op = 0;
            const protocol::operation &op;
        };

    }
}