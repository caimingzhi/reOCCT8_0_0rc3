#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>
#include <Standard_OStream.hpp>
class TDataXtd_Constraint;

//! commands for Standard Attributes.
//! =================================
class DDataStd
{
public:
  DEFINE_STANDARD_ALLOC

  //! Used to browse tree nodes.
  //! commands
  //! ========
  //! command to set and get modeling attributes
  Standard_EXPORT static void AllCommands(Draw_Interpretor& I);

  //! to set and get NamedShape
  Standard_EXPORT static void NamedShapeCommands(Draw_Interpretor& I);

  //! to set and get Integer, Real, Reference, Geometry
  Standard_EXPORT static void BasicCommands(Draw_Interpretor& I);

  //! to set and get Datum attributes
  Standard_EXPORT static void DatumCommands(Draw_Interpretor& I);

  //! to set and get Constraint and Constraint attributes
  Standard_EXPORT static void ConstraintCommands(Draw_Interpretor& I);

  //! to set and get Objects attributes
  Standard_EXPORT static void ObjectCommands(Draw_Interpretor& I);

  //! to display standard attributes
  Standard_EXPORT static void DrawDisplayCommands(Draw_Interpretor& I);

  //! to set and get Name attribute
  Standard_EXPORT static void NameCommands(Draw_Interpretor& I);

  //! to build, edit and browse an explicit tree of labels
  //! package methods
  //! ===============
  Standard_EXPORT static void TreeCommands(Draw_Interpretor& I);

  Standard_EXPORT static void DumpConstraint(const occ::handle<TDataXtd_Constraint>& C,
                                             Standard_OStream&                       S);
};
