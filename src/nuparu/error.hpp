#ifndef NUPARU_ERROR_HPP
#define NUPARU_ERROR_HPP

#include <string>
#include <vector>

namespace nuparu
{

// Error codes.
enum ErrorCode
{
  // No error.
  NONE,
  // Internal error.
  INTERNAL,
  // Invalid argument error.
  INVALID_ARGUMENT,
};

// Captures error information in a lightweight struct as an alternative to
// throwing exceptions. Includes some loose tracking of the stack trace.
struct Error
{
  Error(ErrorCode error_code, const std::string &message)
      : error_code(error_code), message(message){};

  // Updates the top-level values of members, but pushes old values into the
  // stack trace.
  void Update(ErrorCode error_code, const std::string &message);
  void PushTrace(const std::string &trace);
  // Debug string.
  std::string DebugString();

  ErrorCode error_code;
  std::string message;
  // Historical stack trace. Contains manually added lines or previous Error
  // states prior to most recent update.
  std::vector<std::string> stack_trace;
};

std::string GetStringFromErrorCode(ErrorCode error_code);

} // namespace nuparu

#endif
