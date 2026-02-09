#pragma once

#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;

class IGESAppli_FlowLineSpec : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_FlowLineSpec();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& allProperties);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FlowLineName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Modifier(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_FlowLineSpec, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theNameAndModifiers;
};
