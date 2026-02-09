#include <GeomFill_FunctionGuide.hpp>

#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomFill_SectionLaw.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax3.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <math_Matrix.hpp>
#include <Precision.hpp>

GeomFill_FunctionGuide::GeomFill_FunctionGuide(const occ::handle<GeomFill_SectionLaw>& S,
                                               const occ::handle<Adaptor3d_Curve>&     C,
                                               const double                            Param)
    : TheGuide(C),
      TheLaw(S),
      isconst(false),
      First(0.0),
      Last(0.0),
      TheUonS(Param)
{
  double Tol = Precision::Confusion();
  if (TheLaw->IsConstant(Tol))
  {
    isconst  = true;
    TheConst = TheLaw->ConstantSection();
    First    = TheConst->FirstParameter();
    Last     = TheConst->LastParameter();
  }
  else
  {
    isconst = false;
    TheConst.Nullify();
  }
  TheCurve.Nullify();
}

void GeomFill_FunctionGuide::SetParam(const double,
                                      const gp_Pnt& C,
                                      const gp_XYZ& D,
                                      const gp_XYZ& DX)
{
  Centre = C.XYZ();
  Dir    = D;

  gp_Ax3 Rep(gp::Origin(), gp::DZ(), gp::DX());

  gp_Dir  B2 = DX;
  gp_Ax3  RepTriedre(C, D, B2);
  gp_Trsf Transfo;
  Transfo.SetTransformation(RepTriedre, Rep);

  if (isconst)
  {
    TheCurve = new (Geom_TrimmedCurve)(occ::down_cast<Geom_Curve>(TheConst->Copy()), First, Last);
  }
  else
  {
    int NbPoles, NbKnots, Deg;
    TheLaw->SectionShape(NbPoles, NbKnots, Deg);
    NCollection_Array1<int> Mult(1, NbKnots);
    TheLaw->Mults(Mult);
    NCollection_Array1<double> Knots(1, NbKnots);
    TheLaw->Knots(Knots);
    NCollection_Array1<gp_Pnt> Poles(1, NbPoles);
    NCollection_Array1<double> Weights(1, NbPoles);
    TheLaw->D0(TheUonS, Poles, Weights);
    if (TheLaw->IsRational())
      TheCurve = new (Geom_BSplineCurve)(Poles, Weights, Knots, Mult, Deg, TheLaw->IsUPeriodic());
    else
      TheCurve = new (Geom_BSplineCurve)(Poles, Knots, Mult, Deg, TheLaw->IsUPeriodic());
  }

  gp_Ax1 Axe(C, Dir);
  TheCurve->Transform(Transfo);
  TheSurface = new (Geom_SurfaceOfRevolution)(TheCurve, Axe);
}

int GeomFill_FunctionGuide::NbVariables() const
{
  return 3;
}

int GeomFill_FunctionGuide::NbEquations() const
{
  return 3;
}

bool GeomFill_FunctionGuide::Value(const math_Vector& X, math_Vector& F)
{
  gp_Pnt P, P1;

  TheGuide->D0(X(1), P);
  TheSurface->D0(X(2), X(3), P1);

  F(1) = P.Coord(1) - P1.Coord(1);
  F(2) = P.Coord(2) - P1.Coord(2);
  F(3) = P.Coord(3) - P1.Coord(3);

  return true;
}

bool GeomFill_FunctionGuide::Derivatives(const math_Vector& X, math_Matrix& D)
{
  gp_Pnt P, P1;
  gp_Vec DP, DP1U, DP1V;

  TheGuide->D1(X(1), P, DP);
  TheSurface->D1(X(2), X(3), P1, DP1U, DP1V);

  int i;
  for (i = 1; i <= 3; i++)
  {
    D(i, 1) = DP.Coord(i);
    D(i, 2) = -DP1U.Coord(i);
    D(i, 3) = -DP1V.Coord(i);
  }

  return true;
}

bool GeomFill_FunctionGuide::Values(const math_Vector& X, math_Vector& F, math_Matrix& D)
{
  gp_Pnt P, P1;
  gp_Vec DP, DP1U, DP1V;

  TheGuide->D1(X(1), P, DP);
  TheSurface->D1(X(2), X(3), P1, DP1U, DP1V);

  int i;
  for (i = 1; i <= 3; i++)
  {
    F(i) = P.Coord(i) - P1.Coord(i);

    D(i, 1) = DP.Coord(i);
    D(i, 2) = -DP1U.Coord(i);
    D(i, 3) = -DP1V.Coord(i);
  }

  return true;
}

bool GeomFill_FunctionGuide::DerivT(const math_Vector& X,
                                    const gp_XYZ&      DCentre,
                                    const gp_XYZ&      DDir,
                                    math_Vector&       F)
{
  gp_Pnt P;
  gp_Vec DS;
  DSDT(X(2), X(3), DCentre, DDir, DS);

  TheCurve->D0(X(1), P);

  F(1) = P.Coord(1) - DS.Coord(1);
  F(2) = P.Coord(2) - DS.Coord(2);
  F(3) = P.Coord(3) - DS.Coord(3);

  return true;
}

void GeomFill_FunctionGuide::DSDT(const double  U,
                                  const double  V,
                                  const gp_XYZ& DC,
                                  const gp_XYZ& DDir,
                                  gp_Vec&       DS) const
{

  gp_Pnt Pc;
  TheCurve->D0(V, Pc);

  gp_XYZ &Q = Pc.ChangeCoord(), DQ(0, 0, 0);
  if (!isconst)
  {
    std::cout << "Not implemented" << std::endl;
  }

  Q.Subtract(Centre);
  DQ -= DC;

  gp_XYZ DVcrossCQ;
  DVcrossCQ.SetLinearForm(DDir.Crossed(Q), Dir.Crossed(DQ));
  DVcrossCQ.Multiply(std::sin(U));

  double CosU = std::cos(U);
  gp_XYZ DVdotCQ;
  DVdotCQ.SetLinearForm(DDir.Dot(Q) + Dir.Dot(DQ), Dir, Dir.Dot(Q), DDir);
  DVdotCQ.Add(DVcrossCQ);

  DQ.Multiply(CosU);
  DQ.Add(DVdotCQ);
  DQ.Add(DC);
  DS.SetXYZ(DQ);
}
