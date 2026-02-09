#pragma once

#include <BRepTools_History.hpp>

class BRepTest_Objects
{
public:
  Standard_EXPORT static void SetHistory(const occ::handle<BRepTools_History>& theHistory);

  Standard_EXPORT static void AddHistory(const occ::handle<BRepTools_History>& theHistory);

  template <class TheAlgo>
  static void SetHistory(const NCollection_List<TopoDS_Shape>& theArguments, TheAlgo& theAlgo)
  {
    SetHistory(new BRepTools_History(theArguments, theAlgo));
  }

  template <class TheAlgo>
  static void AddHistory(const NCollection_List<TopoDS_Shape>& theArguments, TheAlgo& theAlgo)
  {
    AddHistory(new BRepTools_History(theArguments, theAlgo));
  }

  Standard_EXPORT static occ::handle<BRepTools_History> History();

  Standard_EXPORT static void SetToFillHistory(const bool theFillHist);

  Standard_EXPORT static bool IsHistoryNeeded();
};
