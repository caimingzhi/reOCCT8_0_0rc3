#pragma once

#include <Interface_EntityList.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Resource_FormatType.hpp>
#include <StepData_Factors.hpp>
#include <DESTEP_Parameters.hpp>

class Standard_Transient;
class Interface_EntityIterator;
class Interface_Check;
class TCollection_HAsciiString;

class StepData_StepModel : public Interface_InterfaceModel
{

public:
  Standard_EXPORT StepData_StepModel();

  Standard_EXPORT occ::handle<Standard_Transient> Entity(const int num) const;

  Standard_EXPORT void GetFromAnother(const occ::handle<Interface_InterfaceModel>& other) override;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> NewEmptyModel() const override;

  Standard_EXPORT Interface_EntityIterator Header() const;

  Standard_EXPORT bool HasHeaderEntity(const occ::handle<Standard_Type>& atype) const;

  Standard_EXPORT occ::handle<Standard_Transient> HeaderEntity(
    const occ::handle<Standard_Type>& atype) const;

  Standard_EXPORT void ClearHeader() override;

  Standard_EXPORT void AddHeaderEntity(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void VerifyCheck(occ::handle<Interface_Check>& ach) const override;

  Standard_EXPORT void DumpHeader(Standard_OStream& S, const int level = 0) const override;

  Standard_EXPORT void ClearLabels() override;

  Standard_EXPORT void SetIdentLabel(const occ::handle<Standard_Transient>& ent, const int ident);

  Standard_EXPORT int IdentLabel(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT void PrintLabel(const occ::handle<Standard_Transient>& ent,
                                  Standard_OStream&                      S) const override;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> StringLabel(
    const occ::handle<Standard_Transient>& ent) const override;

  Resource_FormatType SourceCodePage() const { return InternalParameters.ReadCodePage; }

  void SetSourceCodePage(Resource_FormatType theCode) { InternalParameters.ReadCodePage = theCode; }

  Standard_EXPORT void SetLocalLengthUnit(const double theUnit);

  Standard_EXPORT double LocalLengthUnit() const;

  Standard_EXPORT void SetWriteLengthUnit(const double theUnit);

  Standard_EXPORT double WriteLengthUnit() const;

  bool IsInitializedUnit() const { return myReadUnitIsInitialized; }

public:
  DESTEP_Parameters InternalParameters;

  DEFINE_STANDARD_RTTIEXT(StepData_StepModel, Interface_InterfaceModel)

private:
  Interface_EntityList                  theheader;
  occ::handle<NCollection_HArray1<int>> theidnums;
  mutable double                        myWriteUnit              = 1.0;
  double                                myLocalLengthUnit        = 1.0;
  bool                                  myReadUnitIsInitialized  = false;
  mutable bool                          myWriteUnitIsInitialized = false;
};
