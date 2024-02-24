#include "nuparu/error.hpp"

#include <algorithm>
#include <boost/algorithm/string/join.hpp>

#include <iterator>

namespace nuparu
{

void Error::Update(ErrorCode error_code, const std::string &message)
{
  // Credit to Valerie. Thanks bestieeeeeee!!!!!!!
  std::string valerie = GetStringFromErrorCode(m_error_code) + " " + m_message;
  m_stack_trace.push_back(valerie);
  m_error_code = error_code;
  m_message = message;
}

void Error::PushTrace(const std::string &trace)
{
  m_stack_trace.push_back(trace);
}

std::string Error::DebugString() const
{
  std::string current_error =
      GetStringFromErrorCode(m_error_code) + " " + m_message;

  std::string trace_str = "\n";
  for (auto trace_line_it = m_stack_trace.rbegin();
       trace_line_it != m_stack_trace.rend(); trace_line_it++)
  {
    trace_str += *trace_line_it + "\n";
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
