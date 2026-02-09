#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_Status.hpp>
#include <IGESGeom_Plane.hpp>
#include <IGESGeom_ToolPlane.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_MSG.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <Standard_DomainError.hpp>

#include <cstdio>

IGESGeom_ToolPlane::IGESGeom_ToolPlane() = default;

void IGESGeom_ToolPlane::ReadOwnParams(const occ::handle<IGESGeom_Plane>&          ent,
                                       const occ::handle<IGESData_IGESReaderData>& IR,
                                       IGESData_ParamReader&                       PR) const
{

  double                           A, B = 0., C = 0., D = 0., aSize = 0.;
  occ::handle<IGESData_IGESEntity> aCurve;
  gp_XYZ                           attach(0., 0., 0.);
  IGESData_Status                  aStatus;

  if ((!PR.ReadReal(PR.Current(), A)) || (!PR.ReadReal(PR.Current(), B))
      || (!PR.ReadReal(PR.Current(), C)) || (!PR.ReadReal(PR.Current(), D)))
  {
    Message_Msg Msg135("XSTEP_135");
    PR.SendFail(Msg135);
  }

  if (PR.IsParamDefined(PR.CurrentNumber()))
  {
    if (!PR.ReadEntity(IR, PR.Current(), aStatus, aCurve, true))
    {
      Message_Msg Msg136("XSTEP_136");
      switch (aStatus)
      {
        case IGESData_ReferenceError:
        {
          Message_Msg Msg216("IGES_216");
          Msg136.Arg(Msg216.Value());
          PR.SendFail(Msg136);
          break;
        }
        case IGESData_EntityError:
        {
          Message_Msg Msg217("IGES_217");
          Msg136.Arg(Msg217.Value());
          PR.SendFail(Msg136);
          break;
        }
        default:
        {
        }
      }
    }
  }

  if (PR.IsParamDefined(PR.CurrentNumber()))
  {
    Message_Msg Msg139("XSTEP_139");

    PR.ReadXYZ(PR.CurrentList(1, 3), Msg139, attach);

    if (!PR.ReadReal(PR.Current(), aSize))
    {
      Message_Msg Msg138("XSTEP_138");
      PR.SendFail(Msg138);
    }
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(A, B, C, D, aCurve, attach, aSize);
}

void IGESGeom_ToolPlane::WriteOwnParams(const occ::handle<IGESGeom_Plane>& ent,
                                        IGESData_IGESWriter&               IW) const
{
  double A, B, C, D;
  ent->Equation(A, B, C, D);
  IW.Send(A);
  IW.Send(B);
  IW.Send(C);
  IW.Send(D);

  IW.Send(ent->BoundingCurve());

  IW.Send(ent->SymbolAttach().X());
  IW.Send(ent->SymbolAttach().Y());
  IW.Send(ent->SymbolAttach().Z());
  IW.Send(ent->SymbolSize());
}

void IGESGeom_ToolPlane::OwnShared(const occ::handle<IGESGeom_Plane>& ent,
                                   Interface_EntityIterator&          iter) const
{
  iter.GetOneItem(ent->BoundingCurve());
}

void IGESGeom_ToolPlane::OwnCopy(const occ::handle<IGESGeom_Plane>& another,
                                 const occ::handle<IGESGeom_Plane>& ent,
                                 Interface_CopyTool&                TC) const
{
  double A, B, C, D;
  another->Equation(A, B, C, D);
  gp_XYZ attach = (another->SymbolAttach()).XYZ();
  double aSize  = another->SymbolSize();
  DeclareAndCast(IGESData_IGESEntity, aCurve, TC.Transferred(another->BoundingCurve()));
  ent->Init(A, B, C, D, aCurve, attach, aSize);
  ent->SetFormNumber(another->FormNumber());
}

IGESData_DirChecker IGESGeom_ToolPlane::DirChecker(const occ::handle<IGESGeom_Plane>& ent) const
{
  IGESData_DirChecker DC(108, -1, 1);
  DC.Structure(IGESData_DefVoid);
  if (ent->FormNumber() != 0)
  {
    DC.LineFont(IGESData_DefAny);
  }
  else
  {
    DC.LineFont(IGESData_DefVoid);
    DC.LineWeight(IGESData_DefVoid);
    DC.HierarchyStatusIgnored();
  }
  DC.Color(IGESData_DefAny);
  return DC;
}

void IGESGeom_ToolPlane::OwnCheck(const occ::handle<IGESGeom_Plane>& ent,
                                  const Interface_ShareTool&,
                                  occ::handle<Interface_Check>& ach) const
{

  if (ent->FormNumber() < -1 || ent->FormNumber() > 1)
  {
    Message_Msg Msg71("XSTEP_71");
    ach->SendFail(Msg71);
  }

  bool unbounded1 = ent->BoundingCurve().IsNull();
  bool unbounded2 = (ent->FormNumber() == 0);
  if ((unbounded1 && !unbounded2) || (!unbounded1 && unbounded2))
  {
    Message_Msg Msg137("XSTEP_137");
    ach->SendFail(Msg137);
  }

  if (!ent->HasBoundingCurve())
    return;
}

void IGESGeom_ToolPlane::OwnDump(const occ::handle<IGESGeom_Plane>& ent,
                                 const IGESData_IGESDumper&         dumper,
                                 Standard_OStream&                  S,
                                 const int                          level) const
{
  S << "IGESGeom_Plane\n";
  double A, B, C, D;
  ent->Equation(A, B, C, D);

  S << "Plane Coefficient A : " << A << "\n"
    << "Plane Coefficient B : " << B << "\n"
    << "Plane Coefficient C : " << C << "\n"
    << "Plane Coefficient D : " << D << "\n"
    << "The Bounding Curve  : ";
  dumper.Dump(ent->BoundingCurve(), S, (level <= 4) ? 0 : 1);
  S << "\n"
    << "Display Symbol Location : ";
  IGESData_DumpXYZL(S, level, ent->SymbolAttach(), ent->Location());
  S << "  Size  : " << ent->SymbolSize() << std::endl;
}
