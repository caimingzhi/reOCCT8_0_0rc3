

#include <gp_Ax3.hpp>
#include <gp_Dir.hpp>
#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_GeneralModule.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_SingleParentEntity.hpp>
#include <IGESData_ToolLocation.hpp>
#include <IGESData_TransfEntity.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESData_ToolLocation, Standard_Transient)

#define TYPEFORASSOC 402

IGESData_ToolLocation::IGESData_ToolLocation(const occ::handle<IGESData_IGESModel>& amodel,
                                             const occ::handle<IGESData_Protocol>&  protocol)
    : thelib(protocol),
      therefs(0, amodel->NbEntities()),
      theassocs(0, amodel->NbEntities())
{
  theprec  = 1.e-05;
  themodel = amodel;
  therefs.Init(0);
  theassocs.Init(0);
  Load();
}

void IGESData_ToolLocation::Load()
{

  int nb = themodel->NbEntities();
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<IGESData_IGESEntity> ent = themodel->Entity(i);
    if (ent->IsKind(STANDARD_TYPE(IGESData_TransfEntity)))
      continue;

    if (ent->IsKind(STANDARD_TYPE(IGESData_SingleParentEntity)))
    {
      DeclareAndCast(IGESData_SingleParentEntity, assoc, ent);
      int                              nbc    = assoc->NbChildren();
      occ::handle<IGESData_IGESEntity> parent = assoc->SingleParent();
      for (int j = 1; j <= nbc; j++)
        SetParentAssoc(parent, assoc->Child(j));
      continue;
    }
    if (ent->TypeNumber() == TYPEFORASSOC)
      continue;

    SetOwnAsDependent(ent);
  }
}

void IGESData_ToolLocation::SetPrecision(const double prec)
{
  theprec = prec;
}

void IGESData_ToolLocation::SetReference(const occ::handle<IGESData_IGESEntity>& parent,
                                         const occ::handle<IGESData_IGESEntity>& child)
{
  int np = themodel->Number(parent);
  int nc = themodel->Number(child);
  if (np == 0 || nc == 0)
    return;
  if (therefs(nc) > 0)
    np = -1;
  therefs.SetValue(nc, np);
}

void IGESData_ToolLocation::SetParentAssoc(const occ::handle<IGESData_IGESEntity>& parent,
                                           const occ::handle<IGESData_IGESEntity>& child)
{
  int np = themodel->Number(parent);
  int nc = themodel->Number(child);
  if (np == 0 || nc == 0)
    return;
  if (theassocs(nc) > 0)
    np = -1;
  theassocs.SetValue(nc, np);
}

void IGESData_ToolLocation::ResetDependences(const occ::handle<IGESData_IGESEntity>& child)
{
  int nc = themodel->Number(child);
  if (nc == 0)
    return;
  therefs.SetValue(nc, 0);
  theassocs.SetValue(nc, 0);
}

void IGESData_ToolLocation::SetOwnAsDependent(const occ::handle<IGESData_IGESEntity>& ent)
{
  int                                  CN;
  occ::handle<Interface_GeneralModule> gmodule;
  if (!thelib.Select(ent, gmodule, CN))
    return;
  occ::handle<IGESData_GeneralModule> module = occ::down_cast<IGESData_GeneralModule>(gmodule);
  Interface_EntityIterator            list;
  module->OwnSharedCase(CN, ent, list);

  for (list.Start(); list.More(); list.Next())
    SetReference(ent, GetCasted(IGESData_IGESEntity, list.Value()));
}

bool IGESData_ToolLocation::IsTransf(const occ::handle<IGESData_IGESEntity>& ent) const
{
  return ent->IsKind(STANDARD_TYPE(IGESData_TransfEntity));
}

bool IGESData_ToolLocation::IsAssociativity(const occ::handle<IGESData_IGESEntity>& ent) const
{
  return (ent->TypeNumber() == TYPEFORASSOC);
}

bool IGESData_ToolLocation::HasTransf(const occ::handle<IGESData_IGESEntity>& ent) const
{
  return ent->HasTransf();
}

gp_GTrsf IGESData_ToolLocation::ExplicitLocation(const occ::handle<IGESData_IGESEntity>& ent) const
{
  return ent->Location();
}

bool IGESData_ToolLocation::IsAmbiguous(const occ::handle<IGESData_IGESEntity>& ent) const
{
  int num = themodel->Number(ent);
  if (num == 0)
    return false;
  if (therefs(num) < 0 || theassocs(num) < 0)
    return true;
  if (therefs(num) != 0 && theassocs(num) != 0)
    return true;
  return false;
}

bool IGESData_ToolLocation::HasParent(const occ::handle<IGESData_IGESEntity>& ent) const
{
  int num = themodel->Number(ent);
  if (num == 0)
    return false;
  if (therefs(num) < 0 || theassocs(num) < 0)
    throw Standard_DomainError("IGESData_ToolLocation : HasParent");
  if (therefs(num) != 0 && theassocs(num) != 0)
    throw Standard_DomainError("IGESData_ToolLocation : HasParent");
  if (therefs(num) != 0 || theassocs(num) != 0)
    return true;
  return false;
}

occ::handle<IGESData_IGESEntity> IGESData_ToolLocation::Parent(
  const occ::handle<IGESData_IGESEntity>& ent) const
{
  occ::handle<IGESData_IGESEntity> parent;
  int                              num = themodel->Number(ent);
  if (num == 0)
    return parent;
  if (therefs(num) < 0 || theassocs(num) < 0)
    throw Standard_DomainError("IGESData_ToolLocation : Parent");
  if (therefs(num) != 0 && theassocs(num) != 0)
    throw Standard_DomainError("IGESData_ToolLocation : Parent");
  if (therefs(num) != 0)
    parent = themodel->Entity(therefs(num));
  if (theassocs(num) != 0)
    parent = themodel->Entity(theassocs(num));
  return parent;
}

bool IGESData_ToolLocation::HasParentByAssociativity(
  const occ::handle<IGESData_IGESEntity>& ent) const
{
  int num = themodel->Number(ent);
  if (num == 0)
    return false;
  if (therefs(num) < 0 || theassocs(num) < 0)
    throw Standard_DomainError("IGESData_ToolLocation : HasParentByAssociativity");
  if (therefs(num) != 0 && theassocs(num) != 0)
    throw Standard_DomainError("IGESData_ToolLocation : HasParentByAssociativity");
  if (theassocs(num) != 0)
    return true;
  return false;
}

gp_GTrsf IGESData_ToolLocation::ParentLocation(const occ::handle<IGESData_IGESEntity>& ent) const
{
  gp_GTrsf                         locat;
  occ::handle<IGESData_IGESEntity> parent = Parent(ent);

  if (!parent.IsNull())
    locat = EffectiveLocation(parent);
  return locat;
}

gp_GTrsf IGESData_ToolLocation::EffectiveLocation(const occ::handle<IGESData_IGESEntity>& ent) const
{
  gp_GTrsf locat = ent->Location();

  locat.PreMultiply(ParentLocation(ent));
  return locat;
}

bool IGESData_ToolLocation::AnalyseLocation(const gp_GTrsf& loc, gp_Trsf& result) const
{
  return ConvertLocation(theprec, loc, result);
}

bool IGESData_ToolLocation::ConvertLocation(const double    prec,
                                            const gp_GTrsf& loc,
                                            gp_Trsf&        result,
                                            const double    unit)
{
  if (result.Form() != gp_Identity)
    result = gp_Trsf();

  gp_XYZ v1(loc.Value(1, 1), loc.Value(1, 2), loc.Value(1, 3));
  gp_XYZ v2(loc.Value(2, 1), loc.Value(2, 2), loc.Value(2, 3));
  gp_XYZ v3(loc.Value(3, 1), loc.Value(3, 2), loc.Value(3, 3));

  double m1 = v1.Modulus();
  double m2 = v2.Modulus();
  double m3 = v3.Modulus();

  if (m1 < prec || m2 < prec || m3 < prec)
    return false;
  double mm = (m1 + m2 + m3) / 3.;
  if (std::abs(m1 - mm) > prec * mm || std::abs(m2 - mm) > prec * mm
      || std::abs(m3 - mm) > prec * mm)
    return false;
  v1.Divide(m1);
  v2.Divide(m2);
  v3.Divide(m3);
  if (std::abs(v1.Dot(v2)) > prec || std::abs(v2.Dot(v3)) > prec || std::abs(v3.Dot(v1)) > prec)
    return false;

  if (std::abs(mm - 1.) > prec)
    result.SetScale(gp_Pnt(0, 0, 0), mm);
  gp_XYZ tp = loc.TranslationPart();
  if (unit != 1.)
    tp.Multiply(unit);
  if (tp.X() != 0. || tp.Y() != 0. || tp.Z() != 0.)
    result.SetTranslationPart(tp);

  if (v1.X() != 1. || v1.Y() != 0. || v1.Z() != 0. || v2.X() != 0. || v2.Y() != 1. || v2.Z() != 0.
      || v3.X() != 0. || v3.Y() != 0. || v3.Z() != 1.)
  {

    gp_Dir d1(v1);
    gp_Dir d2(v2);
    gp_Dir d3(v3);
    gp_Ax3 axes(gp_Pnt(0, 0, 0), d3, d1);
    d3.Cross(d1);
    if (d3.Dot(d2) < 0)
      axes.YReverse();
    gp_Trsf transf;
    transf.SetTransformation(axes);
    result *= transf;
  }
  return true;
}
