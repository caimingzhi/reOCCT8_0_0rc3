#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Vec;

class IGESGeom_OffsetCurve : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_OffsetCurve();

  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>& aBaseCurve,
                            const int                               anOffsetType,
                            const occ::handle<IGESData_IGESEntity>& aFunction,
                            const int                               aFunctionCoord,
                            const int                               aTaperedOffsetType,
                            const double                            offDistance1,
                            const double                            arcLength1,
                            const double                            offDistance2,
                            const double                            arcLength2,
                            const gp_XYZ&                           aNormalVec,
                            const double                            anOffsetParam,
                            const double                            anotherOffsetParam);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> BaseCurve() const;

  Standard_EXPORT int OffsetType() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Function() const;

  Standard_EXPORT bool HasFunction() const;

  Standard_EXPORT int FunctionParameter() const;

  Standard_EXPORT int TaperedOffsetType() const;

  Standard_EXPORT double FirstOffsetDistance() const;

  Standard_EXPORT double ArcLength1() const;

  Standard_EXPORT double SecondOffsetDistance() const;

  Standard_EXPORT double ArcLength2() const;

  Standard_EXPORT gp_Vec NormalVector() const;

  Standard_EXPORT gp_Vec TransformedNormalVector() const;

  Standard_EXPORT void Parameters(double& StartParam, double& EndParam) const;

  Standard_EXPORT double StartParameter() const;

  Standard_EXPORT double EndParameter() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_OffsetCurve, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity> theBaseCurve;
  int                              theOffsetType;
  occ::handle<IGESData_IGESEntity> theFunction;
  int                              theFunctionCoord;
  int                              theTaperedOffsetType;
  double                           theOffsetDistance1;
  double                           theArcLength1;
  double                           theOffsetDistance2;
  double                           theArcLength2;
  gp_XYZ                           theNormalVector;
  double                           theOffsetParam1;
  double                           theOffsetParam2;
};
