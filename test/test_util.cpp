#include <curl/curl.h>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "util/exception.h"

TEST(default, curl_verion_check) {
    ASSERT_EQ(8, LIBCURL_VERSION_MAJOR);
}

TEST(default, nlohmann_json) {
    nlohmann::json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
    ASSERT_TRUE(j["happy"]);
}

TEST(default, exception) {
    using namespace openai::util;
    OpenAIException e(EType::E_FAILURETOPARSE, "123", "456");
    EXPECT_STREQ("456: 123 (E_FAILURETOPARSE)", e.what());
}
