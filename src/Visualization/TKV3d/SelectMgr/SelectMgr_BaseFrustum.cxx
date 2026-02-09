#include <SelectMgr_BaseFrustum.hpp>

#include <Message.hpp>
#include <SelectMgr_FrustumBuilder.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_BaseFrustum, SelectMgr_BaseIntersector)

SelectMgr_BaseFrustum::SelectMgr_BaseFrustum()
    : myPixelTolerance(2)
{
  myBuilder = new SelectMgr_FrustumBuilder();
}

void SelectMgr_BaseFrustum::SetCamera(const occ::handle<Graphic3d_Camera>& theCamera)
{
  SelectMgr_BaseIntersector::SetCamera(theCamera);
  if (!myBuilder.IsNull())
  {
    myBuilder->SetCamera(theCamera);
    myBuilder->InvalidateViewport();
  }
}

void SelectMgr_BaseFrustum::SetViewport(const double theX,
                                        const double theY,
                                        const double theWidth,
                                        const double theHeight)
{
  myBuilder->SetViewport(theX, theY, theWidth, theHeight);
}

void SelectMgr_BaseFrustum::SetPixelTolerance(const int theTol)
{
  myPixelTolerance = theTol;
}

void SelectMgr_BaseFrustum::SetWindowSize(const int theWidth, const int theHeight)
{
  myBuilder->SetWindowSize(theWidth, theHeight);
}

void SelectMgr_BaseFrustum::WindowSize(int& theWidth, int& theHeight) const
{
  myBuilder->WindowSize(theWidth, theHeight);
}

void SelectMgr_BaseFrustum::SetBuilder(const occ::handle<SelectMgr_FrustumBuilder>& theBuilder)
{
  myBuilder.Nullify();
  myBuilder = theBuilder;
  if (!myBuilder.IsNull())
  {
    myCamera = myBuilder->Camera();
  }
}

bool SelectMgr_BaseFrustum::IsBoundaryIntersectSphere(
  const gp_Pnt&                     theCenter,
  const double                      theRadius,
  const gp_Dir&                     thePlaneNormal,
  const NCollection_Array1<gp_Pnt>& theBoundaries,
  bool&                             theBoundaryInside) const
{
  for (int anIdx = theBoundaries.Lower(); anIdx < theBoundaries.Upper(); ++anIdx)
  {
    const int aNextIdx =
      ((anIdx + 1) == theBoundaries.Upper()) ? theBoundaries.Lower() : (anIdx + 1);
    const gp_Pnt aPnt1 = theBoundaries.Value(anIdx);
    const gp_Pnt aPnt2 = theBoundaries.Value(aNextIdx);
    if (aPnt1.Distance(aPnt2) < Precision::Confusion())
    {
      continue;
    }

    const gp_Pnt aPntProj1 =
      aPnt1.XYZ() - thePlaneNormal.XYZ() * aPnt1.XYZ().Dot(thePlaneNormal.XYZ());
    const gp_Pnt aPntProj2 =
      aPnt2.XYZ() - thePlaneNormal.XYZ() * aPnt2.XYZ().Dot(thePlaneNormal.XYZ());
    if (aPntProj1.Distance(theCenter) < theRadius || aPntProj2.Distance(theCenter) < theRadius)
    {
      theBoundaryInside = true;
      return true;
    }

    gp_Dir aRayDir(gp_Vec(aPntProj1, aPntProj2));
    double aTimeEnter = 0.0, aTimeLeave = 0.0;
    if (RaySphereIntersection(theCenter, theRadius, aPntProj1, aRayDir, aTimeEnter, aTimeLeave))
    {
      if ((aTimeEnter > 0 && aTimeEnter < aPntProj1.Distance(aPntProj2))
          || (aTimeLeave > 0 && aTimeLeave < aPntProj1.Distance(aPntProj2)))
      {
        return true;
      }
    }
  }
  return false;
}

void SelectMgr_BaseFrustum::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, SelectMgr_BaseFrustum)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, SelectMgr_BaseIntersector)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myPixelTolerance)
  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myBuilder)
}
