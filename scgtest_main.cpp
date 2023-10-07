/// Author: zzz00yx, 2023

#include "scgtest.h"

class SCGTestEventListener : public testing::EmptyTestEventListener {
  // Called after a test ends.
  void OnTestEnd(const testing::TestInfo& test_info) override {
    sc_core::sc_get_curr_simcontext()->reset();
  }
};

int sc_main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  testing::TestEventListeners& listeners =
      testing::UnitTest::GetInstance()->listeners();
  listeners.Append(new SCGTestEventListener);
  return RUN_ALL_TESTS();
}
