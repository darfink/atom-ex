#pragma once

#include <atom-ex/Exception.hpp>
#include <cassert>
#include <cerrno>

/// <summary>
/// Asserts a System API call and throws upon failure
/// </summary>
#define ATOM_SYSTEM_ASSERT(COND)                          \
  do {                                                    \
    if(!(COND)) {                                         \
      throw atom::SystemException(ATOM_EXCEPTION_INFO);   \
    }                                                     \
  } while(false)

namespace atom {
  /// <summary>
  /// Describes a system (errno) exception
  /// </summary>
  class SystemException : public Exception {
  public:
    SystemException(Information info, int code = errno) :
      Exception(info, GetErrorCodeString(code), code) { }

    SystemException(
      Information info,
      const Exception& nested,
      int code = errno) :
      Exception(info, GetErrorCodeString(code), nested, code) {
    }

    virtual const char* Name() const {
      return "SystemException";
    }

    virtual SystemException* Clone() const {
      return new SystemException(*this);
    }

    static std::string GetErrorCodeString(int code);
  };
}
