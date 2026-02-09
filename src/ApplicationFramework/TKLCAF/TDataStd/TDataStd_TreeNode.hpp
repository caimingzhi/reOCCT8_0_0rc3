#pragma once

#include <Standard.hpp>

class TDataStd_TreeNode;
typedef TDataStd_TreeNode* TDataStd_PtrTreeNode;

#include <Standard_GUID.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class TDF_AttributeDelta;
class TDF_RelocationTable;
class TDF_DataSet;

class TDataStd_TreeNode : public TDF_Attribute
{

public:
  Standard_EXPORT static bool Find(const TDF_Label& L, occ::handle<TDataStd_TreeNode>& T);

  Standard_EXPORT static occ::handle<TDataStd_TreeNode> Set(const TDF_Label& L);

  Standard_EXPORT static occ::handle<TDataStd_TreeNode> Set(const TDF_Label&     L,
                                                            const Standard_GUID& ExplicitTreeID);

  Standard_EXPORT static const Standard_GUID& GetDefaultTreeID();

  Standard_EXPORT TDataStd_TreeNode();

  Standard_EXPORT bool Append(const occ::handle<TDataStd_TreeNode>& Child);

  Standard_EXPORT bool Prepend(const occ::handle<TDataStd_TreeNode>& Child);

  Standard_EXPORT bool InsertBefore(const occ::handle<TDataStd_TreeNode>& Node);

  Standard_EXPORT bool InsertAfter(const occ::handle<TDataStd_TreeNode>& Node);

  Standard_EXPORT bool Remove();

  Standard_EXPORT int Depth() const;

  Standard_EXPORT int NbChildren(const bool allLevels = false) const;

  Standard_EXPORT bool IsAscendant(const occ::handle<TDataStd_TreeNode>& of) const;

  Standard_EXPORT bool IsDescendant(const occ::handle<TDataStd_TreeNode>& of) const;

  Standard_EXPORT bool IsRoot() const;

  Standard_EXPORT occ::handle<TDataStd_TreeNode> Root() const;

  Standard_EXPORT bool IsFather(const occ::handle<TDataStd_TreeNode>& of) const;

  Standard_EXPORT bool IsChild(const occ::handle<TDataStd_TreeNode>& of) const;

  bool HasFather() const;

  Standard_EXPORT occ::handle<TDataStd_TreeNode> Father() const;

  bool HasNext() const;

  Standard_EXPORT occ::handle<TDataStd_TreeNode> Next() const;

  bool HasPrevious() const;

  Standard_EXPORT occ::handle<TDataStd_TreeNode> Previous() const;

  bool HasFirst() const;

  Standard_EXPORT occ::handle<TDataStd_TreeNode> First() const;

  bool HasLast() const;

  Standard_EXPORT occ::handle<TDataStd_TreeNode> Last();

  Standard_EXPORT occ::handle<TDataStd_TreeNode> FindLast();

  Standard_EXPORT void SetTreeID(const Standard_GUID& explicitID);

  Standard_EXPORT void SetFather(const occ::handle<TDataStd_TreeNode>& F);

  Standard_EXPORT void SetNext(const occ::handle<TDataStd_TreeNode>& F);

  Standard_EXPORT void SetPrevious(const occ::handle<TDataStd_TreeNode>& F);

  Standard_EXPORT void SetFirst(const occ::handle<TDataStd_TreeNode>& F);

  Standard_EXPORT void SetLast(const occ::handle<TDataStd_TreeNode>& F);

  Standard_EXPORT void AfterAddition() override;

  Standard_EXPORT void BeforeForget() override;

  Standard_EXPORT void AfterResume() override;

  Standard_EXPORT bool BeforeUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                  const bool                             forceIt = false) override;

  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                 const bool                             forceIt = false) override;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& aDataSet) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  friend class TDataStd_ChildNodeIterator;

  DEFINE_STANDARD_RTTIEXT(TDataStd_TreeNode, TDF_Attribute)

private:
  TDataStd_PtrTreeNode myFather;
  TDataStd_PtrTreeNode myPrevious;
  TDataStd_PtrTreeNode myNext;
  TDataStd_PtrTreeNode myFirst;
  TDataStd_PtrTreeNode myLast;
  Standard_GUID        myTreeID;
};

inline bool TDataStd_TreeNode::HasFather() const
{
  return myFather != nullptr;
}

inline bool TDataStd_TreeNode::HasNext() const
{
  return myNext != nullptr;
}

inline bool TDataStd_TreeNode::HasPrevious() const
{
  return myPrevious != nullptr;
}

inline bool TDataStd_TreeNode::HasFirst() const
{
  return myFirst != nullptr;
}

inline bool TDataStd_TreeNode::HasLast() const
{
  return myLast != nullptr;
}
