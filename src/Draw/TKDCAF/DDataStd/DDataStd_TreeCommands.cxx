#include <DDataStd.hpp>
#include <DDataStd_TreeBrowser.hpp>
#include <DDF.hpp>
#include <Draw_Appli.hpp>
#include <Draw_Interpretor.hpp>
#include <Message.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDataStd_ChildNodeIterator.hpp>
#include <TDataStd_TreeNode.hpp>
#include <TDF_Data.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>

#include <cstdio>

static int DDataStd_SetNode(Draw_Interpretor& di, int n, const char** a)
{
  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(a[1], DF))
    return 1;
  TDF_Label                      L;
  occ::handle<TDataStd_TreeNode> TN;
  DDF::AddLabel(DF, a[2], L);
  if (n == 3)
  {
    TN = TDataStd_TreeNode::Set(L);
    DDF::ReturnLabel(di, TN->Label());
    return 0;
  }
  else if (n == 4)
  {
    if (!Standard_GUID::CheckGUIDFormat(a[3]))
    {
      di << "DDataStd_SetNode: The format of GUID is invalid\n";
      return 1;
    }
    const Standard_GUID ID(a[3]);
    TN = TDataStd_TreeNode::Set(L, ID);
    DDF::ReturnLabel(di, TN->Label());
    return 0;
  }
  di << "DDataStd_SetNode : Error\n";
  return 1;
}

static int DDataStd_AppendNode(Draw_Interpretor& di, int n, const char** a)
{
  if (n >= 4)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    occ::handle<TDataStd_TreeNode> father, child;

    Standard_GUID ID;
    if (n == 4)
      ID = Standard_GUID(TDataStd_TreeNode::GetDefaultTreeID());
    else
    {
      if (!Standard_GUID::CheckGUIDFormat(a[4]))
      {
        di << "DDataStd_AppendNode: The format of GUID is invalid\n";
        return 1;
      }
      const Standard_GUID varID(a[4]);
      ID = varID;
    }

    if (!DDF::Find(DF, a[2], ID, father))
      return 1;

    TDF_Label L;
    DDF::AddLabel(DF, a[3], L);
    if ((L.FindAttribute(ID, child)) && (!child->IsRoot()))
    {
      di << "DDataStd_AppendNode : Error : childTreeNode don't detach\n";
      return 1;
    }
    child = TDataStd_TreeNode::Set(L, ID);
    if (!father->Append(child))
      return 1;
#ifdef OCCT_DEBUG
    di << "AppendNode: OK\n";
#endif
    return 0;
  }
  di << "DDataStd_AppendNode : Error\n";
  return 1;
}

static int DDataStd_PrependNode(Draw_Interpretor& di, int n, const char** a)
{
  if (n >= 4)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    occ::handle<TDataStd_TreeNode> father, child;

    Standard_GUID ID;
    if (n == 4)
      ID = Standard_GUID(TDataStd_TreeNode::GetDefaultTreeID());
    else
    {
      if (!Standard_GUID::CheckGUIDFormat(a[4]))
      {
        di << "DDataStd_PrependNode: The format of GUID is invalid\n";
        return 1;
      }
      const Standard_GUID varID(a[4]);
      ID = varID;
    }

    if (!DDF::Find(DF, a[2], ID, father))
      return 1;

    TDF_Label L;
    DDF::AddLabel(DF, a[3], L);
    if ((L.FindAttribute(ID, child)) && (!child->IsRoot()))
    {
      di << "DDataStd_PrependNode : Error : childTreeNode don't detach\n";
      return 1;
    }
    child = TDataStd_TreeNode::Set(L, ID);
    if (!father->Prepend(child))
      return 1;
#ifdef OCCT_DEBUG
    di << "PrependNode: OK\n";
#endif
    return 0;
  }
  di << "DDataStd_PrependNode : Error\n";
  return 1;
}

static int DDataStd_RootNode(Draw_Interpretor& di, int n, const char** a)
{
  if (n >= 3)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    occ::handle<TDataStd_TreeNode> TN;

    Standard_GUID ID;
    if (n == 3)
      ID = Standard_GUID(TDataStd_TreeNode::GetDefaultTreeID());
    else
    {
      if (!Standard_GUID::CheckGUIDFormat(a[3]))
      {
        di << "DDataStd_RootNode: The format of GUID is invalid\n";
        return 1;
      }
      const Standard_GUID varID(a[3]);
      ID = varID;
    }

    if (!DDF::Find(DF, a[2], ID, TN))
      return 1;
    DDF::ReturnLabel(di, TN->Root()->Label());
    return 0;
  }
  di << "DDataStd_RootNode : Error\n";
  return 1;
}

static int DDataStd_InsertNodeBefore(Draw_Interpretor& di, int n, const char** a)
{
  if (n >= 4)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    occ::handle<TDataStd_TreeNode> current, TN;

    Standard_GUID ID;
    if (n == 4)
      ID = Standard_GUID(TDataStd_TreeNode::GetDefaultTreeID());
    else
    {
      if (!Standard_GUID::CheckGUIDFormat(a[4]))
      {
        di << "DDataStd_InsertNodeBefore: The format of GUID is invalid\n";
        return 1;
      }
      const Standard_GUID varID(a[4]);
      ID = varID;
    }

    if (!DDF::Find(DF, a[2], ID, current))
      return 1;

    TDF_Label L;
    if (!DDF::FindLabel(DF, a[3], L))
      return 1;
    TN = TDataStd_TreeNode::Set(L, ID);
    if (!current->InsertBefore(TN))
      return 1;
    return 0;
  }
  di << "DDataStd_InsertBefore : Error\n";
  return 1;
}

static int DDataStd_InsertNodeAfter(Draw_Interpretor& di, int n, const char** a)
{
  if (n >= 4)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    occ::handle<TDataStd_TreeNode> current, TN;

    Standard_GUID ID;
    if (n == 4)
      ID = Standard_GUID(TDataStd_TreeNode::GetDefaultTreeID());
    else
    {
      if (!Standard_GUID::CheckGUIDFormat(a[4]))
      {
        di << "DDataStd_InsertNodeAfter: The format of GUID is invalid\n";
        return 1;
      }
      const Standard_GUID varID(a[4]);
      ID = varID;
    }

    if (!DDF::Find(DF, a[2], ID, current))
      return 1;

    TDF_Label L;
    if (!DDF::FindLabel(DF, a[3], L))
      return 1;
    TN = TDataStd_TreeNode::Set(L);
    if (!current->InsertAfter(TN))
      return 1;
    return 0;
  }
  di << "DDataStd_InsertNodeAfter : Error\n";
  return 1;
}

static int DDataStd_DetachNode(Draw_Interpretor& di, int n, const char** a)
{
  if (n >= 3)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    occ::handle<TDataStd_TreeNode> TN;

    Standard_GUID ID;
    if (n == 3)
      ID = Standard_GUID(TDataStd_TreeNode::GetDefaultTreeID());
    else
    {
      if (!Standard_GUID::CheckGUIDFormat(a[3]))
      {
        di << "DDataStd_DetachNode: The format of GUID is invalid\n";
        return 1;
      }
      const Standard_GUID varID(a[3]);
      ID = varID;
    }

    if (!DDF::Find(DF, a[2], ID, TN))
      return 1;
    if (!TN->Remove())
      di << "Can't Detach the TreeNode\n";
    return 0;
  }
  di << "DDataStd_DetachNode : Error\n";
  return 1;
}

static int DDataStd_TreeBrowse(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 3)
    return 1;

  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(a[1], DF))
    return 1;

  TDF_Label lab;
  TDF_Tool::Label(DF, a[2], lab);

  occ::handle<DDataStd_TreeBrowser> NewTreeNode = new DDataStd_TreeBrowser(lab);
  char*                             name        = new char[50];
  if (n == 4)
    Sprintf(name, "treebrowser_%s", a[3]);
  else
    Sprintf(name, "treebrowser_%s", a[1]);

  Draw::Set(name, NewTreeNode);
  TCollection_AsciiString inst1("treebrowser ");
  inst1.AssignCat(name);
  di.Eval(inst1.ToCString());
  return 0;
}

static int DDataStd_OpenNode(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<DDataStd_TreeBrowser> browser =
    occ::down_cast<DDataStd_TreeBrowser>(Draw::GetExisting(a[1]));
  if (browser.IsNull())
  {
    Message::SendFail() << "Syntax error: browser '" << a[1] << "' not found";
    return 1;
  }

  TDF_Label lab;
  if (n == 3)
    TDF_Tool::Label(browser->Label().Data(), a[2], lab);

  if (n == 2 || lab.IsNull())
  {
    TCollection_AsciiString list = browser->OpenRoot();
    di << list.ToCString();
  }
  else
  {
    TCollection_AsciiString list = browser->OpenNode(lab);
    di << list.ToCString();
  }
  return 0;
}

static int DDataStd_ChildNodeIterate(Draw_Interpretor& di, int n, const char** a)
{
  if (n >= 4)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    const bool                     AllLevels = (Draw::Atoi(a[3]) != 0);
    occ::handle<TDataStd_TreeNode> TN, Value;

    Standard_GUID ID;
    if (n == 4)
      ID = Standard_GUID(TDataStd_TreeNode::GetDefaultTreeID());
    else
    {
      if (!Standard_GUID::CheckGUIDFormat(a[4]))
      {
        di << "DDataStd_ChildNodeIterate: The format of GUID is invalid\n";
        return 1;
      }
      const Standard_GUID varID(a[4]);
      ID = varID;
    }

    if (!DDF::Find(DF, a[2], ID, TN))
      return 1;

    TDataStd_ChildNodeIterator itr(TN, AllLevels);
    for (; itr.More(); itr.Next())
    {
      Value = itr.Value();
      TCollection_AsciiString entry;
      TDF_Tool::Entry(Value->Label(), entry);
      di << entry << "\n";
    }
    di << "\n";
    return 0;
  }
  di << "DDataStd_ChildNodeIterate : Error\n";
  return 1;
}

static TDataStd_ChildNodeIterator cni;

static int DDataStd_InitChildNodeIterator(Draw_Interpretor& di, int n, const char** a)
{
  if (n >= 4)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    occ::handle<TDataStd_TreeNode> TN, Value;

    Standard_GUID ID;
    if (n == 4)
      ID = Standard_GUID(TDataStd_TreeNode::GetDefaultTreeID());
    else
    {
      if (!Standard_GUID::CheckGUIDFormat(a[4]))
      {
        di << "DDataStd_ChildNodeIterator: The format of GUID is invalid\n";
        return 1;
      }
      const Standard_GUID varID(a[4]);
      ID = varID;
    }

    if (!DDF::Find(DF, a[2], ID, TN))
      return 1;
    const bool AllLevels = (Draw::Atoi(a[3]) != 0);
    cni.Initialize(TN, AllLevels);
    return 0;
  }
  di << "DDataStd_InitChildNodeIterator : Error\n";
  return 1;
}

static int DDataStd_ChildNodeMore(Draw_Interpretor& di, int, const char**)
{
  if (cni.More())
  {
    di << "TRUE\n";
  }
  else
  {
    di << "FALSE\n";
  }
  return 0;
}

static int DDataStd_ChildNodeNext(Draw_Interpretor&, int, const char**)
{
  cni.Next();
  return 0;
}

static int DDataStd_ChildNodeNextBrother(Draw_Interpretor&, int, const char**)
{
  cni.NextBrother();
  return 0;
}

static int DDataStd_ChildNodeValue(Draw_Interpretor& di, int, const char**)
{
  TCollection_AsciiString entry;
  TDF_Tool::Entry(cni.Value()->Label(), entry);
  di << entry << "\n";
  return 0;
}

void DDataStd::TreeCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  const char* g = "DData : Standard Attribute Commands";

  theCommands.Add("SetNode", "SetNode (DOC Entry [GUID])", __FILE__, DDataStd_SetNode, g);

  theCommands.Add("AppendNode",
                  "AppendNode (DOC FatherEntry childEntry [fatherGUID])",
                  __FILE__,
                  DDataStd_AppendNode,
                  g);

  theCommands.Add("PrependNode",
                  "PrependNode (DOC FatherEntry childEntry [fatherGUID])",
                  __FILE__,
                  DDataStd_PrependNode,
                  g);

  theCommands.Add("InsertNodeBefore",
                  "InsertNodeBefore (DOC TreeNodeEntry TreeNodeWhichHasToBeBefore [GUID])",
                  __FILE__,
                  DDataStd_InsertNodeBefore,
                  g);

  theCommands.Add("InsertNodeAfter",
                  "InsertNodeAfter (DOC TreeNodeEntry TreeNodeWhichHasToBeAfter [GUID])",
                  __FILE__,
                  DDataStd_InsertNodeAfter,
                  g);

  theCommands.Add("DetachNode",
                  "DetachNode (DOC TreeNodeEntry [GUID])",
                  __FILE__,
                  DDataStd_DetachNode,
                  g);

  theCommands.Add("RootNode",
                  "RootNode (DOC TreeNodeEntry [GUID])",
                  __FILE__,
                  DDataStd_RootNode,
                  g);

  theCommands.Add("TreeBrowse",
                  "TreeBrowse dfname entry [browsername]",
                  __FILE__,
                  DDataStd_TreeBrowse,
                  g);

  theCommands.Add("OpenNode",
                  "PRIVATE COMMAND FOR TREE BROWSER!\nReturns the list of sub-TreeNodes : "
                  "OpenTreeNode browsername [entry]",
                  __FILE__,
                  DDataStd_OpenNode,
                  g);

  theCommands.Add("ChildNodeIterate",
                  "ChildNodeIterate Doc TreeNode AllLevels [GUID]",
                  __FILE__,
                  DDataStd_ChildNodeIterate,
                  g);

  theCommands.Add("InitChildNodeIterator",
                  "InitChildNodeIterator Doc TreeNode AllLevels [GUID]",
                  __FILE__,
                  DDataStd_InitChildNodeIterator,
                  g);

  theCommands.Add("ChildNodeMore", "ChildNodeMore", __FILE__, DDataStd_ChildNodeMore, g);

  theCommands.Add("ChildNodeNext", "ChildNodeNext", __FILE__, DDataStd_ChildNodeNext, g);

  theCommands.Add("ChildNodeNextBrother",
                  "ChildNodeNextBrother",
                  __FILE__,
                  DDataStd_ChildNodeNextBrother,
                  g);

  theCommands.Add("ChildNodeValue", "ChildNodeValue", __FILE__, DDataStd_ChildNodeValue, g);
}
