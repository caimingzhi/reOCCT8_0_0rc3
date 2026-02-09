#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <gp_XY.hpp>
#include <BRepMesh_DegreeOfFreedom.hpp>
#include <Precision.hpp>

class BRepMesh_Vertex
{
public:
  DEFINE_STANDARD_ALLOC

  BRepMesh_Vertex()
      : myLocation3d(0),
        myMovability(BRepMesh_Free)
  {
  }

  BRepMesh_Vertex(const gp_XY&                   theUV,
                  const int                      theLocation3d,
                  const BRepMesh_DegreeOfFreedom theMovability)
  {
    Initialize(theUV, theLocation3d, theMovability);
  }

  BRepMesh_Vertex(const double                   theU,
                  const double                   theV,
                  const BRepMesh_DegreeOfFreedom theMovability)
      : myUV(theU, theV),
        myLocation3d(0),
        myMovability(theMovability)
  {
  }

  void Initialize(const gp_XY&                   theUV,
                  const int                      theLocation3d,
                  const BRepMesh_DegreeOfFreedom theMovability)
  {
    myUV         = theUV;
    myLocation3d = theLocation3d;
    myMovability = theMovability;
  }

  const gp_XY& Coord() const { return myUV; }

  gp_XY& ChangeCoord() { return myUV; }

  int Location3d() const { return myLocation3d; }

  BRepMesh_DegreeOfFreedom Movability() const { return myMovability; }

  void SetMovability(const BRepMesh_DegreeOfFreedom theMovability) { myMovability = theMovability; }

  bool IsEqual(const BRepMesh_Vertex& theOther) const
  {
    if (myMovability == BRepMesh_Deleted || theOther.myMovability == BRepMesh_Deleted)
    {
      return false;
    }

    return (myUV.IsEqual(theOther.myUV, Precision::PConfusion()));
  }

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
