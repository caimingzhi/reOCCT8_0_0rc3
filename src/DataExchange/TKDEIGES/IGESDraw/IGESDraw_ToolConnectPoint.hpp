#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESDraw_ConnectPoint;
class IGESData_IGESReaderData;
class IGESData_ParamReader;
class IGESData_IGESWriter;
class Interface_EntityIterator;
class IGESData_DirChecker;
class Interface_ShareTool;
class Interface_Check;
class Interface_CopyTool;
class IGESData_IGESDumper;

class IGESDraw_ToolConnectPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESDraw_ToolConnectPoint();

  Standard_EXPORT void ReadOwnParams(const occ::handle<IGESDraw_ConnectPoint>&   ent,
                                     const occ::handle<IGESData_IGESReaderData>& IR,
                                     IGESData_ParamReader&                       PR) const;

  Standard_EXPORT void WriteOwnParams(const occ::handle<IGESDraw_ConnectPoint>& ent,
                                      IGESData_IGESWriter&                      IW) const;

  Standard_EXPORT void OwnShared(const occ::handle<IGESDraw_ConnectPoint>& ent,
                                 Interface_EntityIterator&                 iter) const;

  Standard_EXPORT IGESData_DirChecker
    DirChecker(const occ::handle<IGESDraw_ConnectPoint>& ent) const;

  Standard_EXPORT void OwnCheck(const occ::handle<IGESDraw_ConnectPoint>& ent,
                                const Interface_ShareTool&                shares,
                                occ::handle<Interface_Check>&             ach) const;

  Standard_EXPORT void OwnCopy(const occ::handle<IGESDraw_ConnectPoint>& entfrom,
                               const occ::handle<IGESDraw_ConnectPoint>& entto,
                               Interface_CopyTool&                       TC) const;

  Standard_EXPORT void OwnDump(const occ::handle<IGESDraw_ConnectPoint>& ent,
                               const IGESData_IGESDumper&                dumper,
                               Standard_OStream&                         S,
                               const int                                 own) const;
};
