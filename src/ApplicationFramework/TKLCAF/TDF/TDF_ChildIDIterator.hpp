#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_GUID.hpp>
#include <TDF_ChildIterator.hpp>
class TDF_Attribute;
class TDF_Label;

//! Iterates on the children of a label, to find
//! attributes having ID as Attribute ID.
//!
//! Level option works as TDF_ChildIterator.
class TDF_ChildIDIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty iterator.
  Standard_EXPORT TDF_ChildIDIterator();

  //! Iterates on the children of the given label. If
  //! <allLevels> option is set to true, it explores not
  //! only the first, but all the sub label levels.
  Standard_EXPORT TDF_ChildIDIterator(const TDF_Label&     aLabel,
                                      const Standard_GUID& anID,
                                      const bool           allLevels = false);

  //! Initializes the iteration on the children of the
  //! given label. If <allLevels> option is set to true,
  //! it explores not only the first, but all the sub
  //! label levels.
  Standard_EXPORT void Initialize(const TDF_Label&     aLabel,
                                  const Standard_GUID& anID,
                                  const bool           allLevels = false);

  //! Returns True if there is a current Item in the
  //! iteration.
  bool More() const;

  //! Move to the next Item
  Standard_EXPORT void Next();

  //! Move to the next Brother. If there is none, go up
  //! etc. This method is interesting only with
  //! "allLevels" behavior, because it avoids to explore
  //! the current label children.
  Standard_EXPORT void NextBrother();

  //! Returns the current item; a null handle if there is none.
  occ::handle<TDF_Attribute> Value() const;

private:
  Standard_GUID              myID;
  TDF_ChildIterator          myItr;
  occ::handle<TDF_Attribute> myAtt;
};

inline bool TDF_ChildIDIterator::More() const
{
  return !myAtt.IsNull();
}

inline occ::handle<TDF_Attribute> TDF_ChildIDIterator::Value() const
{
  return myAtt;
}
