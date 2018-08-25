#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

#include <string>

using namespace std;
using namespace eosio;

struct transfer_args
{
    account_name from;
    account_name to;
    asset quantity;
    string memo;
};

class autostakecpu : public contract
{
  public:
    using contract::contract;

    const symbol_name TOKEN_SYMBOL = S(4, EOS);
    const extended_symbol ACCEPTED_TOKEN = extended_symbol(TOKEN_SYMBOL, N(eosio.token));

    struct delegatebw_args
    {
        account_name from;
        account_name receiver;
        asset stake_net_quantity;
        asset stake_cpu_quantity;
        bool transfer;
    };

    /**
     * @brief An internal function for handling token transfers.
     * @detail The raw transfer data has been pre-processed to convert the `asset` parameter into the `extended_asset` type.
     * @param from The account tokens are transferred from
     * @param to The account tokens are transferred to
     * @param quantity The amount of tokens transferred
     * @param memo The memo of the token transfer
     */
    void ontransfer(account_name from, account_name to, extended_asset quantity, string memo);
};

extern "C"
{
    void apply(uint64_t receiver, uint64_t code, uint64_t action)
    {
        auto self = receiver;
        autostakecpu thiscontract(self);
        if (action == N(transfer))
        {
            auto transfer_data = unpack_action_data<transfer_args>();
            thiscontract.ontransfer(transfer_data.from, transfer_data.to, extended_asset(transfer_data.quantity, code), transfer_data.memo);
        }
    }
}
