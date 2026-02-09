#include <ElCLib.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2dHatch_Intersector.hpp>
#include <Geom2dLProp_CLProps2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <Precision.hpp>

Geom2dHatch_Intersector::Geom2dHatch_Intersector()
    : myConfusionTolerance(0.0),
      myTangencyTolerance(0.0)
{
}

void Geom2dHatch_Intersector::Perform(const gp_Lin2d&            L,
                                      const double               P,
                                      const double               Tol,
                                      const Geom2dAdaptor_Curve& C)
{

  IntRes2d_Domain DL;
  if (P != RealLast())
    DL.SetValues(L.Location(), 0., Tol, ElCLib::Value(P, L), P, Tol);
  else
    DL.SetValues(L.Location(), 0., Tol, true);

  IntRes2d_Domain DE(C.Value(C.FirstParameter()),
                     C.FirstParameter(),
                     Precision::PIntersection(),
                     C.Value(C.LastParameter()),
                     C.LastParameter(),
                     Precision::PIntersection());

  occ::handle<Geom2d_Line> GL = new Geom2d_Line(L);
  Geom2dAdaptor_Curve      CGA(GL);
  void*                    ptrpoureviterlesproblemesdeconst = (void*)(&C);

  Geom2dInt_GInter Inter(CGA,
                         DL,
                         *((Geom2dAdaptor_Curve*)ptrpoureviterlesproblemesdeconst),
                         DE,
                         Precision::PConfusion(),
                         Precision::PIntersection());
  this->SetValues(Inter);
}

void Geom2dHatch_Intersector::LocalGeometry(const Geom2dAdaptor_Curve& E,
                                            const double               U,
                                            gp_Dir2d&                  Tang,
                                            gp_Dir2d&                  Norm,
                                            double&                    C) const
{

  Geom2dLProp_CLProps2d Prop(E.Curve(), U, 2, Precision::PConfusion());

  if (!Prop.IsTangentDefined())
    return;

  Prop.Tangent(Tang);
  C = Prop.Curvature();
  if (C > Precision::PConfusion() && C < RealLast())
    Prop.Normal(Norm);
  else
    Norm.SetCoord(Tang.Y(), -Tang.X());
}
