#pragma once

#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;

class IGESBasic_ExternalReferenceFile : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_ExternalReferenceFile();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aNameArray);

  Standard_EXPORT int NbListEntries() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_ExternalReferenceFile, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theNames;
};
