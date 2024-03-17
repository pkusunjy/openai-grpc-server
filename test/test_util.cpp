#include <curl/curl.h>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

TEST(util, nlohmann_json) {
    nlohmann::json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
    ASSERT_TRUE(j["happy"]);
}
