#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESDimen_Section;
class IGESData_IGESReaderData;
class IGESData_ParamReader;
class IGESData_IGESWriter;
class Interface_EntityIterator;
class IGESData_DirChecker;
class Interface_ShareTool;
class Interface_Check;
class Interface_CopyTool;
class IGESData_IGESDumper;

//! Tool to work on a Section. Called by various Modules
//! (ReadWriteModule, GeneralModule, SpecificModule)
class IGESDimen_ToolSection
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a ToolSection, ready to work
  Standard_EXPORT IGESDimen_ToolSection();

  //! Reads own parameters from file. <PR> gives access to them,
  //! <IR> detains parameter types and values
  Standard_EXPORT void ReadOwnParams(const occ::handle<IGESDimen_Section>&       ent,
                                     const occ::handle<IGESData_IGESReaderData>& IR,
                                     IGESData_ParamReader&                       PR) const;

  //! Writes own parameters to IGESWriter
  Standard_EXPORT void WriteOwnParams(const occ::handle<IGESDimen_Section>& ent,
                                      IGESData_IGESWriter&                  IW) const;

  //! Lists the Entities shared by a Section <ent>, from
  //! its specific (own) parameters
  Standard_EXPORT void OwnShared(const occ::handle<IGESDimen_Section>& ent,
                                 Interface_EntityIterator&             iter) const;

  //! Sets automatic unambiguous Correction on a Section
  //! (LineFont forced to Rank = 1, DataType forced to 1)
  Standard_EXPORT bool OwnCorrect(const occ::handle<IGESDimen_Section>& ent) const;

  //! Returns specific DirChecker
  Standard_EXPORT IGESData_DirChecker DirChecker(const occ::handle<IGESDimen_Section>& ent) const;

  //! Performs Specific Semantic Check
  Standard_EXPORT void OwnCheck(const occ::handle<IGESDimen_Section>& ent,
                                const Interface_ShareTool&            shares,
                                occ::handle<Interface_Check>&         ach) const;

  //! Copies Specific Parameters
  Standard_EXPORT void OwnCopy(const occ::handle<IGESDimen_Section>& entfrom,
                               const occ::handle<IGESDimen_Section>& entto,
                               Interface_CopyTool&                   TC) const;

  //! Dump of Specific Parameters
  Standard_EXPORT void OwnDump(const occ::handle<IGESDimen_Section>& ent,
                               const IGESData_IGESDumper&            dumper,
                               Standard_OStream&                     S,
                               const int                             own) const;
};

