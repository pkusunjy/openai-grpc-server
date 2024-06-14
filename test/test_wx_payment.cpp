#include "gtest/gtest.h"
#include "../src/service/wx_payment.h"

TEST(wx_payment, nonce_str) {
    wx_payment::WxPaymentImpl impl;
    std::string nonce_str;
    ASSERT_EQ(0, impl.generate_nonce_str(nonce_str));
    ASSERT_FALSE(nonce_str.empty());
}

TEST(wx_payment, http_authorization) {
    wx_payment::WxPaymentImpl impl;
    wx_payment::AuthorizationInput input;
    input.http_method = "GET";
    input.url = "https://www.baidu.com";
    input.nonce_str = "abcdef";
    input.timestamp = "1718355298";
    input.request_body = "{}";
    std::string res;
    ASSERT_EQ(0, impl.generate_http_authorization(input, res));
    ASSERT_FALSE(!res.empty());
}
