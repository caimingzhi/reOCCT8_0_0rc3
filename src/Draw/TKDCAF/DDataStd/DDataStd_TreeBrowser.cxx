#include <DDataStd.hpp>
#include <DDataStd_TreeBrowser.hpp>
#include <Draw_Display.hpp>
#include <Draw_Drawable3D.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDataStd_Name.hpp>
#include <TDataStd_TreeNode.hpp>
#include <TDF.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DDataStd_TreeBrowser, Draw_Drawable3D)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Communication convention with tcl:
// tcl waits for a string of characters, being an information list.
// In this list, each item is separated from another by a separator: '\'.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define TDF_BrowserSeparator1 '\\'
#define TDF_BrowserSeparator2 ' '
#define TDF_BrowserSeparator3 '#'
#define TDF_BrowserSeparator4 ','

//=================================================================================================

DDataStd_TreeBrowser::DDataStd_TreeBrowser(const TDF_Label& aLabel)
    : myRoot(aLabel)
{
}

//=================================================================================================

void DDataStd_TreeBrowser::DrawOn(Draw_Display& /*dis*/) const
{
  std::cout << "DDataStd_TreeBrowser" << std::endl;
}

//=================================================================================================

occ::handle<Draw_Drawable3D> DDataStd_TreeBrowser::Copy() const
{
  return new DDataStd_TreeBrowser(myRoot);
}

//=================================================================================================

void DDataStd_TreeBrowser::Dump(Standard_OStream& S) const
{
  S << "DDataStd_TreeBrowser on a label: " << std::endl;
  S << myRoot;
}

//=================================================================================================

void DDataStd_TreeBrowser::Whatis(Draw_Interpretor& I) const
{
  I << "function browser";
}

//=================================================================================================

void DDataStd_TreeBrowser::Label(const TDF_Label& aLabel)
{
  myRoot = aLabel;
}

//=================================================================================================

TDF_Label DDataStd_TreeBrowser::Label() const
{
  return myRoot;
}

//=================================================================================================

TCollection_AsciiString DDataStd_TreeBrowser::OpenRoot() const
{
  TCollection_AsciiString        list;
  occ::handle<TDataStd_TreeNode> TN;
  if (myRoot.FindAttribute(TDataStd_TreeNode::GetDefaultTreeID(), TN))
  {
    OpenNode(TN, list);
  }
  return list;
}

//=======================================================================
// function : OpenNode
// purpose  :
// the items are separated by "\\".
//=======================================================================

TCollection_AsciiString DDataStd_TreeBrowser::OpenNode(const TDF_Label& aLabel) const
{
  TCollection_AsciiString        list;
  occ::handle<TDataStd_TreeNode> nodeToOpen;
  if (aLabel.FindAttribute(TDataStd_TreeNode::GetDefaultTreeID(), nodeToOpen))
  {
    bool                           split   = false;
    occ::handle<TDataStd_TreeNode> current = nodeToOpen->First();
    while (!current.IsNull())
    {
      if (split)
        list.AssignCat(TDF_BrowserSeparator1);
      OpenNode(current, list);
      split   = true;
      current = current->Next();
    }
  }
  return list;
}

//=======================================================================
// function : OpenNode
// purpose  :
// An item is composed as follows:
// "LabelEntry "Name" DynamicType Executable|Forgotten Failed|Success First|Null [ LabelFather]"
// First/Null : has/has not child
//=======================================================================

void DDataStd_TreeBrowser::OpenNode(const occ::handle<TDataStd_TreeNode>& aTreeNode,
                                    TCollection_AsciiString&              aList) const
{
  // Label entry. -0
  TCollection_AsciiString tmp;
  TDF_Tool::Entry(aTreeNode->Label(), tmp);
  aList.AssignCat(tmp);
  // Name         -1
  aList.AssignCat(TDF_BrowserSeparator2);
  occ::handle<TDataStd_Name> name;
  aList.AssignCat("\"");
  if (aTreeNode->Label().FindAttribute(TDataStd_Name::GetID(), name))
  {
    aList.AssignCat(name->Get());
  }
  aList.AssignCat("\"");
  // Dynamic type.      -2
  aList.AssignCat(TDF_BrowserSeparator2);
  TCollection_ExtendedString ext;
  if (TDF::ProgIDFromGUID(aTreeNode->ID(), ext))
    aList.AssignCat(ext);
  else
    aList.AssignCat(aTreeNode->DynamicType()->Name());
  // Executable or Forgotten?  -3
  //  aList.AssignCat(TDF_BrowserSeparator2);
  //   if (aTreeNode->IsExecutable()) aList.AssignCat("Executable");
  //   else aList.AssignCat("Forgotten");
  // Failed or Success?        -4
  //  aList.AssignCat(TDF_BrowserSeparator2);
  //   if (aTreeNode->Failed()) aList.AssignCat("Failed");
  //   else aList.AssignCat("Success");
  // Children?             -3
  aList.AssignCat(TDF_BrowserSeparator2);
  if (aTreeNode->First().IsNull())
    aList.AssignCat("Null");
  else
    aList.AssignCat("First");
  // Father?                -4
  aList.AssignCat(TDF_BrowserSeparator2);
  if (!aTreeNode->HasFather())
    aList.AssignCat("Null");
  else
  {
    TDF_Tool::Entry(aTreeNode->Father()->Label(), tmp);
    aList.AssignCat(tmp);
  }
  // First?                -5
  aList.AssignCat(TDF_BrowserSeparator2);
  if (!aTreeNode->HasFirst())
    aList.AssignCat("Null");
  else
  {
    TDF_Tool::Entry(aTreeNode->First()->Label(), tmp);
    aList.AssignCat(tmp);
  }
  // Next?                -6
  aList.AssignCat(TDF_BrowserSeparator2);
  if (!aTreeNode->HasNext())
    aList.AssignCat("Null");
  else
  {
    TDF_Tool::Entry(aTreeNode->Next()->Label(), tmp);
    aList.AssignCat(tmp);
  }
  // Previous?                -7
  aList.AssignCat(TDF_BrowserSeparator2);
  if (!aTreeNode->HasPrevious())
    aList.AssignCat("Null");
  else
  {
    TDF_Tool::Entry(aTreeNode->Previous()->Label(), tmp);
    aList.AssignCat(tmp);
  }
}
