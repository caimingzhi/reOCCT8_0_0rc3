#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESGeom_Boundary;
class IGESData_IGESReaderData;
class IGESData_ParamReader;
class IGESData_IGESWriter;
class Interface_EntityIterator;
class IGESData_DirChecker;
class Interface_ShareTool;
class Interface_Check;
class Interface_CopyTool;
class IGESData_IGESDumper;

//! Tool to work on a Boundary. Called by various Modules
//! (ReadWriteModule, GeneralModule, SpecificModule)
class IGESGeom_ToolBoundary
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a ToolBoundary, ready to work
  Standard_EXPORT IGESGeom_ToolBoundary();

  //! Reads own parameters from file. <PR> gives access to them,
  //! <IR> detains parameter types and values
  Standard_EXPORT void ReadOwnParams(const occ::handle<IGESGeom_Boundary>&       ent,
                                     const occ::handle<IGESData_IGESReaderData>& IR,
                                     IGESData_ParamReader&                       PR) const;

  //! Writes own parameters to IGESWriter
  Standard_EXPORT void WriteOwnParams(const occ::handle<IGESGeom_Boundary>& ent,
                                      IGESData_IGESWriter&                  IW) const;

  //! Lists the Entities shared by a Boundary <ent>, from
  //! its specific (own) parameters
  Standard_EXPORT void OwnShared(const occ::handle<IGESGeom_Boundary>& ent,
                                 Interface_EntityIterator&             iter) const;

  //! Sets automatic unambiguous Correction on a Boundary
  //! (if BoundaryType = 0, Nullify all ParameterCurves)
  Standard_EXPORT bool OwnCorrect(const occ::handle<IGESGeom_Boundary>& ent) const;

  //! Returns specific DirChecker
  Standard_EXPORT IGESData_DirChecker DirChecker(const occ::handle<IGESGeom_Boundary>& ent) const;

  //! Performs Specific Semantic Check
  Standard_EXPORT void OwnCheck(const occ::handle<IGESGeom_Boundary>& ent,
                                const Interface_ShareTool&            shares,
                                occ::handle<Interface_Check>&         ach) const;

  //! Copies Specific Parameters
  Standard_EXPORT void OwnCopy(const occ::handle<IGESGeom_Boundary>& entfrom,
                               const occ::handle<IGESGeom_Boundary>& entto,
                               Interface_CopyTool&                   TC) const;

  //! Dump of Specific Parameters
  Standard_EXPORT void OwnDump(const occ::handle<IGESGeom_Boundary>& ent,
                               const IGESData_IGESDumper&            dumper,
                               Standard_OStream&                     S,
                               const int                             own) const;
};
