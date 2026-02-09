#include <IGESData_LineFontEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDraw_SegmentedViewsVisible.hpp>
#include <IGESDraw_ToolSegmentedViewsVisible.hpp>
#include <IGESGraph_Color.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_Integer.hpp>

IGESDraw_ToolSegmentedViewsVisible::IGESDraw_ToolSegmentedViewsVisible() = default;

void IGESDraw_ToolSegmentedViewsVisible::ReadOwnParams(
  const occ::handle<IGESDraw_SegmentedViewsVisible>& ent,
  const occ::handle<IGESData_IGESReaderData>&        IR,
  IGESData_ParamReader&                              PR) const
{

  int nbval;

  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> views;
  occ::handle<NCollection_HArray1<double>>                               breakpointParameters;
  occ::handle<NCollection_HArray1<int>>                                  displayFlags;
  occ::handle<NCollection_HArray1<int>>                                  colorValues;
  occ::handle<NCollection_HArray1<occ::handle<IGESGraph_Color>>>         colorDefinitions;
  occ::handle<NCollection_HArray1<int>>                                  lineFontValues;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>> lineFontDefinitions;
  occ::handle<NCollection_HArray1<int>>                                  lineWeights;

  bool st = PR.ReadInteger(PR.Current(), "No. of View/segment blocks", nbval);
  if (st && nbval > 0)
  {
    views                = new NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>(1, nbval);
    breakpointParameters = new NCollection_HArray1<double>(1, nbval);
    displayFlags         = new NCollection_HArray1<int>(1, nbval);
    colorValues          = new NCollection_HArray1<int>(1, nbval);
    colorDefinitions     = new NCollection_HArray1<occ::handle<IGESGraph_Color>>(1, nbval);
    lineFontValues       = new NCollection_HArray1<int>(1, nbval);
    lineFontDefinitions  = new NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>(1, nbval);
    lineWeights          = new NCollection_HArray1<int>(1, nbval);

    occ::handle<IGESData_ViewKindEntity> tempView;
    double                               tempBreak;
    int                                  tempDisplay;
    int                                  tempColorValue;
    occ::handle<IGESGraph_Color>         tempColorDef;
    int                                  tempLineFontValue;
    occ::handle<IGESData_LineFontEntity> tempLineFontDef;
    int                                  tempLine;

    for (int i = 1; i <= nbval; i++)
    {

      if (PR.ReadEntity(IR,
                        PR.Current(),
                        "Instance of views",
                        STANDARD_TYPE(IGESData_ViewKindEntity),
                        tempView))
        views->SetValue(i, tempView);

      if (PR.ReadReal(PR.Current(), "array breakpointParameters", tempBreak))
        breakpointParameters->SetValue(i, tempBreak);

      if (PR.ReadInteger(PR.Current(), "array displayFlags", tempDisplay))
        displayFlags->SetValue(i, tempDisplay);

      int curnum = PR.CurrentNumber();

      PR.ReadInteger(PR.Current(), "array colorValues", tempColorValue);

      if (tempColorValue < 0)
      {
        colorValues->SetValue(i, -1);
        tempColorDef = GetCasted(IGESGraph_Color, PR.ParamEntity(IR, curnum));
        if (tempColorDef.IsNull())
          PR.AddFail("A Color Definition Entity is incorrect");
        else
          colorDefinitions->SetValue(i, tempColorDef);
      }
      else
        colorValues->SetValue(i, tempColorValue);

      curnum = PR.CurrentNumber();

      PR.ReadInteger(PR.Current(), "array lineFontValues", tempLineFontValue);

      if (tempLineFontValue < 0)
      {
        lineFontValues->SetValue(i, -1);
        tempLineFontDef = GetCasted(IGESData_LineFontEntity, PR.ParamEntity(IR, curnum));
        if (tempLineFontDef.IsNull())
          PR.AddFail("A Line Font Definition Entity is incorrect");
        lineFontDefinitions->SetValue(i, tempLineFontDef);
      }
      else
        lineFontValues->SetValue(i, tempLineFontValue);

      if (PR.ReadInteger(PR.Current(), "array lineWeights", tempLine))
        lineWeights->SetValue(i, tempLine);
    }
  }
  else
    PR.AddFail("No. of View/segment blocks : Not Positive");

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(views,
            breakpointParameters,
            displayFlags,
            colorValues,
            colorDefinitions,
            lineFontValues,
            lineFontDefinitions,
            lineWeights);
}

void IGESDraw_ToolSegmentedViewsVisible::WriteOwnParams(
  const occ::handle<IGESDraw_SegmentedViewsVisible>& ent,
  IGESData_IGESWriter&                               IW) const
{
  int Up = ent->NbSegmentBlocks();
  IW.Send(Up);
  for (int i = 1; i <= Up; i++)
  {
    IW.Send(ent->ViewItem(i));
    IW.Send(ent->BreakpointParameter(i));
    IW.Send(ent->DisplayFlag(i));

    if (ent->IsColorDefinition(i))
      IW.Send(ent->ColorDefinition(i), true);
    else
      IW.Send(ent->ColorValue(i));

    if (ent->IsFontDefinition(i))
      IW.Send(ent->LineFontDefinition(i), true);
    else
      IW.Send(ent->LineFontValue(i));

    IW.Send(ent->LineWeightItem(i));
  }
}

void IGESDraw_ToolSegmentedViewsVisible::OwnShared(
  const occ::handle<IGESDraw_SegmentedViewsVisible>& ent,
  Interface_EntityIterator&                          iter) const
{
  int Up = ent->NbSegmentBlocks();
  for (int i = 1; i <= Up; i++)
  {
    iter.GetOneItem(ent->ViewItem(i));
    if (ent->IsColorDefinition(i))
      iter.GetOneItem(ent->ColorDefinition(i));
    if (!ent->IsFontDefinition(i))
      iter.GetOneItem(ent->LineFontDefinition(i));
  }
}

void IGESDraw_ToolSegmentedViewsVisible::OwnCopy(
  const occ::handle<IGESDraw_SegmentedViewsVisible>& another,
  const occ::handle<IGESDraw_SegmentedViewsVisible>& ent,
  Interface_CopyTool&                                TC) const
{
  int                                                                    nbval;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> views;
  occ::handle<NCollection_HArray1<double>>                               breakpointParameters;
  occ::handle<NCollection_HArray1<int>>                                  displayFlags;
  occ::handle<NCollection_HArray1<int>>                                  colorValues;
  occ::handle<NCollection_HArray1<occ::handle<IGESGraph_Color>>>         colorDefinitions;
  occ::handle<NCollection_HArray1<int>>                                  lineFontValues;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>> lineFontDefinitions;
  occ::handle<NCollection_HArray1<int>>                                  lineWeights;

  occ::handle<IGESData_ViewKindEntity> retView;
  occ::handle<IGESGraph_Color>         retColorDef;
  occ::handle<IGESData_LineFontEntity> retLineFontDef;

  nbval                = another->NbSegmentBlocks();
  views                = new NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>(1, nbval);
  breakpointParameters = new NCollection_HArray1<double>(1, nbval);
  displayFlags         = new NCollection_HArray1<int>(1, nbval);
  colorValues          = new NCollection_HArray1<int>(1, nbval);
  lineFontValues       = new NCollection_HArray1<int>(1, nbval);
  colorDefinitions     = new NCollection_HArray1<occ::handle<IGESGraph_Color>>(1, nbval);
  lineFontDefinitions  = new NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>(1, nbval);
  lineWeights          = new NCollection_HArray1<int>(1, nbval);

  for (int i = 1; i <= nbval; i++)
  {
    retView = another->ViewItem(i);
    DeclareAndCast(IGESData_ViewKindEntity, tempView, TC.Transferred(retView));
    views->SetValue(i, tempView);

    breakpointParameters->SetValue(i, another->BreakpointParameter(i));

    displayFlags->SetValue(i, another->DisplayFlag(i));

    if (another->IsColorDefinition(i))
    {
      retColorDef = another->ColorDefinition(i);
      DeclareAndCast(IGESGraph_Color, tempColorDef, TC.Transferred(retColorDef));
      colorDefinitions->SetValue(i, tempColorDef);
    }
    else
    {
      colorValues->SetValue(i, another->ColorValue(i));
    }

    if (another->IsFontDefinition(i))
    {
      retLineFontDef = another->LineFontDefinition(i);
      DeclareAndCast(IGESData_LineFontEntity, tempLineFontDef, TC.Transferred(retLineFontDef));
      lineFontDefinitions->SetValue(i, tempLineFontDef);
    }
    else
    {
      lineFontValues->SetValue(i, another->LineFontValue(i));
    }

    lineWeights->SetValue(i, another->LineWeightItem(i));
  }

  ent->Init(views,
            breakpointParameters,
            displayFlags,
            colorValues,
            colorDefinitions,
            lineFontValues,
            lineFontDefinitions,
            lineWeights);
}

IGESData_DirChecker IGESDraw_ToolSegmentedViewsVisible::DirChecker(
  const occ::handle<IGESDraw_SegmentedViewsVisible>&) const
{
  IGESData_DirChecker DC(402, 19);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(0);
  DC.UseFlagRequired(1);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESDraw_ToolSegmentedViewsVisible::OwnCheck(
  const occ::handle<IGESDraw_SegmentedViewsVisible>&,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>&) const
{
}

void IGESDraw_ToolSegmentedViewsVisible::OwnDump(
  const occ::handle<IGESDraw_SegmentedViewsVisible>& ent,
  const IGESData_IGESDumper&                         dumper,
  Standard_OStream&                                  S,
  const int                                          level) const
{
  int sublevel = (level <= 4) ? 0 : 1;

  S << "IGESDraw_SegmentedViewsVisible\n"
    << "View Entities            :\n"
    << "Breakpoint parameters    :\n"
    << "Display flags            :\n"
    << "Color Values             :\n"
    << "Color Definitions        :\n"
    << "LineFont Values          :\n"
    << "LineFont Definitions     :\n"
    << "Line Weights :\n"
    << "Count Of Blocks = " << ent->NbSegmentBlocks() << "\n";
  switch (level)
  {
    case 4:
      S << " [ for content, ask level > 4 ]\n";
      break;
    case 5:
    case 6:
    {
      int I;
      int up = ent->NbSegmentBlocks();
      for (I = 1; I <= up; I++)
      {
        S << "[" << I << "]:\n"
          << "View Entity : ";
        dumper.Dump(ent->ViewItem(I), S, sublevel);
        S << "\n"
          << "Breakpoint parameter : " << ent->BreakpointParameter(I) << "\n"
          << "Display Flag : " << ent->DisplayFlag(I) << "\n";
        if ((ent->ColorDefinition(I)).IsNull())
        {
          S << "Color Value : " << ent->ColorValue(I);
        }
        else
        {
          S << "Color Definition : ";
          dumper.Dump(ent->ColorDefinition(I), S, sublevel);
        }
        S << "\n";
        if ((ent->LineFontDefinition(I)).IsNull())
        {
          S << "LineFont Value : " << ent->LineFontValue(I);
        }
        else
        {
          S << "LineFont Definition : ";
          dumper.Dump(ent->LineFontDefinition(I), S, sublevel);
        }
        S << "\n"
          << "Line Weight : " << ent->LineWeightItem(I) << "\n";
      }
    }
    break;
  }
  S << std::endl;
}
