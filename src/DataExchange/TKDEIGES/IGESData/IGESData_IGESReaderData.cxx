

#include <IGESData_DirPart.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESType.hpp>
#include <IGESData_UndefinedEntity.hpp>
#include <Interface_Check.hpp>
#include <Interface_ParamSet.hpp>
#include <Interface_ParamType.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESData_IGESReaderData, Interface_FileReaderData)

IGESData_IGESReaderData::IGESData_IGESReaderData(const int nbe, const int nbp)
    : Interface_FileReaderData(nbe, nbp),
      thectyp(0, 0),
      thedirs(0, nbe)
{
  thestep = IGESData_ReadDir;
  thedefw = 0.;
  theparh = new Interface_ParamSet(30);
  thestar = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
  thechk  = new Interface_Check;
}

void IGESData_IGESReaderData::AddStartLine(const char* aval)
{
  thestar->Append(new TCollection_HAsciiString(aval));
}

occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> IGESData_IGESReaderData::
  StartSection() const
{
  return thestar;
}

void IGESData_IGESReaderData::AddGlobal(const Interface_ParamType atype, const char* aval)
{
  theparh->Append(aval, (int)strlen(aval), atype, 0);
}

void IGESData_IGESReaderData::SetGlobalSection()
{
  thehead.Init(theparh, thechk);
}

const IGESData_GlobalSection& IGESData_IGESReaderData::GlobalSection() const
{
  return thehead;
}

void IGESData_IGESReaderData::SetDirPart(const int   num,
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
                                         const char* subs)
{
  IGESData_DirPart& DP = thedirs(num);
  DP.Init(i1,
          i2,
          i3,
          i4,
          i5,
          i6,
          i7,
          i8,
          i9,
          i10,
          i11,
          i12,
          i13,
          i14,
          i15,
          i16,
          i17,
          res1,
          res2,
          label,
          subs);
}

const IGESData_DirPart& IGESData_IGESReaderData::DirPart(const int num) const
{
  return thedirs(num);
}

void IGESData_IGESReaderData::DirValues(const int    num,
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
                                        const char*& subs) const
{
  thedirs(num).Values(i1,
                      i2,
                      i3,
                      i4,
                      i5,
                      i6,
                      i7,
                      i8,
                      i9,
                      i10,
                      i11,
                      i12,
                      i13,
                      i14,
                      i15,
                      i16,
                      i17,
                      res1,
                      res2,
                      label,
                      subs);
}

IGESData_IGESType IGESData_IGESReaderData::DirType(const int num) const
{
  return thedirs(num).Type();
}

int IGESData_IGESReaderData::NbEntities() const
{
  return thedirs.Upper();
}

int IGESData_IGESReaderData::FindNextRecord(const int num) const
{
  if (num >= thedirs.Upper())
    return 0;
  else
    return (num + 1);
}

void IGESData_IGESReaderData::SetEntityNumbers() {}

occ::handle<Interface_Check> IGESData_IGESReaderData::GlobalCheck() const
{
  return thechk;
}

void IGESData_IGESReaderData::SetDefaultLineWeight(const double defw)
{
  thedefw = defw;
}

double IGESData_IGESReaderData::DefaultLineWeight() const
{
  return thedefw;
}
