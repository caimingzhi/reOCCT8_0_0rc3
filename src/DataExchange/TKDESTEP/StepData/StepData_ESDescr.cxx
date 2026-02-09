

#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <StepData_ESDescr.hpp>
#include <StepData_PDescr.hpp>
#include <StepData_Simple.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepData_ESDescr, StepData_EDescr)

StepData_ESDescr::StepData_ESDescr(const char* name)
    : thenom(name)
{
}

void StepData_ESDescr::SetNbFields(const int nb)
{

  int minb, i, oldnb = NbFields();
  thenames.Clear();
  if (nb == 0)
  {
    thedescr.Nullify();
    return;
  }
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> li =
    new NCollection_HArray1<occ::handle<Standard_Transient>>(1, nb);
  if (oldnb == 0)
  {
    thedescr = li;
    return;
  }

  minb = (oldnb > nb ? nb : oldnb);
  for (i = 1; i <= minb; i++)
  {
    DeclareAndCast(StepData_PDescr, pde, thedescr->Value(i));
    if (!pde.IsNull())
      thenames.Bind(pde->Name(), i);
    li->SetValue(i, pde);
  }
  thedescr = li;
}

void StepData_ESDescr::SetField(const int                           num,
                                const char*                         name,
                                const occ::handle<StepData_PDescr>& descr)
{

  if (num < 1 || num > NbFields())
    return;
  occ::handle<StepData_PDescr> pde = new StepData_PDescr;
  pde->SetFrom(descr);
  pde->SetName(name);
  thedescr->SetValue(num, pde);
  thenames.Bind(name, num);
}

void StepData_ESDescr::SetBase(const occ::handle<StepData_ESDescr>& base)
{
  thebase = base;
}

void StepData_ESDescr::SetSuper(const occ::handle<StepData_ESDescr>& super)
{

  occ::handle<StepData_ESDescr> sup = super->Base();
  if (sup.IsNull())
    sup = super;
  if (!thebase.IsNull())
    thebase->SetSuper(sup);
  else
    thesuper = sup;
}

const char* StepData_ESDescr::TypeName() const
{
  return thenom.ToCString();
}

const TCollection_AsciiString& StepData_ESDescr::StepType() const
{
  return thenom;
}

occ::handle<StepData_ESDescr> StepData_ESDescr::Base() const
{
  return thebase;
}

occ::handle<StepData_ESDescr> StepData_ESDescr::Super() const
{
  return thesuper;
}

bool StepData_ESDescr::IsSub(const occ::handle<StepData_ESDescr>& other) const
{

  occ::handle<StepData_ESDescr> oth = other->Base();
  if (oth.IsNull())
    oth = other;
  if (!thebase.IsNull())
    return thebase->IsSub(oth);
  occ::handle<Standard_Transient> t1 = this;
  if (oth == t1)
    return true;
  if (oth == thesuper)
    return true;
  else if (thesuper.IsNull())
    return false;
  return thesuper->IsSub(oth);
}

int StepData_ESDescr::NbFields() const
{
  return (thedescr.IsNull() ? 0 : thedescr->Length());
}

int StepData_ESDescr::Rank(const char* name) const
{
  int rank;
  if (!thenames.Find(name, rank))
    return 0;
  return rank;
}

const char* StepData_ESDescr::Name(const int num) const
{
  if (num < 1)
    return "";
  if (num > NbFields())
    return "";
  DeclareAndCast(StepData_PDescr, pde, thedescr->Value(num));
  return pde->Name();
}

occ::handle<StepData_PDescr> StepData_ESDescr::Field(const int num) const
{
  return GetCasted(StepData_PDescr, thedescr->Value(num));
}

occ::handle<StepData_PDescr> StepData_ESDescr::NamedField(const char* name) const
{
  occ::handle<StepData_PDescr> pde;
  int                          rank = Rank(name);
  if (rank > 0)
    pde = GetCasted(StepData_PDescr, thedescr->Value(rank));
  return pde;
}

bool StepData_ESDescr::Matches(const char* name) const
{

  if (thenom.IsEqual(name))
    return true;
  if (thesuper.IsNull())
    return false;
  return thesuper->Matches(name);
}

bool StepData_ESDescr::IsComplex() const
{
  return false;
}

occ::handle<StepData_Described> StepData_ESDescr::NewEntity() const
{

  occ::handle<StepData_Simple> ent = new StepData_Simple(this);
  return ent;
}
