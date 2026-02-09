#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_ReadWriteModule.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class IGESData_IGESReaderData;
class IGESData_ParamReader;
class IGESData_IGESWriter;

class IGESGraph_ReadWriteModule : public IGESData_ReadWriteModule
{

public:
  Standard_EXPORT IGESGraph_ReadWriteModule();

  Standard_EXPORT int CaseIGES(const int typenum, const int formnum) const override;

  Standard_EXPORT void ReadOwnParams(const int                                   CN,
                                     const occ::handle<IGESData_IGESEntity>&     ent,
                                     const occ::handle<IGESData_IGESReaderData>& IR,
                                     IGESData_ParamReader&                       PR) const override;

  Standard_EXPORT void WriteOwnParams(const int                               CN,
                                      const occ::handle<IGESData_IGESEntity>& ent,
                                      IGESData_IGESWriter&                    IW) const override;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_ReadWriteModule, IGESData_ReadWriteModule)
};
