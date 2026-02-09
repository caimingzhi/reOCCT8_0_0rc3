

#include <ElCLib.hpp>
#include <GccAna_Circ2dTanOnRad.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedLin.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <Standard_NegativeValue.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

GccAna_Circ2dTanOnRad::GccAna_Circ2dTanOnRad(const GccEnt_QualifiedLin& Qualified1,
                                             const gp_Lin2d&            OnLine,
                                             const double               Radius,
                                             const double               Tolerance)
    : cirsol(1, 2),
      qualifier1(1, 2),
      TheSame1(1, 2),
      pnttg1sol(1, 2),
      pntcen3(1, 2),
      par1sol(1, 2),
      pararg1(1, 2),
      parcen3(1, 2)
{

  double   Tol = std::abs(Tolerance);
  gp_Dir2d dirx(gp_Dir2d::D::X);
  WellDone = false;
  NbrSol   = 0;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsOutside() || Qualified1.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }
  int                     nbsol = 0;
  NCollection_Array1<int> eps(1, 2);
  gp_Lin2d                L1 = Qualified1.Qualified();
  gp_Pnt2d                origin1(L1.Location());
  gp_Dir2d                dir1(L1.Direction());
  gp_Dir2d                normL1(-dir1.Y(), dir1.X());

  if (Radius < 0.0)
  {
    throw Standard_NegativeValue();
  }
  else if ((OnLine.Direction()).IsParallel(dir1, Tol))
  {
    WellDone = true;
  }
  else
  {
    if (Qualified1.IsEnclosed())
    {

      eps(1) = -1;
      nbsol  = 1;
    }
    else if (Qualified1.IsOutside())
    {

      eps(1) = 1;
      nbsol  = 1;
    }
    else
    {

      eps(1) = 1;
      eps(2) = -1;
      nbsol  = 2;
    }
    double dx1 = dir1.X();
    double dy1 = dir1.Y();
    double lx1 = origin1.X();
    double ly1 = origin1.Y();
    for (int j = 1; j <= nbsol; j++)
    {
      gp_Lin2d L1para(gp_Pnt2d(lx1 + eps(j) * Radius * dy1, ly1 - eps(j) * Radius * dx1), dir1);
      IntAna2d_AnaIntersection Intp(OnLine, L1para);
      if (Intp.IsDone())
      {
        if (!Intp.IsEmpty())
        {
          for (int i = 1; i <= Intp.NbPoints(); i++)
          {
            NbrSol++;
            gp_Pnt2d Center(Intp.Point(i).Value());
            cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius);

            gp_Dir2d dc1(origin1.XY() - Center.XY());
            if (!Qualified1.IsUnqualified())
            {
              qualifier1(NbrSol) = Qualified1.Qualifier();
            }
            else if (dc1.Dot(normL1) > 0.0)
            {
              qualifier1(NbrSol) = GccEnt_outside;
            }
            else
            {
              qualifier1(NbrSol) = GccEnt_enclosed;
            }
            TheSame1(NbrSol) = 0;
            if (gp_Vec2d(Center, origin1).Dot(gp_Dir2d(-dy1, dx1)) > 0.0)
            {
              pnttg1sol(NbrSol) = gp_Pnt2d(Center.XY() + Radius * gp_XY(-dy1, dx1));
              pntcen3(NbrSol)   = cirsol(1).Location();
            }
            else
            {
              pnttg1sol(NbrSol) = gp_Pnt2d(Center.XY() - Radius * gp_XY(-dy1, dx1));
              pntcen3(NbrSol)   = cirsol(1).Location();
            }
            par1sol(NbrSol) = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
            pararg1(NbrSol) = ElCLib::Parameter(L1, pnttg1sol(NbrSol));
            parcen3(NbrSol) = ElCLib::Parameter(OnLine, pntcen3(NbrSol));
          }
        }
        WellDone = true;
      }
    }
  }
}
