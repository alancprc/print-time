#include "profileTT.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

ProfileTT PTT;  //create global PTT ProfileTT object

const int InitSnapSize = 512;

enum TIMING_PRINT_TYPE {
  TIMING_PRINT_NONE,  // supported print types
  TIMING_PRINT_SHORT,
  TIMING_PRINT_DETAILED,
  TIMING_PRINT_DELTA,
  TIMING_PRINT_IMMEDIATE,
};

const int STR_FS = 35;  // field width of Print_TEST_time text
// data arrays
static vector<double> snapTime;
static vector<int> isDetailed;
static vector<string> snapMsg;
static char m_titleStr[STR_FS];

static UTL_TIME TimeP;  // measure time with unison UTL_TIME class
static int timingPrintMode;
static int snapCount;  // measure counter

static double execTimeLast = 0;
static double firstSnapTime;
static double lastSnapTime;
static double indexTime;

ProfileTT::ProfileTT()
{
  lastSnapTime = 0.0;
  firstSnapTime = 0.0;

  snapTime.reserve(InitSnapSize);
  isDetailed.reserve(InitSnapSize);
  snapMsg.reserve(InitSnapSize);
}

void ProfileTT::OnStartProfileTTime(UnsignedS profilePrintMode, const char *titleStr)
{
  //cout<<"profilePrintMode  " << profilePrintMode<<endl;

  if ((profilePrintMode < TIMING_PRINT_NONE) || (profilePrintMode > TIMING_PRINT_IMMEDIATE)) {
    cout << endl
         << "### profilePrintMode  " << profilePrintMode
         << " is not valid from " << __func__ << " ###" << endl;
    cout << " supported modes:  " << endl;
    cout << "  TIMING_PRINT_NONE      " << TIMING_PRINT_NONE << endl;
    cout << "  TIMING_PRINT_SHORT     " << TIMING_PRINT_SHORT << endl;
    cout << "  TIMING_PRINT_DETAILED   " << TIMING_PRINT_DETAILED << endl;
    cout << "  TIMING_PRINT_DELTA     " << TIMING_PRINT_DELTA << endl;
    cout << "  TIMING_PRINT_IMMEDIATE " << TIMING_PRINT_IMMEDIATE << endl;

    profilePrintMode = 0;
  }

  firstSnapTime = TimeP.GetTimer() * 1000.;
  if (lastSnapTime == 0.) {
    indexTime = 0.;
  }
  else {
    indexTime = firstSnapTime - lastSnapTime;
  }

  timingPrintMode = profilePrintMode;
  TimeP.StartTimer();
  strncpy(m_titleStr, titleStr, STR_FS - 1);

  snapCount = 0;
  snapTime.push_back(0);
  isDetailed.push_back(1);
  snapMsg.push_back("");

  if (timingPrintMode == TIMING_PRINT_IMMEDIATE) {
    printf("*******************************************************************************\n");
    printf("%-*s %10s\n", STR_FS - 1, m_titleStr, "current");
    printf("*******************************************************************************\n");
  }
}

double ProfileTT::OnStopProfileTTime()
{
  double timing_ex_time_total = 0.;
  lastSnapTime = TimeP.GetTimer() * 1000.;

  if ((timingPrintMode == TIMING_PRINT_NONE) || (snapCount == 0)) {
    // measure entire program test time
    timing_ex_time_total = TimeP.GetTimer() * 1000.;
  }
  else {
    timing_ex_time_total = snapTime[snapCount];

    PrintHeader();
    PrintTestTimes();
    PrintTotalTime(timing_ex_time_total);
  }

  snapTime.clear();
  isDetailed.clear();
  snapMsg.clear();

  return (timing_ex_time_total);
}

double ProfileTT::GetIndexTime() { return (indexTime); }

void ProfileTT::SnapProfileTTime(const char *message)
{
  double elapsedTime;

  if (timingPrintMode != TIMING_PRINT_NONE) {
    snapCount++;

    snapTime.push_back(TimeP.GetTimer() * 1000.);
    isDetailed.push_back(1);

    char tmp[STR_FS] = "\0";
    strncpy(tmp, message, STR_FS - 1 - 5);
    snapMsg.push_back(tmp);

    if (timingPrintMode == TIMING_PRINT_IMMEDIATE) {
      elapsedTime = snapTime[snapCount] - snapTime[snapCount - 1];
      printf("%-*s %11.3f\n", STR_FS - 1, message, elapsedTime);
    }
  }
}

void ProfileTT::SnapProfileTTimeDetail(const char *message)
{
  if (timingPrintMode == TIMING_PRINT_DETAILED) {
    SnapProfileTTime(message);
    isDetailed[snapCount] = 0;
  }
}
void ProfileTT::GetProfileTTimes(FloatS1D &profileTime, StringS1D &profileTimeStr)
{
  double elapsedTime = 0.;
  double totalDetailTime = 0.;

  if (timingPrintMode != TIMING_PRINT_NONE) {
    profileTime.Resize(snapCount, SV_CONTENT_LOSE);
    profileTimeStr.Resize(snapCount, SV_CONTENT_LOSE);

    for (int i = 1; i < snapCount + 1; i++) {
      elapsedTime = snapTime[i] - snapTime[i - 1];
      totalDetailTime = totalDetailTime + elapsedTime;

      profileTimeStr[i - 1] = snapMsg[i].c_str();

      if (timingPrintMode == TIMING_PRINT_SHORT) {
        profileTime[i - 1] = elapsedTime;
      }
      else {
        if (isDetailed[i] == 1) {
          profileTime[i - 1] = totalDetailTime;
          totalDetailTime = 0.;
        }
        else {
          profileTime[i - 1] = elapsedTime;
        }
      }
    }
  }
  else {
    profileTime.Resize(1, SV_CONTENT_LOSE);
    profileTimeStr.Resize(1, SV_CONTENT_LOSE);
  }
}

void ProfileTT::PrintHeader()
{
  switch (timingPrintMode) {
    case TIMING_PRINT_SHORT:
      printf("*******************************************************************************\n");
      printf("%-*s %11s%11s%11s\n", STR_FS - 1, m_titleStr, "current", "current%", "snap");
      printf("*******************************************************************************\n");
      break;
    case TIMING_PRINT_DETAILED:
      printf("*******************************************************************************\n");
      printf("%-*s %11s%11s\n", STR_FS - 1, m_titleStr, "current", "detailed");
      printf("*******************************************************************************\n");
      break;
    case TIMING_PRINT_DELTA:
      printf("*******************************************************************************\n");
      //	    printf("%-34s %11s%11s%11s%11s\n",m_titleStr,"current","reference","cur-ref","cur/ref");
      printf("%-*s %11s%11s%11s%11s\n", STR_FS - 1, m_titleStr, "current",
             "reference", "cur-ref", "cur/ref");
      printf("*******************************************************************************\n");
      break;
    case TIMING_PRINT_IMMEDIATE:
      // header was printed at run time
      break;
    default:
      printf("MOO timingPrintMode");
      break;
  }
}

void ProfileTT::PrintTestTimes()
{
  double referenceTime = 0.;
  double referenceTimeRatio = 0.;
  double elapsedTime = 0.;
  double elapsedTimePercent = 0.;
  double totalDetailTime = 0.;

  if (timingPrintMode == TIMING_PRINT_IMMEDIATE) {
    // was printed at run time
  }
  else {
    for (int i = 1; i < snapCount + 1; i++) {
      elapsedTime = snapTime[i] - snapTime[i - 1];
      totalDetailTime = totalDetailTime + elapsedTime;

      printf("%4d %-*s", i, STR_FS - 5, snapMsg[i].c_str());

      switch (timingPrintMode) {
        case TIMING_PRINT_SHORT:
          elapsedTimePercent = 100. * elapsedTime / snapTime[snapCount];
          printf("%11.3f%11.3f%11.3f\n", elapsedTime, elapsedTimePercent, snapTime[i]);
          break;
        case TIMING_PRINT_DETAILED:
          if (isDetailed[i] == 1) {
            printf("%11.3f", totalDetailTime);
            totalDetailTime = 0.;
          }
          else {
            printf("%11s", "");
          }
          printf("%11.3f\n", elapsedTime);
          break;
        case TIMING_PRINT_DELTA:
          referenceTime = elapsedTime;
          if (referenceTime != 0) {
            referenceTimeRatio = elapsedTime / referenceTime;
          }
          else {
            referenceTimeRatio = 999.999;
          }
          printf("%11.3f%11.3f%11.3f%11.3f\n", elapsedTime, referenceTime,
                 elapsedTime - referenceTime, referenceTimeRatio);
          break;
        default:
          printf("MOO timingPrintMode");
          break;
      }
    }
  }
}

void ProfileTT::PrintTotalTime(double totalTestTime)
{
  double totalRefTestTime;

  printf("*******************************************************************************\n");
  //	printf("%-*s",STR_FS,"TotalExecutionTime_ms");
  char totalTitleStr[STR_FS] = "";
  strncpy(totalTitleStr, "TotalExecutionTime_ms", STR_FS - 1);
  printf("%-*s", STR_FS, totalTitleStr);

  switch (timingPrintMode) {
    case TIMING_PRINT_SHORT:
      printf("%11.3f%11.3f%11.3f\n", totalTestTime, 100., totalTestTime);
      break;
    case TIMING_PRINT_DETAILED:
      printf("%11.3f%11.3f\n", totalTestTime, totalTestTime);
      break;
    case TIMING_PRINT_DELTA:
      totalRefTestTime = totalTestTime;
      printf("%11.3f%11.3f%11.3f%11.3f\n", totalTestTime, totalRefTestTime,
             totalTestTime - totalRefTestTime, totalTestTime / totalRefTestTime);
      break;
    case TIMING_PRINT_IMMEDIATE:
      printf("%11.3f\n", totalTestTime);
      break;
    default:
      printf("MOO timingPrintMode");
      break;
  }

  printf("*******************************************************************************\n");
}

void ProfileTT::PrintExecTime()
{
  // prints execution time since last PrintExecTime or PrintlnExecTime
  // without new line

  double elapsedTime = TimeP.GetTimer() - execTimeLast;
  cout << setw(10) << elapsedTime * 1000.;
  //  printf("%10.3f", elapsedTime *1000.);

  execTimeLast = TimeP.GetTimer();
}

void ProfileTT::PrintlnExecTime()
{
  // prints execution time since last PrintExecTime or PrintlnExecTime
  // with new line

  double elapsedTime = TimeP.GetTimer() - execTimeLast;
  cout << setw(10) << elapsedTime * 1000. << endl;
  //    printf("%10.3f\n", elapsedTime*1000.);

  execTimeLast = TimeP.GetTimer();
}

double ProfileTT::GetElapsedTime()
{
  static double elapsedTimeS = 0.;
  static double execTimeLastS = 0.;

  elapsedTimeS = (TimeP.GetTimer() - execTimeLastS) * 1000.;
  execTimeLastS = TimeP.GetTimer();

  return (elapsedTimeS);
}
