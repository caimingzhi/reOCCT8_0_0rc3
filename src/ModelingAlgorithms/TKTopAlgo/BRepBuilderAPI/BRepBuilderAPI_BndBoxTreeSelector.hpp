#pragma once

#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_UBTree.hpp>

//=======================================================================
//! Class BRepBuilderAPI_BndBoxTreeSelector
//!   derived from UBTree::Selector
//!   This class is used to select overlapping boxes, stored in
//!   NCollection::UBTree; contains methods to maintain the selection
//!   condition and to retrieve selected objects after search.
//=======================================================================

class BRepBuilderAPI_BndBoxTreeSelector : public NCollection_UBTree<int, Bnd_Box>::Selector
{
public:
  //! Constructor; calls the base class constructor
  BRepBuilderAPI_BndBoxTreeSelector()

    = default;

  //! Implementation of rejection method
  //! @return
  //!   True if the bounding box does not intersect with the current
  bool Reject(const Bnd_Box& theBox) const override { return (myBox.IsOut(theBox)); }

  //! Implementation of acceptance method
  //!   This method is called when the bounding box intersect with the current.
  //!   It stores the object - the index of box in the list of accepted objects.
  //! @return
  //!   True, because the object is accepted
  bool Accept(const int& theObj) override
  {
    myResInd.Append(theObj);
    return true;
  }

  //! Clear the list of intersecting boxes
  void ClearResList() { myResInd.Clear(); }

  //! Set current box to search for overlapping with him
  void SetCurrent(const Bnd_Box& theBox) { myBox = theBox; }

  //! Get list of indexes of boxes intersecting with the current box
  const NCollection_List<int>& ResInd() { return myResInd; }

private:
  NCollection_List<int> myResInd;
  Bnd_Box               myBox;
};
