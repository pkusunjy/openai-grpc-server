#include "gtest/gtest.h"
#include "yaml-cpp/parser.h"

TEST(yaml_parser, basic) {
  YAML::Parser parser;
  ASSERT_FALSE(parser);
}