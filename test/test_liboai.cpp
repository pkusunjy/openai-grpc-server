#include "gtest/gtest.h"
#include "liboai.h"

TEST(liboai, authorization) {
  static liboai::Authorization& auth = liboai::Authorization::Authorizer();
  ASSERT_TRUE(auth.SetKeyEnv("OPENAI_API_KEY"));
}

TEST(liboai, chat_completion) {
  liboai::OpenAI oai;
  liboai::Conversation convo;
  convo.AddUserData("What is the point of taxes?");

  liboai::Response response =
      oai.ChatCompletion->create("gpt-3.5-turbo", convo);
  convo.Update(response);
  EXPECT_FALSE(convo.GetLastResponse().empty());
  std::cout << convo.GetLastResponse() << std::endl;
}