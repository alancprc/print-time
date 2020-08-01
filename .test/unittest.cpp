#include <gmock/gmock.h>
#include "../../print-time/print-time.h"
#include "../../print-time/profileTT.h"

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

TEST(UtilFuncTest, singleItemTest)
{
  PTT.OnStartProfileTTime(1, "on start");
  PTT.SnapProfileTTime("1");
  TIME.Wait(1e-3);
  PTT.OnStopProfileTTime();
}

TEST(UtilFuncTest, shortTest)
{
  PTT.OnStartProfileTTime(1, "on start");
  PTT.SnapProfileTTime("1");
  EXPECT_NO_THROW(PTT.SnapProfileTTime("2"));
  EXPECT_NO_THROW(PTT.SnapProfileTTime("3"));
  for (int i = 0; i != 10; ++i) {
    EXPECT_NO_THROW(PTT.SnapProfileTTimeDetail("loop"));
    TIME.Wait(1e-3);
  }
  EXPECT_NO_THROW(PTT.SnapProfileTTime("4"));
  PTT.OnStopProfileTTime();
}

TEST(UtilFuncTest, detailedTest)
{
  PTT.OnStartProfileTTime(2, "on start");
  PTT.SnapProfileTTime("1");
  EXPECT_NO_THROW(PTT.SnapProfileTTime("2"));
  EXPECT_NO_THROW(PTT.SnapProfileTTime("3"));
  for (int i = 0; i != 10; ++i) {
    EXPECT_NO_THROW(PTT.SnapProfileTTimeDetail("loop"));
    TIME.Wait(1e-3);
  }
  EXPECT_NO_THROW(PTT.SnapProfileTTime("4"));
  PTT.OnStopProfileTTime();
}
