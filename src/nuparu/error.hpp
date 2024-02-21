#ifndef NUPARU_ERROR_HPP
#define NUPARU_ERROR_HPP

#include <optional>
#include <string>
#include <type_traits>
#include <vector>

#include <boost/current_function.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/stringize.hpp>

#define SIMPLETRACE(val)                                                       \
  (std::string(__FILE__) + " : " + std::string(BOOST_CURRENT_FUNCTION) +       \
   " : " + std::to_string(__LINE__))

#define TRY(statement)                                                         \
  {                                                                            \
    auto _error = statement;                                                   \
    if (!_error.None())                                                        \
    {                                                                          \
      _error.PushTrace(SIMPLETRACE(0));                                        \
      return _error;                                                           \
    }                                                                          \
  }

#define STRICT_TRY(statement)                                                  \
  {                                                                            \
    auto _error = statement;                                                   \
    if (!_error.None())                                                        \
    {                                                                          \
      _error.PushTrace(SIMPLETRACE(0));                                        \
      std::cerr << _error.DebugString();                                       \
    }                                                                          \
  }

#define ERRORVAR(val) _erroror_##__LINE__

#define TRY_ASSIGN(lhs, statement)                                             \
  auto ERRORVAR(0) = statement;                                                \
  if (!ERRORVAR(0).Err().None())                                               \
  {                                                                            \
    ERRORVAR(0).MutableErr().PushTrace(SIMPLETRACE(0));                        \
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

  ErrorCode Code() const { return m_error_code; }
  bool None() const { return m_error_code == ErrorCode::NONE; }

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

template <typename T,
          std::enable_if_t<std::conjunction_v<                  //
                               std::is_default_constructible<T> //
                               >                                //
                           ,
                           int> = 0 //
          >
class ErrorOr
{
public:
  ErrorOr(Error error) : m_error(error), m_value() {}
  template <typename U,
            std::enable_if_t<std::disjunction_v<              //
                                 std::is_constructible<T, U>, //
                                 std::is_convertible<U, T>,   //
                                 std::is_same<T, U>           //
                                 >                            //
                             ,
                             int> = 0 //
            >
  ErrorOr(const U &value) : m_error(ErrorCode::NONE), m_value(value)
  {
  }
  template <typename U,
            std::enable_if_t<std::disjunction_v<              //
                                 std::is_constructible<T, U>, //
                                 std::is_convertible<U, T>,   //
                                 std::is_same<T, U>           //
                                 >                            //
                             ,
                             int> = 0 //
            >
  ErrorOr(U &&value) : m_error(ErrorCode::NONE), m_value(value)
  {
  }

  Error &MutableErr() { return m_error; }
  const Error &Err() { return m_error; }
  T Value() const { return m_value; }

private:
  Error m_error;
  T m_value;
};

std::string GetStringFromErrorCode(ErrorCode error_code);

} // namespace nuparu

#endif
