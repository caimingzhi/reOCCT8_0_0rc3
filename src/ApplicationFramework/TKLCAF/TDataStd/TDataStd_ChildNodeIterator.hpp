#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
class TDataStd_TreeNode;

//! Iterates on the ChildStepren step of a step, at the
//! first level only. It is possible to ask the
//! iterator to explore all the sub step levels of the
//! given one, with the option "allLevels".
class TDataStd_ChildNodeIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty iterator.
  Standard_EXPORT TDataStd_ChildNodeIterator();

  //! Iterates on the ChildStepren of the given Step. If
  //! <allLevels> option is set to true, it explores not
  //! only the first, but all the sub Step levels.
  Standard_EXPORT TDataStd_ChildNodeIterator(const occ::handle<TDataStd_TreeNode>& aTreeNode,
                                             const bool allLevels = false);

  //! Initializes the iteration on the Children Step of
  //! the given Step. If <allLevels> option is set to
  //! true, it explores not only the first, but all the
  //! sub Step levels.
  Standard_EXPORT void Initialize(const occ::handle<TDataStd_TreeNode>& aTreeNode,
                                  const bool                            allLevels = false);

  //! Returns True if there is a current Item in the
  //! iteration.
  bool More() const { return !myNode.IsNull(); }

  //! Move to the next Item
  Standard_EXPORT void Next();

  //! Move to the next Brother. If there is none, go up
  //! etc. This method is interesting only with
  //! "allLevels" behavior, because it avoids to explore
  //! the current Step ChildStepren.
  Standard_EXPORT void NextBrother();

  //! Returns the current item; a null Step if there is
  //! no one.
  const occ::handle<TDataStd_TreeNode>& Value() const { return myNode; }

private:
  occ::handle<TDataStd_TreeNode> myNode;
  int                            myFirstLevel;
};
