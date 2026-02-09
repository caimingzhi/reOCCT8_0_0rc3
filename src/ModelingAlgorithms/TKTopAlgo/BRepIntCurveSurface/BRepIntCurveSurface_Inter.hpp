#pragma once

#include <GeomAdaptor_Curve.hpp>
#include <IntCurveSurface_HInter.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IntCurveSurface_TransitionOnCurve.hpp>

class BRepTopAdaptor_TopolTool;
class TopoDS_Shape;
class GeomAdaptor_Curve;
class gp_Lin;
class IntCurveSurface_IntersectionPoint;
class gp_Pnt;
class TopoDS_Face;

class BRepIntCurveSurface_Inter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepIntCurveSurface_Inter();

  Standard_EXPORT void Init(const TopoDS_Shape&      theShape,
                            const GeomAdaptor_Curve& theCurve,
                            const double             theTol);

  Standard_EXPORT void Init(const TopoDS_Shape& theShape,
                            const gp_Lin&       theLine,
                            const double        theTol);

  Standard_EXPORT void Load(const TopoDS_Shape& theShape, const double theTol);

  Standard_EXPORT void Init(const GeomAdaptor_Curve& theCurve);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT IntCurveSurface_IntersectionPoint Point() const;

  Standard_EXPORT const gp_Pnt& Pnt() const;

  Standard_EXPORT double U() const;

  Standard_EXPORT double V() const;

  Standard_EXPORT double W() const;

  Standard_EXPORT TopAbs_State State() const;

  Standard_EXPORT IntCurveSurface_TransitionOnCurve Transition() const;

  Standard_EXPORT const TopoDS_Face& Face() const;

protected:
  Standard_EXPORT void Find();

  Standard_EXPORT bool FindPoint();

  Standard_EXPORT void Clear();

private:
  double                                    myTolerance;
  occ::handle<GeomAdaptor_Curve>            myCurve;
  IntCurveSurface_HInter                    myIntcs;
  int                                       myCurrentindex;
  int                                       myCurrentnbpoints;
  occ::handle<BRepTopAdaptor_TopolTool>     myFastClass;
  TopAbs_State                              myCurrentstate;
  double                                    myCurrentU;
  double                                    myCurrentV;
  Bnd_Box                                   myCurveBox;
  int                                       myIndFace;
  NCollection_Sequence<TopoDS_Shape>        myFaces;
  occ::handle<NCollection_HArray1<Bnd_Box>> myFaceBoxes;
};
