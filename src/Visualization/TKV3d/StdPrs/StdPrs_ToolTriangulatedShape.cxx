#include <StdPrs_ToolTriangulatedShape.hpp>

#include <BRepBndLib.hpp>
#include <BRepMesh_DiscretFactory.hpp>
#include <BRepTools.hpp>
#include <BRep_Tool.hpp>
#include <Prs3d.hpp>
#include <Prs3d_Drawer.hpp>
#include <TopLoc_Location.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>

bool StdPrs_ToolTriangulatedShape::IsTriangulated(const TopoDS_Shape& theShape)
{
  TopLoc_Location aLocDummy;
  for (TopExp_Explorer aFaceIter(theShape, TopAbs_FACE); aFaceIter.More(); aFaceIter.Next())
  {
    const TopoDS_Face&                     aFace = TopoDS::Face(aFaceIter.Current());
    const occ::handle<Poly_Triangulation>& aTri  = BRep_Tool::Triangulation(aFace, aLocDummy);
    if (aTri.IsNull())
    {
      return false;
    }
  }
  return true;
}

bool StdPrs_ToolTriangulatedShape::IsClosed(const TopoDS_Shape& theShape)
{
  if (theShape.IsNull())
  {
    return true;
  }

  switch (theShape.ShapeType())
  {
    case TopAbs_COMPOUND:
    case TopAbs_COMPSOLID:
    default:
    {

      for (TopoDS_Iterator anIter(theShape); anIter.More(); anIter.Next())
      {
        const TopoDS_Shape& aShape = anIter.Value();
        if (!IsClosed(aShape))
        {
          return false;
        }
      }
      return true;
    }
    case TopAbs_SOLID:
    {

      if (!BRep_Tool::IsClosed(theShape))
        return false;

      for (TopoDS_Iterator anIter(theShape); anIter.More(); anIter.Next())
      {
        const TopoDS_Shape& aShape = anIter.Value();
        if (aShape.IsNull())
        {
          continue;
        }

        if (aShape.ShapeType() == TopAbs_FACE)
        {

          return false;
        }
        else if (!IsTriangulated(aShape))
        {

          return false;
        }
      }
      return true;
    }
    case TopAbs_SHELL:
    case TopAbs_FACE:
    {

      return false;
    }
    case TopAbs_WIRE:
    case TopAbs_EDGE:
    case TopAbs_VERTEX:
    {

      return true;
    }
  }
}

double StdPrs_ToolTriangulatedShape::GetDeflection(const TopoDS_Shape&              theShape,
                                                   const occ::handle<Prs3d_Drawer>& theDrawer)
{
  if (theDrawer->TypeOfDeflection() != Aspect_TOD_RELATIVE)
  {
    return theDrawer->MaximalChordialDeviation();
  }

  Bnd_Box aBndBox;
  BRepBndLib::Add(theShape, aBndBox, false);
  if (aBndBox.IsVoid())
  {
    return theDrawer->MaximalChordialDeviation();
  }
  else if (aBndBox.IsOpen())
  {
    if (!aBndBox.HasFinitePart())
    {
      return theDrawer->MaximalChordialDeviation();
    }
    aBndBox = aBndBox.FinitePart();
  }

  const double aDeflection = Prs3d::GetDeflection(aBndBox,
                                                  theDrawer->DeviationCoefficient(),
                                                  theDrawer->MaximalChordialDeviation());
  theDrawer->SetMaximalChordialDeviation(aDeflection);
  return aDeflection;
}

bool StdPrs_ToolTriangulatedShape::IsTessellated(const TopoDS_Shape&              theShape,
                                                 const occ::handle<Prs3d_Drawer>& theDrawer)
{
  return BRepTools::Triangulation(theShape, GetDeflection(theShape, theDrawer), true);
}

bool StdPrs_ToolTriangulatedShape::Tessellate(const TopoDS_Shape&              theShape,
                                              const occ::handle<Prs3d_Drawer>& theDrawer)
{
  bool wasRecomputed = false;

  if (IsTessellated(theShape, theDrawer))
  {
    return wasRecomputed;
  }

  const double aDeflection = GetDeflection(theShape, theDrawer);

  occ::handle<BRepMesh_DiscretRoot> aMeshAlgo =
    BRepMesh_DiscretFactory::Get().Discret(theShape, aDeflection, theDrawer->DeviationAngle());
  if (!aMeshAlgo.IsNull())
  {
    aMeshAlgo->Perform();
    wasRecomputed = true;
  }

  return wasRecomputed;
}

void StdPrs_ToolTriangulatedShape::ClearOnOwnDeflectionChange(
  const TopoDS_Shape&              theShape,
  const occ::handle<Prs3d_Drawer>& theDrawer,
  const bool                       theToResetCoeff)
{
  if (!theDrawer->IsAutoTriangulation() || theShape.IsNull())
  {
    return;
  }

  const bool   isOwnDeviationAngle       = theDrawer->HasOwnDeviationAngle();
  const bool   isOwnDeviationCoefficient = theDrawer->HasOwnDeviationCoefficient();
  const double anAngleNew                = theDrawer->DeviationAngle();
  const double anAnglePrev               = theDrawer->PreviousDeviationAngle();
  const double aCoeffNew                 = theDrawer->DeviationCoefficient();
  const double aCoeffPrev                = theDrawer->PreviousDeviationCoefficient();
  if ((!isOwnDeviationAngle || std::abs(anAngleNew - anAnglePrev) <= Precision::Angular())
      && (!isOwnDeviationCoefficient || std::abs(aCoeffNew - aCoeffPrev) <= Precision::Confusion()))
  {
    return;
  }

  BRepTools::Clean(theShape);
  if (theToResetCoeff)
  {
    theDrawer->UpdatePreviousDeviationAngle();
    theDrawer->UpdatePreviousDeviationCoefficient();
  }
}
