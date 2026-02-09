#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGeom_Direction.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESSolid_ToolToroidalSurface.hpp>
#include <IGESSolid_ToroidalSurface.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>

IGESSolid_ToolToroidalSurface::IGESSolid_ToolToroidalSurface() = default;

void IGESSolid_ToolToroidalSurface::ReadOwnParams(const occ::handle<IGESSolid_ToroidalSurface>& ent,
                                                  const occ::handle<IGESData_IGESReaderData>&   IR,
                                                  IGESData_ParamReader& PR) const
{
  occ::handle<IGESGeom_Point>      tempCenter;
  double                           majRad, minRad;
  occ::handle<IGESGeom_Direction>  tempAxis;
  occ::handle<IGESData_IGESEntity> tempRefdir;

  PR.ReadEntity(IR, PR.Current(), "Center point", STANDARD_TYPE(IGESGeom_Point), tempCenter);

  PR.ReadEntity(IR, PR.Current(), "Axis direction", STANDARD_TYPE(IGESGeom_Direction), tempAxis);

  PR.ReadReal(PR.Current(), "Major Radius", majRad);

  PR.ReadReal(PR.Current(), "Minor Radius", minRad);

  if (ent->FormNumber() == 1)

    PR.ReadEntity(IR, PR.Current(), "Reference direction", tempRefdir);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempCenter, tempAxis, majRad, minRad, occ::down_cast<IGESGeom_Direction>(tempRefdir));
}

void IGESSolid_ToolToroidalSurface::WriteOwnParams(
  const occ::handle<IGESSolid_ToroidalSurface>& ent,
  IGESData_IGESWriter&                          IW) const
{
  IW.Send(ent->Center());
  IW.Send(ent->Axis());
  IW.Send(ent->MajorRadius());
  IW.Send(ent->MinorRadius());
  if (ent->IsParametrised())
    IW.Send(ent->ReferenceDir());
}

void IGESSolid_ToolToroidalSurface::OwnShared(const occ::handle<IGESSolid_ToroidalSurface>& ent,
                                              Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Center());
  iter.GetOneItem(ent->Axis());
  iter.GetOneItem(ent->ReferenceDir());
}

void IGESSolid_ToolToroidalSurface::OwnCopy(const occ::handle<IGESSolid_ToroidalSurface>& another,
                                            const occ::handle<IGESSolid_ToroidalSurface>& ent,
                                            Interface_CopyTool&                           TC) const
{
  DeclareAndCast(IGESGeom_Point, tempCenter, TC.Transferred(another->Center()));
  DeclareAndCast(IGESGeom_Direction, tempAxis, TC.Transferred(another->Axis()));
  double majRad = another->MajorRadius();
  double minRad = another->MinorRadius();
  if (another->IsParametrised())
  {
    DeclareAndCast(IGESGeom_Direction, tempRefdir, TC.Transferred(another->ReferenceDir()));
    ent->Init(tempCenter, tempAxis, majRad, minRad, tempRefdir);
  }
  else
  {
    occ::handle<IGESGeom_Direction> tempRefdir;
    ent->Init(tempCenter, tempAxis, majRad, minRad, tempRefdir);
  }
}

IGESData_DirChecker IGESSolid_ToolToroidalSurface::DirChecker(
  const occ::handle<IGESSolid_ToroidalSurface>&) const
{
  IGESData_DirChecker DC(198, 0, 1);

  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.Color(IGESData_DefAny);

  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(1);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESSolid_ToolToroidalSurface::OwnCheck(const occ::handle<IGESSolid_ToroidalSurface>& ent,
                                             const Interface_ShareTool&,
                                             occ::handle<Interface_Check>& ach) const
{
  if (ent->MajorRadius() <= 0.0)
    ach->AddFail("Major Radius : Not Positive");
  if (ent->MinorRadius() <= 0.0)
    ach->AddFail("Minor Radius : Not Positive");
  if (ent->MinorRadius() >= ent->MajorRadius())
    ach->AddFail("Minor Radius : Value not < Major radius");
  int fn = 0;
  if (ent->IsParametrised())
    fn = 1;
  if (fn != ent->FormNumber())
    ach->AddFail("Parametrised Status Mismatches with Form Number");
}

void IGESSolid_ToolToroidalSurface::OwnDump(const occ::handle<IGESSolid_ToroidalSurface>& ent,
                                            const IGESData_IGESDumper&                    dumper,
                                            Standard_OStream&                             S,
                                            const int level) const
{
  S << "IGESSolid_ToroidalSurface\n";
  int sublevel = (level <= 4) ? 0 : 1;

  S << "Center : ";
  dumper.Dump(ent->Center(), S, sublevel);
  S << "\n"
    << "Axis direction : ";
  dumper.Dump(ent->Axis(), S, sublevel);
  S << "\n"
    << "Major Radius : " << ent->MajorRadius() << "  "
    << "Minor Radius : " << ent->MinorRadius() << "\n";
  if (ent->IsParametrised())
  {
    S << "Surface is Parametrised  -  Reference direction : ";
    dumper.Dump(ent->ReferenceDir(), S, sublevel);
    S << std::endl;
  }
  else
    S << "Surface is UnParametrised" << std::endl;
}
