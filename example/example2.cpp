/// Author: yanxin, 2023

#include "scgtest.h"

using namespace sc_core;

class Module : public sc_module {
 public:
  SC_HAS_PROCESS(Module);

  int cnt = 0;
  sc_in_clk sci_clk;
  Module(sc_module_name name) : sc_module(name) {
    SC_METHOD(method);
    sensitive << sci_clk.pos();
    dont_initialize();
  }

  void method() {
    cnt++;
    std::cout << sc_time_stamp() << " - " << name() << " running\n";
  }
};

class ModuleTest : public testing::Test {
 public:
  Module module{"module"};
  sc_clock clk{"clk", 1, SC_NS};
  void SetUp() override { module.sci_clk(clk); }
};

SCGTEST_F(ModuleTest, a) {
  EXPECT_EQ(sc_time_stamp(), SC_ZERO_TIME);
  wait(5, SC_NS);
  EXPECT_EQ(module.cnt, 5);
  wait(5, SC_NS);
  EXPECT_EQ(module.cnt, 10);
}

SCGTEST_F(ModuleTest, b) {
  EXPECT_EQ(sc_time_stamp(), SC_ZERO_TIME);
  wait(5, SC_NS);
  EXPECT_EQ(module.cnt, 5);
  module.cnt = 0;
  wait(5, SC_NS);
  EXPECT_EQ(module.cnt, 5);
}
