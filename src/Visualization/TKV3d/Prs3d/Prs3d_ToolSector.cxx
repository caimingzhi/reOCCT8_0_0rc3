#include <Prs3d_ToolSector.hpp>

#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Poly_Triangle.hpp>
#include <NCollection_Array1.hpp>
#include <Prs3d_ToolQuadric.hpp>

//=================================================================================================

Prs3d_ToolSector::Prs3d_ToolSector(const double theRadius,
                                   const int    theNbSlices,
                                   const int    theNbStacks)
    : myRadius(theRadius)
{
  mySlicesNb = theNbSlices;
  myStacksNb = theNbStacks;
}

//=================================================================================================

gp_Pnt Prs3d_ToolSector::Vertex(const double theU, const double theV) const
{
  const double aU      = theU * M_PI / 2.0;
  const double aRadius = myRadius * theV;
  return gp_Pnt(std::cos(aU) * aRadius, std::sin(aU) * aRadius, 0.0);
}

//=================================================================================================

occ::handle<Graphic3d_ArrayOfTriangles> Prs3d_ToolSector::Create(const double   theRadius,
                                                                 const int      theNbSlices,
                                                                 const int      theNbStacks,
                                                                 const gp_Trsf& theTrsf)
{
  occ::handle<Graphic3d_ArrayOfTriangles> anArray;
  Prs3d_ToolSector                        aTool(theRadius, theNbSlices, theNbStacks);
  aTool.FillArray(anArray, theTrsf);
  return anArray;
}
