#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Document;
class TCollection_HAsciiString;

class StepBasic_DocumentUsageConstraint : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_DocumentUsageConstraint();

  Standard_EXPORT void Init(const occ::handle<StepBasic_Document>&       aSource,
                            const occ::handle<TCollection_HAsciiString>& ase,
                            const occ::handle<TCollection_HAsciiString>& asev);

  Standard_EXPORT occ::handle<StepBasic_Document> Source() const;

  Standard_EXPORT void SetSource(const occ::handle<StepBasic_Document>& aSource);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> SubjectElement() const;

  Standard_EXPORT void SetSubjectElement(const occ::handle<TCollection_HAsciiString>& ase);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> SubjectElementValue() const;

  Standard_EXPORT void SetSubjectElementValue(const occ::handle<TCollection_HAsciiString>& asev);

  DEFINE_STANDARD_RTTIEXT(StepBasic_DocumentUsageConstraint, Standard_Transient)

private:
  occ::handle<StepBasic_Document>       theSource;
  occ::handle<TCollection_HAsciiString> theSE;
  occ::handle<TCollection_HAsciiString> theSEV;
};

