#pragma once

#include <Unison.h>

// usage:
//  ProfileTT::PrintExecTime();
//  ProfileTT::PrintExecTime();
//  ProfileTT::PrintlnExecTime();

class ProfileTT
{
 public:
  ProfileTT();

  /**@brief starts profiler timer.
   * shall be called in on init flow. */
  static void OnStartProfileTTime(UnsignedS profilePrintMode, const char *titleStr);

  /**@brief print profile result.
   * shall be called in on power down flow. */
  static double OnStopProfileTTime();

  /**@brief snap timer for profile execution time. */
  static void SnapProfileTTime(const char *message);

  /**@brief snap timer for detailed profile execution time. */
  static void SnapProfileTTimeDetail(const char *message);

  /**@brief returns profile times. */
  static void GetProfileTTimes(FloatS1D &profileTime, StringS1D &profileTimeStr);

  /**@brief prints execution time since last printExecTime or printlnExecTime. */
  static void PrintExecTime();

  /**@brief prints execution time since last printExecTime or printlnExecTime. */
  static void PrintlnExecTime();

  /** @brief returns elapsed time in ms since last GetElapsedTime. */
  static double GetElapsedTime();

  /**@brief prints execution time since last printExecTime or printlnExecTime. */
  static double GetIndexTime();

 protected:
 private:
  /**@brief print test time profile header. */
  static void PrintHeader();

  /**@brief private print test time profile. */
  static void PrintTestTimes();

  /**@brief private print total test time profile. */
  static void PrintTotalTime(double);
};

enum TIMING_PRINT_TYPE {
  TIMING_PRINT_NONE = 0,      // supported print types
  TIMING_PRINT_SHORT = 1,     // print SnapProfileTTime only
  TIMING_PRINT_DETAILED = 2,  // print SnapProfileTTime and SnapProfileTTimeDetail
  TIMING_PRINT_DELTA = 3,     // print delta
  TIMING_PRINT_IMMEDIATE = 4,  // print duaring test
};

extern ProfileTT PTT;  //create global PTT
