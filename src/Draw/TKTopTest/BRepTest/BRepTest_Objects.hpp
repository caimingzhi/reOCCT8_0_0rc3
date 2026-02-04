#pragma once


#include <BRepTools_History.hpp>

//! Provides the access to the useful tools common for the algorithms.
class BRepTest_Objects
{
public:
  //! Sets the given history into the session.
  Standard_EXPORT static void SetHistory(const occ::handle<BRepTools_History>& theHistory);

  //! Adds the given history to the history in the session.
  Standard_EXPORT static void AddHistory(const occ::handle<BRepTools_History>& theHistory);

  //! Sets the history of the given algorithm into the session.
  template <class TheAlgo>
  static void SetHistory(const NCollection_List<TopoDS_Shape>& theArguments, TheAlgo& theAlgo)
  {
    SetHistory(new BRepTools_History(theArguments, theAlgo));
  }

  //! Adds the history of the given algorithm into the session.
  template <class TheAlgo>
  static void AddHistory(const NCollection_List<TopoDS_Shape>& theArguments, TheAlgo& theAlgo)
  {
    AddHistory(new BRepTools_History(theArguments, theAlgo));
  }

  //! Returns the history from the session.
  Standard_EXPORT static occ::handle<BRepTools_History> History();

  //! Enables/Disables the history saving
  Standard_EXPORT static void SetToFillHistory(const bool theFillHist);

  //! Returns the flag controlling the history collection
  Standard_EXPORT static bool IsHistoryNeeded();
};

