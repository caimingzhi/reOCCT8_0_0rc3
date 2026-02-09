#pragma once

#include <AppCont_Function.hpp>

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Macro.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Real.hpp>

class TopoDS_Edge;
class Geom2d_Curve;
class Geom_Curve;
class gp_Pnt;
class gp_Pnt2d;

class BRepFill_MultiLine : public AppCont_Function
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_MultiLine();

  Standard_EXPORT BRepFill_MultiLine(const TopoDS_Face&               Face1,
                                     const TopoDS_Face&               Face2,
                                     const TopoDS_Edge&               Edge1,
                                     const TopoDS_Edge&               Edge2,
                                     const bool                       Inv1,
                                     const bool                       Inv2,
                                     const occ::handle<Geom2d_Curve>& Bissec);

  Standard_EXPORT bool IsParticularCase() const;

  Standard_EXPORT GeomAbs_Shape Continuity() const;

  Standard_EXPORT void Curves(occ::handle<Geom_Curve>&   Curve,
                              occ::handle<Geom2d_Curve>& PCurve1,
                              occ::handle<Geom2d_Curve>& PCurve2) const;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT gp_Pnt Value(const double U) const;

  Standard_EXPORT gp_Pnt2d ValueOnF1(const double U) const;

  Standard_EXPORT gp_Pnt2d ValueOnF2(const double U) const;

  Standard_EXPORT void Value3dOnF1OnF2(const double U,
                                       gp_Pnt&      P3d,
                                       gp_Pnt2d&    PF1,
                                       gp_Pnt2d&    PF2) const;

  Standard_EXPORT bool Value(const double                  theU,
                             NCollection_Array1<gp_Pnt2d>& thePnt2d,
                             NCollection_Array1<gp_Pnt>&   thePnt) const override;

  Standard_EXPORT bool D1(const double                  theU,
                          NCollection_Array1<gp_Vec2d>& theVec2d,
                          NCollection_Array1<gp_Vec>&   theVec) const override;

private:
  TopoDS_Face         myFace1;
  TopoDS_Face         myFace2;
  Geom2dAdaptor_Curve myU1;
  Geom2dAdaptor_Curve myV1;
  Geom2dAdaptor_Curve myU2;
  Geom2dAdaptor_Curve myV2;
  bool                myIsoU1;
  bool                myIsoU2;
  Geom2dAdaptor_Curve myBis;
  int                 myKPart;
  GeomAbs_Shape       myCont;
};
