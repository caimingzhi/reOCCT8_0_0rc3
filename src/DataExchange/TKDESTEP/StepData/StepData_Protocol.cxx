

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <StepData_Described.hpp>
#include <StepData_ECDescr.hpp>
#include <StepData_EDescr.hpp>
#include <StepData_ESDescr.hpp>
#include <StepData_PDescr.hpp>
#include <StepData_Protocol.hpp>
#include <StepData_StepModel.hpp>
#include <StepData_UndefinedEntity.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(StepData_Protocol, Interface_Protocol)

static const char* thename = "(DEFAULT)";

StepData_Protocol::StepData_Protocol() = default;

int StepData_Protocol::NbResources() const
{
  return 0;
}

occ::handle<Interface_Protocol> StepData_Protocol::Resource(const int) const
{
  occ::handle<Interface_Protocol> nulproto;
  return nulproto;
}

int StepData_Protocol::CaseNumber(const occ::handle<Standard_Transient>& obj) const
{
  if (obj.IsNull())
    return 0;
  int num = TypeNumber(obj->DynamicType());
  if (num > 0)
    return num;
  occ::handle<StepData_Described> dc = occ::down_cast<StepData_Described>(obj);
  if (dc.IsNull())
    return 0;
  return DescrNumber(dc->Description());
}

int StepData_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (atype == STANDARD_TYPE(StepData_UndefinedEntity))
    return 1;
  return 0;
}

const char* StepData_Protocol::SchemaName(const occ::handle<Interface_InterfaceModel>&) const
{
  return thename;
}

occ::handle<Interface_InterfaceModel> StepData_Protocol::NewModel() const
{
  return new StepData_StepModel;
}

bool StepData_Protocol::IsSuitableModel(const occ::handle<Interface_InterfaceModel>& model) const
{
  return model->IsKind(STANDARD_TYPE(StepData_StepModel));
}

occ::handle<Standard_Transient> StepData_Protocol::UnknownEntity() const
{
  return new StepData_UndefinedEntity;
}

bool StepData_Protocol::IsUnknownEntity(const occ::handle<Standard_Transient>& ent) const
{
  if (!ent.IsNull())
    return ent->IsKind(STANDARD_TYPE(StepData_UndefinedEntity));
  return false;
}

int StepData_Protocol::DescrNumber(const occ::handle<StepData_EDescr>& adescr) const
{
  if (thedscnum.IsBound(adescr))
    return thedscnum.Find(adescr);
  return 0;
}

void StepData_Protocol::AddDescr(const occ::handle<StepData_EDescr>& adescr, const int CN)
{
  occ::handle<StepData_ESDescr> sd = occ::down_cast<StepData_ESDescr>(adescr);
  thedscnum.Bind(adescr, CN);

  if (!sd.IsNull())
    thedscnam.Bind(sd->TypeName(), sd);
  char fonom[10];
  Sprintf(fonom, "%d", CN);
  thedscnam.Bind(fonom, adescr);
}

bool StepData_Protocol::HasDescr() const
{
  return !thedscnam.IsEmpty();
}

occ::handle<StepData_EDescr> StepData_Protocol::Descr(const int num) const
{
  occ::handle<StepData_EDescr> dsc;
  if (thedscnam.IsEmpty())
    return dsc;
  char fonom[10];
  Sprintf(fonom, "%d", num);
  occ::handle<Standard_Transient> aTDsc;
  if (thedscnam.Find(fonom, aTDsc))
    dsc = occ::down_cast<StepData_EDescr>(aTDsc);
  else
    dsc.Nullify();
  return dsc;
}

occ::handle<StepData_EDescr> StepData_Protocol::Descr(const char* name, const bool anylevel) const
{
  occ::handle<StepData_EDescr> sd;
  if (!thedscnam.IsEmpty())
  {
    occ::handle<Standard_Transient> aTSd;
    if (thedscnam.Find(name, aTSd))
      return occ::down_cast<StepData_EDescr>(aTSd);
  }
  if (!anylevel)
    return sd;

  int i, nb = NbResources();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<StepData_Protocol> sp = occ::down_cast<StepData_Protocol>(Resource(i));
    if (sp.IsNull())
      continue;
    sd = sp->Descr(name, anylevel);
    if (!sd.IsNull())
      return sd;
  }
  return sd;
}

occ::handle<StepData_ESDescr> StepData_Protocol::ESDescr(const char* name,
                                                         const bool  anylevel) const
{
  return occ::down_cast<StepData_ESDescr>(Descr(name, anylevel));
}

occ::handle<StepData_ECDescr> StepData_Protocol::ECDescr(
  const NCollection_Sequence<TCollection_AsciiString>& names,
  const bool                                           anylevel) const
{
  int                                                                 i, nb = names.Length();
  occ::handle<StepData_ECDescr>                                       cd;
  NCollection_DataMap<occ::handle<Standard_Transient>, int>::Iterator iter(thedscnum);
  for (; iter.More(); iter.Next())
  {
    cd = occ::down_cast<StepData_ECDescr>(iter.Key());
    if (cd.IsNull())
      continue;
    if (cd->NbMembers() != nb)
      continue;
    bool ok = true;
    for (i = 1; i <= nb; i++)
    {
      if (!names(i).IsEqual(cd->Member(i)->TypeName()))
      {
        ok = false;
        break;
      }
    }
    if (ok)
      return cd;
  }
  cd.Nullify();
  if (!anylevel)
    return cd;

  nb = NbResources();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<StepData_Protocol> sp = occ::down_cast<StepData_Protocol>(Resource(i));
    if (sp.IsNull())
      continue;
    cd = sp->ECDescr(names, anylevel);
    if (!cd.IsNull())
      return cd;
  }
  return cd;
}

void StepData_Protocol::AddPDescr(const occ::handle<StepData_PDescr>& pdescr)
{
  thepdescr.Bind(pdescr->Name(), pdescr);
}

occ::handle<StepData_PDescr> StepData_Protocol::PDescr(const char* name, const bool anylevel) const
{
  occ::handle<StepData_PDescr> sd;
  if (!thepdescr.IsEmpty())
  {
    occ::handle<Standard_Transient> aTSd;
    if (thepdescr.Find(name, aTSd))
      return occ::down_cast<StepData_PDescr>(aTSd);
  }
  if (!anylevel)
    return sd;

  int i, nb = NbResources();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<StepData_Protocol> sp = occ::down_cast<StepData_Protocol>(Resource(i));
    if (sp.IsNull())
      continue;
    sd = sp->PDescr(name, anylevel);
    if (!sd.IsNull())
      return sd;
  }
  return sd;
}

void StepData_Protocol::AddBasicDescr(const occ::handle<StepData_ESDescr>& esdescr)
{
  thedscbas.Bind(esdescr->TypeName(), esdescr);
}

occ::handle<StepData_EDescr> StepData_Protocol::BasicDescr(const char* name,
                                                           const bool  anylevel) const
{
  occ::handle<StepData_EDescr> sd;
  if (!thedscbas.IsEmpty())
  {
    occ::handle<Standard_Transient> aTSd;
    if (thedscbas.Find(name, aTSd))
      return occ::down_cast<StepData_EDescr>(aTSd);
  }
  if (!anylevel)
    return sd;

  int i, nb = NbResources();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<StepData_Protocol> sp = occ::down_cast<StepData_Protocol>(Resource(i));
    if (sp.IsNull())
      continue;
    sd = sp->BasicDescr(name, anylevel);
    if (!sd.IsNull())
      return sd;
  }
  return sd;
}
