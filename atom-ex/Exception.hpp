#pragma once

#include <memory>
#include <string>

#define ATOM_EXCEPTION_INFO \
  { __FILE__, __LINE__, __FUNCTION__ }

// A shorthand define to create class specific exceptions
#define ATOM_DEFINE_EXCEPTION(name) \
  ATOM_DEFINE_EXCEPTION_INHERIT(name, atom::Exception)

// A shorthand define to create a class specific exception
#define ATOM_DEFINE_EXCEPTION_INHERIT(CLASS, BASE)               \
  class CLASS : public BASE {                                    \
  public:                                                        \
    CLASS(Information info, std::string message, int code = 0) : \
      BASE(info, message, code) { }                              \
    CLASS(                                                       \
      Information info,                                          \
      std::string message,                                       \
      const Exception& nested,                                   \
      int code = 0) : BASE(info, message, nested, code) { }      \
    virtual const char* Name() const { return #CLASS; }          \
    virtual CLASS* Clone() const { return new CLASS(*this); }    \
  }

namespace atom {
  class Exception : public std::exception {
  public:
    /// <summary>
    /// Describes an exception information object
    /// </summary>
    struct Information {
      const char* file;
      unsigned int line;
      const char* function;
    };

    /// <summary>
    /// Constructs a new exception object
    /// </summary>
    Exception(Information info, std::string message, int code = 0);

    /// <summary>
    /// Constructs a new exception object with a nested exception
    /// </summary>
    Exception(
      Information info,
      std::string message,
      const Exception& nested,
      int code = 0);

    /// <summary>
    /// Destructor for the exception object
    /// </summary>
    virtual ~Exception();

    /// <summary>
    /// Returns the code
    /// </summary>
    int Code() const;

    /// <summary>
    /// Returns the message text
    /// </summary>
    const std::string& Message() const;

    /// <summary>
    /// Returns a string consisting of the message name and text
    /// </summary>
    std::string DisplayText() const;

    /// <summary>
    /// Returns the nested exception (or null)
    /// </summary>
    const std::shared_ptr<Exception> Nested() const;

    /// <summary>
    /// Returns the name of the exception
    /// </summary>
    virtual const char* Name() const;

    /// <summary>
    /// Clones the current exception
    /// </summary>
    virtual Exception* Clone() const;

    /// <summary>
    /// Returns a static string describing the exception
    /// </summary>
    virtual const char* what() const throw();

  protected:
    // Protected members
    std::string mMessage;

  private:
    // Private members
    std::shared_ptr<Exception> mNested;
    Information mInfo;
    int mCode;
  };

  /// <summary>
  /// Print out the exceptions display text when outputting to any stream
  /// </summary>
  std::wostream& operator<<(std::wostream& stream, const Exception& exception);

  /// <summary>
  /// Print out the exceptions display text when outputting to any stream
  /// </summary>
  std::ostream& operator<<(std::ostream& stream, const Exception& exception);

  inline int Exception::Code() const {
    return mCode;
  }

  inline const std::string& Exception::Message() const {
    return mMessage;
  }

  inline const std::shared_ptr<Exception> Exception::Nested() const {
    return mNested;
  }
}
