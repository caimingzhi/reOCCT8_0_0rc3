#pragma once

#include <BVH_Traverse.hpp>
#include <BVH_BoxSet.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>

template <int Dimension>
class BOPTools_BoxSelector
    : public BVH_Traverse<double, Dimension, BVH_BoxSet<double, Dimension, int>, bool>
{
public:
  typedef typename BVH::VectorType<double, Dimension>::Type BVH_VecNd;

public:
  BOPTools_BoxSelector() = default;

public:
  void Clear() { myIndices.Clear(); }

  void SetBox(const BVH_Box<double, Dimension>& theBox) { myBox = theBox; }

  const NCollection_List<int>& Indices() const { return myIndices; }

public:
  bool RejectNode(const BVH_VecNd& theCMin,
                  const BVH_VecNd& theCMax,
                  bool&            theIsInside) const override
  {
    bool hasOverlap;
    theIsInside = myBox.Contains(theCMin, theCMax, hasOverlap);
    return !hasOverlap;
  }

  bool RejectElement(const int theIndex) { return myBox.IsOut(this->myBVHSet->Box(theIndex)); }

  bool AcceptMetric(const bool& theIsInside) const override { return theIsInside; }

  bool Accept(const int theIndex, const bool& theIsInside) override
  {
    if (theIsInside || !RejectElement(theIndex))
    {
      myIndices.Append(this->myBVHSet->Element(theIndex));
      return true;
    }
    return false;
  }

protected:
  BVH_Box<double, Dimension> myBox;
  NCollection_List<int>      myIndices;
};
