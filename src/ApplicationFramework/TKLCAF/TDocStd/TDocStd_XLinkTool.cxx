#include <TDocStd_XLinkTool.hpp>

#include <TDataStd_TreeNode.hpp>
#include <TDF_ClosureMode.hpp>
#include <TDF_ClosureTool.hpp>
#include <TDF_CopyTool.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_IDFilter.hpp>
#include <TDF_Label.hpp>
#include <TDF_Reference.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDF_Tool.hpp>
#include <TDocStd_Document.hpp>
#include <TDocStd_XLink.hpp>

TDocStd_XLinkTool::TDocStd_XLinkTool()
{
  isDone = false;
  myRT   = new TDF_RelocationTable();
}

void TDocStd_XLinkTool::Copy(const TDF_Label& target, const TDF_Label& source)
{
  occ::handle<TDocStd_Document> TARGET, SOURCE;
  TARGET = TDocStd_Document::Get(target);
  SOURCE = TDocStd_Document::Get(source);
  if (TARGET != SOURCE)
  {
    if (!TDF_Tool::IsSelfContained(source))
    {
      throw Standard_DomainError("TDocStd_XLinkTool::Copy : not self-contained");
    }
  }

  occ::handle<TDataStd_TreeNode> aFather, aPrev, aNext;
  occ::handle<TDataStd_TreeNode> anOldFather, anOldPrev, anOldNext;
  occ::handle<TDataStd_TreeNode> aNode, anOldNode;
  if (TDataStd_TreeNode::Find(source, aNode))
  {
    aFather = aNode->Father();
    aPrev   = aNode->Previous();
    aNext   = aNode->Next();
    aNode->Remove();
  }
  if (TDataStd_TreeNode::Find(target, anOldNode))
  {
    anOldFather = anOldNode->Father();
    anOldPrev   = anOldNode->Previous();
    anOldNext   = anOldNode->Next();
    anOldNode->Remove();
  }

  myRT                        = new TDF_RelocationTable(true);
  myDS                        = new TDF_DataSet;
  occ::handle<TDF_DataSet> DS = new TDF_DataSet();
  TDF_ClosureMode          mode(true);
  myDS->AddLabel(source);
  myRT->SetRelocation(source, target);
  TDF_IDFilter filter(false);
  TDF_ClosureTool::Closure(myDS, filter, mode);
  TDF_CopyTool::Copy(myDS, myRT);

  if (!aNode.IsNull())
  {
    if (!aPrev.IsNull())
      aPrev->InsertAfter(aNode);
    else if (!aNext.IsNull())
    {
      aNext->InsertBefore(aNode);
    }
    else if (!aFather.IsNull())
      aNode->SetFather(aFather);
  }

  if (!anOldNode.IsNull())
  {
    if (TDataStd_TreeNode::Find(target, anOldNode))
    {
      if (!anOldPrev.IsNull())
        anOldPrev->InsertAfter(anOldNode);
      else if (!anOldNext.IsNull())
      {
        anOldNext->InsertBefore(anOldNode);
      }
      else if (!anOldFather.IsNull())
        anOldNode->SetFather(anOldFather);
    }
  }

  isDone = true;
}

void TDocStd_XLinkTool::CopyWithLink(const TDF_Label& target, const TDF_Label& source)
{
  occ::handle<TDF_Reference> REF;
  if (target.FindAttribute(TDF_Reference::GetID(), REF))
  {
    throw Standard_DomainError(" TDocStd_CopyWithLink : already a ref");
  }
  Copy(target, source);
  if (isDone)
  {
    TCollection_AsciiString xlabelentry, xdocentry;
    TDF_Tool::Entry(source, xlabelentry);
    occ::handle<TDocStd_Document> aSourceD  = TDocStd_Document::Get(source);
    occ::handle<TDocStd_Document> aTargetD  = TDocStd_Document::Get(target);
    int                           aDocEntry = 0;
    if (aSourceD != aTargetD)
      aDocEntry = aTargetD->CreateReference(aSourceD);
    xdocentry = aDocEntry;

    occ::handle<TDocStd_XLink> X = TDocStd_XLink::Set(target);
    X->LabelEntry(xlabelentry);
    X->DocumentEntry(xdocentry);
    TDF_Reference::Set(target, source);
    isDone = true;
  }
}

void TDocStd_XLinkTool::UpdateLink(const TDF_Label& label)
{
  occ::handle<TDF_Reference> REF;
  if (!label.FindAttribute(TDF_Reference::GetID(), REF))
  {
    throw Standard_DomainError(" TDocStd_XLinkTool::UpdateLink : not ref registered");
  }
  TDocStd_XLinkTool XLinkTool;
  Copy(label, REF->Get());
}

bool TDocStd_XLinkTool::IsDone() const
{
  return isDone;
}

occ::handle<TDF_RelocationTable> TDocStd_XLinkTool::RelocationTable() const
{
  return myRT;
}

occ::handle<TDF_DataSet> TDocStd_XLinkTool::DataSet() const
{
  return myDS;
}
