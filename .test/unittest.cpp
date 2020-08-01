#include <gmock/gmock.h>
#include "../../print-time/print-time.h"

#include <Unison.h>

using namespace std;

#if __cplusplus > 201100
template <typename T, typename = typename std::enable_if<std::is_base_of<BasicVar, T>::value>::type>
std::ostream& operator<<(std::ostream& os, const T& obj)
{
  return os << std::string(obj.GetText());
}
#endif

TMResultM StartGTest()
{
  int argc = 1;
  const char* argv[] = {"a.out"};

  std::cout << "\n\n\nRunning main() from unittest.cpp\n";
  testing::InitGoogleMock(&argc, const_cast<char**>(argv));
  int result = RUN_ALL_TESTS();
  return result == 0 ? TM_PASS : TM_FAIL;
}

TEST(PrintTimeTest, startstopTest)
{
  PrintTime pt(__PRETTY_FUNCTION__);
  TIME.Wait(10e-3);

  pt.Start();
  TIME.Wait(1e-3);
  pt.Stop("wait 1ms");
}

TEST(PrintTimeTest, snapTest)
{
  PrintTime pt(__PRETTY_FUNCTION__);
  TIME.Wait(10e-3);
  pt.Start();
  pt.Snap("before wait 1ms");
  TIME.Wait(1e-3);
  pt.Snap("after wait 1ms");
}
