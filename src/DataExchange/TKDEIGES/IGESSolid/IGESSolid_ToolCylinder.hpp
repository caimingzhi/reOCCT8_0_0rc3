#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESSolid_Cylinder;
class IGESData_IGESReaderData;
class IGESData_ParamReader;
class IGESData_IGESWriter;
class Interface_EntityIterator;
class IGESData_DirChecker;
class Interface_ShareTool;
class Interface_Check;
class Interface_CopyTool;
class IGESData_IGESDumper;

//! Tool to work on a Cylinder. Called by various Modules
//! (ReadWriteModule, GeneralModule, SpecificModule)
class IGESSolid_ToolCylinder
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a ToolCylinder, ready to work
  Standard_EXPORT IGESSolid_ToolCylinder();

  //! Reads own parameters from file. <PR> gives access to them,
  //! <IR> detains parameter types and values
  Standard_EXPORT void ReadOwnParams(const occ::handle<IGESSolid_Cylinder>&      ent,
                                     const occ::handle<IGESData_IGESReaderData>& IR,
                                     IGESData_ParamReader&                       PR) const;

  //! Writes own parameters to IGESWriter
  Standard_EXPORT void WriteOwnParams(const occ::handle<IGESSolid_Cylinder>& ent,
                                      IGESData_IGESWriter&                   IW) const;

  //! Lists the Entities shared by a Cylinder <ent>, from
  //! its specific (own) parameters
  Standard_EXPORT void OwnShared(const occ::handle<IGESSolid_Cylinder>& ent,
                                 Interface_EntityIterator&              iter) const;

  //! Returns specific DirChecker
  Standard_EXPORT IGESData_DirChecker DirChecker(const occ::handle<IGESSolid_Cylinder>& ent) const;

  //! Performs Specific Semantic Check
  Standard_EXPORT void OwnCheck(const occ::handle<IGESSolid_Cylinder>& ent,
                                const Interface_ShareTool&             shares,
                                occ::handle<Interface_Check>&          ach) const;

  //! Copies Specific Parameters
  Standard_EXPORT void OwnCopy(const occ::handle<IGESSolid_Cylinder>& entfrom,
                               const occ::handle<IGESSolid_Cylinder>& entto,
                               Interface_CopyTool&                    TC) const;

  //! Dump of Specific Parameters
  Standard_EXPORT void OwnDump(const occ::handle<IGESSolid_Cylinder>& ent,
                               const IGESData_IGESDumper&             dumper,
                               Standard_OStream&                      S,
                               const int                              own) const;
};

