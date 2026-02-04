#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <TopoDS_Face.hpp>
class Geom_Surface;
class Geom_Curve;

class Draft_FaceInfo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Draft_FaceInfo();

  Standard_EXPORT Draft_FaceInfo(const occ::handle<Geom_Surface>& S, const bool HasNewGeometry);

  Standard_EXPORT void RootFace(const TopoDS_Face& F);

  Standard_EXPORT bool NewGeometry() const;

  Standard_EXPORT void Add(const TopoDS_Face& F);

  Standard_EXPORT const TopoDS_Face& FirstFace() const;

  Standard_EXPORT const TopoDS_Face& SecondFace() const;

  Standard_EXPORT const occ::handle<Geom_Surface>& Geometry() const;

  Standard_EXPORT occ::handle<Geom_Surface>& ChangeGeometry();

  Standard_EXPORT const TopoDS_Face& RootFace() const;

  Standard_EXPORT occ::handle<Geom_Curve>& ChangeCurve();

  Standard_EXPORT const occ::handle<Geom_Curve>& Curve() const;

private:
  bool                      myNewGeom;
  occ::handle<Geom_Surface> myGeom;
  TopoDS_Face               myRootFace;
  TopoDS_Face               myF1;
  TopoDS_Face               myF2;
  occ::handle<Geom_Curve>   myCurv;
};

