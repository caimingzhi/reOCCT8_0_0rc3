#include <BRepAdaptor_Surface.hpp>
#include <BRepClass3d_Intersector3d.hpp>
#include <BRepClass_FaceClassifier.hpp>
#include <Geom_Line.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <IntCurveSurface_HInter.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <TopoDS_Face.hpp>

//============================================================================
BRepClass3d_Intersector3d::BRepClass3d_Intersector3d()
    : U(0.0),
      V(0.0),
      W(0.0),
      done(false),
      hasapoint(false),
      state(TopAbs_UNKNOWN)
{
}

//============================================================================
void BRepClass3d_Intersector3d::Perform(const gp_Lin& L,
                                        const double /*Prm*/,
                                        const double       Tol,
                                        const TopoDS_Face& Face)
{

  IntCurveSurface_HInter   HICS;
  BRepAdaptor_Surface      surface;
  BRepClass_FaceClassifier classifier2d;

  occ::handle<Geom_Line> geomline = new Geom_Line(L);
  GeomAdaptor_Curve      LL(geomline);

  surface.Initialize(Face, true);

  const bool   IsUPer  = surface.IsUPeriodic();
  const bool   IsVPer  = surface.IsVPeriodic();
  const double uperiod = IsUPer ? surface.UPeriod() : 0.0;
  const double vperiod = IsVPer ? surface.VPeriod() : 0.0;

  double U1 = surface.FirstUParameter();
  double U2 = surface.LastUParameter();
  double V1 = surface.FirstVParameter();
  double V2 = surface.LastVParameter();

  //--
  occ::handle<GeomAdaptor_Curve>   HLL      = new GeomAdaptor_Curve(LL);
  occ::handle<BRepAdaptor_Surface> Hsurface = new BRepAdaptor_Surface(surface);
  //--
  HICS.Perform(HLL, Hsurface);

  W = RealLast();
  if (HICS.IsDone())
  {
    for (int index = HICS.NbPoints(); index >= 1; index--)
    {
      gp_Pnt2d Puv(HICS.Point(index).U(), HICS.Point(index).V());

      int N1 = 0;
      int N2 = 0;

      double X = Puv.X();
      double Y = Puv.Y();

      if (IsUPer)
      {
        if (X > U2)
        {
          N1 = RealToInt((X - U1) / uperiod);
        }
        if (X < U1)
        {
          N1 = RealToInt((X - U2) / uperiod);
        }
        Puv.SetX(X - uperiod * N1);
      }

      if (IsVPer)
      {
        if (Y > V2)
        {
          N2 = RealToInt((Y - V1) / vperiod);
        }
        if (Y < V1)
        {
          N2 = RealToInt((Y - V2) / vperiod);
        }
        Puv.SetY(Y - vperiod * N2);
      }

      classifier2d.Perform(Face, Puv, Tol);
      TopAbs_State currentstate = classifier2d.State();
      if (currentstate == TopAbs_IN || currentstate == TopAbs_ON)
      {
        const IntCurveSurface_IntersectionPoint& HICSPoint = HICS.Point(index);
        double                                   HICSW     = HICSPoint.W();
        //  Modified by skv - Fri Mar  4 12:07:34 2005 OCC7966 Begin
        if ((W > HICSW) && (HICSW > -Tol))
        {
          // 	if(W > HICSW) {
          //  Modified by skv - Fri Mar  4 12:07:34 2005 OCC7966 End
          hasapoint  = true;
          U          = HICSPoint.U();
          V          = HICSPoint.V();
          W          = HICSW;
          transition = HICSPoint.Transition();
          pnt        = HICSPoint.Pnt();
          state      = currentstate;
          face       = Face;
          if (Face.Orientation() == TopAbs_REVERSED)
          {
            if (transition == IntCurveSurface_In)
              transition = IntCurveSurface_Out;
            else
              transition = IntCurveSurface_In;
          }
        }
      } //-- classifier state is IN or ON
      done = true;
    } //-- Loop on Intersection points.
  } //-- HICS.IsDone()
}
