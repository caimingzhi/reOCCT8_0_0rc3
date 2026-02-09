

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepData_ReadWriteModule.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepData_ReadWriteModule, Interface_ReaderModule)

int StepData_ReadWriteModule::CaseNum(const occ::handle<Interface_FileReaderData>& data,
                                      const int                                    num) const
{
  DeclareAndCast(StepData_StepReaderData, stepdat, data);
  if (stepdat.IsNull())
    return 0;
  if (stepdat->IsComplex(num))
  {
    NCollection_Sequence<TCollection_AsciiString> types;
    stepdat->ComplexType(num, types);
    if (types.IsEmpty())
      return 0;
    if (types.Length() == 1)
      return CaseStep(types.Value(1));
    else
      return CaseStep(types);
  }
  return CaseStep(stepdat->RecordType(num));
}

int StepData_ReadWriteModule::CaseStep(const NCollection_Sequence<TCollection_AsciiString>&) const
{
  return 0;
}

bool StepData_ReadWriteModule::IsComplex(const int) const
{
  return false;
}

TCollection_AsciiString StepData_ReadWriteModule::ShortType(const int) const
{
  return TCollection_AsciiString("");
}

bool StepData_ReadWriteModule::ComplexType(const int,
                                           NCollection_Sequence<TCollection_AsciiString>&) const
{
  return false;
}

void StepData_ReadWriteModule::Read(const int                                    CN,
                                    const occ::handle<Interface_FileReaderData>& data,
                                    const int                                    num,
                                    occ::handle<Interface_Check>&                ach,
                                    const occ::handle<Standard_Transient>&       ent) const
{
  DeclareAndCast(StepData_StepReaderData, stepdat, data);
  if (stepdat.IsNull())
    return;
  ReadStep(CN, stepdat, num, ach, ent);
}
