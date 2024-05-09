#include <nlohmann/json.hpp>

#include "gtest/gtest.h"

TEST(util, nlohmann_json) {
  nlohmann::json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
  ASSERT_TRUE(j["happy"]);
}
