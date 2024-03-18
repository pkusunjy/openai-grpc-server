#include <gtest/gtest.h>

#include "liboai.h"

TEST(liboai, add) {
    ASSERT_EQ(4, 2 + 2);
}

TEST(liboai, chat_completion) {
    liboai::OpenAI oai;
    liboai::Conversation convo;
    convo.AddUserData("What is the point of taxes?");
    ASSERT_TRUE(oai.auth.SetKey("OPENAI_API_KEY"));

    try {
        liboai::Response response = oai.ChatCompletion->create(
            "gpt-3.5-turbo", convo
        );
        convo.Update(response);
        EXPECT_EQ("12", convo.GetLastResponse());
        std::cout << convo.GetLastResponse() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}