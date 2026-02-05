#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESBasic_ExternalRefFile;
class IGESData_IGESReaderData;
class IGESData_ParamReader;
class IGESData_IGESWriter;
class Interface_EntityIterator;
class IGESData_DirChecker;
class Interface_ShareTool;
class Interface_Check;
class Interface_CopyTool;
class IGESData_IGESDumper;

//! Tool to work on a ExternalRefFile. Called by various Modules
//! (ReadWriteModule, GeneralModule, SpecificModule)
class IGESBasic_ToolExternalRefFile
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a ToolExternalRefFile, ready to work
  Standard_EXPORT IGESBasic_ToolExternalRefFile();

  //! Reads own parameters from file. <PR> gives access to them,
  //! <IR> detains parameter types and values
  Standard_EXPORT void ReadOwnParams(const occ::handle<IGESBasic_ExternalRefFile>& ent,
                                     const occ::handle<IGESData_IGESReaderData>&   IR,
                                     IGESData_ParamReader&                         PR) const;

  //! Writes own parameters to IGESWriter
  Standard_EXPORT void WriteOwnParams(const occ::handle<IGESBasic_ExternalRefFile>& ent,
                                      IGESData_IGESWriter&                          IW) const;

  //! Lists the Entities shared by a ExternalRefFile <ent>, from
  //! its specific (own) parameters
  Standard_EXPORT void OwnShared(const occ::handle<IGESBasic_ExternalRefFile>& ent,
                                 Interface_EntityIterator&                     iter) const;

  //! Returns specific DirChecker
  Standard_EXPORT IGESData_DirChecker
    DirChecker(const occ::handle<IGESBasic_ExternalRefFile>& ent) const;

  //! Performs Specific Semantic Check
  Standard_EXPORT void OwnCheck(const occ::handle<IGESBasic_ExternalRefFile>& ent,
                                const Interface_ShareTool&                    shares,
                                occ::handle<Interface_Check>&                 ach) const;

  //! Copies Specific Parameters
  Standard_EXPORT void OwnCopy(const occ::handle<IGESBasic_ExternalRefFile>& entfrom,
                               const occ::handle<IGESBasic_ExternalRefFile>& entto,
                               Interface_CopyTool&                           TC) const;

  //! Dump of Specific Parameters
  Standard_EXPORT void OwnDump(const occ::handle<IGESBasic_ExternalRefFile>& ent,
                               const IGESData_IGESDumper&                    dumper,
                               Standard_OStream&                             S,
                               const int                                     own) const;
};
