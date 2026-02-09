#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_Status.hpp>
#include <IGESGeom_OffsetCurve.hpp>
#include <IGESGeom_ToolOffsetCurve.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <Standard_DomainError.hpp>

IGESGeom_ToolOffsetCurve::IGESGeom_ToolOffsetCurve() = default;

void IGESGeom_ToolOffsetCurve::ReadOwnParams(const occ::handle<IGESGeom_OffsetCurve>&    ent,
                                             const occ::handle<IGESData_IGESReaderData>& IR,
                                             IGESData_ParamReader&                       PR) const
{

  Message_Msg Msg121("XSTEP_121");

  int                              anOffsetType, aFunctionCoord, aTaperedOffsetType;
  double                           offDistance1, offDistance2;
  double                           arcLength1, arcLength2, anOffsetParam, anotherOffsetParam;
  gp_XYZ                           aNormalVec;
  occ::handle<IGESData_IGESEntity> aBaseCurve;
  occ::handle<IGESData_IGESEntity> aFunction;
  IGESData_Status                  aStatus;

  if (!PR.ReadEntity(IR, PR.Current(), aStatus, aBaseCurve))
  {
    Message_Msg Msg110("XSTEP_110");
    switch (aStatus)
    {
      case IGESData_ReferenceError:
      {
        Message_Msg Msg216("IGES_216");
        Msg110.Arg(Msg216.Value());
        PR.SendFail(Msg110);
        break;
      }
      case IGESData_EntityError:
      {
        Message_Msg Msg217("IGES_217");
        Msg110.Arg(Msg217.Value());
        PR.SendFail(Msg110);
        break;
      }
      default:
      {
      }
    }
  }

  if (!PR.ReadInteger(PR.Current(), anOffsetType))
  {
    Message_Msg Msg111("XSTEP_111");
    PR.SendFail(Msg111);
  }

  if (!PR.ReadEntity(IR, PR.Current(), aStatus, aFunction, true))
  {
    Message_Msg Msg112("XSTEP_112");
    switch (aStatus)
    {
      case IGESData_ReferenceError:
      {
        Message_Msg Msg216("IGES_216");
        Msg112.Arg(Msg216.Value());
        PR.SendFail(Msg112);
        break;
      }
      case IGESData_EntityError:
      {
        Message_Msg Msg217("IGES_217");
        Msg112.Arg(Msg217.Value());
        PR.SendFail(Msg112);
        break;
      }
      default:
      {
      }
    }
  }

  if (!PR.ReadInteger(PR.Current(), aFunctionCoord))
  {
    Message_Msg Msg113("XSTEP_113");
    PR.SendFail(Msg113);
  }

  if (!PR.ReadInteger(PR.Current(), aTaperedOffsetType))
  {
    Message_Msg Msg114("XSTEP_114");
    PR.SendFail(Msg114);
  }

  if (!PR.ReadReal(PR.Current(), offDistance1))
  {
    Message_Msg Msg115("XSTEP_115");
    PR.SendFail(Msg115);
  }

  if (!PR.ReadReal(PR.Current(), arcLength1))
  {
    Message_Msg Msg116("XSTEP_116");
    PR.SendFail(Msg116);
  }

  if (!PR.ReadReal(PR.Current(), offDistance2))
  {
    Message_Msg Msg117("XSTEP_117");
    PR.SendFail(Msg117);
  }

  if (!PR.ReadReal(PR.Current(), arcLength2))
  {
    Message_Msg Msg118("XSTEP_118");
    PR.SendFail(Msg118);
  }

  PR.ReadXYZ(PR.CurrentList(1, 3), Msg121, aNormalVec);

  if (!PR.ReadReal(PR.Current(), anOffsetParam))
  {
    Message_Msg Msg119("XSTEP_119");
    PR.SendFail(Msg119);
  }

  if (!PR.ReadReal(PR.Current(), anotherOffsetParam))
  {
    Message_Msg Msg120("XSTEP_120");
    PR.SendFail(Msg120);
  }

  PR.ReadXYZ(PR.CurrentList(1, 3), Msg121, aNormalVec);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(aBaseCurve,
            anOffsetType,
            aFunction,
            aFunctionCoord,
            aTaperedOffsetType,
            offDistance1,
            arcLength1,
            offDistance2,
            arcLength2,
            aNormalVec,
            anOffsetParam,
            anotherOffsetParam);
}

void IGESGeom_ToolOffsetCurve::WriteOwnParams(const occ::handle<IGESGeom_OffsetCurve>& ent,
                                              IGESData_IGESWriter&                     IW) const
{
  IW.Send(ent->BaseCurve());
  IW.Send(ent->OffsetType());

  IW.Send(ent->Function());

  IW.Send(ent->FunctionParameter());
  IW.Send(ent->TaperedOffsetType());
  IW.Send(ent->FirstOffsetDistance());
  IW.Send(ent->ArcLength1());
  IW.Send(ent->SecondOffsetDistance());
  IW.Send(ent->ArcLength2());
  IW.Send(ent->NormalVector().X());
  IW.Send(ent->NormalVector().Y());
  IW.Send(ent->NormalVector().Z());
  IW.Send(ent->StartParameter());
  IW.Send(ent->EndParameter());
}

void IGESGeom_ToolOffsetCurve::OwnShared(const occ::handle<IGESGeom_OffsetCurve>& ent,
                                         Interface_EntityIterator&                iter) const
{
  iter.GetOneItem(ent->BaseCurve());
  iter.GetOneItem(ent->Function());
}

void IGESGeom_ToolOffsetCurve::OwnCopy(const occ::handle<IGESGeom_OffsetCurve>& another,
                                       const occ::handle<IGESGeom_OffsetCurve>& ent,
                                       Interface_CopyTool&                      TC) const
{
  int    anOffsetType, aFunctionCoord, aTaperedOffsetType;
  double offDistance1, offDistance2;
  double arcLength1, arcLength2, anOffsetParam1, anOffsetParam2;

  DeclareAndCast(IGESData_IGESEntity, aBaseCurve, TC.Transferred(another->BaseCurve()));
  anOffsetType = another->OffsetType();
  DeclareAndCast(IGESData_IGESEntity, aFunction, TC.Transferred(another->Function()));
  aFunctionCoord     = another->FunctionParameter();
  aTaperedOffsetType = another->TaperedOffsetType();
  offDistance1       = another->FirstOffsetDistance();
  arcLength1         = another->ArcLength1();
  offDistance2       = another->SecondOffsetDistance();
  arcLength2         = another->ArcLength2();
  gp_XYZ aNormalVec  = (another->NormalVector()).XYZ();
  anOffsetParam1     = another->StartParameter();
  anOffsetParam2     = another->EndParameter();

  ent->Init(aBaseCurve,
            anOffsetType,
            aFunction,
            aFunctionCoord,
            aTaperedOffsetType,
            offDistance1,
            arcLength1,
            offDistance2,
            arcLength2,
            aNormalVec,
            anOffsetParam1,
            anOffsetParam2);
}

bool IGESGeom_ToolOffsetCurve::OwnCorrect(const occ::handle<IGESGeom_OffsetCurve>& ent) const
{
  if (ent->OffsetType() == 3)
    return false;
  occ::handle<IGESData_IGESEntity> func = ent->Function();
  if (func.IsNull())
    return false;

  func.Nullify();
  ent->Init(ent->BaseCurve(),
            ent->OffsetType(),
            func,
            0,
            ent->TaperedOffsetType(),
            ent->FirstOffsetDistance(),
            ent->ArcLength1(),
            ent->SecondOffsetDistance(),
            ent->ArcLength2(),
            ent->NormalVector().XYZ(),
            ent->StartParameter(),
            ent->EndParameter());
  return true;
}

IGESData_DirChecker IGESGeom_ToolOffsetCurve::DirChecker(
  const occ::handle<IGESGeom_OffsetCurve>&) const
{
  IGESData_DirChecker DC(130, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);

  DC.Color(IGESData_DefAny);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGeom_ToolOffsetCurve::OwnCheck(const occ::handle<IGESGeom_OffsetCurve>& ent,
                                        const Interface_ShareTool&,
                                        occ::handle<Interface_Check>& ach) const
{

  int ot = ent->OffsetType();
  if (ot < 1 || ot > 3)
  {
    Message_Msg Msg111("XSTEP_111");
    ach->SendFail(Msg111);
  }

  if (ot != 1 && ((ent->TaperedOffsetType() < 1) || (ent->TaperedOffsetType() > 2)))
  {
    Message_Msg Msg114("XSTEP_114");
    ach->SendFail(Msg114);
  }
}

void IGESGeom_ToolOffsetCurve::OwnDump(const occ::handle<IGESGeom_OffsetCurve>& ent,
                                       const IGESData_IGESDumper&               dumper,
                                       Standard_OStream&                        S,
                                       const int                                level) const
{
  int sublevel = (level <= 4) ? 0 : 1;

  S << "IGESGeom_OffsetCurve\n"
    << "The curve to be offset     :\n";
  dumper.Dump(ent->BaseCurve(), S, sublevel);
  S << "Offset Distance Flag       : " << ent->OffsetType() << "\n"
    << "Curve entity whose coordinate defines the offset : ";
  dumper.Dump(ent->Function(), S, sublevel);
  S << "\n"
    << "In which Coordinate to use : " << ent->FunctionParameter() << "\n"
    << "Tapered Offset Type Flag   : " << ent->TaperedOffsetType() << "\n"
    << "First Offset Distance      : " << ent->FirstOffsetDistance() << "  "
    << "Arc Length : " << ent->ArcLength1() << "\n"
    << "Second Offset Distance     : " << ent->SecondOffsetDistance() << "  "
    << "Arc Length : " << ent->ArcLength2() << "\n"
    << "Normal Vector : ";
  IGESData_DumpXYZL(S, level, ent->NormalVector(), ent->VectorLocation());
  S << "\n";
  S << "Offset curve Parameters. Starting : " << ent->StartParameter() << "  "
    << "Ending : " << ent->EndParameter() << std::endl;
}
