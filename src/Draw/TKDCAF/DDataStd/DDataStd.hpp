#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>
#include <Standard_OStream.hpp>
class TDataXtd_Constraint;

class DDataStd
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void AllCommands(Draw_Interpretor& I);

  Standard_EXPORT static void NamedShapeCommands(Draw_Interpretor& I);

  Standard_EXPORT static void BasicCommands(Draw_Interpretor& I);

  Standard_EXPORT static void DatumCommands(Draw_Interpretor& I);

  Standard_EXPORT static void ConstraintCommands(Draw_Interpretor& I);

  Standard_EXPORT static void ObjectCommands(Draw_Interpretor& I);

  Standard_EXPORT static void DrawDisplayCommands(Draw_Interpretor& I);

  Standard_EXPORT static void NameCommands(Draw_Interpretor& I);

  Standard_EXPORT static void TreeCommands(Draw_Interpretor& I);

  Standard_EXPORT static void DumpConstraint(const occ::handle<TDataXtd_Constraint>& C,
                                             Standard_OStream&                       S);
};
