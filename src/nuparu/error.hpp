#ifndef NUPARU_ERROR_HPP
#define NUPARU_ERROR_HPP

#include <optional>
#include <string>
#include <vector>

#define TRY(statement)                                                         \
  {                                                                            \
    auto _error = statement;                                                   \
    if (!_error.None())                                                        \
    {                                                                          \
      _error.PushTrace("__FILE__ __func__ __LINE__");                          \
      return _error;                                                           \
    }                                                                          \
  }

#define ERRORVAR(val) _erroror_##__func__##__LINE__

#define TRY_ASSIGN(lhs, statement)                                             \
  auto ERRORVAR(0) = statement;                                                \
  if (!ERRORVAR(0).MutableError().None())                                      \
  {                                                                            \
    ERRORVAR(0).MutableError().PushTrace("__FILE__ __func__ __LINE__");        \
    return ERRORVAR(0);                                                        \
  }                                                                            \
  lhs = std::move(ERRORVAR(0)).Value();

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
class Error
{
public:
  Error(ErrorCode error_code, const std::string &message = "")
      : m_error_code(error_code), m_message(message)
  {
  }

  ErrorCode Code() { return m_error_code; }
  bool None() { return m_error_code == ErrorCode::NONE; }

  // Updates the top-level values of members, but pushes old values into the
  // stack trace.
  void Update(ErrorCode error_code, const std::string &message);

  // Push a stack trace into the error. Useful for more refined logging.
  void PushTrace(const std::string &trace);

  // Debug string.
  std::string DebugString();

private:
  ErrorCode m_error_code;
  std::string m_message;
  // Historical stack trace. Contains manually added lines or previous Error
  // states prior to most recent update.
  std::vector<std::string> m_stack_trace;
};

template <typename T> class ErrorOr
{
public:
  ErrorOr(Error error) : m_error(error), m_value(std::nullopt) {}
  ErrorOr(const T &value) : m_error(ErrorCode::NONE), m_value() {}

  Error &MutableError() { return m_error; }
  T Value() const { return m_value; }

private:
  Error m_error;
  T m_value;
};

std::string GetStringFromErrorCode(ErrorCode error_code);

} // namespace nuparu

#endif
