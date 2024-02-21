#include "nuparu/error.hpp"

#include <algorithm>
#include <boost/algorithm/string/join.hpp>

namespace nuparu
{

void Error::Update(ErrorCode error_code, const std::string &message)
{
  // Credit to Valerie. Thanks bestieeeeeee!!!!!!!
  std::string valerie =
      GetStringFromErrorCode(this->error_code) + " " + this->message;
  this->stack_trace.push_back(valerie);
  this->error_code = error_code;
  this->message = message;
}

void Error::PushTrace(const std::string &trace)
{
  this->stack_trace.push_back(trace);
}

std::string Error::DebugString()
{
  std::string current_error =
      GetStringFromErrorCode(this->error_code) + " " + this->message;
  std::string trace_str = "\n";
  for (const auto &trace_line : this->stack_trace)
  {
    trace_str += trace_line + "\n";
  }
  return current_error + trace_str;
}

std::string GetStringFromErrorCode(ErrorCode error_code)
{
  switch (error_code)
  {
  case ErrorCode::NONE:
    return "NONE";
  case ErrorCode::INTERNAL:
    return "INTERNAL";
  case ErrorCode::INVALID_ARGUMENT:
    return "INVALID_ARGUMENT";
  }
}

} // namespace nuparu
