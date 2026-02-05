#include <gp_GTrsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <IGESGeom_OffsetCurve.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_OffsetCurve, IGESData_IGESEntity)

IGESGeom_OffsetCurve::IGESGeom_OffsetCurve() = default;

void IGESGeom_OffsetCurve::Init(const occ::handle<IGESData_IGESEntity>& aBaseCurve,
                                const int                               anOffsetType,
                                const occ::handle<IGESData_IGESEntity>& aFunction,
                                const int                               aFunctionCoord,
                                const int                               aTaperedOffsetType,
                                const double                            offDistance1,
                                const double                            anArcLength1,
                                const double                            offDistance2,
                                const double                            anArcLength2,
                                const gp_XYZ&                           aNormalVec,
                                const double                            anOffsetParam,
                                const double                            anotherOffsetParam)
{
  theBaseCurve         = aBaseCurve;
  theOffsetType        = anOffsetType;
  theFunction          = aFunction;
  theFunctionCoord     = aFunctionCoord;
  theTaperedOffsetType = aTaperedOffsetType;
  theOffsetDistance1   = offDistance1;
  theArcLength1        = anArcLength1;
  theOffsetDistance2   = offDistance2;
  theArcLength2        = anArcLength2;
  theNormalVector      = aNormalVec;
  theOffsetParam1      = anOffsetParam;
  theOffsetParam2      = anotherOffsetParam;
  InitTypeAndForm(130, 0);
}

occ::handle<IGESData_IGESEntity> IGESGeom_OffsetCurve::BaseCurve() const
{
  return theBaseCurve;
}

int IGESGeom_OffsetCurve::OffsetType() const
{
  return theOffsetType;
}

occ::handle<IGESData_IGESEntity> IGESGeom_OffsetCurve::Function() const
{
  return theFunction;
}

int IGESGeom_OffsetCurve::FunctionParameter() const
{
  return theFunctionCoord;
}

int IGESGeom_OffsetCurve::TaperedOffsetType() const
{
  return theTaperedOffsetType;
}

double IGESGeom_OffsetCurve::FirstOffsetDistance() const
{
  return theOffsetDistance1;
}

double IGESGeom_OffsetCurve::ArcLength1() const
{
  return theArcLength1;
}

double IGESGeom_OffsetCurve::SecondOffsetDistance() const
{
  return theOffsetDistance2;
}

double IGESGeom_OffsetCurve::ArcLength2() const
{
  return theArcLength2;
}

gp_Vec IGESGeom_OffsetCurve::NormalVector() const
{
  return (gp_Vec(theNormalVector));
}

gp_Vec IGESGeom_OffsetCurve::TransformedNormalVector() const
{
  if (!HasTransf())
    return gp_Vec(theNormalVector);
  gp_XYZ   tempXYZ(theNormalVector);
  gp_GTrsf loc = Location();
  loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
  loc.Transforms(tempXYZ);
  return gp_Vec(tempXYZ);
}

double IGESGeom_OffsetCurve::StartParameter() const
{
  return theOffsetParam1;
}

double IGESGeom_OffsetCurve::EndParameter() const
{
  return theOffsetParam2;
}

void IGESGeom_OffsetCurve::Parameters(double& TT1, double& TT2) const
{
  TT1 = theOffsetParam1;
  TT2 = theOffsetParam2;
}

bool IGESGeom_OffsetCurve::HasFunction() const
{
  return (!theFunction.IsNull());
}
