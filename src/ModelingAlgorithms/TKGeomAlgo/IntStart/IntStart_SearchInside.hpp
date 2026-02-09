#ifndef OCCT_DEBUG
  #define No_Standard_RangeError
  #define No_Standard_OutOfRange
#endif

#include <math_FunctionSetRoot.hpp>
#include <Precision.hpp>
#include <gp_Pnt2d.hpp>

#include <TopAbs_State.hpp>

IntStart_SearchInside::IntStart_SearchInside()
    : done(false)
{
}

IntStart_SearchInside::IntStart_SearchInside(TheFunction&                     Func,
                                             const ThePSurface&               PS,
                                             const occ::handle<TheTopolTool>& T,
                                             const double                     Epsilon)
{

  Perform(Func, PS, T, Epsilon);
}

void IntStart_SearchInside::Perform(TheFunction&                     Func,
                                    const ThePSurface&               PS,
                                    const occ::handle<TheTopolTool>& T,
                                    const double                     Epsilon)
{

  done = false;
  list.Clear();
  double       aBinf[2], aBsup[2], aUVap[2], atoler[2];
  math_Vector  Binf(aBinf, 1, 2), Bsup(aBsup, 1, 2), UVap(aUVap, 1, 2), toler(atoler, 1, 2);
  gp_Pnt       psol;
  bool         testpnt;
  int          i, j, nbpt;
  TopAbs_State situ;
  double       umin, umax, vmin, vmax;
  Binf(1) = umin = ThePSurfaceTool::FirstUParameter(PS);
  Binf(2) = vmin = ThePSurfaceTool::FirstVParameter(PS);
  Bsup(1) = umax = ThePSurfaceTool::LastUParameter(PS);
  Bsup(2) = vmax = ThePSurfaceTool::LastVParameter(PS);

  int NbsampleU = T->NbSamplesU();
  int NbsampleV = T->NbSamplesV();
  int Nbsample  = T->NbSamples();

  double du = Bsup(1) - Binf(1);
  double dv = Bsup(2) - Binf(2);
  du /= (double)NbsampleU * 0.5;
  dv /= (double)NbsampleV * 0.5;

  double toler1 = toler(1) = ThePSurfaceTool::UResolution(PS, Precision::Confusion());
  double toler2 = toler(2) = ThePSurfaceTool::VResolution(PS, Precision::Confusion());
  double Maxtoler1toler2   = toler1;
  if (toler2 > Maxtoler1toler2)
    Maxtoler1toler2 = toler2;

  Maxtoler1toler2 *= 1000;
  if (Maxtoler1toler2 > du * 0.001)
    Maxtoler1toler2 = du * 0.001;
  if (Maxtoler1toler2 > dv * 0.001)
    Maxtoler1toler2 = dv * 0.001;

  Func.Set(PS);
  double Tol = Func.Tolerance();

  math_FunctionSetRoot Rsnld(Func, toler);

  umin += du * 0.01;
  vmin += dv * 0.01;
  umax -= du * 0.01;
  vmax -= dv * 0.01;

  for (i = 1; i <= Nbsample + 12; i++)
  {
    gp_Pnt2d s2d;
    gp_Pnt   s3d;
    bool     nepastester = false;
    if (i <= Nbsample)
    {
      T->SamplePoint(i, s2d, s3d);
      UVap(1) = s2d.X();
      UVap(2) = s2d.Y();

      double u1, v1, u2, v2;
      u1 = Binf(1) = std::max(umin, UVap(1) - du);
      v1 = Binf(2) = std::max(vmin, UVap(2) - dv);
      u2 = Bsup(1) = std::min(umax, UVap(1) + du);
      v2 = Bsup(2) = std::min(vmax, UVap(2) + dv);

      gp_Pnt      Pextrm1 = ThePSurfaceTool::Value(PS, u1, v1);
      gp_Pnt      Pextrm2 = ThePSurfaceTool::Value(PS, u2, v2);
      double      aValf[1];
      math_Vector Valf(aValf, 1, 1);
      Func.Value(UVap, Valf);
      double rvalf  = Valf(1);
      double DistPP = Pextrm1.SquareDistance(Pextrm2);
      if (rvalf * rvalf > 3.0 * DistPP)
      {
        nepastester = true;
      }
    }
    else
    {
      if (i == Nbsample + 1)
      {
        s2d.SetCoord(umin + du * 0.02, vmin + dv * 0.02);
      }
      else if (i == Nbsample + 2)
      {
        s2d.SetCoord(umax - du * 0.02, vmin + dv * 0.02);
      }
      else if (i == Nbsample + 3)
      {
        s2d.SetCoord(umin + du * 0.02, vmax - dv * 0.02);
      }
      else if (i == Nbsample + 4)
      {
        s2d.SetCoord(umax - du * 0.02, vmax - dv * 0.02);
      }

      else if (i == Nbsample + 5)
      {
        s2d.SetCoord(umin + du * 0.02, vmin + dv * 0.02);
      }
      else if (i == Nbsample + 6)
      {
        s2d.SetCoord(umax - du * 0.02, vmin + dv * 0.02);
      }
      else if (i == Nbsample + 7)
      {
        s2d.SetCoord(umin + du * 0.02, vmax - dv * 0.02);
      }
      else if (i == Nbsample + 8)
      {
        s2d.SetCoord(umax - du * 0.02, vmax - dv * 0.02);
      }

      else if (i == Nbsample + 9)
      {
        s2d.SetCoord(umin + du * 0.005, vmin + dv * 0.005);
      }
      else if (i == Nbsample + 10)
      {
        s2d.SetCoord(umax - du * 0.005, vmin + dv * 0.005);
      }
      else if (i == Nbsample + 11)
      {
        s2d.SetCoord(umin + du * 0.005, vmax - dv * 0.005);
      }
      else
      {
        s2d.SetCoord(umax - du * 0.005, vmax - dv * 0.005);
      }

      UVap(1) = s2d.X();
      UVap(2) = s2d.Y();

      Binf(1) = std::max(umin, UVap(1) - du);
      Binf(2) = std::max(vmin, UVap(2) - dv);
      Bsup(1) = std::min(umax, UVap(1) + du);
      Bsup(2) = std::min(vmax, UVap(2) + dv);
    }

    if (nepastester == false)
    {
      Rsnld.Perform(Func, UVap, Binf, Bsup);
      if (Rsnld.IsDone())
      {
        if (std::abs(Func.Root()) <= Tol)
        {
          if (!Func.IsTangent())
          {
            psol = Func.Point();
            Rsnld.Root(UVap);

            j       = 1;
            nbpt    = list.Length();
            testpnt = (j <= nbpt);

            while (testpnt)
            {
              const IntSurf_InteriorPoint& IPj = list(j);
              const gp_Pnt&                Pj  = IPj.Value();
              if ((std::abs(Pj.X() - psol.X()) <= Epsilon)
                  && (std::abs(Pj.Y() - psol.Y()) <= Epsilon)
                  && (std::abs(Pj.Z() - psol.Z()) <= Epsilon)
                  && (std::abs(UVap(1) - IPj.UParameter()) <= toler1)
                  && (std::abs(UVap(2) - IPj.VParameter()) <= toler2))
              {
                testpnt = false;
              }
              else
              {
                j       = j + 1;
                testpnt = (j <= nbpt);
              }
            }
            if (j > nbpt)
            {

              situ = T->Classify(gp_Pnt2d(UVap(1), UVap(2)), Maxtoler1toler2, false);
              if (situ == TopAbs_IN)
              {
                list.Append(IntSurf_InteriorPoint(psol,
                                                  UVap(1),
                                                  UVap(2),
                                                  Func.Direction3d(),
                                                  Func.Direction2d()));
              }
            }
          }
        }
      }
    }
  }

  done = true;
}

void IntStart_SearchInside::Perform(TheFunction&       Func,
                                    const ThePSurface& PS,
                                    const double       UStart,
                                    const double       VStart)
{
  done = false;
  list.Clear();
  math_Vector Binf(1, 2), Bsup(1, 2), toler(1, 2);

  Binf(1) = ThePSurfaceTool::FirstUParameter(PS);
  Binf(2) = ThePSurfaceTool::FirstVParameter(PS);
  Bsup(1) = ThePSurfaceTool::LastUParameter(PS);
  Bsup(2) = ThePSurfaceTool::LastVParameter(PS);

  toler(1) = ThePSurfaceTool::UResolution(PS, Precision::Confusion());
  toler(2) = ThePSurfaceTool::VResolution(PS, Precision::Confusion());

  if (UStart - Binf(1) > -toler(1) && UStart - Bsup(1) < toler(1) && VStart - Binf(2) > -toler(2)
      && VStart - Bsup(2) < toler(2))
  {

    Func.Set(PS);
    math_Vector UVap(1, 2);
    UVap(1) = UStart;
    UVap(2) = VStart;

    math_FunctionSetRoot Rsnld(Func, toler);
    Rsnld.Perform(Func, UVap, Binf, Bsup);
    if (Rsnld.IsDone())
    {
      double tol  = Func.Tolerance();
      double valf = Func.Root();
      if (std::abs(valf) <= tol && !Func.IsTangent())
      {
        const gp_Pnt& psol = Func.Point();
        Rsnld.Root(UVap);
        IntSurf_InteriorPoint intp(psol, UVap(1), UVap(2), Func.Direction3d(), Func.Direction2d());
        list.Append(intp);
      }
    }
  }

  done = true;
}
