#pragma once

#include <GeomAdaptor_TransformedSurface.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <NCollection_Array1.hpp>
#include <TopoDS_Face.hpp>

class gp_Pln;
class gp_Cylinder;
class gp_Cone;
class gp_Sphere;
class gp_Torus;
class Geom_BezierSurface;
class Geom_BSplineSurface;
class gp_Ax1;
class gp_Dir;

class BRepAdaptor_Surface : public GeomAdaptor_TransformedSurface
{
  DEFINE_STANDARD_RTTIEXT(BRepAdaptor_Surface, GeomAdaptor_TransformedSurface)
public:
  Standard_EXPORT BRepAdaptor_Surface();

  Standard_EXPORT BRepAdaptor_Surface(const TopoDS_Face& F, const bool R = true);

  Standard_EXPORT occ::handle<Adaptor3d_Surface> ShallowCopy() const override;

  Standard_EXPORT void Initialize(const TopoDS_Face& F, const bool Restriction = true);

  Standard_EXPORT const TopoDS_Face& Face() const;

  Standard_EXPORT double Tolerance() const;

private:
  TopoDS_Face myFace;
};
