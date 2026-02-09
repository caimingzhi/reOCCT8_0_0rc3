#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESSolid_ToolTorus.hpp>
#include <IGESSolid_Torus.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>

IGESSolid_ToolTorus::IGESSolid_ToolTorus() = default;

void IGESSolid_ToolTorus::ReadOwnParams(const occ::handle<IGESSolid_Torus>& ent,
                                        const occ::handle<IGESData_IGESReaderData>&,
                                        IGESData_ParamReader& PR) const
{
  double r1, r2;
  double tempreal;
  gp_XYZ tempPoint, tempAxis;

  PR.ReadReal(PR.Current(), "Radius of revolution", r1);
  PR.ReadReal(PR.Current(), "Radius of disc", r2);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Center Point (X)", tempreal))
      tempPoint.SetX(tempreal);
  }
  else
    tempPoint.SetX(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Center Point (Y)", tempreal))
      tempPoint.SetY(tempreal);
  }
  else
    tempPoint.SetY(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Center Point (Z)", tempreal))
      tempPoint.SetZ(tempreal);
  }
  else
    tempPoint.SetZ(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Axis direction (I)", tempreal))
      tempAxis.SetX(tempreal);
  }
  else
    tempAxis.SetX(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Axis direction (J)", tempreal))
      tempAxis.SetY(tempreal);
  }
  else
    tempAxis.SetY(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Axis direction (K)", tempreal))
      tempAxis.SetZ(tempreal);
  }
  else
    tempAxis.SetZ(1.0);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(r1, r2, tempPoint, tempAxis);
  double eps = 1.E-05;
  if (!tempAxis.IsEqual(ent->Axis().XYZ(), eps))
    PR.AddWarning("Axis poorly unitary, normalized");
}

void IGESSolid_ToolTorus::WriteOwnParams(const occ::handle<IGESSolid_Torus>& ent,
                                         IGESData_IGESWriter&                IW) const
{
  IW.Send(ent->MajorRadius());
  IW.Send(ent->DiscRadius());
  IW.Send(ent->AxisPoint().X());
  IW.Send(ent->AxisPoint().Y());
  IW.Send(ent->AxisPoint().Z());
  IW.Send(ent->Axis().X());
  IW.Send(ent->Axis().Y());
  IW.Send(ent->Axis().Z());
}

void IGESSolid_ToolTorus::OwnShared(const occ::handle<IGESSolid_Torus>&,
                                    Interface_EntityIterator&) const
{
}

void IGESSolid_ToolTorus::OwnCopy(const occ::handle<IGESSolid_Torus>& another,
                                  const occ::handle<IGESSolid_Torus>& ent,
                                  Interface_CopyTool&) const
{
  ent->Init(another->MajorRadius(),
            another->DiscRadius(),
            another->AxisPoint().XYZ(),
            another->Axis().XYZ());
}

IGESData_DirChecker IGESSolid_ToolTorus::DirChecker(const occ::handle<IGESSolid_Torus>&) const
{
  IGESData_DirChecker DC(160, 0);

  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.Color(IGESData_DefAny);

  DC.UseFlagRequired(0);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESSolid_ToolTorus::OwnCheck(const occ::handle<IGESSolid_Torus>& ent,
                                   const Interface_ShareTool&,
                                   occ::handle<Interface_Check>& ach) const
{
  if (ent->MajorRadius() <= 0.0)
    ach->AddFail("Radius of revolution : Not Positive");
  if (ent->DiscRadius() <= 0.0)
    ach->AddFail("Radius of disc : Not Positive");
  if (ent->DiscRadius() >= ent->MajorRadius())
    ach->AddFail("Radius of disc : is not Less than Radius of revolution");
}

void IGESSolid_ToolTorus::OwnDump(const occ::handle<IGESSolid_Torus>& ent,
                                  const IGESData_IGESDumper&,
                                  Standard_OStream& S,
                                  const int         level) const
{
  S << "IGESSolid_Torus\n"
    << "Radius of revolution : " << ent->MajorRadius() << "  "
    << "Radius of the disc   : " << ent->DiscRadius() << "\n"
    << "Center Point   : ";
  IGESData_DumpXYZL(S, level, ent->AxisPoint(), ent->Location());
  S << "\nAxis direction : ";
  IGESData_DumpXYZL(S, level, ent->Axis(), ent->VectorLocation());
  S << std::endl;
}
