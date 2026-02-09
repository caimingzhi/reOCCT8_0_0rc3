#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IGESData_SpecificLib.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>

class IGESData_IGESModel;
class IGESData_Protocol;
class IGESData_IGESEntity;

class IGESData_IGESDumper
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_IGESDumper(const occ::handle<IGESData_IGESModel>& model,
                                      const occ::handle<IGESData_Protocol>&  protocol);

  Standard_EXPORT void PrintDNum(const occ::handle<IGESData_IGESEntity>& ent,
                                 Standard_OStream&                       S) const;

  Standard_EXPORT void PrintShort(const occ::handle<IGESData_IGESEntity>& ent,
                                  Standard_OStream&                       S) const;

  Standard_EXPORT void Dump(const occ::handle<IGESData_IGESEntity>& ent,
                            Standard_OStream&                       S,
                            const int                               own,
                            const int                               attached = -1) const;

  Standard_EXPORT void OwnDump(const occ::handle<IGESData_IGESEntity>& ent,
                               Standard_OStream&                       S,
                               const int                               own) const;

private:
  occ::handle<IGESData_IGESModel> themodel;
  IGESData_SpecificLib            thelib;
};
