#include "autostakenet.hpp"

void autostakenet::ontransfer(account_name from, account_name to, extended_asset quantity, string memo)
{
    if (to != _self)
        return;

    eosio_assert(quantity.get_extended_symbol() == ACCEPTED_TOKEN, "Only core token is accepted");

    account_name recepient = string_to_name(memo.c_str());
    eosio_assert(is_account(recepient), "The recepient account does not exist");

    action(permission_level{_self, N(active)}, N(eosio), N(delegatebw),
           delegatebw_args{
               _self,
               recepient,
               asset(quantity.amount, TOKEN_SYMBOL),
               asset(0, TOKEN_SYMBOL),
               true})
        .send();
}