#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Real.hpp>
class TCollection_HAsciiString;
class Standard_Transient;

class IGESDefs_GenericData : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDefs_GenericData();

  Standard_EXPORT void Init(
    const int                                                                nbPropVal,
    const occ::handle<TCollection_HAsciiString>&                             aName,
    const occ::handle<NCollection_HArray1<int>>&                             allTypes,
    const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& allValues);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT int NbTypeValuePairs() const;

  Standard_EXPORT int Type(const int Index) const;

  Standard_EXPORT occ::handle<Standard_Transient> Value(const int Index) const;

  Standard_EXPORT int ValueAsInteger(const int ValueNum) const;

  Standard_EXPORT double ValueAsReal(const int ValueNum) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ValueAsString(const int ValueNum) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> ValueAsEntity(const int ValueNum) const;

  Standard_EXPORT bool ValueAsLogical(const int ValueNum) const;

  DEFINE_STANDARD_RTTIEXT(IGESDefs_GenericData, IGESData_IGESEntity)

private:
  int                                                               theNbPropertyValues;
  occ::handle<TCollection_HAsciiString>                             theName;
  occ::handle<NCollection_HArray1<int>>                             theTypes;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> theValues;
};
