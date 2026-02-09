#pragma once

#include <Adaptor3d_Surface.hpp>
#include <math_MultipleVarFunction.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <gp_Pln.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Cone.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>

class Extrema_GlobOptFuncCQuadric : public math_MultipleVarFunction
{
public:
  Standard_EXPORT Extrema_GlobOptFuncCQuadric(const Adaptor3d_Curve* C);

  Standard_EXPORT Extrema_GlobOptFuncCQuadric(const Adaptor3d_Curve* C,
                                              const double           theTf,
                                              const double           theTl);

  Standard_EXPORT Extrema_GlobOptFuncCQuadric(const Adaptor3d_Curve* C, const Adaptor3d_Surface* S);

  Standard_EXPORT void LoadQuad(const Adaptor3d_Surface* S,
                                const double             theUf,
                                const double             theUl,
                                const double             theVf,
                                const double             theVl);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT bool Value(const math_Vector& theX, double& theF) override;

  Standard_EXPORT void QuadricParameters(const math_Vector& theCT, math_Vector& theUV) const;

private:
  bool checkInputData(const math_Vector& X, double& ct);

  void value(double ct, double& F);

  const Adaptor3d_Curve*   myC;
  const Adaptor3d_Surface* myS;
  GeomAbs_SurfaceType      mySType;
  gp_Pln                   myPln;
  gp_Cone                  myCone;
  gp_Cylinder              myCylinder;
  gp_Sphere                mySphere;
  gp_Torus                 myTorus;
  gp_Pnt                   myPTrim[4];

  double myTf;
  double myTl;
  double myUf;
  double myUl;
  double myVf;
  double myVl;
};
