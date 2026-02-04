#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Face.hpp>
#include <gp_Pnt.hpp>
class Geom_Curve;
class Geom2d_Curve;

class Draft_EdgeInfo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Draft_EdgeInfo();

  Standard_EXPORT Draft_EdgeInfo(const bool HasNewGeometry);

  Standard_EXPORT void Add(const TopoDS_Face& F);

  Standard_EXPORT void RootFace(const TopoDS_Face& F);

  Standard_EXPORT void Tangent(const gp_Pnt& P);

  Standard_EXPORT bool IsTangent(gp_Pnt& P) const;

  Standard_EXPORT bool NewGeometry() const;

  Standard_EXPORT void SetNewGeometry(const bool NewGeom);

  Standard_EXPORT const occ::handle<Geom_Curve>& Geometry() const;

  Standard_EXPORT const TopoDS_Face& FirstFace() const;

  Standard_EXPORT const TopoDS_Face& SecondFace() const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& FirstPC() const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& SecondPC() const;

  Standard_EXPORT occ::handle<Geom_Curve>& ChangeGeometry();

  Standard_EXPORT occ::handle<Geom2d_Curve>& ChangeFirstPC();

  Standard_EXPORT occ::handle<Geom2d_Curve>& ChangeSecondPC();

  Standard_EXPORT const TopoDS_Face& RootFace() const;

  Standard_EXPORT void Tolerance(const double tol);

  Standard_EXPORT double Tolerance() const;

private:
  bool                      myNewGeom;
  occ::handle<Geom_Curve>   myGeom;
  TopoDS_Face               myFirstF;
  TopoDS_Face               mySeconF;
  occ::handle<Geom2d_Curve> myFirstPC;
  occ::handle<Geom2d_Curve> mySeconPC;
  TopoDS_Face               myRootFace;
  bool                      myTgt;
  gp_Pnt                    myPt;
  double                    myTol;
};

