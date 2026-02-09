#pragma once

#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_UBTree.hpp>

class BRepBuilderAPI_BndBoxTreeSelector : public NCollection_UBTree<int, Bnd_Box>::Selector
{
public:
  BRepBuilderAPI_BndBoxTreeSelector()

    = default;

  bool Reject(const Bnd_Box& theBox) const override { return (myBox.IsOut(theBox)); }

  bool Accept(const int& theObj) override
  {
    myResInd.Append(theObj);
    return true;
  }

  void ClearResList() { myResInd.Clear(); }

  void SetCurrent(const Bnd_Box& theBox) { myBox = theBox; }

  const NCollection_List<int>& ResInd() { return myResInd; }

private:
  NCollection_List<int> myResInd;
  Bnd_Box               myBox;
};
