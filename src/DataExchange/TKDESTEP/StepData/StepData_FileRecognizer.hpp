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
  Standard_EXPORT bool Evaluate(const TCollection_AsciiString&   akey,
                                occ::handle<Standard_Transient>& res);

  Standard_EXPORT occ::handle<Standard_Transient> Result() const;

  Standard_EXPORT void Add(const occ::handle<StepData_FileRecognizer>& reco);

  DEFINE_STANDARD_RTTI_INLINE(StepData_FileRecognizer, Standard_Transient)

protected:
  Standard_EXPORT StepData_FileRecognizer();

  Standard_EXPORT void SetOK(const occ::handle<Standard_Transient>& aresult);

  Standard_EXPORT void SetKO();

  Standard_EXPORT virtual void Eval(const TCollection_AsciiString& akey) = 0;

private:
  occ::handle<Standard_Transient>      theres;
  bool                                 hasnext;
  occ::handle<StepData_FileRecognizer> thenext;
};
