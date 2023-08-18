/// Author: yanxin, 2023

#include "scgtest.h"

using namespace sc_core;

SCGTEST(x, a) {
  EXPECT_EQ(sc_time_stamp(), SC_ZERO_TIME);
  wait(1, SC_NS);
  EXPECT_EQ(sc_time_stamp(), sc_time(1, SC_NS));
  wait(1, SC_NS);
  EXPECT_EQ(sc_time_stamp(), sc_time(2, SC_NS));
}

SCGTEST(x, b) {
  EXPECT_EQ(sc_time_stamp(), SC_ZERO_TIME);
  wait(1, SC_NS);
  EXPECT_EQ(sc_time_stamp(), sc_time(1, SC_NS));
  wait(1, SC_NS);
  EXPECT_EQ(sc_time_stamp(), sc_time(2, SC_NS));
  wait(1, SC_NS);
  EXPECT_EQ(sc_time_stamp(), sc_time(3, SC_NS));
}
