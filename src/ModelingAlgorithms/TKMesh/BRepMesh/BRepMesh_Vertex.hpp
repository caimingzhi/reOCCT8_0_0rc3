#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <gp_XY.hpp>
#include <BRepMesh_DegreeOfFreedom.hpp>
#include <Precision.hpp>

//! Light weighted structure representing vertex
//! of the mesh in parametric space. Vertex could be
//! associated with 3d point stored in external map.
class BRepMesh_Vertex
{
public:
  DEFINE_STANDARD_ALLOC

  //! Default constructor
  BRepMesh_Vertex()
      : myLocation3d(0),
        myMovability(BRepMesh_Free)
  {
  }

  //! Creates vertex associated with point in 3d space.
  //! @param theUV position of vertex in parametric space.
  //! @param theLocation3d index of 3d point to be associated with vertex.
  //! @param theMovability movability of the vertex.
  BRepMesh_Vertex(const gp_XY&                   theUV,
                  const int                      theLocation3d,
                  const BRepMesh_DegreeOfFreedom theMovability)
  {
    Initialize(theUV, theLocation3d, theMovability);
  }

  //! Creates vertex without association with point in 3d space.
  //! @param theU U position of vertex in parametric space.
  //! @param theV V position of vertex in parametric space.
  //! @param theMovability movability of the vertex.
  BRepMesh_Vertex(const double                   theU,
                  const double                   theV,
                  const BRepMesh_DegreeOfFreedom theMovability)
      : myUV(theU, theV),
        myLocation3d(0),
        myMovability(theMovability)
  {
  }

  //! Initializes vertex associated with point in 3d space.
  //! @param theUV position of vertex in parametric space.
  //! @param theLocation3d index of 3d point to be associated with vertex.
  //! @param theMovability movability of the vertex.
  void Initialize(const gp_XY&                   theUV,
                  const int                      theLocation3d,
                  const BRepMesh_DegreeOfFreedom theMovability)
  {
    myUV         = theUV;
    myLocation3d = theLocation3d;
    myMovability = theMovability;
  }

  //! Returns position of the vertex in parametric space.
  const gp_XY& Coord() const { return myUV; }

  //! Returns position of the vertex in parametric space for modification.
  gp_XY& ChangeCoord() { return myUV; }

  //! Returns index of 3d point associated with the vertex.
  int Location3d() const { return myLocation3d; }

  //! Returns movability of the vertex.
  BRepMesh_DegreeOfFreedom Movability() const { return myMovability; }

  //! Sets movability of the vertex.
  void SetMovability(const BRepMesh_DegreeOfFreedom theMovability) { myMovability = theMovability; }

  //! Checks for equality with another vertex.
  //! @param theOther vertex to be checked against this one.
  //! @return TRUE if equal, FALSE if not.
  bool IsEqual(const BRepMesh_Vertex& theOther) const
  {
    if (myMovability == BRepMesh_Deleted || theOther.myMovability == BRepMesh_Deleted)
    {
      return false;
    }

    return (myUV.IsEqual(theOther.myUV, Precision::PConfusion()));
  }

  //! Alias for IsEqual.
  bool operator==(const BRepMesh_Vertex& Other) const { return IsEqual(Other); }

private:
  gp_XY                    myUV;
  int                      myLocation3d;
  BRepMesh_DegreeOfFreedom myMovability;
};

namespace std
{
  template <>
  struct hash<BRepMesh_Vertex>
  {
    size_t operator()(const BRepMesh_Vertex& theVertex) const noexcept
    {
      return std::hash<double>{}(
        (std::floor(1e5 * theVertex.Coord().X()) * std::floor(1e5 * theVertex.Coord().Y())));
    }
  };
} // namespace std
