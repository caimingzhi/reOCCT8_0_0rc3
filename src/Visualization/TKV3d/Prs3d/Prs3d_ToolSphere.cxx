#include <Prs3d_ToolSphere.hpp>

#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Poly_Triangle.hpp>
#include <NCollection_Array1.hpp>
#include <Prs3d_ToolQuadric.hpp>

//=================================================================================================

Prs3d_ToolSphere::Prs3d_ToolSphere(const double theRadius,
                                   const int    theNbSlices,
                                   const int    theNbStacks)
    : myRadius(theRadius)
{
  mySlicesNb = theNbSlices;
  myStacksNb = theNbStacks;
}

//=================================================================================================

gp_Pnt Prs3d_ToolSphere::Vertex(const double theU, const double theV) const
{
  const double aU = theU * M_PI * 2.0;
  const double aV = theV * M_PI;
  return gp_Pnt(myRadius * std::cos(aU) * std::sin(aV),
                -myRadius * std::sin(aU) * std::sin(aV),
                myRadius * std::cos(aV));
}

//=================================================================================================

gp_Dir Prs3d_ToolSphere::Normal(const double theU, const double theV) const
{
  const double aU = theU * M_PI * 2.0;
  const double aV = theV * M_PI;
  return gp_Dir(std::cos(aU) * std::sin(aV), -std::sin(aU) * std::sin(aV), std::cos(aV));
}

//=================================================================================================

occ::handle<Graphic3d_ArrayOfTriangles> Prs3d_ToolSphere::Create(const double   theRadius,
                                                                 const int      theNbSlices,
                                                                 const int      theNbStacks,
                                                                 const gp_Trsf& theTrsf)
{
  occ::handle<Graphic3d_ArrayOfTriangles> anArray;
  Prs3d_ToolSphere                        aTool(theRadius, theNbSlices, theNbStacks);
  aTool.FillArray(anArray, theTrsf);
  return anArray;
}
