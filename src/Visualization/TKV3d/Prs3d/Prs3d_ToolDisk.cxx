#include <Prs3d_ToolDisk.hpp>

#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Poly_Triangle.hpp>
#include <NCollection_Array1.hpp>
#include <Prs3d_ToolQuadric.hpp>

//=================================================================================================

Prs3d_ToolDisk::Prs3d_ToolDisk(const double theInnerRadius,
                               const double theOuterRadius,
                               const int    theNbSlices,
                               const int    theNbStacks)
    : myInnerRadius(theInnerRadius),
      myOuterRadius(theOuterRadius),
      myStartAngle(0.0),
      myEndAngle(M_PI * 2.0)
{
  mySlicesNb = theNbSlices;
  myStacksNb = theNbStacks;
}

//=================================================================================================

gp_Pnt Prs3d_ToolDisk::Vertex(const double theU, const double theV) const
{
  const double aU      = myStartAngle + theU * (myEndAngle - myStartAngle);
  const double aRadius = myInnerRadius + (myOuterRadius - myInnerRadius) * theV;
  return gp_Pnt(std::cos(aU) * aRadius, std::sin(aU) * aRadius, 0.0);
}

//=================================================================================================

occ::handle<Graphic3d_ArrayOfTriangles> Prs3d_ToolDisk::Create(const double   theInnerRadius,
                                                               const double   theOuterRadius,
                                                               const int      theNbSlices,
                                                               const int      theNbStacks,
                                                               const gp_Trsf& theTrsf)
{
  occ::handle<Graphic3d_ArrayOfTriangles> anArray;
  Prs3d_ToolDisk aTool(theInnerRadius, theOuterRadius, theNbSlices, theNbStacks);
  aTool.FillArray(anArray, theTrsf);
  return anArray;
}
