#include <Adaptor3d_HSurfaceTool.hpp>
#include <Contap_HContTool.hpp>
#include <Contap_SurfFunction.hpp>
#include <Contap_SurfProps.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Vec.hpp>
#include <math_Matrix.hpp>
#include <StdFail_UndefinedDerivative.hpp>

Contap_SurfFunction::Contap_SurfFunction()
    : myMean(1.),
      myType(Contap_ContourStd),
      myDir(gp_Dir::D::Z),
      myAng(0.0),
      myCosAng(0.),
      tol(1.e-6),
      valf(0.0),
      Usol(0.0),
      Vsol(0.0),
      Fpu(0.0),
      Fpv(0.0),
      tangent(false),
      computed(false),
      derived(false)
{
}

void Contap_SurfFunction::Set(const occ::handle<Adaptor3d_Surface>& S)
{
  mySurf = S;
  int    i;
  int    nbs = Contap_HContTool::NbSamplePoints(S);
  double U, V;
  gp_Vec norm;
  if (nbs > 0)
  {
    myMean = 0.;
    for (i = 1; i <= nbs; i++)
    {
      Contap_HContTool::SamplePoint(S, i, U, V);

      Contap_SurfProps::Normale(S, U, V, solpt, norm);
      myMean = myMean + norm.Magnitude();
    }
    myMean = myMean / ((double)nbs);
  }
  computed = false;
  derived  = false;
}

int Contap_SurfFunction::NbVariables() const
{
  return 2;
}

int Contap_SurfFunction::NbEquations() const
{
  return 1;
}

bool Contap_SurfFunction::Value(const math_Vector& X, math_Vector& F)
{
  Usol = X(1);
  Vsol = X(2);

  gp_Vec norm;
  Contap_SurfProps::Normale(mySurf, Usol, Vsol, solpt, norm);
  switch (myType)
  {
    case Contap_ContourStd:
    {
      F(1) = valf = (norm.Dot(myDir)) / myMean;
    }
    break;
    case Contap_ContourPrs:
    {
      F(1) = valf = (norm.Dot(gp_Vec(myEye, solpt))) / myMean;
    }
    break;
    case Contap_DraftStd:
    {
      F(1) = valf = (norm.Dot(myDir) - myCosAng * norm.Magnitude()) / myMean;
    }
    break;
    default:
    {
    }
  }
  computed = false;
  derived  = false;
  return true;
}

bool Contap_SurfFunction::Derivatives(const math_Vector& X, math_Matrix& Grad)
{

  Usol = X(1);
  Vsol = X(2);

  gp_Vec norm, dnu, dnv;
  Contap_SurfProps::NormAndDn(mySurf, Usol, Vsol, solpt, norm, dnu, dnv);

  switch (myType)
  {
    case Contap_ContourStd:
    {

      Grad(1, 1) = (dnu.Dot(myDir)) / myMean;
      Grad(1, 2) = (dnv.Dot(myDir)) / myMean;
    }
    break;
    case Contap_ContourPrs:
    {
      gp_Vec Ep(myEye, solpt);
      Grad(1, 1) = (dnu.Dot(Ep)) / myMean;
      Grad(1, 2) = (dnv.Dot(Ep)) / myMean;
    }
    break;
    case Contap_DraftStd:
    {

      norm.Normalize();
      Grad(1, 1) = (dnu.Dot(myDir) - myCosAng * dnu.Dot(norm)) / myMean;
      Grad(1, 2) = (dnv.Dot(myDir) - myCosAng * dnv.Dot(norm)) / myMean;
    }
    break;
    case Contap_DraftPrs:
    default:
    {
    }
  }
  Fpu      = Grad(1, 1);
  Fpv      = Grad(1, 2);
  computed = false;
  derived  = true;
  return true;
}

bool Contap_SurfFunction::Values(const math_Vector& X, math_Vector& F, math_Matrix& Grad)
{

  Usol = X(1);
  Vsol = X(2);

  gp_Vec norm, dnu, dnv;
  Contap_SurfProps::NormAndDn(mySurf, Usol, Vsol, solpt, norm, dnu, dnv);

  switch (myType)
  {

    case Contap_ContourStd:
    {
      F(1) = (norm.Dot(myDir)) / myMean;

      Grad(1, 1) = (dnu.Dot(myDir)) / myMean;
      Grad(1, 2) = (dnv.Dot(myDir)) / myMean;
    }
    break;
    case Contap_ContourPrs:
    {
      gp_Vec Ep(myEye, solpt);
      F(1) = (norm.Dot(Ep)) / myMean;

      Grad(1, 1) = (dnu.Dot(Ep)) / myMean;
      Grad(1, 2) = (dnv.Dot(Ep)) / myMean;
    }
    break;
    case Contap_DraftStd:
    {
      F(1) = (norm.Dot(myDir) - myCosAng * norm.Magnitude()) / myMean;
      norm.Normalize();

      Grad(1, 1) = (dnu.Dot(myDir) - myCosAng * dnu.Dot(norm)) / myMean;
      Grad(1, 2) = (dnv.Dot(myDir) - myCosAng * dnv.Dot(norm)) / myMean;
    }
    break;
    case Contap_DraftPrs:
    default:
    {
    }
  }
  valf     = F(1);
  Fpu      = Grad(1, 1);
  Fpv      = Grad(1, 2);
  computed = false;
  derived  = true;
  return true;
}

bool Contap_SurfFunction::IsTangent()
{
  if (!computed)
  {
    computed = true;
    if (!derived)
    {

      gp_Vec norm, dnu, dnv;
      Contap_SurfProps::NormAndDn(mySurf, Usol, Vsol, solpt, norm, dnu, dnv);

      switch (myType)
      {
        case Contap_ContourStd:
        {

          Fpu = (dnu.Dot(myDir)) / myMean;
          Fpv = (dnv.Dot(myDir)) / myMean;
        }
        break;
        case Contap_ContourPrs:
        {
          gp_Vec Ep(myEye, solpt);

          Fpu = (dnu.Dot(Ep)) / myMean;
          Fpv = (dnv.Dot(Ep)) / myMean;
        }
        break;
        case Contap_DraftStd:
        {

          norm.Normalize();
          Fpu = (dnu.Dot(myDir) - myCosAng * dnu.Dot(norm)) / myMean;
          Fpv = (dnv.Dot(myDir) - myCosAng * dnv.Dot(norm)) / myMean;
        }
        break;
        case Contap_DraftPrs:
        default:
        {
        }
      }
      derived = true;
    }
    tangent  = false;
    double D = std::sqrt(Fpu * Fpu + Fpv * Fpv);

    if (D <= gp::Resolution())
    {
      tangent = true;
    }
    else
    {
      d2d = gp_Dir2d(-Fpv, Fpu);
      gp_Vec d1u, d1v;
      Adaptor3d_HSurfaceTool::D1(mySurf, Usol, Vsol, solpt, d1u, d1v);

      gp_XYZ d3dxyz(-Fpv * d1u.XYZ());
      d3dxyz.Add(Fpu * d1v.XYZ());
      d3d.SetXYZ(d3dxyz);

      if (d3d.Magnitude() <= tol)
      {
        tangent = true;
      }
    }
  }
  return tangent;
}
