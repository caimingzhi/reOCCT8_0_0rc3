#pragma once

#include <Standard.hpp>

#include <Interface_ReaderModule.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>

#include <string_view>

class Interface_FileReaderData;
class TCollection_AsciiString;
class Interface_Check;
class Standard_Transient;
class StepData_StepReaderData;
class StepData_StepWriter;

class StepData_ReadWriteModule : public Interface_ReaderModule
{

public:
  Standard_EXPORT int CaseNum(const occ::handle<Interface_FileReaderData>& data,
                              const int                                    num) const override;

  Standard_EXPORT virtual int CaseStep(const TCollection_AsciiString& atype) const = 0;

  Standard_EXPORT virtual int CaseStep(
    const NCollection_Sequence<TCollection_AsciiString>& types) const;

  Standard_EXPORT virtual bool IsComplex(const int CN) const;

  Standard_EXPORT virtual const std::string_view& StepType(const int CN) const = 0;

  Standard_EXPORT virtual TCollection_AsciiString ShortType(const int CN) const;

  Standard_EXPORT virtual bool ComplexType(
    const int                                      CN,
    NCollection_Sequence<TCollection_AsciiString>& types) const;

  Standard_EXPORT void Read(const int                                    CN,
                            const occ::handle<Interface_FileReaderData>& data,
                            const int                                    num,
                            occ::handle<Interface_Check>&                ach,
                            const occ::handle<Standard_Transient>&       ent) const override;

  Standard_EXPORT virtual void ReadStep(const int                                   CN,
                                        const occ::handle<StepData_StepReaderData>& data,
                                        const int                                   num,
                                        occ::handle<Interface_Check>&               ach,
                                        const occ::handle<Standard_Transient>&      ent) const = 0;

  Standard_EXPORT virtual void WriteStep(const int                              CN,
                                         StepData_StepWriter&                   SW,
                                         const occ::handle<Standard_Transient>& ent) const = 0;

  DEFINE_STANDARD_RTTIEXT(StepData_ReadWriteModule, Interface_ReaderModule)
};
