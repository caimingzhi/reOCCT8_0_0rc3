#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt2d;
class gp_Pnt;
class gp_Dir;

class IGESGeom_ConicArc : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_ConicArc();

  Standard_EXPORT void Init(const double A,
                            const double B,
                            const double C,
                            const double D,
                            const double E,
                            const double F,
                            const double ZT,
                            const gp_XY& aStart,
                            const gp_XY& anEnd);

  Standard_EXPORT bool OwnCorrect();

  Standard_EXPORT int ComputedFormNumber() const;

  Standard_EXPORT void Equation(double& A, double& B, double& C, double& D, double& E, double& F)
    const;

  Standard_EXPORT double ZPlane() const;

  Standard_EXPORT gp_Pnt2d StartPoint() const;

  Standard_EXPORT gp_Pnt TransformedStartPoint() const;

  Standard_EXPORT gp_Pnt2d EndPoint() const;

  Standard_EXPORT gp_Pnt TransformedEndPoint() const;

  Standard_EXPORT bool IsFromEllipse() const;

  Standard_EXPORT bool IsFromParabola() const;

  Standard_EXPORT bool IsFromHyperbola() const;

  Standard_EXPORT bool IsClosed() const;

  Standard_EXPORT gp_Dir Axis() const;

  Standard_EXPORT gp_Dir TransformedAxis() const;

  Standard_EXPORT void Definition(gp_Pnt& Center,
                                  gp_Dir& MainAxis,
                                  double& rmin,
                                  double& rmax) const;

  Standard_EXPORT void TransformedDefinition(gp_Pnt& Center,
                                             gp_Dir& MainAxis,
                                             double& rmin,
                                             double& rmax) const;

  Standard_EXPORT void ComputedDefinition(double& Xcen,
                                          double& Ycen,
                                          double& Xax,
                                          double& Yax,
                                          double& Rmin,
                                          double& Rmax) const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_ConicArc, IGESData_IGESEntity)

private:
  double theA;
  double theB;
  double theC;
  double theD;
  double theE;
  double theF;
  double theZT;
  gp_XY  theStart;
  gp_XY  theEnd;
};
