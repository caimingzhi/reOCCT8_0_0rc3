#pragma once

#include <IGESData_GlobalSection.hpp>
#include <Interface_InterfaceModel.hpp>

class IGESData_IGESEntity;
class Interface_Check;
class Standard_Transient;
class TCollection_HAsciiString;

class IGESData_IGESModel : public Interface_InterfaceModel
{

public:
  Standard_EXPORT IGESData_IGESModel();

  Standard_EXPORT void ClearHeader() override;

  Standard_EXPORT void DumpHeader(Standard_OStream& S, const int level = 0) const override;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  StartSection() const;

  Standard_EXPORT int NbStartLines() const;

  Standard_EXPORT const char* StartLine(const int num) const;

  Standard_EXPORT void ClearStartSection();

  Standard_EXPORT void SetStartSection(
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& list,
    const bool                                                                       copy = true);

  Standard_EXPORT void AddStartLine(const char* line, const int atnum = 0);

  const IGESData_GlobalSection& GlobalSection() const { return theheader; }

  IGESData_GlobalSection& ChangeGlobalSection() { return theheader; }

  Standard_EXPORT void SetGlobalSection(const IGESData_GlobalSection& header);

  Standard_EXPORT bool ApplyStatic(const char* param = "");

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Entity(const int num) const;

  Standard_EXPORT int DNum(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT void GetFromAnother(const occ::handle<Interface_InterfaceModel>& other) override;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> NewEmptyModel() const override;

  Standard_EXPORT void VerifyCheck(occ::handle<Interface_Check>& ach) const override;

  Standard_EXPORT void SetLineWeights(const double defw);

  Standard_EXPORT void ClearLabels() override;

  Standard_EXPORT void PrintLabel(const occ::handle<Standard_Transient>& ent,
                                  Standard_OStream&                      S) const override;

  Standard_EXPORT void PrintToLog(const occ::handle<Standard_Transient>& ent,
                                  Standard_OStream&                      S) const override;

  Standard_EXPORT void PrintInfo(const occ::handle<Standard_Transient>& ent,
                                 Standard_OStream&                      S) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> StringLabel(
    const occ::handle<Standard_Transient>& ent) const override;

  DEFINE_STANDARD_RTTIEXT(IGESData_IGESModel, Interface_InterfaceModel)

private:
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thestart;
  IGESData_GlobalSection                                                    theheader;
};
