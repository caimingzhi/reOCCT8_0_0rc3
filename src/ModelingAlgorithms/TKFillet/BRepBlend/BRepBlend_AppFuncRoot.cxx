#include <Blend_AppFunction.hpp>
#include <BRepBlend_AppFuncRoot.hpp>
#include <BRepBlend_Line.hpp>
#include <gp_Pnt.hpp>
#include <math_FunctionSetRoot.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepBlend_AppFuncRoot, Approx_SweepFunction)

BRepBlend_AppFuncRoot::BRepBlend_AppFuncRoot(occ::handle<BRepBlend_Line>& Line,
                                             Blend_AppFunction&           Func,
                                             const double                 Tol3d,
                                             const double                 Tol2d)
    : myLine(Line),
      myFunc(&Func),
      myTolerance(1, Func.NbVariables()),
      X1(1, Func.NbVariables()),
      X2(1, Func.NbVariables()),
      XInit(1, Func.NbVariables()),
      Sol(1, Func.NbVariables())
{
  int NbPoles, NbKnots, Degree, NbPoles2d;
  int ii;

  Func.GetTolerance(myTolerance, Tol3d);
  int dim = Func.NbVariables();
  for (ii = 1; ii <= dim; ii++)
  {
    if (myTolerance(ii) > Tol2d)
    {
      myTolerance(ii) = Tol2d;
    }
  }

  Func.GetShape(NbPoles, NbKnots, Degree, NbPoles2d);

  if (Func.IsRational())
  {
    double Xmax = -1.e100, Xmin = 1.e100, Ymax = -1.e100, Ymin = 1.e100, Zmax = -1.e100,
           Zmin = 1.e100;
    Blend_Point P;
    for (ii = 1; ii <= myLine->NbPoints(); ii++)
    {
      P    = myLine->Point(ii);
      Xmax = std::max(std::max(P.PointOnS1().X(), P.PointOnS2().X()), Xmax);
      Xmin = std::min(std::min(P.PointOnS1().X(), P.PointOnS2().X()), Xmin);
      Ymax = std::max(std::max(P.PointOnS1().Y(), P.PointOnS2().Y()), Ymax);
      Ymin = std::min(std::min(P.PointOnS1().Y(), P.PointOnS2().Y()), Ymin);
      Zmax = std::max(std::max(P.PointOnS1().Z(), P.PointOnS2().Z()), Zmax);
      Zmin = std::min(std::min(P.PointOnS1().Z(), P.PointOnS2().Z()), Zmin);

      myBary.SetCoord((Xmax + Xmin) / 2, (Ymax + Ymin) / 2, (Zmax + Zmin) / 2);
    }
  }
  else
  {
    myBary.SetCoord(0, 0, 0);
  }
}

bool BRepBlend_AppFuncRoot::D0(const double Param,
                               const double,
                               const double,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<double>&   Weigths)
{
  bool               Ok   = true;
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  Ok                      = SearchPoint(*Func, Param, myPnt);

  if (Ok)
    (*Func).Section(myPnt, Poles, Poles2d, Weigths);
  return Ok;
}

bool BRepBlend_AppFuncRoot::D1(const double Param,
                               const double,
                               const double,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Vec>&   DPoles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<gp_Vec2d>& DPoles2d,
                               NCollection_Array1<double>&   Weigths,
                               NCollection_Array1<double>&   DWeigths)
{
  bool               Ok   = true;
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;

  Ok = SearchPoint(*Func, Param, myPnt);

  if (Ok)
  {
    Ok = (*Func).Section(myPnt, Poles, DPoles, Poles2d, DPoles2d, Weigths, DWeigths);
  }

  return Ok;
}

bool BRepBlend_AppFuncRoot::D2(const double Param,
                               const double,
                               const double,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Vec>&   DPoles,
                               NCollection_Array1<gp_Vec>&   D2Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<gp_Vec2d>& DPoles2d,
                               NCollection_Array1<gp_Vec2d>& D2Poles2d,
                               NCollection_Array1<double>&   Weigths,
                               NCollection_Array1<double>&   DWeigths,
                               NCollection_Array1<double>&   D2Weigths)
{
  bool               Ok   = true;
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;

  Ok = SearchPoint(*Func, Param, myPnt);
  if (Ok)
  {
    Ok = (*Func).Section(myPnt,
                         Poles,
                         DPoles,
                         D2Poles,
                         Poles2d,
                         DPoles2d,
                         D2Poles2d,
                         Weigths,
                         DWeigths,
                         D2Weigths);
  }
  return Ok;
}

int BRepBlend_AppFuncRoot::Nb2dCurves() const
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  int                i, j, k, nbpol2d;
  (*Func).GetShape(i, j, k, nbpol2d);
  return nbpol2d;
}

void BRepBlend_AppFuncRoot::SectionShape(int& NbPoles, int& NbKnots, int& Degree) const
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  int                ii;
  (*Func).GetShape(NbPoles, NbKnots, Degree, ii);
}

void BRepBlend_AppFuncRoot::Knots(NCollection_Array1<double>& TKnots) const
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  Func->Knots(TKnots);
}

void BRepBlend_AppFuncRoot::Mults(NCollection_Array1<int>& TMults) const
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  Func->Mults(TMults);
}

bool BRepBlend_AppFuncRoot::IsRational() const
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  return (*Func).IsRational();
}

int BRepBlend_AppFuncRoot::NbIntervals(const GeomAbs_Shape S) const
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  return Func->NbIntervals(S);
}

void BRepBlend_AppFuncRoot::Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape S) const
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  Func->Intervals(T, S);
}

void BRepBlend_AppFuncRoot::SetInterval(const double First, const double Last)
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  Func->Set(First, Last);
}

void BRepBlend_AppFuncRoot::Resolution(const int    Index,
                                       const double Tol,
                                       double&      TolU,
                                       double&      TolV) const
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  Func->Resolution(Index, Tol, TolU, TolV);
}

void BRepBlend_AppFuncRoot::GetTolerance(const double                BoundTol,
                                         const double                SurfTol,
                                         const double                AngleTol,
                                         NCollection_Array1<double>& Tol3d) const
{
  int                ii;
  math_Vector        V3d(1, Tol3d.Length()), V1d(1, Tol3d.Length());
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;

  Func->GetTolerance(BoundTol, SurfTol, AngleTol, V3d, V1d);
  for (ii = 1; ii <= Tol3d.Length(); ii++)
    Tol3d(ii) = V3d(ii);
}

void BRepBlend_AppFuncRoot::SetTolerance(const double Tol3d, const double Tol2d)
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  int                ii, dim = Func->NbVariables();
  Func->GetTolerance(myTolerance, Tol3d);
  for (ii = 1; ii <= dim; ii++)
  {
    if (myTolerance(ii) > Tol2d)
    {
      myTolerance(ii) = Tol2d;
    }
  }
}

gp_Pnt BRepBlend_AppFuncRoot::BarycentreOfSurf() const
{
  return myBary;
}

double BRepBlend_AppFuncRoot::MaximalSection() const
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  return Func->GetSectionSize();
}

void BRepBlend_AppFuncRoot::GetMinimalWeight(NCollection_Array1<double>& Weigths) const
{
  Blend_AppFunction* Func = (Blend_AppFunction*)myFunc;
  Func->GetMinimalWeight(Weigths);
}

bool BRepBlend_AppFuncRoot::SearchPoint(Blend_AppFunction& Func,
                                        const double       Param,
                                        Blend_Point&       Pnt)
{
  bool Trouve;
  int  dim = Func.NbVariables();

  int    I1 = 1, I2 = myLine->NbPoints(), Index;
  double t1, t2;

  if (Param < myLine->Point(I1).Parameter())
  {
    return false;
  }
  if (Param > myLine->Point(I2).Parameter())
  {
    return false;
  }

  Trouve = SearchLocation(Param, I1, I2, Index);

  if (Trouve)
  {
    Pnt = myLine->Point(Index);
    Vec(XInit, Pnt);
  }
  else
  {

    Pnt = myLine->Point(Index);
    Vec(X1, Pnt);
    t1 = Pnt.Parameter();

    Pnt = myLine->Point(Index + 1);
    Vec(X2, Pnt);
    t2 = Pnt.Parameter();

    double Parammt1 = (Param - t1) / (t2 - t1);
    double t2mParam = (t2 - Param) / (t2 - t1);
    for (int i = 1; i <= dim; i++)
    {
      XInit(i) = X2(i) * Parammt1 + X1(i) * t2mParam;
    }
  }

  Func.Set(Param);
  Func.GetBounds(X1, X2);
  math_FunctionSetRoot rsnld(Func, myTolerance, 30);

  rsnld.Perform(Func, XInit, X1, X2);

  if (!rsnld.IsDone())
  {
#ifdef BREPBLEND_DEB
    std::cout << "AppFunc : RNLD Not done en t = " << Param << std::endl;
#endif
    return false;
  }
  rsnld.Root(Sol);

  Point(Func, Param, Sol, Pnt);

  if ((!Trouve) && (rsnld.NbIterations() > 3))
  {
#ifdef OCCT_DEBUG
    std::cout << "Evaluation in t = " << Param << "given" << std::endl;
    rsnld.Dump(std::cout);
#endif
    myLine->InsertBefore(Index + 1, Pnt);
  }
  return true;
}

bool BRepBlend_AppFuncRoot::SearchLocation(const double Param,
                                           const int    FirstIndex,
                                           const int    LastIndex,
                                           int&         ParamIndex) const
{
  int    Ideb = FirstIndex, Ifin = LastIndex, Idemi;
  double Valeur;

  Valeur = myLine->Point(Ideb).Parameter();
  if (Param == Valeur)
  {
    ParamIndex = Ideb;
    return true;
  }

  Valeur = myLine->Point(Ifin).Parameter();
  if (Param == Valeur)
  {
    ParamIndex = Ifin;
    return true;
  }

  while (Ideb + 1 != Ifin)
  {
    Idemi  = (Ideb + Ifin) / 2;
    Valeur = myLine->Point(Idemi).Parameter();
    if (Valeur < Param)
    {
      Ideb = Idemi;
    }
    else
    {
      if (Valeur > Param)
      {
        Ifin = Idemi;
      }
      else
      {
        ParamIndex = Idemi;
        return true;
      }
    }
  }

  ParamIndex = Ideb;
  return false;
}
