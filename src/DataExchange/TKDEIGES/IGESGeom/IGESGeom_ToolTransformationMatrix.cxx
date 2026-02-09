#include <gp_GTrsf.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGeom_ToolTransformationMatrix.hpp>
#include <IGESGeom_TransformationMatrix.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

IGESGeom_ToolTransformationMatrix::IGESGeom_ToolTransformationMatrix() = default;

void IGESGeom_ToolTransformationMatrix::ReadOwnParams(
  const occ::handle<IGESGeom_TransformationMatrix>& ent,
  const occ::handle<IGESData_IGESReaderData>&,
  IGESData_ParamReader& PR) const
{

  double                                   temp;
  occ::handle<NCollection_HArray2<double>> aMatrix = new NCollection_HArray2<double>(1, 3, 1, 4);

  for (int I = 1; I <= 3; I++)
  {
    for (int J = 1; J <= 4; J++)
    {

      if (PR.ReadReal(PR.Current(), temp))
        aMatrix->SetValue(I, J, temp);
      else
      {
        Message_Msg Msg215("XSTEP_215");
        PR.SendFail(Msg215);
      }
    }
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(aMatrix);
}

void IGESGeom_ToolTransformationMatrix::WriteOwnParams(
  const occ::handle<IGESGeom_TransformationMatrix>& ent,
  IGESData_IGESWriter&                              IW) const
{
  for (int I = 1; I <= 3; I++)
  {
    for (int J = 1; J <= 4; J++)
    {
      IW.Send(ent->Data(I, J));
    }
  }
}

void IGESGeom_ToolTransformationMatrix::OwnShared(const occ::handle<IGESGeom_TransformationMatrix>&,
                                                  Interface_EntityIterator&) const
{
}

void IGESGeom_ToolTransformationMatrix::OwnCopy(
  const occ::handle<IGESGeom_TransformationMatrix>& another,
  const occ::handle<IGESGeom_TransformationMatrix>& ent,
  Interface_CopyTool&) const
{
  occ::handle<NCollection_HArray2<double>> data = new NCollection_HArray2<double>(1, 3, 1, 4);
  for (int I = 1; I <= 3; I++)
  {
    for (int J = 1; J <= 4; J++)
    {
      data->SetValue(I, J, another->Data(I, J));
    }
  }

  ent->Init(data);
  ent->SetFormNumber(another->FormNumber());
}

bool IGESGeom_ToolTransformationMatrix::OwnCorrect(
  const occ::handle<IGESGeom_TransformationMatrix>& ent) const
{
  if (ent->FormNumber() > 1)
    return false;
  int cfn = (ent->Value().IsNegative() ? 1 : 0);
  if (cfn == ent->FormNumber())
    return false;
  ent->SetFormNumber(cfn);
  return true;
}

IGESData_DirChecker IGESGeom_ToolTransformationMatrix::DirChecker(
  const occ::handle<IGESGeom_TransformationMatrix>&) const
{
  IGESData_DirChecker DC(124);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);

  DC.Color(IGESData_DefAny);
  DC.BlankStatusIgnored();
  DC.SubordinateStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();

  return DC;
}

void IGESGeom_ToolTransformationMatrix::OwnCheck(
  const occ::handle<IGESGeom_TransformationMatrix>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{

  int form = ent->FormNumber();
  if ((form != 0) && (form != 1) && ((form < 10) || (form > 12)))
  {
    Message_Msg Msg71("XSTEP_71");
    ach->SendFail(Msg71);
  }
}

void IGESGeom_ToolTransformationMatrix::OwnDump(
  const occ::handle<IGESGeom_TransformationMatrix>& ent,
  const IGESData_IGESDumper&,
  Standard_OStream& S,
  const int) const
{
  S << "IGESGeom_TransformationMatrix\n"
    << "| R11, R12, R13, T1 |       " << ent->Data(1, 1) << ", " << ent->Data(1, 2) << ", "
    << ent->Data(1, 3) << ", " << ent->Data(1, 4) << "\n"
    << "| R21, R22, R23, T2 |       " << ent->Data(2, 1) << ", " << ent->Data(2, 2) << ", "
    << ent->Data(2, 3) << ", " << ent->Data(2, 4) << "\n"
    << "| R31, R32, R33, T3 |       " << ent->Data(3, 1) << ", " << ent->Data(3, 2) << ", "
    << ent->Data(3, 3) << ", " << ent->Data(3, 4) << "\n";

  switch (ent->FormNumber())
  {
    case 0:
      S << "-- Direct Orthogonal Matrix" << std::endl;
      break;
    case 1:
      S << "-- Reverse Orthogonal Matrix" << std::endl;
      break;
    case 10:
      S << "-- Cartesien Coordinate System" << std::endl;
      break;
    case 11:
      S << "-- Cylindrical Coordinate System" << std::endl;
      break;
    case 12:
      S << "-- Spherical Coordinate System" << std::endl;
      break;
    default:
      S << "--  (Incorrect Form Number)" << std::endl;
      break;
  }
}
