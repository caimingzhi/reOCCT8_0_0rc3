#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESGraph_NominalSize : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_NominalSize();

  Standard_EXPORT void Init(const int                                    nbProps,
                            const double                                 aNominalSizeValue,
                            const occ::handle<TCollection_HAsciiString>& aNominalSizeName,
                            const occ::handle<TCollection_HAsciiString>& aStandardName);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT double NominalSizeValue() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> NominalSizeName() const;

  Standard_EXPORT bool HasStandardName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> StandardName() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_NominalSize, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  double                                theNominalSizeValue;
  occ::handle<TCollection_HAsciiString> theNominalSizeName;
  occ::handle<TCollection_HAsciiString> theStandardName;
};
