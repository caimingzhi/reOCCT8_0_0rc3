#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt;

class IGESGeom_Plane : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_Plane();

  Standard_EXPORT void Init(const double                            A,
                            const double                            B,
                            const double                            C,
                            const double                            D,
                            const occ::handle<IGESData_IGESEntity>& aCurve,
                            const gp_XYZ&                           attach,
                            const double                            aSize);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT void Equation(double& A, double& B, double& C, double& D) const;

  Standard_EXPORT void TransformedEquation(double& A, double& B, double& C, double& D) const;

  Standard_EXPORT bool HasBoundingCurve() const;

  Standard_EXPORT bool HasBoundingCurveHole() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> BoundingCurve() const;

  Standard_EXPORT bool HasSymbolAttach() const;

  Standard_EXPORT gp_Pnt SymbolAttach() const;

  Standard_EXPORT gp_Pnt TransformedSymbolAttach() const;

  Standard_EXPORT double SymbolSize() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_Plane, IGESData_IGESEntity)

private:
  double                           theA;
  double                           theB;
  double                           theC;
  double                           theD;
  occ::handle<IGESData_IGESEntity> theCurve;
  gp_XYZ                           theAttach;
  double                           theSize;
};
