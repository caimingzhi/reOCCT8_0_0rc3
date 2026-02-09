#include <BRepFill.hpp>
#include <BRepOffsetAPI_MakeEvolved.hpp>
#include <gp_Ax3.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS.hpp>

static const NCollection_List<TopoDS_Shape> anEmptyList;

BRepOffsetAPI_MakeEvolved::BRepOffsetAPI_MakeEvolved() = default;

BRepOffsetAPI_MakeEvolved::BRepOffsetAPI_MakeEvolved(const TopoDS_Shape&    Spine,
                                                     const TopoDS_Wire&     Profil,
                                                     const GeomAbs_JoinType Join,
                                                     const bool             AxeProf,
                                                     const bool             Solid,
                                                     const bool             ProfOnSpine,
                                                     const double           Tol,
                                                     const bool             theIsVolume,
                                                     const bool             theRunInParallel)
    : myIsVolume(theIsVolume)
{
  if (Spine.ShapeType() != TopAbs_WIRE && Spine.ShapeType() != TopAbs_FACE)
  {
    throw Standard_TypeMismatch("BRepOffsetAPI_MakeEvolved: face or wire is expected as a spine");
  }
  if (theIsVolume)
  {
    myVolume.SetParallelMode(theRunInParallel);
    TopoDS_Wire aSpine;
    if (Spine.ShapeType() == TopAbs_WIRE)
    {
      aSpine = TopoDS::Wire(Spine);
    }
    else
    {
      aSpine = TopoDS::Wire(TopoDS_Iterator(Spine).Value());
    }
    myVolume.Perform(aSpine, Profil, Tol, Solid);
    if (!myVolume.IsDone())
    {
      return;
    }
  }
  else
  {
    gp_Ax3 Axis(gp::Origin(), gp::DZ(), gp::DX());

    if (!AxeProf)
    {
      bool POS;
      BRepFill::Axe(Spine, Profil, Axis, POS, std::max(Tol, Precision::Confusion()));
      if (ProfOnSpine && !POS)
        return;
    }
    if (Spine.ShapeType() == TopAbs_WIRE)
    {
      myEvolved.Perform(TopoDS::Wire(Spine), Profil, Axis, Join, Solid);
    }
    else
    {
      myEvolved.Perform(TopoDS::Face(Spine), Profil, Axis, Join, Solid);
    }
  }

  Build();
}

const BRepFill_Evolved& BRepOffsetAPI_MakeEvolved::Evolved() const
{
  if (myIsVolume)
  {
    throw Standard_TypeMismatch(
      "BRepOffsetAPI_MakeEvolved: myEvolved is accessed while in volume mode");
  }
  return myEvolved;
}

void BRepOffsetAPI_MakeEvolved::Build(const Message_ProgressRange&)
{
  if (myEvolved.IsDone())
  {
    myShape = myEvolved.Shape();
  }
  else if (myVolume.IsDone())
  {
    myShape = myVolume.Shape();
  }

  Done();
}

const TopoDS_Shape& BRepOffsetAPI_MakeEvolved::Top() const
{
  return myEvolved.Top();
}

const TopoDS_Shape& BRepOffsetAPI_MakeEvolved::Bottom() const
{
  return myEvolved.Bottom();
}

const NCollection_List<TopoDS_Shape>& BRepOffsetAPI_MakeEvolved::GeneratedShapes(
  const TopoDS_Shape& SpineShape,
  const TopoDS_Shape& ProfShape) const
{
  if (!myEvolved.IsDone())
    return anEmptyList;

  return myEvolved.GeneratedShapes(SpineShape, ProfShape);
}
