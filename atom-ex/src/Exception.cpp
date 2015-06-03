#include <atom-unicode/Unicode.hpp>
#include <atom-ex/Exception.hpp>
#include <sstream>
#include <iomanip>

namespace atom {
  Exception::Exception(Information info, std::string message, int code) :
      mNested(nullptr),
      mMessage(message),
      mInfo(info),
      mCode(code) {
  }

  Exception::Exception(
      Information info,
      std::string message,
      const Exception& nested,
      int code) :
      Exception(info, message, code) {
    mNested.reset(nested.Clone());
  }

  Exception::~Exception() {
  }

  const char* Exception::Name() const {
    return "Exception";
  }

  Exception* Exception::Clone() const {
    return new Exception(*this);
  }

  const char* Exception::what() const throw() {
    return mMessage.c_str();
  }

  std::string Exception::DisplayText() const {
    std::stringstream stream;

    if(!mMessage.empty()) {
      stream << this->Name(); 

      if(mCode != 0) {
        stream << std::hex << std::setfill('0');
        stream << "(0x" << std::uppercase << std::setw(2) << mCode << ")";
        stream.unsetf(std::ios::hex);
      }

      stream << ": " << mMessage;
    }

#ifdef _DEBUG
    stream << std::endl << "  at " << mInfo.file << "(" << mInfo.line << "): " << mInfo.function;
#endif

    if(mNested != nullptr) {
      stream << std::endl << mNested->DisplayText();
    }

    return stream.str();
  }

  std::wostream& operator<<(std::wostream& stream, const Exception& exception) {
    return (stream << atom::ConvertUTF<wchar_t>(exception.DisplayText()));
  }

  std::ostream& operator<<(std::ostream& stream, const Exception& exception) {
    return (stream << exception.DisplayText());
  }
}
