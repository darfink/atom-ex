#pragma once

#include <atom-ex/Exception.hpp>
#include <windows.h>
#include <cassert>

/// <summary>
/// Asserts a Windows API call and throws upon failure
/// </summary>
#define ATOM_WINSERT(COND)                                \
  do {                                                    \
    if(!(COND)) {                                         \
      throw atom::WindowsException(ATOM_EXCEPTION_INFO);  \
    }                                                     \
  } while(false)

namespace atom {
  /// <summary>
  /// Describes a windows (Win32) API exception
  /// </summary>
  class WindowsException : public Exception {
  public:
    WindowsException(Information info, int code = GetLastError()) :
      Exception(info, GetErrorCodeString(code), code) { }

    WindowsException(
      Information info,
      const Exception& nested,
      int code = GetLastError()) :
      Exception(info, GetErrorCodeString(code), nested, code) {
    }

    virtual const char* Name() const {
      return "WindowsException";
    }

    virtual WindowsException* Clone() const {
      return new WindowsException(*this);
    }

    static std::string GetErrorCodeString(unsigned int code);
  };
}
