#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class Standard_Transient;
class Standard_NoSuchObject;
class TCollection_AsciiString;

class StepData_FileRecognizer : public Standard_Transient
{

public:
  //! Evaluates if recognition has a result, returns it if yes
  //! In case of success, Returns True and puts result in "res"
  //! In case of Failure, simply Returns False
  //! Works by calling deferred method Eval, and in case of failure,
  //! looks for Added Recognizers to work
  Standard_EXPORT bool Evaluate(const TCollection_AsciiString&   akey,
                                occ::handle<Standard_Transient>& res);

  //! Returns result of last recognition (call of Evaluate)
  Standard_EXPORT occ::handle<Standard_Transient> Result() const;

  //! Adds a new Recognizer to the Compound, at the end
  //! Several calls to Add work by adding in the order of calls :
  //! Hence, when Eval has failed to recognize, Evaluate will call
  //! Evaluate from the first added Recognizer if there is one,
  //! and to the second if there is still no result, and so on
  Standard_EXPORT void Add(const occ::handle<StepData_FileRecognizer>& reco);

  DEFINE_STANDARD_RTTI_INLINE(StepData_FileRecognizer, Standard_Transient)

protected:
  //! Assumes that no result has yet been recognized
  Standard_EXPORT StepData_FileRecognizer();

  //! Records the result of the recognition. Called by specific
  //! method Eval to record a result : after calling it, Eval has
  //! finished and can return
  Standard_EXPORT void SetOK(const occ::handle<Standard_Transient>& aresult);

  //! Records that recognition gives no result
  Standard_EXPORT void SetKO();

  //! THIS METHOD DEFINES THE RECOGNITION PROTOCOL, it is proper to
  //! each precise type of Recognizer
  //! For a suitable type of akey, it calls SetOK(result) where
  //! result is an empty result of appropriate type, then returns
  Standard_EXPORT virtual void Eval(const TCollection_AsciiString& akey) = 0;

private:
  occ::handle<Standard_Transient>      theres;
  bool                                 hasnext;
  occ::handle<StepData_FileRecognizer> thenext;
};

