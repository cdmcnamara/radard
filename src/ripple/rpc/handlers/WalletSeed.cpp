//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012-2014 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

namespace ripple {

// {
//   secret: <string>
// }
Json::Value doWalletSeed (RPC::Context& context)
{
    RippleAddress   seed;
    bool bSecret = context.params_.isMember ("secret");

    if (bSecret && !seed.setSeedGeneric (context.params_["secret"].asString ()))
    {
        return rpcError (rpcBAD_SEED);
    }
    else
    {
        RippleAddress   raAccount;

        if (!bSecret)
        {
            seed.setSeedRandom ();
        }

        RippleAddress raGenerator = RippleAddress::createGeneratorPublic (seed);

        raAccount.setAccountPublic (raGenerator, 0);

        Json::Value obj (Json::objectValue);

        obj["seed"]     = seed.humanSeed ();
        obj["key"]      = seed.humanSeed1751 ();
        obj["deprecated"] = "Use wallet_propose instead";

        return obj;
    }
}
} // ripple
