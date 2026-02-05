#include <Contap_ArcFunction.hpp>
#include <Contap_HContTool.hpp>
#include <Contap_HCurve2dTool.hpp>
#include <Contap_SurfProps.hpp>
#include <gp_Dir.hpp>
#include <IntSurf_Quadric.hpp>

Contap_ArcFunction::Contap_ArcFunction()
    : myMean(1.),
      myType(Contap_ContourStd),
      myDir(gp_Dir::D::Z),
      myCosAng(0.0)
{
}

void Contap_ArcFunction::Set(const occ::handle<Adaptor3d_Surface>& S)
{
  mySurf = S;
  int    i;
  int    nbs = Contap_HContTool::NbSamplePoints(S);
  double U, V;
  //  gp_Vec d1u,d1v;
  gp_Vec norm;
  if (nbs > 0)
  {
    myMean = 0.;
    for (i = 1; i <= nbs; i++)
    {
      Contap_HContTool::SamplePoint(S, i, U, V);
      //      Adaptor3d_HSurfaceTool::D1(S,U,V,solpt,d1u,d1v);
      //      myMean = myMean + d1u.Crossed(d1v).Magnitude();
      Contap_SurfProps::Normale(S, U, V, solpt, norm);
      myMean = myMean + norm.Magnitude();
    }
    myMean = myMean / ((double)nbs);
  }
}

bool Contap_ArcFunction::Value(const double U, double& F)
{
  // gp_Vec d1u,d1v;
  gp_Pnt2d pt2d(Contap_HCurve2dTool::Value(myArc, U));
  //  Adaptor3d_HSurfaceTool::D1(mySurf,pt2d.X(),pt2d.Y(),solpt,d1u,d1v);
  //  gp_Vec norm(d1u.Crossed(d1v));
  gp_Vec norm;
  Contap_SurfProps::Normale(mySurf, pt2d.X(), pt2d.Y(), solpt, norm);

  switch (myType)
  {
    case Contap_ContourStd:
    {
      F = (norm.Dot(myDir)) / myMean;
    }
    break;
    case Contap_ContourPrs:
    {
      F = (norm.Dot(gp_Vec(myEye, solpt))) / myMean;
    }
    break;
    case Contap_DraftStd:
    {
      F = (norm.Dot(myDir) - myCosAng * norm.Magnitude()) / myMean;
    }
    break;
    case Contap_DraftPrs:
    default:
    {
    }
  }
  return true;
}

bool Contap_ArcFunction::Derivative(const double U, double& D)
{
  gp_Pnt2d pt2d;
  gp_Vec2d d2d;
  double   dfu = 0., dfv = 0.;
  //  gp_Vec d1u,d1v,d2u,d2v,d2uv;
  Contap_HCurve2dTool::D1(myArc, U, pt2d, d2d);
  //  Adaptor3d_HSurfaceTool::D2(mySurf,pt2d.X(),pt2d.Y(),solpt,d1u,d1v,d2u,d2v,d2uv);
  gp_Vec norm, dnu, dnv;
  Contap_SurfProps::NormAndDn(mySurf, pt2d.X(), pt2d.Y(), solpt, norm, dnu, dnv);

  switch (myType)
  {
    case Contap_ContourStd:
    {
      //      dfu = ((d2u.Crossed(d1v) + d1u.Crossed(d2uv)).Dot(myDir))/myMean;
      //      dfv = ((d2uv.Crossed(d1v) + d1u.Crossed(d2v)).Dot(myDir))/myMean;
      dfu = (dnu.Dot(myDir)) / myMean;
      dfv = (dnv.Dot(myDir)) / myMean;
    }
    break;
    case Contap_ContourPrs:
    {
      gp_Vec Ep(myEye, solpt);
      //      dfu = ((d2u.Crossed(d1v) + d1u.Crossed(d2uv)).Dot(Ep))/myMean;
      //      dfv = ((d2uv.Crossed(d1v) + d1u.Crossed(d2v)).Dot(Ep))/myMean;
      dfu = (dnu.Dot(Ep)) / myMean;
      dfv = (dnv.Dot(Ep)) / myMean;
    }
    break;
    case Contap_DraftStd:
    {
      /*
      gp_Vec norm(d1u.Crossed(d1v).Normalized());
      gp_Vec dnorm(d2u.Crossed(d1v) + d1u.Crossed(d2uv));
      dfu = (dnorm.Dot(myDir)-myCosAng*dnorm.Dot(norm))/myMean;
      dnorm = d2uv.Crossed(d1v) + d1u.Crossed(d2v);
      dfv = (dnorm.Dot(myDir)-myCosAng*dnorm.Dot(norm))/myMean;
      */
      norm.Normalize();
      dfu = (dnu.Dot(myDir) - myCosAng * dnu.Dot(norm)) / myMean;
      dfv = (dnv.Dot(myDir) - myCosAng * dnv.Dot(norm)) / myMean;
    }
    break;
    case Contap_DraftPrs:
    default:
    {
    }
  }
  D = d2d.X() * dfu + d2d.Y() * dfv;
  return true;
}

bool Contap_ArcFunction::Values(const double U, double& F, double& D)
{
  gp_Pnt2d pt2d;
  gp_Vec2d d2d;
  double   dfu = 0., dfv = 0.;
  // gp_Vec d1u,d1v,d2u,d2v,d2uv;
  Contap_HCurve2dTool::D1(myArc, U, pt2d, d2d);
  //  Adaptor3d_HSurfaceTool::D2(mySurf,pt2d.X(),pt2d.Y(),solpt,d1u,d1v,d2u,d2v,d2uv);
  //  gp_Vec norm(d1u.Crossed(d1v));
  gp_Vec norm, dnu, dnv;
  Contap_SurfProps::NormAndDn(mySurf, pt2d.X(), pt2d.Y(), solpt, norm, dnu, dnv);

  switch (myType)
  {
    case Contap_ContourStd:
    {
      F = (norm.Dot(myDir)) / myMean;
      //      dfu = ((d2u.Crossed(d1v) + d1u.Crossed(d2uv)).Dot(myDir))/myMean;
      //      dfv = ((d2uv.Crossed(d1v) + d1u.Crossed(d2v)).Dot(myDir))/myMean;
      dfu = (dnu.Dot(myDir)) / myMean;
      dfv = (dnv.Dot(myDir)) / myMean;
    }
    break;
    case Contap_ContourPrs:
    {
      gp_Vec Ep(myEye, solpt);
      F = (norm.Dot(Ep)) / myMean;
      //      dfu = ((d2u.Crossed(d1v) + d1u.Crossed(d2uv)).Dot(Ep))/myMean;
      //      dfv = ((d2uv.Crossed(d1v) + d1u.Crossed(d2v)).Dot(Ep))/myMean;
      dfu = (dnu.Dot(Ep)) / myMean;
      dfv = (dnv.Dot(Ep)) / myMean;
    }
    break;
    case Contap_DraftStd:
    {
      F = (norm.Dot(myDir) - myCosAng * norm.Magnitude()) / myMean;
      norm.Normalize();
      /*
      gp_Vec dnorm(d2u.Crossed(d1v) + d1u.Crossed(d2uv));
      dfu = (dnorm.Dot(myDir)-myCosAng*dnorm.Dot(norm))/myMean;
      dnorm = d2uv.Crossed(d1v) + d1u.Crossed(d2v);
      dfv = (dnorm.Dot(myDir)-myCosAng*dnorm.Dot(norm))/myMean;
      */
      dfu = (dnu.Dot(myDir) - myCosAng * dnu.Dot(norm)) / myMean;
      dfv = (dnv.Dot(myDir) - myCosAng * dnv.Dot(norm)) / myMean;
    }
    break;
    case Contap_DraftPrs:
    default:
    {
    }
  }

  D = d2d.X() * dfu + d2d.Y() * dfv;
  return true;
}

int Contap_ArcFunction::GetStateNumber()
{
  seqpt.Append(solpt);
  return seqpt.Length();
}

int Contap_ArcFunction::NbSamples() const
{
  return std::max(std::max(Contap_HContTool::NbSamplesU(mySurf, 0., 0.),
                           Contap_HContTool::NbSamplesV(mySurf, 0., 0.)),
                  Contap_HContTool::NbSamplesOnArc(myArc));
}

// modified by NIZNHY-PKV Thu Mar 29 16:53:07 2001f

//=================================================================================================

const IntSurf_Quadric& Contap_ArcFunction::Quadric() const
{
  return (myQuad);
}

// modified by NIZNHY-PKV Thu Mar 29 16:53:09 2001t
