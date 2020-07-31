#pragma once
/* uncomment the following line to work with Unison Profiler */
//#include <Unison.h>
#include <ctime>
#include <string>
#include <vector>

class PrintTime
{
 public:
  PrintTime(const std::string &message = "");
  ~PrintTime();
  void Start();
  void Stop(const std::string &message = "");
  void Snap(const std::string &message = "");

 private:
#ifdef UTL_UNISON_VERSION_MAJOR
  Profiler prof_;
#endif
  std::string msg_;
  timespec start_;
  mutable timespec last_;
  std::vector<timespec> startTimes_;
  void Print(const timespec &start, const std::string &msg = "") const;
};

