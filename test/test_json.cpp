#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(default, add) {
    json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
    ASSERT_TRUE(j["happy"]);
}

