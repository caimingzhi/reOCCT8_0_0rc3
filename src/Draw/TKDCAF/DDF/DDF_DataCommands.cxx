#include <TDF_ClosureMode.hpp>
#include <TDF_ClosureTool.hpp>
#include <TDF_CopyTool.hpp>

#include <DDF.hpp>
#include <DDF_Data.hpp>

#include <Draw_Appli.hpp>
#include <Draw_Drawable3D.hpp>
#include <Draw_Interpretor.hpp>

#include <Standard_NotImplemented.hpp>

#include <TDF_Data.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDF_Tool.hpp>
#include <TDF_CopyLabel.hpp>
#include <TDF_AttributeIterator.hpp>
#include <Standard_Handle.hpp>
#include <TDF_Attribute.hpp>
#include <NCollection_Map.hpp>

static int MakeDF(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<Draw_Drawable3D> D = Draw::Get(a[1]);
  occ::handle<DDF_Data>        NewDDF;

  if (!D.IsNull())
  {
    NewDDF = occ::down_cast<DDF_Data>(D);
    if (!NewDDF.IsNull())
    {
      di << "DDF_BasicCommands::MakeDF - Sorry, this Data Framework already exists\n";
      return 0;
    }
  }

  occ::handle<TDF_Data> NewDF = new TDF_Data();
  NewDDF                      = new DDF_Data(NewDF);
  Draw::Set(a[1], NewDDF);

  return 0;
}

static int ClearDF(Draw_Interpretor& di, int n, const char** a)

{
  if (n < 2)
    return 1;

  occ::handle<Draw_Drawable3D> D = Draw::Get(a[1]);
  occ::handle<DDF_Data>        DDF;

  if (!D.IsNull())
  {
    DDF = occ::down_cast<DDF_Data>(D);
    if (!DDF.IsNull())
    {
      occ::handle<TDF_Data> DF = DDF->DataFramework();
      if (!DF.IsNull())
      {
        occ::handle<TDF_Data> NewEmpty = new TDF_Data;
        DDF->DataFramework(NewEmpty);
      }
      return 0;
    }
  }

  di << "DDF_BasicCommands::MakeDF - Sorry, this Data Framework doesn't exist\n";

  return 0;
}

static int CopyDF(Draw_Interpretor&, int n, const char** a)
{
  if (n < 4 || n > 5)
    return 1;

  occ::handle<TDF_Data> DF1;
  occ::handle<TDF_Data> DF2;
  const char*           Entry1;
  const char*           Entry2;

  if (!DDF::GetDF(a[1], DF1))
    return 1;

  Entry1 = a[2];
  Entry2 = a[3];

  if (n == 4)
  {
    DF2    = DF1;
    Entry2 = a[3];
  }
  else if (n == 5)
  {
    if (!DDF::GetDF(a[3], DF2))
      return 1;
    Entry2 = a[4];
  }

  TDF_Label Label1;
  if (!DDF::FindLabel(DF1, Entry1, Label1))
    return 1;

  TDF_Label Label2;
  if (!DDF::FindLabel(DF2, Entry2, Label2, false))
  {
    DDF::AddLabel(DF2, Entry2, Label2);
  }

  occ::handle<TDF_DataSet> DataSet = new TDF_DataSet;
  DataSet->AddLabel(Label1);
  TDF_ClosureTool::Closure(DataSet);
  occ::handle<TDF_RelocationTable> Reloc = new TDF_RelocationTable();
  Reloc->SetRelocation(Label1, Label2);
  TDF_CopyTool::Copy(DataSet, Reloc);

  return 0;
}

static int MiniDumpDF(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<Draw_Drawable3D> D;
  occ::handle<DDF_Data>        DDF;

  D = Draw::Get(a[1]);

  if (D.IsNull())
  {
    di << "DDF_BasicCommands : Sorry this Data Framework doesn't exist\n";
    return false;
  }

  DDF = occ::down_cast<DDF_Data>(D);

  if (DDF.IsNull())
  {
    di << "DDF_BasicCommands : Sorry this Data Framework doesn't exist\n";
    return false;
  }

  di << "*********** Dump of " << a[1] << " ***********\n";

  Standard_SStream aSStream;
  DDF->DataFramework()->Dump(aSStream);
  aSStream << std::ends;
  di << aSStream << "\n";

  return 0;
}

static int XDumpDF(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<Draw_Drawable3D> D;
  occ::handle<DDF_Data>        DDF;

  D = Draw::Get(a[1]);

  if (D.IsNull())
  {
    di << "DDF_BasicCommands : Sorry this Data Framework doesn't exist\n";
    return false;
  }

  DDF = occ::down_cast<DDF_Data>(D);

  if (DDF.IsNull())
  {
    di << "DDF_BasicCommands : Sorry this Data Framework doesn't exist\n";
    return false;
  }

  di << "*********** Dump of " << a[1] << " ***********\n";

  TDF_IDFilter filter(false);

  Standard_SStream aSStream;
  TDF_Tool::ExtendedDeepDump(aSStream, DDF->DataFramework(), filter);
  aSStream << std::ends;
  di << aSStream << "\n";

  return 0;
}

static int CopyLabel_SCopy(Draw_Interpretor& di, int n, const char** a)
{
  TDF_Label SOURCE, TARGET;
  if (n == 4)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    if (!DDF::FindLabel(DF, a[2], SOURCE))
      return 1;
    if (DDF::FindLabel(DF, a[3], TARGET))
    {
      di << " target label is already set \n";
      return 1;
    }
    DDF::AddLabel(DF, a[3], TARGET);
    TDF_CopyLabel cop;
    cop.Load(SOURCE, TARGET);
    cop.Perform();
    if (!cop.IsDone())
      di << "copy not done\n";
    return 0;
  }
  di << "DDF_CopyLabel : Error\n";
  return 1;
}

static int DDF_CheckAttrs(Draw_Interpretor& di, int n, const char** a)
{
  TDF_Label SOURCE, TARGET;
  if (n == 4)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    if (!DDF::FindLabel(DF, a[2], SOURCE))
      return 1;
    if (!DDF::FindLabel(DF, a[3], TARGET))
      return 1;

    occ::handle<TDF_DataSet> ds1  = new TDF_DataSet();
    occ::handle<TDF_DataSet> ds2  = new TDF_DataSet();
    bool                     Shar = false;
    for (TDF_AttributeIterator itr(SOURCE); itr.More(); itr.Next())
    {
      itr.Value()->References(ds1);

      const NCollection_Map<occ::handle<TDF_Attribute>>& attMap = ds1->Attributes();
      for (NCollection_Map<occ::handle<TDF_Attribute>>::Iterator attMItr(attMap); attMItr.More();
           attMItr.Next())
      {
        const occ::handle<TDF_Attribute>& sAtt = attMItr.Key();

        for (TDF_AttributeIterator itr2(TARGET); itr2.More(); itr2.Next())
        {
          itr2.Value()->References(ds2);

          const NCollection_Map<occ::handle<TDF_Attribute>>& attMap2 = ds2->Attributes();
          for (NCollection_Map<occ::handle<TDF_Attribute>>::Iterator attMItr2(attMap2);
               attMItr2.More();
               attMItr2.Next())
          {
            const occ::handle<TDF_Attribute>& tAtt = attMItr2.Key();

            if (tAtt->IsInstance(sAtt->DynamicType()))
              if (tAtt == sAtt)
              {
                TCollection_AsciiString entr1, entr2;
                if (!Shar)
                {
                  TDF_Tool::Entry(SOURCE, entr1);
                  TDF_Tool::Entry(TARGET, entr2);

                  di << "\tSHAREABLE attribute(s) found between Lab1 = " << entr1.ToCString()
                     << " and Lab2 = " << entr2.ToCString() << "\n";
                  Shar = true;
                }
                TDF_Tool::Entry(sAtt->Label(), entr1);

                di << "\tAttribute dynamic type = " << sAtt->DynamicType()->Name();
                di << ",\tlocated on Label = " << entr1.ToCString() << "\n";
              }
          }
          ds2->Clear();
        }
      }
      ds1->Clear();
    }
    if (!Shar)
      di << "Shareable attributes not found\n";
    return 0;
  }
  di << "DDF_CheckAttrs : Error\n";
  return 1;
}

static int DDF_CheckLabel(Draw_Interpretor& di, int n, const char** a)
{

  TDF_Label SOURCE;
  if (n == 3)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    if (!DDF::FindLabel(DF, a[2], SOURCE))
      return 1;

    occ::handle<TDF_DataSet> ds1 = new TDF_DataSet();
    for (TDF_AttributeIterator itr(SOURCE); itr.More(); itr.Next())
    {
      itr.Value()->References(ds1);

      di << "\tSource Attribute dynamic type = " << itr.Value()->DynamicType()->Name() << "\n";
      const NCollection_Map<occ::handle<TDF_Attribute>>& attMap = ds1->Attributes();
      for (NCollection_Map<occ::handle<TDF_Attribute>>::Iterator attMItr(attMap); attMItr.More();
           attMItr.Next())
      {
        const occ::handle<TDF_Attribute>& sAtt = attMItr.Key();
        TCollection_AsciiString           entry;
        TDF_Tool::Entry(sAtt->Label(), entry);

        di << "\t\tReferences attribute dynamic type = " << sAtt->DynamicType()->Name();
        di << ",\tLabel = " << entry.ToCString() << "\n";
      }
      ds1->Clear();
    }

    return 0;
  }
  di << "DDF_ChecLabel : Error\n";
  return 1;
}

static int DDF_SetAccessByEntry(Draw_Interpretor& di, int nb, const char** a)
{
  int aRet = 0;
  if (nb != 3)
  {
    di << "SetAccessByEntry DOC 1|0\n";
    aRet = 1;
  }
  else
  {
    occ::handle<TDF_Data> aDF;
    if (DDF::GetDF(a[1], aDF))
    {
      bool aSet = (Draw::Atoi(a[2]) == 1);
      aDF->SetAccessByEntries(aSet);
    }
    else
    {
      aRet = 1;
    }
  }
  return aRet;
}

void DDF::DataCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  const char* g = "DF Data Framework commands";

  theCommands.Add("MakeDF", "Makes a new DF: MakeDF dfname", __FILE__, MakeDF, g);

  theCommands.Add("ClearDF", "Clears a DF: ClearDF dfname", __FILE__, ClearDF, g);

  theCommands.Add("CopyDF",
                  "Copies a label: CopyDF dfname1 entry1 [dfname2] entry2",
                  __FILE__,
                  CopyDF,
                  g);

  theCommands.Add("XDumpDF",
                  "Exented deep dump of a DF (with attributes content): DumpDF dfname",
                  __FILE__,
                  XDumpDF,
                  g);

  theCommands.Add("MiniDumpDF",
                  "Mini dump of a DF (with attributes content): DumpDF dfname",
                  __FILE__,
                  MiniDumpDF,
                  g);

  theCommands.Add("CopyLabel", "CopyLabel (DOC, from, to)", __FILE__, CopyLabel_SCopy, g);

  theCommands.Add("CheckAttrs", "CheckAttrs DocName Lab1 Lab2 ", __FILE__, DDF_CheckAttrs, g);

  theCommands.Add("CheckLabel", "CheckLabel DocName Label ", __FILE__, DDF_CheckLabel, g);

  theCommands.Add("SetAccessByEntry",
                  "SetAccessByEntry DOC 1|0",
                  __FILE__,
                  DDF_SetAccessByEntry,
                  g);
}
