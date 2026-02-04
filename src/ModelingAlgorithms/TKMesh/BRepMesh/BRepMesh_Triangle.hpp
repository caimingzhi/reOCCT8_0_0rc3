#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_HashUtils.hpp>

#include <BRepMesh_DegreeOfFreedom.hpp>

//! Light weighted structure representing triangle
//! of mesh consisting of oriented links.
class BRepMesh_Triangle
{
public:
  DEFINE_STANDARD_ALLOC

  //! Default constructor.
  BRepMesh_Triangle()
      : myMovability(BRepMesh_Free)
  {
    myEdges[0]        = 0;
    myEdges[1]        = 0;
    myEdges[2]        = 0;
    myOrientations[0] = false;
    myOrientations[1] = false;
    myOrientations[2] = false;
  }

  //! Constructor.
  //! @param theEdges array of edges of triangle.
  //! @param theOrientations array of edge's orientations.
  //! @param theMovability movability of triangle.
  BRepMesh_Triangle(const int (&theEdges)[3],
                    const bool (&theOrientations)[3],
                    const BRepMesh_DegreeOfFreedom theMovability)
  {
    Initialize(theEdges, theOrientations, theMovability);
  }

  //! Initializes the triangle by the given parameters.
  //! @param theEdges array of edges of triangle.
  //! @param theOrientations array of edge's orientations.
  //! @param theMovability movability of triangle.
  void Initialize(const int (&theEdges)[3],
                  const bool (&theOrientations)[3],
                  const BRepMesh_DegreeOfFreedom theMovability)
  {
    memcpy(myEdges, theEdges, sizeof(theEdges));
    memcpy(myOrientations, theOrientations, sizeof(theOrientations));
    myMovability = theMovability;
  }

  //! Gets edges with orientations composing the triangle.
  //! @param[out] theEdges array edges are stored to.
  //! @param[out] theOrientations array orientations are stored to.
  void Edges(int (&theEdges)[3], bool (&theOrientations)[3]) const
  {
    memcpy(theEdges, myEdges, sizeof(myEdges));
    memcpy(theOrientations, myOrientations, sizeof(myOrientations));
  }

  //! Returns movability of the triangle.
  BRepMesh_DegreeOfFreedom Movability() const { return myMovability; }

  //! Sets movability of the triangle.
  void SetMovability(const BRepMesh_DegreeOfFreedom theMovability) { myMovability = theMovability; }

  //! Checks for equality with another triangle.
  //! @param theOther triangle to be checked against this one.
  //! @return TRUE if equal, FALSE if not.
  bool IsEqual(const BRepMesh_Triangle& theOther) const
  {
    if (myMovability == BRepMesh_Deleted || theOther.myMovability == BRepMesh_Deleted)
      return false;

    if (myEdges[0] == theOther.myEdges[0] && myEdges[1] == theOther.myEdges[1]
        && myEdges[2] == theOther.myEdges[2])
    {
      return true;
    }

    if (myEdges[0] == theOther.myEdges[1] && myEdges[1] == theOther.myEdges[2]
        && myEdges[2] == theOther.myEdges[0])
    {
      return true;
    }

    if (myEdges[0] == theOther.myEdges[2] && myEdges[1] == theOther.myEdges[0]
        && myEdges[2] == theOther.myEdges[1])
    {
      return true;
    }

    return false;
  }

  //! Alias for IsEqual.
  bool operator==(const BRepMesh_Triangle& theOther) const { return IsEqual(theOther); }

  int                      myEdges[3];
  bool                     myOrientations[3];
  BRepMesh_DegreeOfFreedom myMovability;
};

namespace std
{
template <>
struct hash<BRepMesh_Triangle>
{
  size_t operator()(const BRepMesh_Triangle& theTriangle) const noexcept
  {
    int aCombination[3] = {theTriangle.myEdges[0], theTriangle.myEdges[1], theTriangle.myEdges[2]};
    std::sort(aCombination, aCombination + 3); // Sort the numbers in ascending order
    return opencascade::hashBytes(aCombination, sizeof(aCombination));
  }
};
} // namespace std

