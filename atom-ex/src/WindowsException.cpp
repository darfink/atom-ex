#include <atom-unicode/Unicode.hpp>
#include <atom-ex/WindowsException.hpp>

namespace atom {
  std::string WindowsException::GetErrorCodeString(unsigned int code) {
    if(!code) {
      return std::string();
    }

    void* messageBuffer = nullptr;

    size_t bufferSize = FormatMessageW(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
      FORMAT_MESSAGE_FROM_SYSTEM |
      FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      code,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      reinterpret_cast<wchar_t*>(&messageBuffer),
      0,
      NULL);

    if(bufferSize > 0) {
      wchar_t* message = reinterpret_cast<wchar_t*>(messageBuffer);
      std::wstring result(message, message + bufferSize);

      assert(LocalFree(messageBuffer) == NULL);
      return atom::ConvertUTF<char>(result);
    }

    return std::string();
  }
}
