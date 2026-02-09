#include <BRepBuilderAPI_MakeFace.hpp>
#include <Geom_Surface.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Pln.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Wire.hpp>

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace() = default;

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const TopoDS_Face& F)
    : myMakeFace(F)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Pln& P)
    : myMakeFace(P)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Cylinder& C)
    : myMakeFace(C)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Cone& C)
    : myMakeFace(C)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Sphere& S)
    : myMakeFace(S)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Torus& T)
    : myMakeFace(T)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const occ::handle<Geom_Surface>& S,
                                                 const double                     TolDegen)
    : myMakeFace(S, TolDegen)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Pln& P,
                                                 const double  UMin,
                                                 const double  UMax,
                                                 const double  VMin,
                                                 const double  VMax)
    : myMakeFace(P, UMin, UMax, VMin, VMax)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Cylinder& C,
                                                 const double       UMin,
                                                 const double       UMax,
                                                 const double       VMin,
                                                 const double       VMax)
    : myMakeFace(C, UMin, UMax, VMin, VMax)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Cone& C,
                                                 const double   UMin,
                                                 const double   UMax,
                                                 const double   VMin,
                                                 const double   VMax)
    : myMakeFace(C, UMin, UMax, VMin, VMax)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Sphere& S,
                                                 const double     UMin,
                                                 const double     UMax,
                                                 const double     VMin,
                                                 const double     VMax)
    : myMakeFace(S, UMin, UMax, VMin, VMax)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Torus& T,
                                                 const double    UMin,
                                                 const double    UMax,
                                                 const double    VMin,
                                                 const double    VMax)
    : myMakeFace(T, UMin, UMax, VMin, VMax)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const occ::handle<Geom_Surface>& S,
                                                 const double                     UMin,
                                                 const double                     UMax,
                                                 const double                     VMin,
                                                 const double                     VMax,
                                                 const double                     TolDegen)
    : myMakeFace(S, UMin, UMax, VMin, VMax, TolDegen)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const TopoDS_Wire& W, const bool OnlyPlane)
    : myMakeFace(W, OnlyPlane)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Pln&      P,
                                                 const TopoDS_Wire& W,
                                                 const bool         Inside)
    : myMakeFace(P, W, Inside)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Cylinder& C,
                                                 const TopoDS_Wire& W,
                                                 const bool         Inside)
    : myMakeFace(C, W, Inside)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Cone&     C,
                                                 const TopoDS_Wire& W,
                                                 const bool         Inside)
    : myMakeFace(C, W, Inside)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Sphere&   S,
                                                 const TopoDS_Wire& W,
                                                 const bool         Inside)
    : myMakeFace(S, W, Inside)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const gp_Torus&    T,
                                                 const TopoDS_Wire& W,
                                                 const bool         Inside)
    : myMakeFace(T, W, Inside)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const occ::handle<Geom_Surface>& S,
                                                 const TopoDS_Wire&               W,
                                                 const bool                       Inside)
    : myMakeFace(S, W, Inside)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

BRepBuilderAPI_MakeFace::BRepBuilderAPI_MakeFace(const TopoDS_Face& F, const TopoDS_Wire& W)
    : myMakeFace(F, W)
{
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

void BRepBuilderAPI_MakeFace::Init(const TopoDS_Face& F)
{
  myMakeFace.Init(F);
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

void BRepBuilderAPI_MakeFace::Init(const occ::handle<Geom_Surface>& S,
                                   const bool                       Bound,
                                   const double                     TolDegen)
{
  myMakeFace.Init(S, Bound, TolDegen);
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

void BRepBuilderAPI_MakeFace::Init(const occ::handle<Geom_Surface>& SS,
                                   const double                     Um,
                                   const double                     UM,
                                   const double                     Vm,
                                   const double                     VM,
                                   const double                     TolDegen)
{
  myMakeFace.Init(SS, Um, UM, Vm, VM, TolDegen);
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

void BRepBuilderAPI_MakeFace::Add(const TopoDS_Wire& W)
{
  myMakeFace.Add(W);
  if (myMakeFace.IsDone())
  {
    Done();
    myShape = myMakeFace.Shape();
  }
}

const TopoDS_Face& BRepBuilderAPI_MakeFace::Face() const
{
  return myMakeFace.Face();
}

BRepBuilderAPI_MakeFace::operator TopoDS_Face() const
{
  return Face();
}

bool BRepBuilderAPI_MakeFace::IsDone() const
{
  return myMakeFace.IsDone();
}

BRepBuilderAPI_FaceError BRepBuilderAPI_MakeFace::Error() const
{
  switch (myMakeFace.Error())
  {

    case BRepLib_FaceDone:
      return BRepBuilderAPI_FaceDone;

    case BRepLib_NoFace:
      return BRepBuilderAPI_NoFace;

    case BRepLib_NotPlanar:
      return BRepBuilderAPI_NotPlanar;

    case BRepLib_CurveProjectionFailed:
      return BRepBuilderAPI_CurveProjectionFailed;

    case BRepLib_ParametersOutOfRange:
      return BRepBuilderAPI_ParametersOutOfRange;
  }

  return BRepBuilderAPI_FaceDone;
}
