#pragma once


#include <Standard.hpp>
#include <Standard_Macro.hpp>
#include <Standard_HashUtils.hpp>

//! Structure containing two IDs (of nodes) for using as a key in a map
//! (as representation of a mesh link)
//!
struct MeshVS_TwoNodes
{
  int First, Second;

  MeshVS_TwoNodes(int aFirst = 0, int aSecond = 0)
      : First(aFirst),
        Second(aSecond)
  {
  }

  bool operator==(const MeshVS_TwoNodes& theTwoNode) const
  {
    return ((First == theTwoNode.First) && (Second == theTwoNode.Second))
           || ((First == theTwoNode.Second) && (Second == theTwoNode.First));
  }
};

namespace std
{
template <>
struct hash<MeshVS_TwoNodes>
{
  size_t operator()(const MeshVS_TwoNodes& theTwoNodes) const noexcept
  {
    // Combine two int values into a single hash value.
    int aCombination[2]{theTwoNodes.First, theTwoNodes.Second};
    if (aCombination[0] > aCombination[1])
    {
      std::swap(aCombination[0], aCombination[1]);
    }
    return opencascade::hashBytes(aCombination, sizeof(aCombination));
  }
};
} // namespace std

