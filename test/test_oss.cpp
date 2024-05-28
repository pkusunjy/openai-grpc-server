#include "gtest/gtest.h"
#include "src/plugin/oss.h"

plugin::OssClient client;

TEST(oss, initialize) {
  ASSERT_EQ(client.initialize(), 0);
}

TEST(oss, put_object) {
  ASSERT_EQ(client.put_object("example.jpg", "example.jpg"), 0);
}