#pragma once

#include <atom-ex/SystemException.hpp>
#include <atom-unicode/Unicode.hpp>
#include <cstring>

namespace atom {
  std::string SystemException::GetErrorCodeString(int code) {
    std::wstring error(_wcserror(code));
    return atom::ConvertUTF<char>(error);
  }
}
