#include <IGESBasic_HArray1OfHArray1OfIGESEntity.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_Status.hpp>
#include <IGESGeom_Boundary.hpp>
#include <IGESGeom_ToolBoundary.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Integer.hpp>

#include <cstdio>

IGESGeom_ToolBoundary::IGESGeom_ToolBoundary() = default;

void IGESGeom_ToolBoundary::ReadOwnParams(const occ::handle<IGESGeom_Boundary>&       ent,
                                          const occ::handle<IGESData_IGESReaderData>& IR,
                                          IGESData_ParamReader&                       PR) const
{

  int                                                                num;
  int                                                                tempType, tempPreference;
  occ::handle<IGESData_IGESEntity>                                   tempSurface;
  occ::handle<NCollection_HArray1<int>>                              tempSenses;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> tempModelCurves;
  occ::handle<IGESBasic_HArray1OfHArray1OfIGESEntity>                tempParameterCurves;
  IGESData_Status                                                    aStatus;

  if (!PR.ReadInteger(PR.Current(), tempType))
  {
    Message_Msg Msg122("XTSEP_122");
    PR.SendFail(Msg122);
  }
  if (!PR.ReadInteger(PR.Current(), tempPreference))
  {
    Message_Msg Msg123("XTSEP_123");
    PR.SendFail(Msg123);
  }

  if (!PR.ReadEntity(IR, PR.Current(), aStatus, tempSurface))
  {
    Message_Msg Msg124("XTSEP_124");
    switch (aStatus)
    {
      case IGESData_ReferenceError:
      {
        Message_Msg Msg216("IGES_216");
        Msg124.Arg(Msg216.Value());
        PR.SendFail(Msg124);
        break;
      }
      case IGESData_EntityError:
      {
        Message_Msg Msg217("IGES_217");
        Msg124.Arg(Msg217.Value());
        PR.SendFail(Msg124);
        break;
      }
      default:
      {
      }
    }
  }

  if (PR.ReadInteger(PR.Current(), num) && (num > 0))
  {
    tempSenses          = new NCollection_HArray1<int>(1, num);
    tempModelCurves     = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, num);
    tempParameterCurves = new IGESBasic_HArray1OfHArray1OfIGESEntity(1, num);
  }
  else
  {
    Message_Msg Msg126("XTSEP_126");
    PR.SendFail(Msg126);
  }

  if (!tempSenses.IsNull() && !tempModelCurves.IsNull() && !tempParameterCurves.IsNull())
  {

    for (int i = 1; i <= num; i++)

    {
      occ::handle<IGESData_IGESEntity> tempEnt;

      if (PR.ReadEntity(IR, PR.Current(), aStatus, tempEnt))
        tempModelCurves->SetValue(i, tempEnt);
      else
      {
        Message_Msg Msg127("XTSEP_127");
        switch (aStatus)
        {
          case IGESData_ReferenceError:
          {
            Message_Msg Msg216("IGES_216");
            Msg127.Arg(Msg216.Value());
            PR.SendFail(Msg127);
            break;
          }
          case IGESData_EntityError:
          {
            Message_Msg Msg217("IGES_217");
            Msg127.Arg(Msg217.Value());
            PR.SendFail(Msg127);
            break;
          }
          default:
          {
          }
        }
      }

      int tempSense;

      if (PR.ReadInteger(PR.Current(), tempSense))
        tempSenses->SetValue(i, tempSense);
      else
      {
        Message_Msg Msg128("XTSEP_128");
        PR.SendFail(Msg128);
      }

      int tempCount;

      if (PR.ReadInteger(PR.Current(), tempCount) && (tempCount >= 0))
      {
        occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> tempParCurves;
        if (tempCount > 0)
        {
          Message_Msg Msg130("XTSEP_130");

          PR.ReadEnts(IR, PR.CurrentList(tempCount), Msg130, tempParCurves);
        }
        tempParameterCurves->SetValue(i, tempParCurves);
      }
      else
      {
        Message_Msg Msg129("XTSEP_129");
        PR.SendFail(Msg129);
      }
    }
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent
    ->Init(tempType, tempPreference, tempSurface, tempModelCurves, tempSenses, tempParameterCurves);
}

void IGESGeom_ToolBoundary::WriteOwnParams(const occ::handle<IGESGeom_Boundary>& ent,
                                           IGESData_IGESWriter&                  IW) const
{
  int i, j, num1;
  IW.Send(ent->BoundaryType());
  IW.Send(ent->PreferenceType());
  IW.Send(ent->Surface());
  IW.Send(ent->NbModelSpaceCurves());
  for (num1 = ent->NbModelSpaceCurves(), i = 1; i <= num1; i++)
  {
    IW.Send(ent->ModelSpaceCurve(i));
    IW.Send(ent->Sense(i));
    occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> curves =
      ent->ParameterCurves(i);
    int nbc = ent->NbParameterCurves(i);
    IW.Send(nbc);
    if (nbc > 0)
    {
      for (j = 1; j <= nbc; j++)
        IW.Send(curves->Value(j));
    }
  }
}

void IGESGeom_ToolBoundary::OwnShared(const occ::handle<IGESGeom_Boundary>& ent,
                                      Interface_EntityIterator&             iter) const
{
  int i, j, num1;
  iter.GetOneItem(ent->Surface());
  for (num1 = ent->NbModelSpaceCurves(), i = 1; i <= num1; i++)
  {
    iter.GetOneItem(ent->ModelSpaceCurve(i));
    occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> curves =
      ent->ParameterCurves(i);
    if (!curves.IsNull())
    {
      int nbc = curves->Length();
      for (j = 1; j <= nbc; j++)
        iter.GetOneItem(curves->Value(j));
    }
  }
}

void IGESGeom_ToolBoundary::OwnCopy(const occ::handle<IGESGeom_Boundary>& another,
                                    const occ::handle<IGESGeom_Boundary>& ent,
                                    Interface_CopyTool&                   TC) const
{
  int i, j;
  int tempType       = another->BoundaryType();
  int tempPreference = another->PreferenceType();
  int num1           = another->NbModelSpaceCurves();

  DeclareAndCast(IGESData_IGESEntity, tempSurface, TC.Transferred(another->Surface()));

  occ::handle<NCollection_HArray1<int>> tempSenses = new NCollection_HArray1<int>(1, num1);
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> tempModelCurves =
    new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, num1);
  occ::handle<IGESBasic_HArray1OfHArray1OfIGESEntity> tempParameterCurves =
    new IGESBasic_HArray1OfHArray1OfIGESEntity(1, num1);

  for (i = 1; i <= num1; i++)
  {
    DeclareAndCast(IGESData_IGESEntity, tempEnt, TC.Transferred(another->ModelSpaceCurve(i)));
    tempModelCurves->SetValue(i, tempEnt);
    tempSenses->SetValue(i, another->Sense(i));
    int num2 = another->NbParameterCurves(i);
    occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> ParCurves =
      another->ParameterCurves(i);
    occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> tempParCurves;
    if (num2 > 0)
      tempParCurves = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, num2);
    for (j = 1; j <= num2; j++)
    {
      DeclareAndCast(IGESData_IGESEntity, tempEnt1, TC.Transferred(ParCurves->Value(j)));
      tempParCurves->SetValue(j, tempEnt1);
    }
    tempParameterCurves->SetValue(i, tempParCurves);
  }
  ent
    ->Init(tempType, tempPreference, tempSurface, tempModelCurves, tempSenses, tempParameterCurves);
}

bool IGESGeom_ToolBoundary::OwnCorrect(const occ::handle<IGESGeom_Boundary>& ent) const
{

  bool res = false;
  bool r2d = false;
  int  nb  = ent->NbModelSpaceCurves();
  int  i;
  for (i = 1; i <= nb; i++)
  {
    int nbi = ent->NbParameterCurves(i);
    if (nbi == 0)
      continue;
    for (int j = 1; j <= nbi; j++)
    {
      occ::handle<IGESData_IGESEntity> c2d = ent->ParameterCurve(i, j);
      if (c2d.IsNull())
        continue;
      c2d->InitStatus(c2d->BlankStatus(), c2d->SubordinateStatus(), 5, c2d->HierarchyStatus());
      res = true;
    }
    r2d = true;
  }
  if (!r2d)
    return res;
  if (ent->BoundaryType() != 0)
    return res;

  occ::handle<IGESBasic_HArray1OfHArray1OfIGESEntity> cv2d =
    new IGESBasic_HArray1OfHArray1OfIGESEntity(1, nb);
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> modcv =
    new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, nb);
  occ::handle<NCollection_HArray1<int>> senses = new NCollection_HArray1<int>(1, nb);
  for (i = 1; i <= nb; i++)
  {
    senses->SetValue(i, ent->Sense(i));
    modcv->SetValue(i, ent->ModelSpaceCurve(i));
    cv2d->SetValue(i, ent->ParameterCurves(i));
  }
  ent->Init(1, ent->PreferenceType(), ent->Surface(), modcv, senses, cv2d);
  return true;
}

IGESData_DirChecker IGESGeom_ToolBoundary::DirChecker(const occ::handle<IGESGeom_Boundary>&) const
{
  IGESData_DirChecker DC(141, 0);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefAny);

  DC.Color(IGESData_DefAny);
  DC.SubordinateStatusRequired(0);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGeom_ToolBoundary::OwnCheck(const occ::handle<IGESGeom_Boundary>& ent,
                                     const Interface_ShareTool&,
                                     occ::handle<Interface_Check>& ach) const
{

  if ((ent->BoundaryType() != 0) && (ent->BoundaryType() != 1))
  {
    Message_Msg Msg122("XTSEP_122");
    ach->SendFail(Msg122);
  }
  if ((ent->PreferenceType() < 0) || (ent->PreferenceType() > 3))
  {
    Message_Msg Msg123("XTSEP_123");
    ach->SendFail(Msg123);
  }

  if (ent->BoundaryType() == 1)
  {
    if (ent->Surface()->TypeNumber() == 108)
    {
      Message_Msg Msg125("XTSEP_125");
      ach->SendFail(Msg125);
    }
  }

  int i, num;
  for (num = ent->NbModelSpaceCurves(), i = 1; i <= num; i++)
    if (ent->Sense(i) != 1 && ent->Sense(i) != 2)
    {
      Message_Msg Msg128("XTSEP_128");
      ach->SendFail(Msg128);
    }
}

void IGESGeom_ToolBoundary::OwnDump(const occ::handle<IGESGeom_Boundary>& ent,
                                    const IGESData_IGESDumper&            dumper,
                                    Standard_OStream&                     S,
                                    const int                             level) const
{
  int i, num, sublevel = (level > 4) ? 1 : 0;
  S << "IGESGeom_Boundary\n"
    << "Bounded Surface Representation Type : " << ent->BoundaryType() << "\n"
    << "Trimming Curves Representation : " << ent->PreferenceType() << "\n"
    << "Bounded Surface    : ";
  dumper.Dump(ent->Surface(), S, sublevel);
  S << "\n"
    << "Model Space Curves :\n"
    << "Orientation Flags  :\n"
    << "Parameter Curves Set : ";
  IGESData_DumpEntities(S, dumper, -level, 1, ent->NbModelSpaceCurves(), ent->ModelSpaceCurve);
  S << "\n";
  if (level > 4)
    for (num = ent->NbModelSpaceCurves(), i = 1; i <= num; i++)
    {
      S << "[" << i << "]: "
        << "Model Space Curve : ";
      dumper.Dump(ent->ModelSpaceCurve(i), S, 1);
      S << "  Orientation Flags : " << ent->Sense(i) << "\n"
        << "  Parameter Curves : ";
      occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> curves =
        ent->ParameterCurves(i);
      if (!curves.IsNull())
      {
        IGESData_DumpEntities(S, dumper, level, 1, curves->Length(), curves->Value);
      }
      else
      {
        S << " List Empty";
      }
      S << "\n";
    }
  S << std::endl;
}
