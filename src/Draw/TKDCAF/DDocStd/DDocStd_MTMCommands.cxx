#include <DDocStd.hpp>
#include <TDocStd_MultiTransactionManager.hpp>
#include <DDocStd_DrawDocument.hpp>
#include <Draw.hpp>
#include <DDF_Browser.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>
#include <TDF_AttributeIterator.hpp>
#include <TDataStd_TreeNode.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_Real.hpp>
#include <TDataStd_Name.hpp>
#include <TDataStd_Comment.hpp>
#include <TDataStd_AsciiString.hpp>
#include <TDataStd_IntegerArray.hpp>
#include <TDataStd_RealArray.hpp>
#include <TDataStd_ByteArray.hpp>
#include <TNaming_NamedShape.hpp>
#include <TopoDS_Shape.hpp>
#include <Draw_Interpretor.hpp>
#include <TDF_Reference.hpp>

static occ::handle<TDocStd_MultiTransactionManager> sMultiTransactionManager = nullptr;

static int mtmCreate(Draw_Interpretor&, int n, const char** a)
{
  if (!sMultiTransactionManager.IsNull())
    sMultiTransactionManager->SetUndoLimit(0);

  sMultiTransactionManager = new TDocStd_MultiTransactionManager();
  if (n > 1)
    sMultiTransactionManager->SetUndoLimit(Draw::Atoi(a[1]));
  return 0;
}

static int mtmAddDocument(Draw_Interpretor& di, int n, const char** a)
{
  if (sMultiTransactionManager.IsNull())
  {
    di << "Error   : manager is not initialised\n";
    return 1;
  }
  if (n > 1)
  {
    occ::handle<DDocStd_DrawDocument> aDrawDoc =
      occ::down_cast<DDocStd_DrawDocument>(Draw::Get(a[1]));
    if (aDrawDoc.IsNull())
    {
      di << "Error   : wrong document name\n";
      return 1;
    }
    sMultiTransactionManager->AddDocument(aDrawDoc->GetDocument());
  }
  else
  {
    di << "Error   : document name is not defined\n";
    return 1;
  }
  return 0;
}

static int mtmOpenTransaction(Draw_Interpretor& di, int, const char**)
{
  if (sMultiTransactionManager.IsNull())
  {
    di << "Error   : manager is not initialised\n";
    return 1;
  }
  sMultiTransactionManager->OpenCommand();
  return 0;
}

static int mtmCommitTransaction(Draw_Interpretor& di, int n, const char** a)
{
  if (sMultiTransactionManager.IsNull())
  {
    di << "Error   : manager is not initialised\n";
    return 1;
  }
  if (n > 1)
    sMultiTransactionManager->CommitCommand(TCollection_ExtendedString(a[1], true));
  else
    sMultiTransactionManager->CommitCommand();
  return 0;
}

static int mtmAbortTransaction(Draw_Interpretor& di, int, const char**)
{
  if (sMultiTransactionManager.IsNull())
  {
    di << "Error   : manager is not initialised\n";
    return 1;
  }
  sMultiTransactionManager->AbortCommand();
  return 0;
}

static int mtmDump(Draw_Interpretor& di, int, const char**)
{
  if (sMultiTransactionManager.IsNull())
  {
    di << "Error   : manager is not initialised\n";
    return 1;
  }
  di << "*** Dump of MTM ***\n";

  Standard_SStream aStream;
  sMultiTransactionManager->DumpTransaction(aStream);
  di << aStream;
  di << "\n***     End     ***\n";
  return 0;
}

static int mtmUndo(Draw_Interpretor& di, int, const char**)
{
  if (sMultiTransactionManager.IsNull())
  {
    di << "Error   : manager is not initialised\n";
    return 1;
  }
  sMultiTransactionManager->Undo();
  return 0;
}

static int mtmRedo(Draw_Interpretor& di, int, const char**)
{
  if (sMultiTransactionManager.IsNull())
  {
    di << "Error   : manager is not initialised\n";
    return 1;
  }
  sMultiTransactionManager->Redo();
  return 0;
}

static int mtmNestedMode(Draw_Interpretor& di, int n, const char** a)
{
  if (sMultiTransactionManager.IsNull())
  {
    di << "Error   : manager is not initialised\n";
    return 1;
  }
  bool aMode = false;
  if (n > 1)
  {
    aMode = Draw::Atoi(a[1]) != 0;
  }
  sMultiTransactionManager->SetNestedTransactionMode(aMode);
  return 0;
}

static int XAttributeValue(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 4)
  {
    di << "ERROR: Too few args\n";
    return 1;
  }
  occ::handle<DDF_Browser> browser = occ::down_cast<DDF_Browser>(Draw::GetExisting(argv[1]));
  if (browser.IsNull())
  {
    std::cout << "Syntax error: Not a browser: " << argv[1] << "\n";
    return 1;
  }

  TDF_Label lab;
  TDF_Tool::Label(browser->Data(), argv[2], lab);
  if (lab.IsNull())
  {
    di << "Syntax error: label is Null: " << argv[2] << "\n";
    return 1;
  }

  int                   num = Draw::Atoi(argv[3]);
  TDF_AttributeIterator itr(lab, false);
  for (int i = 1; itr.More() && i < num; i++)
    itr.Next();

  if (!itr.More())
  {
    di << "Syntax error: Attribute #" << num << " not found\n";
    return 1;
  }

  const occ::handle<TDF_Attribute>& att = itr.Value();
  if (att->IsKind(STANDARD_TYPE(TDataStd_TreeNode)))
  {
    occ::handle<TDataStd_TreeNode> TN = occ::down_cast<TDataStd_TreeNode>(att);
    TCollection_AsciiString        ref;
    if (TN->HasFather())
    {
      TDF_Tool::Entry(TN->Father()->Label(), ref);
      di << " ==> " << ref.ToCString();
    }
    else
    {
      di << " <== (" << ref.ToCString();
      occ::handle<TDataStd_TreeNode> child = TN->First();
      while (!child.IsNull())
      {
        TDF_Tool::Entry(child->Label(), ref);
        if (child != TN->First())
          di << ", ";
        di << ref.ToCString();
        child = child->Next();
      }
      di << ")";
    }
  }
  else if (att->IsKind(STANDARD_TYPE(TDF_Reference)))
  {
    occ::handle<TDF_Reference> val = occ::down_cast<TDF_Reference>(att);
    TCollection_AsciiString    ref;
    TDF_Tool::Entry(val->Get(), ref);
    di << "==> " << ref.ToCString();
  }
  else if (att->IsKind(STANDARD_TYPE(TDataStd_Integer)))
  {
    occ::handle<TDataStd_Integer> val = occ::down_cast<TDataStd_Integer>(att);
    TCollection_AsciiString       str(val->Get());
    di << str.ToCString();
  }
  else if (att->IsKind(STANDARD_TYPE(TDataStd_Real)))
  {
    occ::handle<TDataStd_Real> val = occ::down_cast<TDataStd_Real>(att);
    TCollection_AsciiString    str(val->Get());
    di << str.ToCString();
  }
  else if (att->IsKind(STANDARD_TYPE(TDataStd_Name)))
  {
    occ::handle<TDataStd_Name> val = occ::down_cast<TDataStd_Name>(att);
    di << val->Get();
  }
  else if (att->IsKind(STANDARD_TYPE(TDataStd_Comment)))
  {
    occ::handle<TDataStd_Comment> val = occ::down_cast<TDataStd_Comment>(att);
    di << val->Get();
  }
  else if (att->IsKind(STANDARD_TYPE(TDataStd_AsciiString)))
  {
    occ::handle<TDataStd_AsciiString> val = occ::down_cast<TDataStd_AsciiString>(att);
    di << val->Get();
  }
  else if (att->IsKind(STANDARD_TYPE(TDataStd_IntegerArray)))
  {
    occ::handle<TDataStd_IntegerArray> val = occ::down_cast<TDataStd_IntegerArray>(att);
    for (int j = val->Lower(); j <= val->Upper(); j++)
    {
      if (j > val->Lower())
        di << ", ";
      TCollection_AsciiString str(val->Value(j));
      di << str.ToCString();
    }
  }
  else if (att->IsKind(STANDARD_TYPE(TDataStd_RealArray)))
  {
    occ::handle<TDataStd_RealArray> val = occ::down_cast<TDataStd_RealArray>(att);
    for (int j = val->Lower(); j <= val->Upper(); j++)
    {
      if (j > val->Lower())
        di << ", ";
      TCollection_AsciiString str(val->Value(j));
      di << str.ToCString();
    }
  }
  else if (att->IsKind(STANDARD_TYPE(TDataStd_ByteArray)))
  {
    occ::handle<TDataStd_ByteArray> val = occ::down_cast<TDataStd_ByteArray>(att);
    for (int j = val->Lower(); j <= val->Upper(); j++)
    {
      if (j > val->Lower())
        di << ", ";
      TCollection_AsciiString str(val->Value(j));
      di << str.ToCString();
    }
  }
  else if (att->IsKind(STANDARD_TYPE(TNaming_NamedShape)))
  {
    occ::handle<TNaming_NamedShape> val = occ::down_cast<TNaming_NamedShape>(att);
    TopoDS_Shape                    S   = val->Get();
    di << S.TShape()->DynamicType()->Name();
    if (!S.Location().IsIdentity())
      di << "(located)";
  }

  return 0;
}

static int mtmRemoveDocument(Draw_Interpretor& di, int n, const char** a)
{
  if (sMultiTransactionManager.IsNull())
  {
    di << "Error   : manager is not initialised\n";
    return 1;
  }
  if (n > 1)
  {
    occ::handle<DDocStd_DrawDocument> aDrawDoc =
      occ::down_cast<DDocStd_DrawDocument>(Draw::Get(a[1]));
    if (aDrawDoc.IsNull())
    {
      di << "Error   : wrong document name\n";
      return 1;
    }
    sMultiTransactionManager->RemoveDocument(aDrawDoc->GetDocument());
  }
  else
  {
    di << "Error   : document name is not defined\n";
    return 1;
  }
  return 0;
}

void DDocStd::MTMCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  const char* g = "MTM test commands";

  theCommands.Add("mtmCreate",
                  "\t [undo limit]         creates new new multiple transactions' manager",
                  __FILE__,
                  mtmCreate,
                  g);

  theCommands.Add("mtmAdd",
                  "\t <document name>      adds a document to the transactions' manager",
                  __FILE__,
                  mtmAddDocument,
                  g);

  theCommands.Add("mtmRemove",
                  "\t <document name>      removes a document from the transactions' manager",
                  __FILE__,
                  mtmRemoveDocument,
                  g);

  theCommands.Add("mtmOpen",
                  "\t                      opens new transaction",
                  __FILE__,
                  mtmOpenTransaction,
                  g);

  theCommands.Add("mtmCommit",
                  "\t [<transaction name>] commits last opened transaction",
                  __FILE__,
                  mtmCommitTransaction,
                  g);

  theCommands.Add("mtmAbort",
                  "\t                      aborts last opened transaction",
                  __FILE__,
                  mtmAbortTransaction,
                  g);

  theCommands.Add("mtmDump",
                  "\t                      dumps state of the multiple transactions' manager",
                  __FILE__,
                  mtmDump,
                  g);

  theCommands.Add("mtmUndo",
                  "\t                      undos last transaction",
                  __FILE__,
                  mtmUndo,
                  g);

  theCommands.Add("mtmRedo",
                  "\t                      redos last transaction",
                  __FILE__,
                  mtmRedo,
                  g);

  theCommands.Add("mtmNestedMode",
                  "\t [0/1]                sets nested mode if 1 and usets if 0 (default 0)",
                  __FILE__,
                  mtmNestedMode,
                  g);

  theCommands.Add("XAttributeValue",
                  "Doc label #attribute: internal command for browser",
                  __FILE__,
                  XAttributeValue,
                  g);
}
