/// Author: zzz00yx, 2023

#include "scgtest.h"

namespace {
class SCGTestEventListener : public testing::EmptyTestEventListener {
  // Called after a test ends.
  void OnTestEnd(const testing::TestInfo& test_info) override {
    sc_core::sc_get_curr_simcontext()->reset();
  }
};
}  // namespace

int sc_main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  testing::UnitTest::GetInstance()->listeners().Append(
      new SCGTestEventListener{});
  return RUN_ALL_TESTS();
}
