#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESType.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <IGESData_GlobalSection.hpp>
#include <IGESData_DirPart.hpp>
#include <NCollection_Array1.hpp>
#include <IGESData_ReadStage.hpp>
#include <Interface_FileReaderData.hpp>
#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>
#include <Interface_ParamType.hpp>
class Interface_ParamSet;
class Interface_Check;
class IGESData_DirPart;

class IGESData_IGESReaderData : public Interface_FileReaderData
{

public:
  Standard_EXPORT IGESData_IGESReaderData(const int nbe, const int nbp);

  Standard_EXPORT void AddStartLine(const char* aval);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  StartSection() const;

  Standard_EXPORT void AddGlobal(const Interface_ParamType atype, const char* aval);

  Standard_EXPORT void SetGlobalSection();

  Standard_EXPORT const IGESData_GlobalSection& GlobalSection() const;

  Standard_EXPORT void SetDirPart(const int   num,
                                  const int   i1,
                                  const int   i2,
                                  const int   i3,
                                  const int   i4,
                                  const int   i5,
                                  const int   i6,
                                  const int   i7,
                                  const int   i8,
                                  const int   i9,
                                  const int   i10,
                                  const int   i11,
                                  const int   i12,
                                  const int   i13,
                                  const int   i14,
                                  const int   i15,
                                  const int   i16,
                                  const int   i17,
                                  const char* res1,
                                  const char* res2,
                                  const char* label,
                                  const char* subs);

  Standard_EXPORT const IGESData_DirPart& DirPart(const int num) const;

  Standard_EXPORT void DirValues(const int    num,
                                 int&         i1,
                                 int&         i2,
                                 int&         i3,
                                 int&         i4,
                                 int&         i5,
                                 int&         i6,
                                 int&         i7,
                                 int&         i8,
                                 int&         i9,
                                 int&         i10,
                                 int&         i11,
                                 int&         i12,
                                 int&         i13,
                                 int&         i14,
                                 int&         i15,
                                 int&         i16,
                                 int&         i17,
                                 const char*& res1,
                                 const char*& res2,
                                 const char*& label,
                                 const char*& subs) const;

  Standard_EXPORT IGESData_IGESType DirType(const int num) const;

  Standard_EXPORT int NbEntities() const override;

  Standard_EXPORT int FindNextRecord(const int num) const override;

  Standard_EXPORT void SetEntityNumbers();

  Standard_EXPORT occ::handle<Interface_Check> GlobalCheck() const;

  Standard_EXPORT void SetDefaultLineWeight(const double defw);

  Standard_EXPORT double DefaultLineWeight() const;

  DEFINE_STANDARD_RTTIEXT(IGESData_IGESReaderData, Interface_FileReaderData)

private:
  IGESData_IGESType                                                         thectyp;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thestar;
  occ::handle<Interface_ParamSet>                                           theparh;
  IGESData_GlobalSection                                                    thehead;
  NCollection_Array1<IGESData_DirPart>                                      thedirs;
  IGESData_ReadStage                                                        thestep;
  double                                                                    thedefw;
  occ::handle<Interface_Check>                                              thechk;
};
