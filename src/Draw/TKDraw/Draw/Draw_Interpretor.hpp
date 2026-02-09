#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Macro.hpp>
#include <Standard_Boolean.hpp>

struct Tcl_Interp;

typedef Tcl_Interp* Draw_PInterp;

#include <Standard_SStream.hpp>
#include <Standard_Real.hpp>

class TCollection_AsciiString;
class TCollection_ExtendedString;

class Draw_Interpretor
{

public:
  typedef int (*CommandFunction)(Draw_Interpretor& theDI, int theArgNb, const char** theArgVec);

  struct CallBackData
  {

    CallBackData(Draw_Interpretor* theDI)
        : myDI(theDI)
    {
    }

    virtual ~CallBackData() = default;

    virtual int Invoke(Draw_Interpretor& theDI, int theArgNb, const char** theArgVec) = 0;

    Draw_Interpretor* myDI;

    DEFINE_STANDARD_ALLOC
  };

protected:
  struct CallBackDataFunc : public CallBackData
  {

    CallBackDataFunc(Draw_Interpretor* theDI, CommandFunction theFunc)
        : CallBackData(theDI),
          myFunc(theFunc)
    {
    }

    int Invoke(Draw_Interpretor& theDI, int theArgNb, const char** theArgVec) override
    {
      return myFunc != nullptr ? myFunc(theDI, theArgNb, theArgVec) : 1;
    }

    Draw_Interpretor::CommandFunction myFunc;
  };

  template <typename theObjHandle>
  struct CallBackDataMethod : public CallBackData
  {
    typedef typename theObjHandle::element_type element_type;
    typedef int (element_type::*methodType)(Draw_Interpretor&, int, const char**);

    CallBackDataMethod(Draw_Interpretor* theDI, const theObjHandle& theObjPtr, methodType theMethod)
        : CallBackData(theDI),
          myObjPtr(theObjPtr),
          myMethod(theMethod)
    {
    }

    int Invoke(Draw_Interpretor& theDI, int theArgNb, const char** theArgVec) override
    {
      return myMethod != nullptr && !myObjPtr.IsNull()
               ? (myObjPtr.operator->()->*myMethod)(theDI, theArgNb, theArgVec)
               : 1;
    }

    theObjHandle myObjPtr;
    methodType   myMethod;
  };

public:
  Standard_EXPORT Draw_Interpretor();

  Standard_EXPORT void Init();

  inline void Add(const char*     theCommandName,
                  const char*     theHelp,
                  CommandFunction theFunction,
                  const char*     theGroup = "User Commands")
  {
    Add(theCommandName, theHelp, "", theFunction, theGroup);
  }

  inline void Add(const char*     theCommandName,
                  const char*     theHelp,
                  const char*     theFileName,
                  CommandFunction theFunction,
                  const char*     theGroup = "User Commands")
  {
    CallBackDataFunc* aCallback = new CallBackDataFunc(this, theFunction);
    add(theCommandName, theHelp, theFileName, aCallback, theGroup);
  }

  template <typename theHandleType>
  inline void Add(
    const char*                                                              theCommandName,
    const char*                                                              theHelp,
    const char*                                                              theFileName,
    const theHandleType&                                                     theObjPtr,
    typename Draw_Interpretor::CallBackDataMethod<theHandleType>::methodType theMethod,
    const char*                                                              theGroup)
  {
    Draw_Interpretor::CallBackDataMethod<theHandleType>* aCallback =
      new Draw_Interpretor::CallBackDataMethod<theHandleType>(this, theObjPtr, theMethod);
    add(theCommandName, theHelp, theFileName, aCallback, theGroup);
  }

  Standard_EXPORT bool Remove(const char* theCommandName);

public:
  Standard_EXPORT const char* Result() const;

  Standard_EXPORT void Reset();

  Standard_EXPORT Draw_Interpretor& Append(const char* theResult);

  inline Draw_Interpretor& operator<<(const char* theResult) { return Append(theResult); }

  Standard_EXPORT Draw_Interpretor& Append(const TCollection_AsciiString& theResult);

  inline Draw_Interpretor& operator<<(const TCollection_AsciiString& theResult)
  {
    return Append(theResult);
  }

  Standard_EXPORT Draw_Interpretor& Append(const TCollection_ExtendedString& theResult);

  inline Draw_Interpretor& operator<<(const TCollection_ExtendedString& theResult)
  {
    return Append(theResult);
  }

  Standard_EXPORT Draw_Interpretor& Append(const int theResult);

  inline Draw_Interpretor& operator<<(const int theResult) { return Append(theResult); }

  Standard_EXPORT Draw_Interpretor& Append(const double theResult);

  inline Draw_Interpretor& operator<<(const double theResult) { return Append(theResult); }

  Standard_EXPORT Draw_Interpretor& Append(const Standard_SStream& theResult);

  inline Draw_Interpretor& operator<<(const Standard_SStream& theResult)
  {
    return Append(theResult);
  }

  Standard_EXPORT void AppendElement(const char* theResult);

  Standard_EXPORT int Eval(const char* theScript);

  Standard_EXPORT int RecordAndEval(const char* theScript, const int theFlags = 0);

  Standard_EXPORT int EvalFile(const char* theFileName);

  Standard_EXPORT int PrintHelp(const char* theCommandName);

  Standard_EXPORT static bool Complete(const char* theScript);

public:
  Standard_EXPORT ~Draw_Interpretor();

  Standard_EXPORT Draw_Interpretor(const Draw_PInterp& theInterp);

  Standard_EXPORT void Set(const Draw_PInterp& theInterp);

  Standard_EXPORT Draw_PInterp Interp() const;

  Standard_EXPORT void SetDoLog(const bool theDoLog);

  Standard_EXPORT void SetDoEcho(const bool theDoEcho);

  Standard_EXPORT bool GetDoLog() const;

  Standard_EXPORT bool GetDoEcho() const;

  Standard_EXPORT void ResetLog();

  Standard_EXPORT void AddLog(const char* theStr);

  Standard_EXPORT TCollection_AsciiString GetLog();

  int GetLogFileDescriptor() { return myFDLog; }

  bool ToColorize() const { return myToColorize; }

  Standard_EXPORT void SetToColorize(bool theToColorize);

protected:
  Standard_EXPORT void add(const char*   theCommandName,
                           const char*   theHelp,
                           const char*   theFileName,
                           CallBackData* theCallback,
                           const char*   theGroup);

private:
  Draw_PInterp myInterp;
  bool         isAllocated;
  bool         myDoLog;
  bool         myDoEcho;
  bool         myToColorize;
  int          myFDLog;

public:
  DEFINE_STANDARD_ALLOC
};
