#pragma once

#include <NCollection_List.hpp>
#include <Standard_DefineAlloc.hpp>

class gp_Cone;
class gp_Cylinder;
class gp_Pln;
class gp_Sphere;

class IntAna_Quadric
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntAna_Quadric();

  Standard_EXPORT IntAna_Quadric(const gp_Pln& P);

  Standard_EXPORT IntAna_Quadric(const gp_Sphere& Sph);

  Standard_EXPORT IntAna_Quadric(const gp_Cylinder& Cyl);

  Standard_EXPORT IntAna_Quadric(const gp_Cone& Cone);

  Standard_EXPORT void SetQuadric(const gp_Pln& P);

  Standard_EXPORT void SetQuadric(const gp_Sphere& Sph);

  Standard_EXPORT void SetQuadric(const gp_Cone& Con);

  Standard_EXPORT void SetQuadric(const gp_Cylinder& Cyl);

  Standard_EXPORT void Coefficients(double& xCXX,
                                    double& xCYY,
                                    double& xCZZ,
                                    double& xCXY,
                                    double& xCXZ,
                                    double& xCYZ,
                                    double& xCX,
                                    double& xCY,
                                    double& xCZ,
                                    double& xCCte) const;

  Standard_EXPORT void NewCoefficients(double&       xCXX,
                                       double&       xCYY,
                                       double&       xCZZ,
                                       double&       xCXY,
                                       double&       xCXZ,
                                       double&       xCYZ,
                                       double&       xCX,
                                       double&       xCY,
                                       double&       xCZ,
                                       double&       xCCte,
                                       const gp_Ax3& Axis) const;

  const NCollection_List<gp_Pnt>& SpecialPoints() const { return mySpecialPoints; }

private:
  double                   CXX;
  double                   CYY;
  double                   CZZ;
  double                   CXY;
  double                   CXZ;
  double                   CYZ;
  double                   CX;
  double                   CY;
  double                   CZ;
  double                   CCte;
  NCollection_List<gp_Pnt> mySpecialPoints;
};
