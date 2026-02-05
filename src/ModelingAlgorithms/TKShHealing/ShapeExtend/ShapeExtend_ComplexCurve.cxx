#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <ShapeExtend_ComplexCurve.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeExtend_ComplexCurve, Geom_Curve)

//=================================================================================================

ShapeExtend_ComplexCurve::ShapeExtend_ComplexCurve()
{
  myClosed = false;
}

//=================================================================================================

void ShapeExtend_ComplexCurve::Transform(const gp_Trsf& T)
{
  for (int i = 1; i <= NbCurves(); i++)
    Curve(i)->Transform(T);
}

//=================================================================================================

void ShapeExtend_ComplexCurve::D0(const double U, gp_Pnt& P) const
{
  double UOut;
  int    ind = LocateParameter(U, UOut);
  Curve(ind)->D0(UOut, P);
}

//=================================================================================================

void ShapeExtend_ComplexCurve::D1(const double U, gp_Pnt& P, gp_Vec& V1) const
{
  double UOut;
  int    ind = LocateParameter(U, UOut);
  Curve(ind)->D1(UOut, P, V1);
  TransformDN(V1, ind, 1);
}

//=================================================================================================

void ShapeExtend_ComplexCurve::D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const
{
  double UOut;
  int    ind = LocateParameter(U, UOut);
  Curve(ind)->D2(UOut, P, V1, V2);
  TransformDN(V1, ind, 1);
  TransformDN(V2, ind, 2);
}

//=================================================================================================

void ShapeExtend_ComplexCurve::D3(const double U,
                                  gp_Pnt&      P,
                                  gp_Vec&      V1,
                                  gp_Vec&      V2,
                                  gp_Vec&      V3) const
{
  double UOut;
  int    ind = LocateParameter(U, UOut);
  Curve(ind)->D3(UOut, P, V1, V2, V3);
  TransformDN(V1, ind, 1);
  TransformDN(V2, ind, 2);
  TransformDN(V3, ind, 3);
}

//=================================================================================================

gp_Vec ShapeExtend_ComplexCurve::DN(const double U, const int N) const
{
  double UOut;
  int    ind = LocateParameter(U, UOut);
  gp_Vec res = Curve(ind)->DN(UOut, N);
  if (N)
    TransformDN(res, ind, N);
  return res;
}

//=================================================================================================

bool ShapeExtend_ComplexCurve::CheckConnectivity(const double Preci)
{
  int  NbC = NbCurves();
  bool ok  = true;
  for (int i = 1; i < NbC; i++)
  {
    if (i == 1)
      myClosed = Value(FirstParameter()).IsEqual(Value(LastParameter()), Preci);
    ok &= Curve(i)
            ->Value(Curve(i)->LastParameter())
            .IsEqual(Curve(i + 1)->Value(Curve(i + 1)->FirstParameter()), Preci);
  }
#ifdef OCCT_DEBUG
  if (!ok)
    std::cout << "Warning: ShapeExtend_ComplexCurve: not connected in 3d" << std::endl;
#endif
  return ok;
}

//=================================================================================================

void ShapeExtend_ComplexCurve::TransformDN(gp_Vec& V, const int ind, const int N) const
{
  double fact = GetScaleFactor(ind);
  for (int i = 1; i <= N; i++)
    V *= fact;
}
