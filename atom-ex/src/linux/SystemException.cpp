#include <atom-ex/SystemException.hpp>
#include <cstring>

namespace atom {
  std::string SystemException::GetErrorCodeString(int code) {
    return strerror(code);
  }
}
