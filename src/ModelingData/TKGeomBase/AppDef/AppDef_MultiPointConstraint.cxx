#include <AppDef_MultiPointConstraint.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_OutOfRange.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

AppDef_MultiPointConstraint::AppDef_MultiPointConstraint() = default;

AppDef_MultiPointConstraint::AppDef_MultiPointConstraint(const int NbPoles, const int NbPoles2d)
    : AppParCurves_MultiPoint(NbPoles, NbPoles2d)
{
}

AppDef_MultiPointConstraint::AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt>& tabP)
    : AppParCurves_MultiPoint(tabP)
{
}

AppDef_MultiPointConstraint::AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt2d>& tabP2d)
    : AppParCurves_MultiPoint(tabP2d)
{
}

AppDef_MultiPointConstraint::AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt>&   tabP,
                                                         const NCollection_Array1<gp_Pnt2d>& tabP2d)
    : AppParCurves_MultiPoint(tabP, tabP2d)
{
}

AppDef_MultiPointConstraint::AppDef_MultiPointConstraint(
  const NCollection_Array1<gp_Pnt>&   tabP,
  const NCollection_Array1<gp_Pnt2d>& tabP2d,
  const NCollection_Array1<gp_Vec>&   tabVec,
  const NCollection_Array1<gp_Vec2d>& tabVec2d,
  const NCollection_Array1<gp_Vec>&   tabCur,
  const NCollection_Array1<gp_Vec2d>& tabCur2d)
    : AppParCurves_MultiPoint(tabP, tabP2d)
{

  if ((tabP.Length() != tabVec.Length()) || (tabP2d.Length() != tabVec2d.Length())
      || (tabCur.Length() != tabP.Length()) || (tabCur2d.Length() != tabP2d.Length()))
  {
    throw Standard_ConstructionError();
  }

  tabTang   = new NCollection_HArray1<gp_Vec>(1, tabVec.Length());
  tabTang2d = new NCollection_HArray1<gp_Vec2d>(1, tabVec2d.Length());

  int i, Lower = tabVec.Lower();
  for (i = 1; i <= tabVec.Length(); i++)
  {
    tabTang->SetValue(i, tabVec.Value(Lower + i - 1));
  }
  Lower = tabVec2d.Lower();
  for (i = 1; i <= tabVec2d.Length(); i++)
  {
    tabTang2d->SetValue(i, tabVec2d.Value(Lower + i - 1));
  }

  tabCurv   = new NCollection_HArray1<gp_Vec>(1, tabCur.Length());
  tabCurv2d = new NCollection_HArray1<gp_Vec2d>(1, tabCur2d.Length());

  Lower = tabCur.Lower();
  for (i = 1; i <= tabVec.Length(); i++)
  {
    tabCurv->SetValue(i, tabCur.Value(Lower + i - 1));
  }
  Lower = tabCur2d.Lower();
  for (i = 1; i <= tabCur2d.Length(); i++)
  {
    tabCurv2d->SetValue(i, tabCur2d.Value(Lower + i - 1));
  }
}

AppDef_MultiPointConstraint::AppDef_MultiPointConstraint(
  const NCollection_Array1<gp_Pnt>&   tabP,
  const NCollection_Array1<gp_Pnt2d>& tabP2d,
  const NCollection_Array1<gp_Vec>&   tabVec,
  const NCollection_Array1<gp_Vec2d>& tabVec2d)
    : AppParCurves_MultiPoint(tabP, tabP2d)
{

  if ((tabP.Length() != tabVec.Length()) || (tabP2d.Length() != tabVec2d.Length()))
  {
    throw Standard_ConstructionError();
  }

  tabTang   = new NCollection_HArray1<gp_Vec>(1, tabVec.Length());
  tabTang2d = new NCollection_HArray1<gp_Vec2d>(1, tabVec2d.Length());

  int i, Lower = tabVec.Lower();
  for (i = 1; i <= tabVec.Length(); i++)
  {
    tabTang->SetValue(i, tabVec.Value(Lower + i - 1));
  }
  Lower = tabVec2d.Lower();
  for (i = 1; i <= tabVec2d.Length(); i++)
  {
    tabTang2d->SetValue(i, tabVec2d.Value(Lower + i - 1));
  }
}

AppDef_MultiPointConstraint::AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt>& tabP,
                                                         const NCollection_Array1<gp_Vec>& tabVec)
    : AppParCurves_MultiPoint(tabP)
{

  if (tabP.Length() != tabVec.Length())
  {
    throw Standard_ConstructionError();
  }

  tabTang = new NCollection_HArray1<gp_Vec>(1, tabVec.Length());

  int i, Lower = tabVec.Lower();
  for (i = 1; i <= tabVec.Length(); i++)
  {
    tabTang->SetValue(i, tabVec.Value(Lower + i - 1));
  }
}

AppDef_MultiPointConstraint::AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt>& tabP,
                                                         const NCollection_Array1<gp_Vec>& tabVec,
                                                         const NCollection_Array1<gp_Vec>& tabCur)
    : AppParCurves_MultiPoint(tabP)
{

  if ((tabP.Length() != tabVec.Length()) || (tabP.Length() != tabCur.Length()))
  {
    throw Standard_ConstructionError();
  }

  tabTang = new NCollection_HArray1<gp_Vec>(1, tabVec.Length());
  int i, Lower = tabVec.Lower();
  for (i = 1; i <= tabVec.Length(); i++)
  {
    tabTang->SetValue(i, tabVec.Value(Lower + i - 1));
  }

  tabCurv = new NCollection_HArray1<gp_Vec>(1, tabCur.Length());
  Lower   = tabCur.Lower();
  for (i = 1; i <= tabCur.Length(); i++)
  {
    tabCurv->SetValue(i, tabCur.Value(Lower + i - 1));
  }
}

AppDef_MultiPointConstraint::AppDef_MultiPointConstraint(
  const NCollection_Array1<gp_Pnt2d>& tabP2d,
  const NCollection_Array1<gp_Vec2d>& tabVec2d)
    :

      AppParCurves_MultiPoint(tabP2d)
{

  if (tabP2d.Length() != tabVec2d.Length())
  {
    throw Standard_ConstructionError();
  }

  tabTang2d = new NCollection_HArray1<gp_Vec2d>(1, tabVec2d.Length());
  int i, Lower = tabVec2d.Lower();
  for (i = 1; i <= tabVec2d.Length(); i++)
  {
    tabTang2d->SetValue(i, tabVec2d.Value(Lower + i - 1));
  }
}

AppDef_MultiPointConstraint::AppDef_MultiPointConstraint(
  const NCollection_Array1<gp_Pnt2d>& tabP2d,
  const NCollection_Array1<gp_Vec2d>& tabVec2d,
  const NCollection_Array1<gp_Vec2d>& tabCur2d)
    : AppParCurves_MultiPoint(tabP2d)
{

  if ((tabP2d.Length() != tabVec2d.Length()) || (tabCur2d.Length() != tabP2d.Length()))
  {
    throw Standard_ConstructionError();
  }

  tabTang2d = new NCollection_HArray1<gp_Vec2d>(1, tabVec2d.Length());
  int i, Lower = tabVec2d.Lower();
  for (i = 1; i <= tabVec2d.Length(); i++)
  {
    tabTang2d->SetValue(i, tabVec2d.Value(Lower + i - 1));
  }

  tabCurv2d = new NCollection_HArray1<gp_Vec2d>(1, tabCur2d.Length());
  Lower     = tabCur2d.Lower();
  for (i = 1; i <= tabCur2d.Length(); i++)
  {
    tabCurv2d->SetValue(i, tabCur2d.Value(Lower + i - 1));
  }
}

void AppDef_MultiPointConstraint::SetTang(const int Index, const gp_Vec& Tang)
{
  if (tabTang.IsNull())
    tabTang = new NCollection_HArray1<gp_Vec>(1, nbP);
  if ((Index <= 0) || (Index > nbP))
  {
    throw Standard_OutOfRange();
  }
  tabTang->SetValue(Index, Tang);
}

gp_Vec AppDef_MultiPointConstraint::Tang(const int Index) const
{
  if ((Index <= 0) || (Index > nbP))
  {
    throw Standard_OutOfRange();
  }
  return tabTang->Value(Index);
}

void AppDef_MultiPointConstraint::SetTang2d(const int Index, const gp_Vec2d& Tang2d)
{
  if (tabTang2d.IsNull())
    tabTang2d = new NCollection_HArray1<gp_Vec2d>(1, nbP2d);

  if ((Index <= nbP) || (Index > nbP + nbP2d))
  {
    throw Standard_OutOfRange();
  }
  tabTang2d->SetValue(Index - nbP, Tang2d);
}

gp_Vec2d AppDef_MultiPointConstraint::Tang2d(const int Index) const
{
  if ((Index <= nbP) || (Index > nbP + nbP2d))
  {
    throw Standard_OutOfRange();
  }
  return tabTang2d->Value(Index - nbP);
}

void AppDef_MultiPointConstraint::SetCurv(const int Index, const gp_Vec& Curv)
{
  if (tabCurv.IsNull())
    tabCurv = new NCollection_HArray1<gp_Vec>(1, nbP);
  if ((Index <= 0) || (Index > nbP))
  {
    throw Standard_OutOfRange();
  }
  tabCurv->SetValue(Index, Curv);
}

gp_Vec AppDef_MultiPointConstraint::Curv(const int Index) const
{
  if ((Index <= 0) || (Index > nbP))
  {
    throw Standard_OutOfRange();
  }
  return tabCurv->Value(Index);
}

void AppDef_MultiPointConstraint::SetCurv2d(const int Index, const gp_Vec2d& Curv2d)
{
  if (tabCurv2d.IsNull())
    tabCurv2d = new NCollection_HArray1<gp_Vec2d>(1, nbP2d);
  if ((Index <= nbP) || (Index > nbP + nbP2d))
  {
    throw Standard_OutOfRange();
  }
  tabCurv2d->SetValue(Index - nbP, Curv2d);
}

gp_Vec2d AppDef_MultiPointConstraint::Curv2d(const int Index) const
{
  if ((Index <= nbP) || (Index > nbP + nbP2d))
  {
    throw Standard_OutOfRange();
  }
  return tabCurv2d->Value(Index - nbP);
}

bool AppDef_MultiPointConstraint::IsTangencyPoint() const
{
  return !(tabTang.IsNull() && tabTang2d.IsNull());
}

bool AppDef_MultiPointConstraint::IsCurvaturePoint() const
{
  return !(tabCurv.IsNull() && tabCurv2d.IsNull());
}

void AppDef_MultiPointConstraint::Dump(Standard_OStream& o) const
{
  o << "AppDef_MultiPointConstraint dump:" << std::endl;
}
