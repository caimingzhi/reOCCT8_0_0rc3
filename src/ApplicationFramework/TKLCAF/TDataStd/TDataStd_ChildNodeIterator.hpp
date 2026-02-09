#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
class TDataStd_TreeNode;

class TDataStd_ChildNodeIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDataStd_ChildNodeIterator();

  Standard_EXPORT TDataStd_ChildNodeIterator(const occ::handle<TDataStd_TreeNode>& aTreeNode,
                                             const bool allLevels = false);

  Standard_EXPORT void Initialize(const occ::handle<TDataStd_TreeNode>& aTreeNode,
                                  const bool                            allLevels = false);

  bool More() const { return !myNode.IsNull(); }

  Standard_EXPORT void Next();

  Standard_EXPORT void NextBrother();

  const occ::handle<TDataStd_TreeNode>& Value() const { return myNode; }

private:
  occ::handle<TDataStd_TreeNode> myNode;
  int                            myFirstLevel;
};
