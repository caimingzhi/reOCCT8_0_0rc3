

#include <IFSelect_IntParam.hpp>
#include <IFSelect_SelectRange.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectRange, IFSelect_SelectExtract)

IFSelect_SelectRange::IFSelect_SelectRange() = default;

void IFSelect_SelectRange::SetRange(const occ::handle<IFSelect_IntParam>& rankfrom,
                                    const occ::handle<IFSelect_IntParam>& rankto)
{
  thelower = rankfrom;
  theupper = rankto;
}

void IFSelect_SelectRange::SetOne(const occ::handle<IFSelect_IntParam>& rank)
{
  thelower = theupper = rank;
}

void IFSelect_SelectRange::SetFrom(const occ::handle<IFSelect_IntParam>& rankfrom)
{
  thelower = rankfrom;
  theupper.Nullify();
}

void IFSelect_SelectRange::SetUntil(const occ::handle<IFSelect_IntParam>& rankto)
{
  thelower.Nullify();
  theupper = rankto;
}

bool IFSelect_SelectRange::HasLower() const
{
  return (!thelower.IsNull());
}

occ::handle<IFSelect_IntParam> IFSelect_SelectRange::Lower() const
{
  return thelower;
}

int IFSelect_SelectRange::LowerValue() const
{
  if (thelower.IsNull())
    return 0;
  return thelower->Value();
}

bool IFSelect_SelectRange::HasUpper() const
{
  return (!theupper.IsNull());
}

occ::handle<IFSelect_IntParam> IFSelect_SelectRange::Upper() const
{
  return theupper;
}

int IFSelect_SelectRange::UpperValue() const
{
  if (theupper.IsNull())
    return 0;
  return theupper->Value();
}

bool IFSelect_SelectRange::Sort(const int rank,
                                const occ::handle<Standard_Transient>&,
                                const occ::handle<Interface_InterfaceModel>&) const
{
  int rankfrom = 0;
  if (!thelower.IsNull())
    rankfrom = thelower->Value();
  int rankto = 0;
  if (!theupper.IsNull())
    rankto = theupper->Value();
  return (rank >= rankfrom && (rankto == 0 || rankto >= rank));
}

TCollection_AsciiString IFSelect_SelectRange::ExtractLabel() const
{
  char lab[30];
  int  rankfrom = 0;
  if (!thelower.IsNull())
    rankfrom = thelower->Value();
  int rankto = 0;
  if (!theupper.IsNull())
    rankto = theupper->Value();
  if (rankfrom == rankto)
    Sprintf(lab, "Rank no %d", rankfrom);
  else if (rankfrom == 0)
    Sprintf(lab, "Until no %d", rankto);
  else if (rankto == 0)
    Sprintf(lab, "From no %d", rankto);
  else
    Sprintf(lab, "From %d Until %d", rankfrom, rankto);

  return TCollection_AsciiString(lab);
}
