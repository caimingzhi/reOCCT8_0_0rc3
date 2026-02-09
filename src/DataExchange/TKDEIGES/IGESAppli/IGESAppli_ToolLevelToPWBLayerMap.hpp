#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESAppli_LevelToPWBLayerMap;
class IGESData_IGESReaderData;
class IGESData_ParamReader;
class IGESData_IGESWriter;
class Interface_EntityIterator;
class IGESData_DirChecker;
class Interface_ShareTool;
class Interface_Check;
class Interface_CopyTool;
class IGESData_IGESDumper;

class IGESAppli_ToolLevelToPWBLayerMap
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESAppli_ToolLevelToPWBLayerMap();

  Standard_EXPORT void ReadOwnParams(const occ::handle<IGESAppli_LevelToPWBLayerMap>& ent,
                                     const occ::handle<IGESData_IGESReaderData>&      IR,
                                     IGESData_ParamReader&                            PR) const;

  Standard_EXPORT void WriteOwnParams(const occ::handle<IGESAppli_LevelToPWBLayerMap>& ent,
                                      IGESData_IGESWriter&                             IW) const;

  Standard_EXPORT void OwnShared(const occ::handle<IGESAppli_LevelToPWBLayerMap>& ent,
                                 Interface_EntityIterator&                        iter) const;

  Standard_EXPORT IGESData_DirChecker
    DirChecker(const occ::handle<IGESAppli_LevelToPWBLayerMap>& ent) const;

  Standard_EXPORT void OwnCheck(const occ::handle<IGESAppli_LevelToPWBLayerMap>& ent,
                                const Interface_ShareTool&                       shares,
                                occ::handle<Interface_Check>&                    ach) const;

  Standard_EXPORT void OwnCopy(const occ::handle<IGESAppli_LevelToPWBLayerMap>& entfrom,
                               const occ::handle<IGESAppli_LevelToPWBLayerMap>& entto,
                               Interface_CopyTool&                              TC) const;

  Standard_EXPORT void OwnDump(const occ::handle<IGESAppli_LevelToPWBLayerMap>& ent,
                               const IGESData_IGESDumper&                       dumper,
                               Standard_OStream&                                S,
                               const int                                        own) const;
};
