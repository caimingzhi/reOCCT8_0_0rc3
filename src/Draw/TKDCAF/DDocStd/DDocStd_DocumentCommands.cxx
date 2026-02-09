#include <DDocStd.hpp>

#include <BinDrivers_DocumentStorageDriver.hpp>
#include <DDF.hpp>
#include <Draw_Interpretor.hpp>
#include <TDF_Reference.hpp>
#include <TDocStd_Modified.hpp>
#include <TDF_Label.hpp>
#include <TDocStd_XLink.hpp>
#include <TDocStd_XLinkIterator.hpp>
#include <TDocStd_Application.hpp>
#include <Draw.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TDF_Tool.hpp>
#include <TPrsStd_AISViewer.hpp>
#include <AIS_InteractiveContext.hpp>

#include <TDocStd_XLinkTool.hpp>

static int DDocStd_Main(Draw_Interpretor& di, int nb, const char** a)
{
  if (nb == 2)
  {
    occ::handle<TDocStd_Document> DOC;
    if (!DDocStd::GetDocument(a[1], DOC))
      return 1;
    DDocStd::ReturnLabel(di, DOC->Main());
    return 0;
  }
  di << "DDocStd_Main : Error\n";
  return 1;
}

static int DDocStd_Format(Draw_Interpretor& di, int n, const char** a)
{
  occ::handle<TDocStd_Document> D;
  if (n == 2)
  {
    if (!DDocStd::GetDocument(a[1], D))
      return 1;

    di << "FORMAT : ";
    Standard_SStream aStream;
    D->StorageFormat().Print(aStream);
    di << aStream;
    di << "\n";
    return 0;
  }
  if (n == 3)
  {
    if (!DDocStd::GetDocument(a[1], D))
      return 1;
    D->ChangeStorageFormat(a[2]);
    return 0;
  }
  di << "DDocStd_Format : Error\n";
  return 1;
}

static int DDocStd_Copy(Draw_Interpretor& di, int n, const char** a)
{
  if (n == 5)
  {
    occ::handle<TDocStd_Document> DOC, XDOC;
    if (!DDocStd::GetDocument(a[1], DOC))
      return 1;
    if (!DDocStd::GetDocument(a[3], XDOC))
      return 1;
    TDF_Label L, XL;
    if (!DDocStd::Find(DOC, a[2], L))
      return 1;
    if (!DDocStd::Find(XDOC, a[4], XL))
      return 1;
    TDocStd_XLinkTool XLinkTool;
    XLinkTool.Copy(L, XL);
    if (!XLinkTool.IsDone())
    {
      di << "DDocStd_XLinkTool : not done\n";
    }
    return 0;
  }
  di << "DDocStd_XLinkTool : Error\n";
  return 1;
}

static int DDocStd_CopyWithLink(Draw_Interpretor& di, int n, const char** a)
{
  if (n == 5)
  {
    occ::handle<TDocStd_Document> DOC, XDOC;
    if (!DDocStd::GetDocument(a[1], DOC))
      return 1;
    if (!DDocStd::GetDocument(a[3], XDOC))
      return 1;
    TDF_Label L, XL;
    if (!DDocStd::Find(DOC, a[2], L))
      return 1;
    if (!DDocStd::Find(XDOC, a[4], XL))
      return 1;
    TDocStd_XLinkTool XLinkTool;
    XLinkTool.CopyWithLink(L, XL);
    if (!XLinkTool.IsDone())
    {
      di << "DDocStd_CopyWithLink : not done\n";
    }
    return 0;
  }
  di << "DDocStd_CopyWithLink : Error\n";
  return 1;
}

static int DDocStd_UpdateLink(Draw_Interpretor& di, int nb, const char** a)
{
  if (nb == 2 || nb == 3)
  {
    occ::handle<TDocStd_Document> DOC;
    if (!DDocStd::GetDocument(a[1], DOC))
      return 1;
    occ::handle<TDF_Reference> REF;
    TDocStd_XLinkTool          XLinkTool;
    if (nb == 3)
    {
      if (!DDocStd::Find(DOC, a[2], TDF_Reference::GetID(), REF))
        return 1;
      XLinkTool.UpdateLink(REF->Label());
      if (!XLinkTool.IsDone())
      {
        di << "DDocStd_UpdateXLink : not done\n";
      }
    }
    else
    {
      for (TDocStd_XLinkIterator xit(DOC); xit.More(); xit.Next())
      {
        XLinkTool.UpdateLink(xit.Value()->Label());
        if (!XLinkTool.IsDone())
        {
          di << "DDocStd_UpdateXLink : not done\n";
        }
      }
    }
    return 0;
  }
  di << "DDocStd_UpdateXLink : Error\n";
  return 1;
}

static int DDocStd_UndoLimit(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<TDocStd_Document> D;
  if (!DDocStd::GetDocument(a[1], D))
    return 1;

  if (n > 2)
  {
    int lim = Draw::Atoi(a[2]);
    D->SetUndoLimit(lim);
  }

  di << D->GetUndoLimit() << " ";
  di << D->GetAvailableUndos() << " ";
  di << D->GetAvailableRedos();
  return 0;
}

static int DDocStd_Undo(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<TDocStd_Document> D;
  if (!DDocStd::GetDocument(a[1], D))
    return 1;

  int i, step = 1;
  if (n > 2)
  {
    step = Draw::Atoi(a[2]);
  }

  bool undo = a[0][0] == 'U';

  for (i = 1; i <= step; i++)
  {
    if (undo)
    {
      if (!D->Undo())
        di << "Undo not done\n";
    }
    else
    {
      if (!D->Redo())
        di << "Redo not done\n";
    }
  }

  occ::handle<AIS_InteractiveContext> IC;
  if (TPrsStd_AISViewer::Find(D->Main(), IC))
    IC->UpdateCurrentViewer();

  return 0;
}

static int DDocStd_NewCommand(Draw_Interpretor&, int n, const char** a)
{
  if (n < 2)
    return 1;
  occ::handle<TDocStd_Document> D;
  if (!DDocStd::GetDocument(a[1], D))
    return 1;
  D->NewCommand();
  return 0;
}

static int DDocStd_OpenCommand(Draw_Interpretor&, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<TDocStd_Document> D;
  if (!DDocStd::GetDocument(a[1], D))
    return 1;
  D->OpenCommand();
  return 0;
}

static int DDocStd_AbortCommand(Draw_Interpretor&, int n, const char** a)
{
  if (n < 2)
    return 1;
  occ::handle<TDocStd_Document> D;
  if (!DDocStd::GetDocument(a[1], D))
    return 1;
  D->AbortCommand();
  return 0;
}

static int DDocStd_CommitCommand(Draw_Interpretor&, int n, const char** a)
{
  if (n < 2)
    return 1;
  occ::handle<TDocStd_Document> D;
  if (!DDocStd::GetDocument(a[1], D))
    return 1;
  D->CommitCommand();
  return 0;
}

static int DDocStd_DumpDocument(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 2)
  {
    occ::handle<TDocStd_Document> D;
    if (!DDocStd::GetDocument(arg[1], D))
      return 1;
    di << "\n";

    if (D->IsSaved())
      di << "DOCUMENT      : " << D->GetName();
    else
      di << "DOCUMENT      : not saved";
    di << "\n";

    di << "FORMAT        : ";
    Standard_SStream aStream;
    D->StorageFormat().Print(aStream);
    di << aStream;
    di << "\n";

    di << "COMMAND       : ";
    if (D->HasOpenCommand())
      di << " Is Open";
    else
      di << " Is Not Open";

    di << "UNDO          :";
    di << " limit :" << D->GetUndoLimit();
    di << " undos :" << D->GetAvailableUndos() << " ";
    di << " redos :" << D->GetAvailableRedos();
    di << "\n";

    di << "MODIFIED      : ";
    if (D->IsModified())
      di << "true";
    else
      di << "false";
    di << "\n";
    if (!TDocStd_Modified::IsEmpty(D->Main()))
    {
      di << "MODIFICATIONS : ";
      NCollection_Map<TDF_Label>::Iterator it(D->GetModified());
      if (!it.More())
        di << "VALID\n";
      else
      {
        TCollection_AsciiString string;
        for (; it.More(); it.Next())
        {
          TDF_Tool::Entry(it.Key(), string);
          di << string.ToCString() << " ";
        }
        di << "\n";
      }
    }
    return 0;
  }
  di << "DDocStd_DumpDocument : Error\n";
  return 1;
}

static int DDocStd_SetModified(Draw_Interpretor& di, int n, const char** a)
{
  if (n > 2)
  {
    occ::handle<TDocStd_Document> D;
    if (!DDocStd::GetDocument(a[1], D))
      return 1;
    TDF_Label L;
    for (int i = 2; i < n; i++)
    {
      if (DDocStd::Find(D, a[i], L))
        D->SetModified(L);
    }
    return 0;
  }
  di << "DDocStd_SetModified : Error\n";
  return 1;
}

static int DDocStd_Propagate(Draw_Interpretor& di, int, const char**)
{

  di << "DDocStd_Propagate : not implemented\n";
  return 1;
}

static int DDocStd_StoreTriangulation(Draw_Interpretor& theDi,
                                      int               theNbArgs,
                                      const char**      theArgVec)
{
  const occ::handle<TDocStd_Application>&       anApp = DDocStd::GetApplication();
  occ::handle<BinDrivers_DocumentStorageDriver> aDriverXCaf =
    occ::down_cast<BinDrivers_DocumentStorageDriver>(anApp->WriterFromFormat("BinXCAF"));
  occ::handle<BinDrivers_DocumentStorageDriver> aDriverOcaf =
    occ::down_cast<BinDrivers_DocumentStorageDriver>(anApp->WriterFromFormat("BinOcaf"));
  if (aDriverXCaf.IsNull() || aDriverOcaf.IsNull())
  {
    std::cout << "Error: BinXCAF or BinOcaf storage formats are not registered\n";
    return 1;
  }

  if (theNbArgs == 1)
  {
    theDi << (aDriverXCaf->IsWithTriangles() ? "1" : "0");
    return 0;
  }

  for (int anArgIter = 1; anArgIter < theNbArgs; ++anArgIter)
  {
    TCollection_AsciiString aParam(theArgVec[anArgIter]);
    aParam.LowerCase();

    int aParsedIntegerValue(0);
    if (anArgIter == 1 && Draw::ParseInteger(aParam.ToCString(), aParsedIntegerValue))
    {
      const bool toEnable = (aParsedIntegerValue != 0);
      aDriverXCaf->SetWithTriangles(anApp->MessageDriver(), toEnable);
      aDriverOcaf->SetWithTriangles(anApp->MessageDriver(), toEnable);
      continue;
    }

    if (aParam == "-nonormals" || aParam == "-normals")
    {
      bool isWithNormals(true);
      if (anArgIter + 1 < theNbArgs && Draw::ParseOnOff(theArgVec[anArgIter + 1], isWithNormals))
      {
        ++anArgIter;
      }
      if (aParam == "-nonormals")
      {
        isWithNormals = !isWithNormals;
      }
      aDriverXCaf->SetWithNormals(anApp->MessageDriver(), isWithNormals);
      aDriverOcaf->SetWithNormals(anApp->MessageDriver(), isWithNormals);
    }
    if (aParam == "-getnormals")
    {
      theDi << (aDriverXCaf->IsWithNormals() ? "1" : "0");
      continue;
    }
  }
  return 0;
}

void DDocStd::DocumentCommands(Draw_Interpretor& theCommands)
{

  static bool done = false;
  if (done)
    return;
  done = true;

  const char* g = "DDocStd commands";

  theCommands.Add("Main", "Main (DOC)", __FILE__, DDocStd_Main, g);

  theCommands.Add("Format", "Format (DOC, [format])", __FILE__, DDocStd_Format, g);

  theCommands.Add("DumpDocument", "DumpDocument (DOC)", __FILE__, DDocStd_DumpDocument, g);

  theCommands.Add("StoreTriangulation",
                  "StoreTriangulation [toStore={0|1}] [-normals=off] [-noNormals=on]"
                  "\n\t\t:  -normals -noNormals write triangulation normals."
                  "\n\t\t:  Ignored (always off) if toStore=0 or skipped"
                  "\nSetup BinXCAF/BinOcaf storage drivers to write triangulation",
                  __FILE__,
                  DDocStd_StoreTriangulation,
                  g);

  theCommands.Add("Copy", "Copy DOC entry XDOC xentry", __FILE__, DDocStd_Copy, g);

  theCommands.Add("CopyWithLink",
                  "CopyWithLink DOC entry XDOC xentry",
                  __FILE__,
                  DDocStd_CopyWithLink,
                  g);

  theCommands.Add("UpdateLink", "UpdateLink DOC [entry]", __FILE__, DDocStd_UpdateLink, g);

  theCommands.Add("UndoLimit",
                  "UndoLimit DOC (Value), return UndoLimit Undos Redos",
                  __FILE__,
                  DDocStd_UndoLimit,
                  g);

  theCommands.Add("Undo", "Undo DOC (steps = 1)", __FILE__, DDocStd_Undo, g);

  theCommands.Add("Redo", "Redo DOC (steps = 1)", __FILE__, DDocStd_Undo, g);

  theCommands.Add("NewCommand", "NewCommand DOC", __FILE__, DDocStd_NewCommand, g);

  theCommands.Add("OpenCommand", "OpenCommand DOC", __FILE__, DDocStd_OpenCommand, g);

  theCommands.Add("AbortCommand", "AbortCommand DOC", __FILE__, DDocStd_AbortCommand, g);

  theCommands.Add("CommitCommand", "CommitCommand DOC", __FILE__, DDocStd_CommitCommand, g);

  theCommands.Add("SetModified",
                  "SetModified DOC Label1 Label2 ....",
                  __FILE__,
                  DDocStd_SetModified,
                  g);

  theCommands.Add("Propagate", "Propagate DOC", __FILE__, DDocStd_Propagate, g);
}
