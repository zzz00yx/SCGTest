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

## What is SCGTest?

## How does SCGTest work?

## Caveats

## To-Do
