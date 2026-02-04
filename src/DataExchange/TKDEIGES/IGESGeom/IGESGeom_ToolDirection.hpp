#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESGeom_Direction;
class IGESData_IGESReaderData;
class IGESData_ParamReader;
class IGESData_IGESWriter;
class Interface_EntityIterator;
class IGESData_DirChecker;
class Interface_ShareTool;
class Interface_Check;
class Interface_CopyTool;
class IGESData_IGESDumper;

//! Tool to work on a Direction. Called by various Modules
//! (ReadWriteModule, GeneralModule, SpecificModule)
class IGESGeom_ToolDirection
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a ToolDirection, ready to work
  Standard_EXPORT IGESGeom_ToolDirection();

  //! Reads own parameters from file. <PR> gives access to them,
  //! <IR> detains parameter types and values
  Standard_EXPORT void ReadOwnParams(const occ::handle<IGESGeom_Direction>&      ent,
                                     const occ::handle<IGESData_IGESReaderData>& IR,
                                     IGESData_ParamReader&                       PR) const;

  //! Writes own parameters to IGESWriter
  Standard_EXPORT void WriteOwnParams(const occ::handle<IGESGeom_Direction>& ent,
                                      IGESData_IGESWriter&                   IW) const;

  //! Lists the Entities shared by a Direction <ent>, from
  //! its specific (own) parameters
  Standard_EXPORT void OwnShared(const occ::handle<IGESGeom_Direction>& ent,
                                 Interface_EntityIterator&              iter) const;

  //! Returns specific DirChecker
  Standard_EXPORT IGESData_DirChecker DirChecker(const occ::handle<IGESGeom_Direction>& ent) const;

  //! Performs Specific Semantic Check
  Standard_EXPORT void OwnCheck(const occ::handle<IGESGeom_Direction>& ent,
                                const Interface_ShareTool&             shares,
                                occ::handle<Interface_Check>&          ach) const;

  //! Copies Specific Parameters
  Standard_EXPORT void OwnCopy(const occ::handle<IGESGeom_Direction>& entfrom,
                               const occ::handle<IGESGeom_Direction>& entto,
                               Interface_CopyTool&                    TC) const;

  //! Dump of Specific Parameters
  Standard_EXPORT void OwnDump(const occ::handle<IGESGeom_Direction>& ent,
                               const IGESData_IGESDumper&             dumper,
                               Standard_OStream&                      S,
                               const int                              own) const;
};

