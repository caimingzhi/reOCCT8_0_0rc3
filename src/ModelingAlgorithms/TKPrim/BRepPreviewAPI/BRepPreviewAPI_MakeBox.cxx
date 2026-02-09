#include <BRepPreviewAPI_MakeBox.hpp>

#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_MakeVertex.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>

void BRepPreviewAPI_MakeBox::Build(const Message_ProgressRange&)
{
  gp_Pnt anLocation = myWedge.Axes().Location();

  gp_Pnt aFirstPoint(anLocation.X(), anLocation.Y(), anLocation.Z());
  gp_Pnt aSecondPoint(anLocation.X() + myWedge.GetXMax(),
                      anLocation.Y() + myWedge.GetYMax(),
                      anLocation.Z() + myWedge.GetZMax());

  bool aThinOnX = std::abs(aFirstPoint.X() - aSecondPoint.X()) < Precision::Confusion();
  bool aThinOnY = std::abs(aFirstPoint.Y() - aSecondPoint.Y()) < Precision::Confusion();
  bool aThinOnZ = std::abs(aFirstPoint.Z() - aSecondPoint.Z()) < Precision::Confusion();

  int aPreviewType = (int)aThinOnX + (int)aThinOnY + (int)aThinOnZ;

  if (aPreviewType == 3)
  {
    makeVertex(aFirstPoint);
  }
  else if (aPreviewType == 2)
  {
    makeEdge(aFirstPoint, aSecondPoint);
  }

  else if (aPreviewType == 1)
  {
    gp_Pnt aPnt1, aPnt2, aPnt3, aPnt4;
    if (aThinOnX)
    {
      aPnt1 = gp_Pnt(aFirstPoint.X(), aFirstPoint.Y(), aFirstPoint.Z());
      aPnt2 = gp_Pnt(aFirstPoint.X(), aSecondPoint.Y(), aFirstPoint.Z());
      aPnt3 = gp_Pnt(aFirstPoint.X(), aSecondPoint.Y(), aSecondPoint.Z());
      aPnt4 = gp_Pnt(aFirstPoint.X(), aFirstPoint.Y(), aSecondPoint.Z());
    }
    else if (aThinOnY)
    {
      aPnt1 = gp_Pnt(aFirstPoint.X(), aFirstPoint.Y(), aFirstPoint.Z());
      aPnt2 = gp_Pnt(aSecondPoint.X(), aFirstPoint.Y(), aFirstPoint.Z());
      aPnt3 = gp_Pnt(aSecondPoint.X(), aFirstPoint.Y(), aSecondPoint.Z());
      aPnt4 = gp_Pnt(aFirstPoint.X(), aFirstPoint.Y(), aSecondPoint.Z());
    }
    else if (aThinOnZ)
    {
      aPnt1 = gp_Pnt(aFirstPoint.X(), aFirstPoint.Y(), aFirstPoint.Z());
      aPnt2 = gp_Pnt(aSecondPoint.X(), aFirstPoint.Y(), aFirstPoint.Z());
      aPnt3 = gp_Pnt(aSecondPoint.X(), aSecondPoint.Y(), aFirstPoint.Z());
      aPnt4 = gp_Pnt(aFirstPoint.X(), aSecondPoint.Y(), aFirstPoint.Z());
    }

    makeRectangle(aPnt1, aPnt2, aPnt3, aPnt4);
  }

  if (!myShape.IsNull())
  {
    Done();
    return;
  }

  Solid();
}

void BRepPreviewAPI_MakeBox::makeVertex(const gp_Pnt& thePoint)
{
  myShape = BRepBuilderAPI_MakeVertex(thePoint);
}

void BRepPreviewAPI_MakeBox::makeEdge(const gp_Pnt& thePoint1, const gp_Pnt& thePoint2)
{
  myShape = BRepBuilderAPI_MakeEdge(thePoint1, thePoint2);
}

void BRepPreviewAPI_MakeBox::makeRectangle(const gp_Pnt& thePnt1,
                                           const gp_Pnt& thePnt2,
                                           const gp_Pnt& thePnt3,
                                           const gp_Pnt& thePnt4)
{
  TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(thePnt1, thePnt2);
  TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(thePnt2, thePnt3);
  TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(thePnt3, thePnt4);
  TopoDS_Edge anEdge4 = BRepBuilderAPI_MakeEdge(thePnt4, thePnt1);

  BRepBuilderAPI_MakeWire aWire(anEdge1, anEdge2, anEdge3, anEdge4);
  BRepBuilderAPI_MakeFace aFace(aWire);

  myShape = aFace.Shape();
}
