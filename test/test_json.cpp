#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "util/exception.h"

using json = nlohmann::json;

TEST(default, add) {
    json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
    ASSERT_TRUE(j["happy"]);
}

TEST(default, exception) {
    using namespace openai::util;
    OpenAIException e(EType::E_FAILURETOPARSE, "123", "456");
    EXPECT_STREQ("456: 123 (E_FAILURETOPARSE)", e.what());
}
