#pragma once

#include <BRepAdaptor_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

class TopoDS_Edge;
class gp_Pnt;
class gp_Vec;
class gp_Pnt2d;
class gp_Dir2d;
class gp_Vec2d;
class gp_Lin2d;
class gp_Circ2d;
class gp_Elips2d;
class gp_Hypr2d;
class gp_Parab2d;
class Geom_BSplineCurve;
class HLRAlgo_Projector;

class HLRBRep_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_Curve();

  void Projector(const HLRAlgo_Projector* Proj) { myProj = Proj; }

  BRepAdaptor_Curve& Curve();

  Standard_EXPORT void Curve(const TopoDS_Edge& E);

  const BRepAdaptor_Curve& GetCurve() const;

  Standard_EXPORT double Parameter2d(const double P3d) const;

  Standard_EXPORT double Parameter3d(const double P2d) const;

  Standard_EXPORT double Update(double TotMin[16], double TotMax[16]);

  Standard_EXPORT double UpdateMinMax(double TotMin[16], double TotMax[16]);

  Standard_EXPORT double Z(const double U) const;

  gp_Pnt Value3D(const double U) const;

  void D0(const double U, gp_Pnt& P) const;

  void D1(const double U, gp_Pnt& P, gp_Vec& V) const;

  Standard_EXPORT void Tangent(const bool AtStart, gp_Pnt2d& P, gp_Dir2d& D) const;

  double FirstParameter() const;

  double LastParameter() const;

  GeomAbs_Shape Continuity() const;

  int NbIntervals(const GeomAbs_Shape S) const;

  void Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape S) const;

  bool IsClosed() const;

  bool IsPeriodic() const;

  double Period() const;

  gp_Pnt2d Value(const double U) const;

  Standard_EXPORT void D0(const double U, gp_Pnt2d& P) const;

  Standard_EXPORT void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V) const;

  Standard_EXPORT void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt2d&    P,
                          gp_Vec2d&    V1,
                          gp_Vec2d&    V2,
                          gp_Vec2d&    V3) const;

  Standard_EXPORT gp_Vec2d DN(const double U, const int N) const;

  double Resolution(const double R3d) const;

  GeomAbs_CurveType GetType() const;

  Standard_EXPORT gp_Lin2d Line() const;

  Standard_EXPORT gp_Circ2d Circle() const;

  Standard_EXPORT gp_Elips2d Ellipse() const;

  Standard_EXPORT gp_Hypr2d Hyperbola() const;

  Standard_EXPORT gp_Parab2d Parabola() const;

  bool IsRational() const;

  int Degree() const;

  int NbPoles() const;

  Standard_EXPORT void Poles(NCollection_Array1<gp_Pnt2d>& TP) const;

  Standard_EXPORT void Poles(const occ::handle<Geom_BSplineCurve>& aCurve,
                             NCollection_Array1<gp_Pnt2d>&         TP) const;

  Standard_EXPORT void PolesAndWeights(NCollection_Array1<gp_Pnt2d>& TP,
                                       NCollection_Array1<double>&   TW) const;

  Standard_EXPORT void PolesAndWeights(const occ::handle<Geom_BSplineCurve>& aCurve,
                                       NCollection_Array1<gp_Pnt2d>&         TP,
                                       NCollection_Array1<double>&           TW) const;

  int NbKnots() const;

  Standard_EXPORT void Knots(NCollection_Array1<double>& kn) const;

  Standard_EXPORT void Multiplicities(NCollection_Array1<int>& mu) const;

private:
  BRepAdaptor_Curve        myCurve;
  GeomAbs_CurveType        myType;
  const HLRAlgo_Projector* myProj;
  double                   myOX;
  double                   myOZ;
  double                   myVX;
  double                   myVZ;
  double                   myOF;
};

#include <Standard_NotImplemented.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Parab2d.hpp>
#include <HLRBRep_BCurveTool.hpp>

inline BRepAdaptor_Curve& HLRBRep_Curve::Curve()
{
  return myCurve;
}

inline const BRepAdaptor_Curve& HLRBRep_Curve::GetCurve() const
{
  return myCurve;
}

inline gp_Pnt HLRBRep_Curve::Value3D(const double U) const
{
  gp_Pnt P;
  D0(U, P);
  return P;
}

inline void HLRBRep_Curve::D0(const double U, gp_Pnt& P) const
{
  HLRBRep_BCurveTool::D0(myCurve, U, P);
}

inline void HLRBRep_Curve::D1(const double U, gp_Pnt& P, gp_Vec& V) const
{
  HLRBRep_BCurveTool::D1(myCurve, U, P, V);
}

inline double HLRBRep_Curve::FirstParameter() const
{
  return Parameter2d(HLRBRep_BCurveTool::FirstParameter(myCurve));
}

inline double HLRBRep_Curve::LastParameter() const
{
  return Parameter2d(HLRBRep_BCurveTool::LastParameter(myCurve));
}

inline GeomAbs_Shape HLRBRep_Curve::Continuity() const
{
  return HLRBRep_BCurveTool::Continuity(myCurve);
}

inline int HLRBRep_Curve::NbIntervals(const GeomAbs_Shape S) const
{
  return HLRBRep_BCurveTool::NbIntervals(myCurve, S);
}

inline void HLRBRep_Curve::Intervals(NCollection_Array1<double>& Tab, const GeomAbs_Shape Sh) const
{
  HLRBRep_BCurveTool::Intervals(myCurve, Tab, Sh);
}

inline bool HLRBRep_Curve::IsClosed() const
{
  return HLRBRep_BCurveTool::IsClosed(myCurve);
}

inline bool HLRBRep_Curve::IsPeriodic() const
{
  return HLRBRep_BCurveTool::IsPeriodic(myCurve);
}

inline double HLRBRep_Curve::Period() const
{
  return HLRBRep_BCurveTool::Period(myCurve);
}

inline gp_Pnt2d HLRBRep_Curve::Value(const double U) const
{
  gp_Pnt2d P;
  D0(U, P);
  return P;
}

inline double HLRBRep_Curve::Resolution(const double R3d) const
{
  return HLRBRep_BCurveTool::Resolution(myCurve, R3d);
}

inline GeomAbs_CurveType HLRBRep_Curve::GetType() const
{
  return myType;
}

inline int HLRBRep_Curve::Degree() const
{
  return HLRBRep_BCurveTool::Degree(myCurve);
}

inline int HLRBRep_Curve::NbPoles() const
{
  return HLRBRep_BCurveTool::NbPoles(myCurve);
}

inline int HLRBRep_Curve::NbKnots() const
{
  return HLRBRep_BCurveTool::NbKnots(myCurve);
}

inline bool HLRBRep_Curve::IsRational() const
{
  return HLRBRep_BCurveTool::IsRational(myCurve);
}
