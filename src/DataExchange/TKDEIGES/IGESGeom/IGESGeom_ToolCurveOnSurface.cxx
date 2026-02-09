#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_Status.hpp>
#include <IGESGeom_CurveOnSurface.hpp>
#include <IGESGeom_ToolCurveOnSurface.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>

IGESGeom_ToolCurveOnSurface::IGESGeom_ToolCurveOnSurface() = default;

void IGESGeom_ToolCurveOnSurface::ReadOwnParams(const occ::handle<IGESGeom_CurveOnSurface>& ent,
                                                const occ::handle<IGESData_IGESReaderData>& IR,
                                                IGESData_ParamReader& PR) const
{

  int                              aMode, aPreference;
  occ::handle<IGESData_IGESEntity> aSurface;
  occ::handle<IGESData_IGESEntity> aCurveUV;
  occ::handle<IGESData_IGESEntity> aCurve3D;
  IGESData_Status                  aStatus;

  if (!PR.ReadInteger(PR.Current(), aMode))
  {
    Message_Msg Msg276("XSTEP_276");
    PR.SendFail(Msg276);
  }
  if (!PR.ReadEntity(IR, PR.Current(), aStatus, aSurface))
  {
    Message_Msg Msg131("XSTEP_131");
    switch (aStatus)
    {
      case IGESData_ReferenceError:
      {
        Message_Msg Msg216("IGES_216");
        Msg131.Arg(Msg216.Value());
        PR.SendFail(Msg131);
        break;
      }
      case IGESData_EntityError:
      {
        Message_Msg Msg217("IGES_217");
        Msg131.Arg(Msg217.Value());
        PR.SendFail(Msg131);
        break;
      }
      default:
      {
      }
    }
  }

  if (!PR.ReadEntity(IR, PR.Current(), aStatus, aCurveUV, true))
  {
    Message_Msg Msg132("XSTEP_132");
    switch (aStatus)
    {
      case IGESData_ReferenceError:
      {
        Message_Msg Msg216("IGES_216");
        Msg132.Arg(Msg216.Value());
        PR.SendFail(Msg132);
        break;
      }
      case IGESData_EntityError:
      {
        Message_Msg Msg217("IGES_217");
        Msg132.Arg(Msg217.Value());
        PR.SendFail(Msg132);
        break;
      }
      default:
      {
      }
    }
  }

  if (!PR.ReadEntity(IR, PR.Current(), aStatus, aCurve3D, true))
  {
    ;

    Message_Msg Msg133("XSTEP_133");
    switch (aStatus)
    {
      case IGESData_ReferenceError:
      {
        Message_Msg Msg216("IGES_216");
        Msg133.Arg(Msg216.Value());
        PR.SendFail(Msg133);
        break;
      }
      case IGESData_EntityError:
      {
        Message_Msg Msg217("IGES_217");
        Msg133.Arg(Msg217.Value());
        PR.SendFail(Msg133);
        break;
      }
      default:
      {
      }
    }
  }
  if (!PR.ReadInteger(PR.Current(), aPreference))
  {
    Message_Msg Msg277("XSTEP_277");
    PR.SendFail(Msg277);
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(aMode, aSurface, aCurveUV, aCurve3D, aPreference);
}

void IGESGeom_ToolCurveOnSurface::WriteOwnParams(const occ::handle<IGESGeom_CurveOnSurface>& ent,
                                                 IGESData_IGESWriter& IW) const
{
  IW.Send(ent->CreationMode());
  IW.Send(ent->Surface());
  IW.Send(ent->CurveUV());
  IW.Send(ent->Curve3D());
  IW.Send(ent->PreferenceMode());
}

void IGESGeom_ToolCurveOnSurface::OwnShared(const occ::handle<IGESGeom_CurveOnSurface>& ent,
                                            Interface_EntityIterator&                   iter) const
{
  iter.GetOneItem(ent->Surface());
  iter.GetOneItem(ent->CurveUV());
  iter.GetOneItem(ent->Curve3D());
}

void IGESGeom_ToolCurveOnSurface::OwnCopy(const occ::handle<IGESGeom_CurveOnSurface>& another,
                                          const occ::handle<IGESGeom_CurveOnSurface>& ent,
                                          Interface_CopyTool&                         TC) const
{
  DeclareAndCast(IGESData_IGESEntity, aSurface, TC.Transferred(another->Surface()));
  DeclareAndCast(IGESData_IGESEntity, aCurveUV, TC.Transferred(another->CurveUV()));
  DeclareAndCast(IGESData_IGESEntity, aCurve3D, TC.Transferred(another->Curve3D()));

  int aMode       = another->CreationMode();
  int aPreference = another->PreferenceMode();

  ent->Init(aMode, aSurface, aCurveUV, aCurve3D, aPreference);
}

bool IGESGeom_ToolCurveOnSurface::OwnCorrect(const occ::handle<IGESGeom_CurveOnSurface>& ent) const
{
  occ::handle<IGESData_IGESEntity> c2d = ent->CurveUV();
  if (c2d.IsNull())
    return false;
  int uf = c2d->UseFlag();
  if (uf == 5)
    return false;
  c2d->InitStatus(c2d->BlankStatus(), c2d->SubordinateStatus(), 5, c2d->HierarchyStatus());
  return true;
}

IGESData_DirChecker IGESGeom_ToolCurveOnSurface::DirChecker(
  const occ::handle<IGESGeom_CurveOnSurface>&) const
{
  IGESData_DirChecker DC(142, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);

  DC.Color(IGESData_DefAny);

  DC.UseFlagRequired(5);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGeom_ToolCurveOnSurface::OwnCheck(const occ::handle<IGESGeom_CurveOnSurface>& ent,
                                           const Interface_ShareTool&,
                                           occ::handle<Interface_Check>& ach) const
{

  if (ent->CurveUV().IsNull() && ent->Curve3D().IsNull())
  {
    Message_Msg Msg134 = Message_Msg("XSTEP_134");
    ach->SendFail(Msg134);
  }
}

void IGESGeom_ToolCurveOnSurface::OwnDump(const occ::handle<IGESGeom_CurveOnSurface>& ent,
                                          const IGESData_IGESDumper&                  dumper,
                                          Standard_OStream&                           S,
                                          const int                                   level) const
{
  S << "IGESGeom_CurveOnSurface\n\n";
  int sublevel = (level <= 4) ? 0 : 1;

  int crem = ent->CreationMode();
  S << "Creation Mode : " << crem << "  i.e. ";
  if (crem == 0)
    S << " <Unspecified>\n";
  else if (crem == 1)
    S << " Projection of a Curve on a Surface\n";
  else if (crem == 2)
    S << " Intersection of two Surfaces\n";
  else if (crem == 3)
    S << " Isoparametric Curve (either U or V)\n";
  else
    S << " <Incorrect Value>\n";
  S << "The Surface on which the curve lies : ";
  dumper.Dump(ent->Surface(), S, sublevel);
  S << "\n"
       "The curve B (in the parametric space (u, v))  : ";
  dumper.Dump(ent->CurveUV(), S, sublevel);
  S << "\n"
       "The curve C (in the 3D Space) : ";
  dumper.Dump(ent->Curve3D(), S, sublevel);
  S << "\n";
  int pref = ent->PreferenceMode();
  S << "Preferred representation mode : " << pref << "  i.e. ";
  if (pref == 0)
    S << " <Unspecified>\n";
  else if (pref == 1)
    S << " Curve B on Surface\n";
  else if (pref == 2)
    S << " Curve C in 3D Space\n";
  else if (pref == 3)
    S << " Curves B & C equally preferred\n";
  else
    S << " <Incorrect Value>\n";
}
