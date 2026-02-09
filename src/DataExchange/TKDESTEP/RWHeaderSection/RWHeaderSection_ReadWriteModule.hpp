#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_ReadWriteModule.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>

#include <string_view>

class TCollection_AsciiString;
class StepData_StepReaderData;
class Interface_Check;
class Standard_Transient;
class StepData_StepWriter;

class RWHeaderSection_ReadWriteModule : public StepData_ReadWriteModule
{

public:
  Standard_EXPORT RWHeaderSection_ReadWriteModule();

  Standard_EXPORT int CaseStep(const TCollection_AsciiString& atype) const override;

  Standard_EXPORT int CaseStep(
    const NCollection_Sequence<TCollection_AsciiString>& types) const override;

  Standard_EXPORT bool IsComplex(const int CN) const override;

  Standard_EXPORT const std::string_view& StepType(const int CN) const override;

  Standard_EXPORT void ReadStep(const int                                   CN,
                                const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<Standard_Transient>&      ent) const override;

  Standard_EXPORT void WriteStep(const int                              CN,
                                 StepData_StepWriter&                   SW,
                                 const occ::handle<Standard_Transient>& ent) const override;

  DEFINE_STANDARD_RTTIEXT(RWHeaderSection_ReadWriteModule, StepData_ReadWriteModule)
};
