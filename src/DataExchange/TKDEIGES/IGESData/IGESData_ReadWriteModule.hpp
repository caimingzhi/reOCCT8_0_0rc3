#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_ReaderModule.hpp>
#include <Standard_Integer.hpp>
class Interface_FileReaderData;
class Interface_Check;
class Standard_Transient;
class IGESData_IGESEntity;
class IGESData_IGESReaderData;
class IGESData_ParamReader;
class IGESData_IGESWriter;

class IGESData_ReadWriteModule : public Interface_ReaderModule
{

public:
  Standard_EXPORT int CaseNum(const occ::handle<Interface_FileReaderData>& data,
                              const int                                    num) const override;

  Standard_EXPORT virtual int CaseIGES(const int typenum, const int formnum) const = 0;

  Standard_EXPORT void Read(const int                                    CN,
                            const occ::handle<Interface_FileReaderData>& data,
                            const int                                    num,
                            occ::handle<Interface_Check>&                ach,
                            const occ::handle<Standard_Transient>&       ent) const override;

  Standard_EXPORT virtual void ReadOwnParams(const int                                   CN,
                                             const occ::handle<IGESData_IGESEntity>&     ent,
                                             const occ::handle<IGESData_IGESReaderData>& IR,
                                             IGESData_ParamReader& PR) const = 0;

  Standard_EXPORT virtual void WriteOwnParams(const int                               CN,
                                              const occ::handle<IGESData_IGESEntity>& ent,
                                              IGESData_IGESWriter&                    IW) const = 0;

  DEFINE_STANDARD_RTTIEXT(IGESData_ReadWriteModule, Interface_ReaderModule)
};
