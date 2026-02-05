#pragma once

#include <BVH_Traverse.hpp>
#include <BVH_BoxSet.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>

//! Template Selector for elements selection from BVH tree.
template <int Dimension>
class BOPTools_BoxSelector
    : public BVH_Traverse<double, Dimension, BVH_BoxSet<double, Dimension, int>, bool>
{
public:
  typedef typename BVH::VectorType<double, Dimension>::Type BVH_VecNd;

public: //! @name Constructor
  //! Empty constructor
  BOPTools_BoxSelector() = default;

public: //! @name public interfaces
  //! Clears the indices
  void Clear() { myIndices.Clear(); }

  //! Sets the box
  void SetBox(const BVH_Box<double, Dimension>& theBox) { myBox = theBox; }

  //! Returns the list of accepted indices
  const NCollection_List<int>& Indices() const { return myIndices; }

public: //! @name Rejection/Acceptance rules
  //! Checks if the box should be rejected
  bool RejectNode(const BVH_VecNd& theCMin,
                  const BVH_VecNd& theCMax,
                  bool&            theIsInside) const override
  {
    bool hasOverlap;
    theIsInside = myBox.Contains(theCMin, theCMax, hasOverlap);
    return !hasOverlap;
  }

  //! Checks if the element should be rejected
  bool RejectElement(const int theIndex) { return myBox.IsOut(this->myBVHSet->Box(theIndex)); }

  //! Checks if the metric of the node may be accepted
  bool AcceptMetric(const bool& theIsInside) const override { return theIsInside; }

  //! Accepts the element with the index <theIndex> in BVH tree
  bool Accept(const int theIndex, const bool& theIsInside) override
  {
    if (theIsInside || !RejectElement(theIndex))
    {
      myIndices.Append(this->myBVHSet->Element(theIndex));
      return true;
    }
    return false;
  }

protected:                              //! @name Fields
  BVH_Box<double, Dimension> myBox;     //!< Selection box
  NCollection_List<int>      myIndices; //!< Selected indices
};
