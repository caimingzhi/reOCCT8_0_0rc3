#pragma once

#include <Standard_Type.hpp>
#include <Standard_HashUtils.hpp>

typedef std::pair<int, int> MeshVS_NodePair;

//! Provides symmetric hash methods pair of integers.
struct MeshVS_SymmetricPairHasher
{
  //! Computes a hash code for the node pair
  //! @param theNodePair the node pair which hash code is to be computed
  //! @return a computed hash code
  size_t operator()(const MeshVS_NodePair& theNodePair) const noexcept
  {
    // Combine two int values into a single hash value.
    int aCombination[2]{theNodePair.first, theNodePair.second};
    if (aCombination[0] > aCombination[1])
    {
      std::swap(aCombination[0], aCombination[1]);
    }
    return opencascade::hashBytes(aCombination, sizeof(aCombination));
  }

  bool operator()(const MeshVS_NodePair& thePair1, const MeshVS_NodePair& thePair2) const noexcept
  {
    return (thePair1.first == thePair2.first && thePair1.second == thePair2.second)
           || (thePair1.first == thePair2.second && thePair1.second == thePair2.first);
  }
};
