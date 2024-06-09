#include "../src/plugin/prompt.h"
#include "gtest/gtest.h"

TEST(prompt, prompt) {
  plugin::Prompt prompt;
  ASSERT_EQ(prompt.initialize(), 0);
  std::string res;
  ASSERT_EQ(prompt.get_prompt_by_name("ielts_writing_t1_enrich", res), 0);
  EXPECT_EQ(res,
            "You are now an ielts teacher. "
            "I give you a title, you generate a writing article. "
            "This article should have at least 250 words and at most 300 words.");
}
