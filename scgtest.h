/// Author: yanxin, 2023

#include <gtest/gtest.h>

#include <functional>
#include <systemc>

namespace internal {
class GTestModule : public sc_core::sc_module {
  std::function<void()> test_body;
  sc_core::sc_report_handler_proc old_handler{};

  static void sc_stop_report_handler(
      const sc_core::sc_report& report GTEST_ATTRIBUTE_UNUSED_,
      const sc_core::sc_actions& actions GTEST_ATTRIBUTE_UNUSED_) {}

 public:
  SC_HAS_PROCESS(GTestModule);

  GTestModule(const sc_core::sc_module_name& name, std::function<void()> fun)
      : sc_module(name), test_body(std::move(fun)) {
    SC_THREAD(thread);
  }
  ~GTestModule() {
    if (old_handler) {
      sc_core::sc_report_handler::set_handler(old_handler);
    }
  }
  void thread() {
    test_body();
    old_handler = sc_core::sc_report_handler::set_handler(
        &GTestModule::sc_stop_report_handler);
    sc_core::sc_stop();
  }
};
}  // namespace internal

struct HierarchyScope {
  sc_core::sc_module& m;
  HierarchyScope(sc_core::sc_module& _m) : m(_m) {
    m.simcontext()->hierarchy_push(&m);
  }
  ~HierarchyScope() { m.simcontext()->hierarchy_pop(); }
};

#define SCGTEST_TEST_(test_case_name, test_name, parent_class, parent_id)     \
  class GTEST_TEST_CLASS_NAME_(test_case_name, test_name)                     \
      : public parent_class {                                                 \
   public:                                                                    \
    GTEST_TEST_CLASS_NAME_(test_case_name, test_name)() {}                    \
                                                                              \
   private:                                                                   \
    void TestBody() override {                                                \
      internal::GTestModule module{#test_case_name "-" #test_name,            \
                                   [this]() { SC_TestBody(); }};              \
      sc_core::sc_start();                                                    \
    }                                                                         \
    void SC_TestBody();                                                       \
    static ::testing::TestInfo* const test_info_ GTEST_ATTRIBUTE_UNUSED_;     \
    GTEST_DISALLOW_COPY_AND_ASSIGN_(GTEST_TEST_CLASS_NAME_(test_case_name,    \
                                                           test_name));       \
  };                                                                          \
                                                                              \
  ::testing::TestInfo* const GTEST_TEST_CLASS_NAME_(test_case_name,           \
                                                    test_name)::test_info_ =  \
      ::testing::internal::MakeAndRegisterTestInfo(                           \
          #test_case_name, #test_name, NULL, NULL,                            \
          ::testing::internal::CodeLocation(__FILE__, __LINE__), (parent_id), \
          parent_class::SetUpTestCase, parent_class::TearDownTestCase,        \
          new ::testing::internal::TestFactoryImpl<GTEST_TEST_CLASS_NAME_(    \
              test_case_name, test_name)>);                                   \
  void GTEST_TEST_CLASS_NAME_(test_case_name, test_name)::SC_TestBody()

#define SCGTEST_F(test_fixture, test_name)             \
  SCGTEST_TEST_(test_fixture, test_name, test_fixture, \
                ::testing::internal::GetTypeId<test_fixture>())

#define SCGTEST(test_suite_name, test_name)                  \
  SCGTEST_TEST_(test_suite_name, test_name, ::testing::Test, \
                ::testing::internal::GetTestTypeId())
