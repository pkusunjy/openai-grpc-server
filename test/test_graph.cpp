#include "babylon/anyflow/builder.h"
#include "gtest/gtest.h"
#include "src/processor/plus.h"

using ::babylon::anyflow::GraphBuilder;
using ::babylon::anyflow::GraphProcessor;

struct Graph : public ::testing::Test {
  virtual void SetUp() override {
    {
      auto& v = builder.add_vertex([] {
        return std::unique_ptr<processor::Plus>(new processor::Plus);
      });
      v.named_depend("a").to("A");
      v.named_depend("b").to("B");
      v.named_emit("c").to("C");
    }
    builder.finish();
  }
  GraphBuilder builder;
};

TEST_F(Graph, plus) {
  auto graph = builder.build();
  auto a = graph->find_data("A");
  auto b = graph->find_data("B");
  auto c = graph->find_data("C");

  *(a->emit<int>()) = 1;
  *(b->emit<int>()) = 2;
  graph->run(c);
  ASSERT_EQ(3, *c->value<int32_t>());
}
