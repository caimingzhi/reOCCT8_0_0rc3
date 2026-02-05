#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <TDF_Label.hpp>
class TDF_Label;

//! Iterates on the children of a label, at the first
//! level only. It is possible to ask the iterator to
//! explore all the sub label levels of the given one,
//! with the option "allLevels".
class TDF_ChildIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty iterator object to
  //! explore the children of a label.
  Standard_EXPORT TDF_ChildIterator();

  //! Constructs the iterator object defined by
  //! the label aLabel. Iterates on the children of the given label. If
  //! <allLevels> option is set to true, it explores not
  //! only the first, but all the sub label levels.
  Standard_EXPORT TDF_ChildIterator(const TDF_Label& aLabel, const bool allLevels = false);

  //! Initializes the iteration on the children of the
  //! given label.
  //! If <allLevels> option is set to true,
  //! it explores not only the first, but all the sub
  //! label levels.
  //! If allLevels is false, only the first level of
  //! child labels is explored.
  //! In the example below, the label is iterated
  //! using Initialize, More and Next and its
  //! child labels dumped using TDF_Tool::Entry.
  //! Example
  //! void DumpChildren(const
  //! TDF_Label& aLabel)
  //! {
  //! TDF_ChildIterator it;
  //! TCollection_AsciiString es;
  //! for
  //! (it.Initialize(aLabel,true);
  //! it.More(); it.Next()){
  //! TDF_Tool::Entry(it.Value(),es);
  //! std::cout << as.ToCString() << std::endl;
  //! }
  //! }
  Standard_EXPORT void Initialize(const TDF_Label& aLabel, const bool allLevels = false);

  //! Returns true if a current label is found in the
  //! iteration process.
  bool More() const;

  //! Move the current iteration to the next Item.
  Standard_EXPORT void Next();

  //! Moves this iteration to the next brother
  //! label. A brother label is one with the same
  //! father as an initial label.
  //! Use this function when the non-empty
  //! constructor or Initialize has allLevels set to
  //! true. The result is that the iteration does not
  //! explore the children of the current label.
  //! This method is interesting only with
  //! "allLevels" behavior, because it avoids to explore
  //! the current label children.
  Standard_EXPORT void NextBrother();

  //! Returns the current label; or, if there is
  //! none, a null label.
  const TDF_Label Value() const;

private:
  TDF_LabelNodePtr myNode;
  int              myFirstLevel;
};

inline bool TDF_ChildIterator::More() const
{
  return (myNode != nullptr);
}

inline const TDF_Label TDF_ChildIterator::Value() const
{
  return TDF_Label(myNode);
}
