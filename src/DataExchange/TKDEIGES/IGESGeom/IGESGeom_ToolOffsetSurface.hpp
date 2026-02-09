#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESGeom_OffsetSurface;
class IGESData_IGESReaderData;
class IGESData_ParamReader;
class IGESData_IGESWriter;
class Interface_EntityIterator;
class IGESData_DirChecker;
class Interface_ShareTool;
class Interface_Check;
class Interface_CopyTool;
class IGESData_IGESDumper;

class IGESGeom_ToolOffsetSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESGeom_ToolOffsetSurface();

  Standard_EXPORT void ReadOwnParams(const occ::handle<IGESGeom_OffsetSurface>&  ent,
                                     const occ::handle<IGESData_IGESReaderData>& IR,
                                     IGESData_ParamReader&                       PR) const;

  Standard_EXPORT void WriteOwnParams(const occ::handle<IGESGeom_OffsetSurface>& ent,
                                      IGESData_IGESWriter&                       IW) const;

  Standard_EXPORT void OwnShared(const occ::handle<IGESGeom_OffsetSurface>& ent,
                                 Interface_EntityIterator&                  iter) const;

  Standard_EXPORT IGESData_DirChecker
    DirChecker(const occ::handle<IGESGeom_OffsetSurface>& ent) const;

  Standard_EXPORT void OwnCheck(const occ::handle<IGESGeom_OffsetSurface>& ent,
                                const Interface_ShareTool&                 shares,
                                occ::handle<Interface_Check>&              ach) const;

  Standard_EXPORT void OwnCopy(const occ::handle<IGESGeom_OffsetSurface>& entfrom,
                               const occ::handle<IGESGeom_OffsetSurface>& entto,
                               Interface_CopyTool&                        TC) const;

  Standard_EXPORT void OwnDump(const occ::handle<IGESGeom_OffsetSurface>& ent,
                               const IGESData_IGESDumper&                 dumper,
                               Standard_OStream&                          S,
                               const int                                  own) const;
};
