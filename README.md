# SCGTest
GTest on SystemC

## Quickstart
1. Install the gtest and systemc libraries.
```sh
# ubuntu 22.04
sudo apt install libgtest-dev libsystemc-dev
```
2. Include this repo in your cmake file.
``` cmake
include(FetchContent)
FetchContent_Declare(
  SCGTest
  GIT_REPOSITORY https://github.com/zzz00yx/SCGTest.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SCGTest)

target_link_library(<YOUR-TARGET>
    SCGTest
)
```
3. Use a GTest test-fixture to define your SystemC modules and other components, and instance or bind them in `SetUp` function.
```cpp
#include "scgtest.h"

class MyTest : public testing::Test {
 public:
  Module module{"module"};
  sc_clock clk{"clk", 1, SC_NS};

  void SetUp() override { module.sci_clk(clk); }
};
```
4. Using `SCGTEST_F` macros to construct your testcases.
`SCGTEST_F` are completely consistent with the well-known `TEST_F` in GTest from the perspective of the user but works in SystemC context.
```cpp
SCGTEST_F(MyTest, TestName) {
  // ... test body ...
}
```

## What is SCGTest?

## How does SCGTest work?

## Caveats

## To-Do
