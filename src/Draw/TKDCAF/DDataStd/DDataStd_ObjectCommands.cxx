#include <DDataStd.hpp>
#include <DDataStd_DrawPresentation.hpp>
#include <DDF.hpp>
#include <Draw_Interpretor.hpp>
#include <Draw_Appli.hpp>
#include <TDF_Data.hpp>
#include <TDF_Tool.hpp>
#include <TDF_Label.hpp>
#include <TDataStd_Directory.hpp>

#include <TDataStd_NoteBook.hpp>
#include <TDataXtd_Shape.hpp>

#include <DBRep.hpp>

static int DDataStd_NewDirectory(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb != 3)
  {
    di << "Too few arguments" << "\n";
    return 1;
  }
  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(arg[1], DF))
    return 1;
  TDF_Label label;
  DDF::AddLabel(DF, arg[2], label);
  TDataStd_Directory::New(label);
  return 0;
}

static int DDataStd_AddDirectory(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb != 3)
  {
    di << "Too few arguments" << "\n";
    return 1;
  }
  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(arg[1], DF))
    return 1;
  TDF_Label label;
  if (!DDF::FindLabel(DF, arg[2], label))
  {
    di << "No label for entry" << "\n";
    return 1;
  }
  occ::handle<TDataStd_Directory> A;
  if (TDataStd_Directory::Find(label, A))
  {
    occ::handle<TDataStd_Directory> Dir = TDataStd_Directory::AddDirectory(A);
    TCollection_AsciiString         entry;
    TDF_Tool::Entry(Dir->Label(), entry);
    di << entry.ToCString() << " ";
    return 0;
  }
  di << "No Object Attribute on label" << "\n";
  return 1;
}

static int DDataStd_MakeObjectLabel(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb != 3)
  {
    di << "Too few arguments" << "\n";
    return 1;
  }
  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(arg[1], DF))
    return 1;
  TDF_Label label;
  if (!DDF::FindLabel(DF, arg[2], label))
  {
    di << "No label for entry" << "\n";
    return 1;
  }
  occ::handle<TDataStd_Directory> A;
  if (TDataStd_Directory::Find(label, A))
  {
    TCollection_AsciiString entry;
    TDF_Tool::Entry(TDataStd_Directory::MakeObjectLabel(A), entry);
    di << entry.ToCString() << " ";
    return 0;
  }
  di << "No Object Attribute on label" << "\n";
  return 1;
}

static int DDataStd_NewNoteBook(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 3)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(arg[1], DF))
      return 1;
    TDF_Label L;
    DDF::AddLabel(DF, arg[2], L);
    TDataStd_NoteBook::New(L);
    return 0;
  }
  di << "DDataStd_NewNoteBook : Error\n";
  return 1;
}

static int DDataStd_NewShape(Draw_Interpretor& di, int nb, const char** arg)
{

  if (nb < 3)
  {
    di << "Too few arguments" << "\n";
    return 1;
  }
  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(arg[1], DF))
    return 1;
  TDF_Label label;
  DDF::AddLabel(DF, arg[2], label);
  if (nb == 4)
  {
    TopoDS_Shape shape = DBRep::Get(arg[3]);
    if (shape.IsNull())
    {
      di << "Shape argument is invalid" << "\n";
      return 1;
    }
    TDataXtd_Shape::Set(label, shape);
  }
  else
    TDataXtd_Shape::New(label);
  return 0;
}

static int DDataStd_GetShape2(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb < 4)
  {
    di << "Too few arguments" << "\n";
    return 1;
  }
  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(arg[1], DF))
    return 1;
  TDF_Label label;
  if (!DDF::FindLabel(DF, arg[2], label))
  {
    di << "No label for entry" << "\n";
    return 1;
  }
  DBRep::Set(arg[3], TDataXtd_Shape::Get(label));

  return 0;
}

void DDataStd::ObjectCommands(Draw_Interpretor& theCommands)
{

  static bool done = false;
  if (done)
    return;
  done          = true;
  const char* g = "DData : Standard Attribute Commands";

  theCommands.Add("NewNoteBook", "NewNoteBook (DF, entry)", __FILE__, DDataStd_NewNoteBook, g);

  theCommands.Add("NewShape", "NewShape (DF, entry, [in_shape] )", __FILE__, DDataStd_NewShape, g);

  theCommands.Add("GetShape2",
                  "GetShape2 (DF, entry, out_shape )",
                  __FILE__,
                  DDataStd_GetShape2,
                  g);

  theCommands.Add("NewDirectory", "NewDirectory (DF, entry)", __FILE__, DDataStd_NewDirectory, g);

  theCommands.Add("AddDirectory", "AddDirectory (DF, entry)", __FILE__, DDataStd_AddDirectory, g);

  theCommands.Add("MakeObjectLabel",
                  "MakeObjectLabel (DF, entry)",
                  __FILE__,
                  DDataStd_MakeObjectLabel,
                  g);
}
