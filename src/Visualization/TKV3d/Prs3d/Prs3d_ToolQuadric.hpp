#pragma once

#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Poly_Triangulation.hpp>

class Prs3d_ToolQuadric
{
public:
  DEFINE_STANDARD_ALLOC

  static int TrianglesNb(const int theSlicesNb, const int theStacksNb)
  {
    return theSlicesNb * theStacksNb * 2;
  }

  static int VerticesNb(const int  theSlicesNb,
                        const int  theStacksNb,
                        const bool theIsIndexed = true)
  {
    return theIsIndexed ? (theSlicesNb + 1) * (theStacksNb + 1)
                        : TrianglesNb(theSlicesNb, theStacksNb) * 3;
  }

public:
  Standard_EXPORT occ::handle<Graphic3d_ArrayOfTriangles> CreateTriangulation(
    const gp_Trsf& theTrsf) const;

  Standard_EXPORT occ::handle<Poly_Triangulation> CreatePolyTriangulation(
    const gp_Trsf& theTrsf) const;

  Standard_EXPORT void FillArray(occ::handle<Graphic3d_ArrayOfTriangles>& theArray,
                                 const gp_Trsf&                           theTrsf) const;

  int TrianglesNb() const { return mySlicesNb * myStacksNb * 2; }

  int VerticesNb(bool theIsIndexed = true) const
  {
    return theIsIndexed ? (mySlicesNb + 1) * (myStacksNb + 1) : TrianglesNb() * 3;
  }

public:
  Standard_DEPRECATED(
    "Deprecated method, CreateTriangulation() and CreatePolyTriangulation() should be used instead")
  Standard_EXPORT void FillArray(occ::handle<Graphic3d_ArrayOfTriangles>& theArray,
                                 occ::handle<Poly_Triangulation>&         theTriangulation,
                                 const gp_Trsf&                           theTrsf) const;

protected:
  virtual gp_Pnt Vertex(const double theU, const double theV) const = 0;

  virtual gp_Dir Normal(const double theU, const double theV) const = 0;

protected:
  int mySlicesNb;
  int myStacksNb;
};
