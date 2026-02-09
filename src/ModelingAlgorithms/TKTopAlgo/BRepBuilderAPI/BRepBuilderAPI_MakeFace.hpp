#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepLib_MakeFace.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <Standard_Real.hpp>

enum BRepBuilderAPI_FaceError
{
  BRepBuilderAPI_FaceDone,
  BRepBuilderAPI_NoFace,
  BRepBuilderAPI_NotPlanar,
  BRepBuilderAPI_CurveProjectionFailed,
  BRepBuilderAPI_ParametersOutOfRange
};

class TopoDS_Face;
class gp_Pln;
class gp_Cylinder;
class gp_Cone;
class gp_Sphere;
class gp_Torus;
class Geom_Surface;
class TopoDS_Wire;

class BRepBuilderAPI_MakeFace : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_MakeFace();

  Standard_EXPORT BRepBuilderAPI_MakeFace(const TopoDS_Face& F);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Pln& P);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Cylinder& C);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Cone& C);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Sphere& S);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Torus& C);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const occ::handle<Geom_Surface>& S,
                                          const double                     TolDegen);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Pln& P,
                                          const double  UMin,
                                          const double  UMax,
                                          const double  VMin,
                                          const double  VMax);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Cylinder& C,
                                          const double       UMin,
                                          const double       UMax,
                                          const double       VMin,
                                          const double       VMax);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Cone& C,
                                          const double   UMin,
                                          const double   UMax,
                                          const double   VMin,
                                          const double   VMax);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Sphere& S,
                                          const double     UMin,
                                          const double     UMax,
                                          const double     VMin,
                                          const double     VMax);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Torus& C,
                                          const double    UMin,
                                          const double    UMax,
                                          const double    VMin,
                                          const double    VMax);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const occ::handle<Geom_Surface>& S,
                                          const double                     UMin,
                                          const double                     UMax,
                                          const double                     VMin,
                                          const double                     VMax,
                                          const double                     TolDegen);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const TopoDS_Wire& W, const bool OnlyPlane = false);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Pln&      P,
                                          const TopoDS_Wire& W,
                                          const bool         Inside = true);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Cylinder& C,
                                          const TopoDS_Wire& W,
                                          const bool         Inside = true);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Cone&     C,
                                          const TopoDS_Wire& W,
                                          const bool         Inside = true);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Sphere&   S,
                                          const TopoDS_Wire& W,
                                          const bool         Inside = true);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const gp_Torus&    C,
                                          const TopoDS_Wire& W,
                                          const bool         Inside = true);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const occ::handle<Geom_Surface>& S,
                                          const TopoDS_Wire&               W,
                                          const bool                       Inside = true);

  Standard_EXPORT BRepBuilderAPI_MakeFace(const TopoDS_Face& F, const TopoDS_Wire& W);

  Standard_EXPORT void Init(const TopoDS_Face& F);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& S,
                            const bool                       Bound,
                            const double                     TolDegen);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& S,
                            const double                     UMin,
                            const double                     UMax,
                            const double                     VMin,
                            const double                     VMax,
                            const double                     TolDegen);

  Standard_EXPORT void Add(const TopoDS_Wire& W);

  Standard_EXPORT bool IsDone() const override;

  Standard_EXPORT BRepBuilderAPI_FaceError Error() const;

  Standard_EXPORT const TopoDS_Face& Face() const;
  Standard_EXPORT                    operator TopoDS_Face() const;

private:
  BRepLib_MakeFace myMakeFace;
};
