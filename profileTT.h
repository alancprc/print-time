#pragma once

#include <Unison.h>

// usage:
//  ProfileTT::PrintExecTime();
//  ProfileTT::PrintExecTime();
//  ProfileTT::PrintlnExecTime();
//
//

// class definition
class ProfileTT
{
 public:
  ProfileTT();   // default constructor
  ~ProfileTT();  // default destructor

  static void OnStartProfileTTime(UnsignedS profilePrintMode, const char *titleStr);  // starts profiler
  static void SnapProfileTTime(const char *message);
  static void SnapProfileTTimeDetail(const char *message);
  static double OnStopProfileTTime();
  static void GetProfileTTimes(FloatS1D &profileTime, StringS1D &profileTimeStr);  // returns profile times

  static void PrintExecTime();  // prints execution time since last printExecTime or printlnExecTime
  static void PrintlnExecTime();  // prints execution time since last printExecTime or printlnExecTime

  static double GetElapsedTime();
  static double GetIndexTime();

 protected:
 private:
  static void PrintHeader();
  static void PrintTestTimes();
  static void PrintTotalTime(double);

};  // end class ProfileTT

extern ProfileTT PTT;  //create global PTT
