#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <Interface_Protocol.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
class Interface_InterfaceModel;
class StepData_EDescr;
class StepData_ESDescr;
class StepData_ECDescr;
class StepData_PDescr;

class StepData_Protocol : public Interface_Protocol
{

public:
  Standard_EXPORT StepData_Protocol();

  Standard_EXPORT int NbResources() const override;

  Standard_EXPORT occ::handle<Interface_Protocol> Resource(const int num) const override;

  Standard_EXPORT int CaseNumber(const occ::handle<Standard_Transient>& obj) const override;

  Standard_EXPORT int TypeNumber(const occ::handle<Standard_Type>& atype) const override;

  Standard_EXPORT virtual const char* SchemaName(
    const occ::handle<Interface_InterfaceModel>& theModel) const;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> NewModel() const override;

  Standard_EXPORT bool IsSuitableModel(
    const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT occ::handle<Standard_Transient> UnknownEntity() const override;

  Standard_EXPORT bool IsUnknownEntity(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT virtual int DescrNumber(const occ::handle<StepData_EDescr>& adescr) const;

  Standard_EXPORT void AddDescr(const occ::handle<StepData_EDescr>& adescr, const int CN);

  Standard_EXPORT bool HasDescr() const;

  Standard_EXPORT occ::handle<StepData_EDescr> Descr(const int num) const;

  Standard_EXPORT occ::handle<StepData_EDescr> Descr(const char* name,
                                                     const bool  anylevel = true) const;

  Standard_EXPORT occ::handle<StepData_ESDescr> ESDescr(const char* name,
                                                        const bool  anylevel = true) const;

  Standard_EXPORT occ::handle<StepData_ECDescr> ECDescr(
    const NCollection_Sequence<TCollection_AsciiString>& names,
    const bool                                           anylevel = true) const;

  Standard_EXPORT void AddPDescr(const occ::handle<StepData_PDescr>& pdescr);

  Standard_EXPORT occ::handle<StepData_PDescr> PDescr(const char* name,
                                                      const bool  anylevel = true) const;

  Standard_EXPORT void AddBasicDescr(const occ::handle<StepData_ESDescr>& esdescr);

  Standard_EXPORT occ::handle<StepData_EDescr> BasicDescr(const char* name,
                                                          const bool  anylevel = true) const;

  DEFINE_STANDARD_RTTIEXT(StepData_Protocol, Interface_Protocol)

private:
  NCollection_DataMap<occ::handle<Standard_Transient>, int>                     thedscnum;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> thedscnam;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> thepdescr;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> thedscbas;
};
