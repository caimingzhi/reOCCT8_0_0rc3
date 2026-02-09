#include <DDataStd.hpp>
#include <TDataStd.hpp>
#include <TDataStd_Real.hpp>
#include <TDataStd_RealEnum.hpp>
#include <TDataXtd.hpp>
#include <TDataXtd_Constraint.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>
#include <TNaming_NamedShape.hpp>

void DDataStd::AllCommands(Draw_Interpretor& theCommands)
{
  NamedShapeCommands(theCommands);
  BasicCommands(theCommands);
  DatumCommands(theCommands);
  ConstraintCommands(theCommands);
  ObjectCommands(theCommands);
  DrawDisplayCommands(theCommands);
  NameCommands(theCommands);
  TreeCommands(theCommands);
}

void DDataStd::DumpConstraint(const occ::handle<TDataXtd_Constraint>& CTR, Standard_OStream& anOS)
{
  TCollection_AsciiString S;
  TDF_Tool::Entry(CTR->Label(), S);
  anOS << S << " ";
  TDataXtd::Print(CTR->GetType(), anOS);
  for (int i = 1; i <= CTR->NbGeometries(); i++)
  {
    anOS << " G_" << i << " (";
    TDF_Tool::Entry(CTR->GetGeometry(i)->Label(), S);
    anOS << S << ") ";
  }
  if (CTR->IsPlanar())
  {
    anOS << " P (";
    TDF_Tool::Entry(CTR->GetPlane()->Label(), S);
    anOS << S << ") ";
  }
  if (CTR->IsDimension())
  {
    anOS << " V (";
    TDF_Tool::Entry(CTR->GetValue()->Label(), S);
    anOS << S << ") ";
    Standard_DISABLE_DEPRECATION_WARNINGS TDataStd_RealEnum t = CTR->GetValue()->GetDimension();
    TDataStd::Print(t, anOS);
    double val = CTR->GetValue()->Get();
    if (t == TDataStd_ANGULAR)
      val = (180. * val) / M_PI;
    Standard_ENABLE_DEPRECATION_WARNINGS anOS << " ";
    anOS << val;
  }
  if (!CTR->Verified())
    anOS << " NotVerifed";
}
