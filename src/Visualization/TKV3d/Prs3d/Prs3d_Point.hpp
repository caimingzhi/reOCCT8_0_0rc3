#pragma once


#include <Graphic3d_ArrayOfPoints.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_PointAspect.hpp>

template <class AnyPoint, class PointTool>
class Prs3d_Point
{
public:
  DEFINE_STANDARD_ALLOC

private:
  Standard_EXPORT static void DrawPoint(const AnyPoint&                    thePoint,
                                        const occ::handle<Graphic3d_Group> theGroup)
  {
    double aX, aY, aZ;
    PointTool::Coord(thePoint, aX, aY, aZ);
    occ::handle<Graphic3d_ArrayOfPoints> anArrayOfPoints = new Graphic3d_ArrayOfPoints(1);
    anArrayOfPoints->AddVertex(aX, aY, aZ);
    theGroup->AddPrimitiveArray(anArrayOfPoints);
  }

public:
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& thePrs,
                                  const AnyPoint&                        thePoint,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer)
  {
    occ::handle<Graphic3d_Group> aGroup = thePrs->CurrentGroup();
    aGroup->SetPrimitivesAspect(theDrawer->PointAspect()->Aspect());
    DrawPoint(thePoint, aGroup);
  }

  Standard_EXPORT static bool Match(const AnyPoint& thePoint,
                                    const double    theX,
                                    const double    theY,
                                    const double    theZ,
                                    const double    theDistance)
  {
    double aX, aY, aZ;
    PointTool::Coord(thePoint, aX, aY, aZ);
    return std::sqrt((theX - aX) * (theX - aX) + (theY - aY) * (theY - aY)
                     + (theZ - aZ) * (theZ - aZ))
           <= theDistance;
  }
};

