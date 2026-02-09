#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESSolid_RightAngularWedge.hpp>
#include <IGESSolid_ToolRightAngularWedge.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>

IGESSolid_ToolRightAngularWedge::IGESSolid_ToolRightAngularWedge() = default;

void IGESSolid_ToolRightAngularWedge::ReadOwnParams(
  const occ::handle<IGESSolid_RightAngularWedge>& ent,
  const occ::handle<IGESData_IGESReaderData>&,
  IGESData_ParamReader& PR) const
{
  gp_XYZ tempSize, tempCorner, tempXAxis, tempZAxis;
  double lowX;
  double tempreal;

  PR.ReadXYZ(PR.CurrentList(1, 3), "Size of RightAngularWedge", tempSize);

  PR.ReadReal(PR.Current(), "Small X length", lowX);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Corner Point (X)", tempreal))
      tempCorner.SetX(tempreal);
  }
  else
    tempCorner.SetX(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Corner Point (Y)", tempreal))
      tempCorner.SetY(tempreal);
  }
  else
    tempCorner.SetY(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Corner Point (Z)", tempreal))
      tempCorner.SetZ(tempreal);
  }
  else
    tempCorner.SetZ(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Local X axis (I)", tempreal))
      tempXAxis.SetX(tempreal);
  }
  else
    tempXAxis.SetX(1.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Local X axis (J)", tempreal))
      tempXAxis.SetY(tempreal);
  }
  else
    tempXAxis.SetY(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Local X axis (K)", tempreal))
      tempXAxis.SetZ(tempreal);
  }
  else
    tempXAxis.SetZ(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Local Z axis (I)", tempreal))
      tempZAxis.SetX(tempreal);
  }
  else
    tempZAxis.SetX(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Local Z axis (J)", tempreal))
      tempZAxis.SetY(tempreal);
  }
  else
    tempZAxis.SetY(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Local Z axis (K)", tempreal))
      tempZAxis.SetZ(tempreal);
  }
  else
    tempZAxis.SetZ(1.0);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempSize, lowX, tempCorner, tempXAxis, tempZAxis);
  double eps = 1.E-05;
  if (!tempXAxis.IsEqual(ent->XAxis().XYZ(), eps))
    PR.AddWarning("XAxis poorly unitary, normalized");
  if (!tempZAxis.IsEqual(ent->ZAxis().XYZ(), eps))
    PR.AddWarning("ZAxis poorly unitary, normalized");
}

void IGESSolid_ToolRightAngularWedge::WriteOwnParams(
  const occ::handle<IGESSolid_RightAngularWedge>& ent,
  IGESData_IGESWriter&                            IW) const
{
  IW.Send(ent->Size().X());
  IW.Send(ent->Size().Y());
  IW.Send(ent->Size().Z());
  IW.Send(ent->XSmallLength());
  IW.Send(ent->Corner().X());
  IW.Send(ent->Corner().Y());
  IW.Send(ent->Corner().Z());
  IW.Send(ent->XAxis().X());
  IW.Send(ent->XAxis().Y());
  IW.Send(ent->XAxis().Z());
  IW.Send(ent->ZAxis().X());
  IW.Send(ent->ZAxis().Y());
  IW.Send(ent->ZAxis().Z());
}

void IGESSolid_ToolRightAngularWedge::OwnShared(const occ::handle<IGESSolid_RightAngularWedge>&,
                                                Interface_EntityIterator&) const
{
}

void IGESSolid_ToolRightAngularWedge::OwnCopy(
  const occ::handle<IGESSolid_RightAngularWedge>& another,
  const occ::handle<IGESSolid_RightAngularWedge>& ent,
  Interface_CopyTool&) const
{
  ent->Init(another->Size(),
            another->XSmallLength(),
            another->Corner().XYZ(),
            another->XAxis().XYZ(),
            another->ZAxis().XYZ());
}

IGESData_DirChecker IGESSolid_ToolRightAngularWedge::DirChecker(
  const occ::handle<IGESSolid_RightAngularWedge>&) const
{
  IGESData_DirChecker DC(152, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.Color(IGESData_DefAny);

  DC.UseFlagRequired(0);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESSolid_ToolRightAngularWedge::OwnCheck(const occ::handle<IGESSolid_RightAngularWedge>& ent,
                                               const Interface_ShareTool&,
                                               occ::handle<Interface_Check>& ach) const
{
  double eps    = 1.E-04;
  double prosca = ent->XAxis() * ent->ZAxis();
  if (prosca < -eps || prosca > eps)
    ach->AddFail("Local Z axis : Not orthogonal to X axis");
  if (ent->Size().X() <= 0. || ent->Size().Y() <= 0. || ent->Size().Z() <= 0.)
    ach->AddFail("Size : Values are not positive");
  if (ent->XSmallLength() <= 0.0)
    ach->AddFail("Small X Length : Not Positive");
  if (ent->XSmallLength() >= ent->Size().X())
    ach->AddFail("Small X Length : Value not < LX");
}

void IGESSolid_ToolRightAngularWedge::OwnDump(const occ::handle<IGESSolid_RightAngularWedge>& ent,
                                              const IGESData_IGESDumper&,
                                              Standard_OStream& S,
                                              const int         level) const
{
  S << "IGESSolid_RightAngularWedge\n"
    << "Size   : ";
  IGESData_DumpXYZ(S, ent->Size());
  S << "  ";
  S << "XSmall : " << ent->XSmallLength() << "\n"
    << "Corner : ";
  IGESData_DumpXYZL(S, level, ent->Corner(), ent->Location());
  S << "\nXAxis : ";
  IGESData_DumpXYZL(S, level, ent->XAxis(), ent->VectorLocation());
  S << "\nZAxis : ";
  IGESData_DumpXYZL(S, level, ent->ZAxis(), ent->VectorLocation());
  S << std::endl;
}
