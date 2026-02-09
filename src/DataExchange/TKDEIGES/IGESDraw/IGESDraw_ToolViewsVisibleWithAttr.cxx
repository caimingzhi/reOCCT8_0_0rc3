#include <IGESData_LineFontEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDraw_ToolViewsVisibleWithAttr.hpp>
#include <IGESDraw_ViewsVisibleWithAttr.hpp>
#include <IGESGraph_Color.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Integer.hpp>

#include <cstdio>

IGESDraw_ToolViewsVisibleWithAttr::IGESDraw_ToolViewsVisibleWithAttr() = default;

void IGESDraw_ToolViewsVisibleWithAttr::ReadOwnParams(
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& ent,
  const occ::handle<IGESData_IGESReaderData>&       IR,
  IGESData_ParamReader&                             PR) const
{

  int                                                                    tempNbBlocks, tempNbEntity;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> tempViewEntities;
  occ::handle<NCollection_HArray1<occ::handle<IGESGraph_Color>>>         tempColorDefinitions;
  occ::handle<NCollection_HArray1<int>>                                  tempLineFonts;
  occ::handle<NCollection_HArray1<int>>                                  tempColorValues;
  occ::handle<NCollection_HArray1<int>>                                  tempLineWeights;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>     tempDisplayEntities;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>> tempLineDefinitions;

  if (PR.ReadInteger(PR.Current(), "Number Of Blocks", tempNbBlocks))
  {

    if (tempNbBlocks <= 0)
      PR.AddFail("Number Of Blocks : Not Positive");
    else
    {
      tempViewEntities =
        new NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>(1, tempNbBlocks);
      tempLineFonts = new NCollection_HArray1<int>(1, tempNbBlocks);
      tempLineDefinitions =
        new NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>(1, tempNbBlocks);
      tempColorValues      = new NCollection_HArray1<int>(1, tempNbBlocks);
      tempColorDefinitions = new NCollection_HArray1<occ::handle<IGESGraph_Color>>(1, tempNbBlocks);
      tempLineWeights      = new NCollection_HArray1<int>(1, tempNbBlocks);
    }
  }

  if (PR.DefinedElseSkip())
    PR.ReadInteger(PR.Current(), "Number of Entities Displayed", tempNbEntity);
  else
  {
    tempNbEntity = 0;
    PR.AddWarning("Number of Entities Displayed : undefined, set to Zero");
  }

  if (tempNbEntity < 0)
    PR.AddFail("Number Of Entities Displayed : Less than Zero");

  if (!(tempViewEntities.IsNull()))
  {

    int I;
    for (I = 1; I <= tempNbBlocks; I++)
    {
      occ::handle<IGESData_ViewKindEntity> tempView;
      int                                  tempLineFont;
      occ::handle<IGESData_LineFontEntity> tempEntity1;
      int                                  tempColorValue;
      occ::handle<IGESGraph_Color>         tempColorDef;
      int                                  tempLineWeightValue;

      if (PR.ReadEntity(IR,
                        PR.Current(),
                        "View Entity",
                        STANDARD_TYPE(IGESData_ViewKindEntity),
                        tempView))
        tempViewEntities->SetValue(I, tempView);

      if (PR.ReadInteger(PR.Current(), "Line Font Value", tempLineFont))
        tempLineFonts->SetValue(I, tempLineFont);

      if (tempLineFont == 0
          && PR.ReadEntity(IR,
                           PR.Current(),
                           "Line Font Definition",
                           STANDARD_TYPE(IGESData_LineFontEntity),
                           tempEntity1,
                           true))
        tempLineDefinitions->SetValue(I, tempEntity1);

      int curnum = PR.CurrentNumber();

      if (PR.DefinedElseSkip())

        PR.ReadInteger(PR.Current(), "Color Value", tempColorValue);

      else
      {
        tempColorValue = 0;
        PR.AddWarning("Color Value : undefined, set to Zero");
      }
      if (tempColorValue < 0)
      {
        tempColorValues->SetValue(I, -1);
        tempColorDef = GetCasted(IGESGraph_Color, PR.ParamEntity(IR, curnum));
        if (tempColorDef.IsNull())
          PR.AddFail("A Color Definition Entity is incorrect");
        else
          tempColorDefinitions->SetValue(I, tempColorDef);
      }
      else
        tempColorValues->SetValue(I, tempColorValue);

      if (PR.ReadInteger(PR.Current(), "Line Weight Value", tempLineWeightValue))
        tempLineWeights->SetValue(I, tempLineWeightValue);
    }
  }

  if (tempNbEntity > 0)
  {
    PR.ReadEnts(IR, PR.CurrentList(tempNbEntity), "Displayed Entities", tempDisplayEntities);
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempViewEntities,
            tempLineFonts,
            tempLineDefinitions,
            tempColorValues,
            tempColorDefinitions,
            tempLineWeights,
            tempDisplayEntities);
}

void IGESDraw_ToolViewsVisibleWithAttr::WriteOwnParams(
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& ent,
  IGESData_IGESWriter&                              IW) const
{
  int up = ent->NbViews();
  IW.Send(up);
  IW.Send(ent->NbDisplayedEntities());

  int I;
  for (I = 1; I <= up; I++)
  {
    IW.Send(ent->ViewItem(I));
    IW.Send(ent->LineFontValue(I));
    IW.Send(ent->FontDefinition(I));
    if (ent->IsColorDefinition(I))
      IW.Send(ent->ColorDefinition(I), true);
    else
      IW.Send(ent->ColorValue(I));
    IW.Send(ent->LineWeightItem(I));
  }
  up = ent->NbDisplayedEntities();
  for (I = 1; I <= up; I++)
    IW.Send(ent->DisplayedEntity(I));
}

void IGESDraw_ToolViewsVisibleWithAttr::OwnShared(
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& ent,
  Interface_EntityIterator&                         iter) const
{
  int up = ent->NbViews();

  int I;
  for (I = 1; I <= up; I++)
  {
    iter.GetOneItem(ent->ViewItem(I));
    iter.GetOneItem(ent->FontDefinition(I));
    if (ent->IsColorDefinition(I))
      iter.GetOneItem(ent->ColorDefinition(I));
  }
}

void IGESDraw_ToolViewsVisibleWithAttr::OwnImplied(
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& ent,
  Interface_EntityIterator&                         iter) const
{
  int I, up;
  up = ent->NbDisplayedEntities();
  for (I = 1; I <= up; I++)
    iter.GetOneItem(ent->DisplayedEntity(I));
}

void IGESDraw_ToolViewsVisibleWithAttr::OwnCopy(
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& another,
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& ent,
  Interface_CopyTool&                               TC) const
{
  int                                                                    I;
  int                                                                    up = another->NbViews();
  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> tempViewEntities =
    new NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>(1, up);
  occ::handle<NCollection_HArray1<int>> tempLineFonts = new NCollection_HArray1<int>(1, up);
  occ::handle<NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>> tempLineDefinitions =
    new NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>(1, up);
  occ::handle<NCollection_HArray1<int>> tempColorValues = new NCollection_HArray1<int>(1, up);
  occ::handle<NCollection_HArray1<occ::handle<IGESGraph_Color>>> tempColorDefinitions =
    new NCollection_HArray1<occ::handle<IGESGraph_Color>>(1, up);
  occ::handle<NCollection_HArray1<int>> tempLineWeights = new NCollection_HArray1<int>(1, up);

  for (I = 1; I <= up; I++)
  {
    DeclareAndCast(IGESData_ViewKindEntity, tempView, TC.Transferred(another->ViewItem(I)));
    tempViewEntities->SetValue(I, tempView);
    int tempLineFont = another->LineFontValue(I);
    tempLineFonts->SetValue(I, tempLineFont);
    if (another->IsFontDefinition(I))
    {
      DeclareAndCast(IGESData_LineFontEntity,
                     tempEntity1,
                     TC.Transferred(another->FontDefinition(I)));
      tempLineDefinitions->SetValue(I, tempEntity1);
    }
    if (another->IsColorDefinition(I))
    {
      DeclareAndCast(IGESGraph_Color, tempEntity2, TC.Transferred(another->ColorDefinition(I)));
      tempColorDefinitions->SetValue(I, tempEntity2);
    }
    else
    {
      int tempColorValue = another->ColorValue(I);
      tempColorValues->SetValue(I, tempColorValue);
    }
    int tempLineWeight = another->LineWeightItem(I);
    tempLineWeights->SetValue(I, tempLineWeight);
  }

  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> tempDisplayEntities;
  ent->Init(tempViewEntities,
            tempLineFonts,
            tempLineDefinitions,
            tempColorValues,
            tempColorDefinitions,
            tempLineWeights,
            tempDisplayEntities);
}

void IGESDraw_ToolViewsVisibleWithAttr::OwnRenew(
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& another,
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& ent,
  const Interface_CopyTool&                         TC) const
{
  Interface_EntityIterator newdisp;
  int                      I, up;
  up = another->NbDisplayedEntities();
  if (up == 0)
    return;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> tempDisplayEntities;
  occ::handle<Standard_Transient>                                    anew;
  for (I = 1; I <= up; I++)
  {
    if (TC.Search(another->DisplayedEntity(I), anew))
      newdisp.GetOneItem(anew);
  }

  up = newdisp.NbEntities();
  I  = 0;
  if (up > 0)
    tempDisplayEntities = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, up);
  for (newdisp.Start(); newdisp.More(); newdisp.Next())
  {
    I++;
    DeclareAndCast(IGESData_IGESEntity, tempEntity, newdisp.Value());
    tempDisplayEntities->SetValue(I, tempEntity);
  }
  ent->InitImplied(tempDisplayEntities);
}

IGESData_DirChecker IGESDraw_ToolViewsVisibleWithAttr::DirChecker(
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>&) const
{
  IGESData_DirChecker DC(402, 4);
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

void IGESDraw_ToolViewsVisibleWithAttr::OwnCheck(
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  int nb = ent->NbViews();
  int i;
  for (i = 1; i <= nb; i++)
  {
    if (ent->LineFontValue(i) != 0 && ent->IsFontDefinition(i))
      ach->AddFail("At least one Line Font Definition Mismatch (both Value and Entity");
  }
  const occ::handle<IGESData_ViewKindEntity>& entcomp = ent;
  int                                         res     = 0;
  nb                                                  = ent->NbDisplayedEntities();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<IGESData_IGESEntity> displayed = ent->DisplayedEntity(i);
    if (entcomp != displayed->View())
      res++;
  }
  if (!res)
    return;
  char mess[80];
  Sprintf(mess, "Mismatch for %d Entities displayed", res);
  ach->AddFail(mess, "Mismatch for %d Entities displayed");
}

void IGESDraw_ToolViewsVisibleWithAttr::OwnWhenDelete(
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& ent) const
{
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> tempDisplayEntities;
  ent->InitImplied(tempDisplayEntities);
}

void IGESDraw_ToolViewsVisibleWithAttr::OwnDump(
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& ent,
  const IGESData_IGESDumper&                        dumper,
  Standard_OStream&                                 S,
  const int                                         level) const
{
  int tempSubLevel = (level <= 4) ? 0 : 1;

  S << "IGESDraw_ViewsVisibleWithAttr\n"
    << "View Entities            :\n"
    << "Line Font Values         :\n"
    << "Line Font Definitions    :\n"
    << "Color Number/Definitions :\n"
    << "Line Weights             :\n"
    << "Count of View Blocks : " << ent->NbViews() << "\n";
  if (level > 4)
  {
    int I;
    int upper = ent->NbViews();
    for (I = 1; I <= upper; I++)
    {
      S << "[" << I << "]:\n"
        << "View Entity : ";
      dumper.Dump(ent->ViewItem(I), S, tempSubLevel);
      S << "\n";

      if (ent->IsFontDefinition(I))
      {
        S << "Line Font Definition  : ";
        dumper.Dump(ent->FontDefinition(I), S, tempSubLevel);
        S << "\n";
      }
      else
        S << "Line Font Value       : " << ent->LineFontValue(I) << "\n";

      if (ent->IsColorDefinition(I))
      {
        S << "Color Definition : ";
        dumper.Dump(ent->ColorDefinition(I), S, tempSubLevel);
        S << std::endl;
      }
      else
        S << "Color Value      : " << ent->ColorValue(I) << "\n";

      S << "Line Weight      : " << ent->LineWeightItem(I) << "\n";
    }
  }
  S << "Displayed Entities : ";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbDisplayedEntities(), ent->DisplayedEntity);
  S << std::endl;
}

bool IGESDraw_ToolViewsVisibleWithAttr::OwnCorrect(
  const occ::handle<IGESDraw_ViewsVisibleWithAttr>& ent) const
{

  bool                                        res     = false;
  int                                         nb      = ent->NbDisplayedEntities();
  const occ::handle<IGESData_ViewKindEntity>& entcomp = ent;
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<IGESData_IGESEntity> displayed = ent->DisplayedEntity(i);
    if (entcomp != displayed->View())
      res = true;
  }
  if (!res)
    return res;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> nulDisplayEntities;
  ent->InitImplied(nulDisplayEntities);
  return res;
}
