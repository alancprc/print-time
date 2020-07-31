#include "print-time.h"

#include <iomanip>
#include <iostream>

using namespace std;

PrintTime::PrintTime(const std::string &message)
    :
#ifdef UTL_UNISON_VERSION_MAJOR
      prof_(message.c_str()),
#endif
      msg_(message)
{
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_);
  last_ = start_;
}

PrintTime::~PrintTime() { Print(start_, msg_); }

void PrintTime::Start()
{
  timespec tmp;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tmp);
  startTimes_.push_back(tmp);
}

void PrintTime::Stop(const std::string &message)
{
  if (!startTimes_.empty()) {
    const timespec &start = startTimes_.back();
    Print(start, message);
    startTimes_.pop_back();
  } else {
    Print(start_, message);
  }
}

void PrintTime::Snap(const std::string &message)
{
  Print(last_, message);
}

void PrintTime::Print(const timespec &start, const std::string &msg) const
{
  timespec now;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);

  double elapsed_ms = (double)(now.tv_sec - start.tv_sec) * 1e3 +
                      (double)(now.tv_nsec - start.tv_nsec) * 1e-6;
  last_ = now;
  if (!msg.empty())
    std::cerr << setw(12) << elapsed_ms << "ms\t" << msg << std::endl;
}
