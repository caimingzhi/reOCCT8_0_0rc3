#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_ReadWriteModule.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class IGESData_IGESReaderData;
class IGESData_ParamReader;
class IGESData_IGESWriter;

//! Defines Solid File Access Module for IGESSolid (specific parts)
//! Specific actions concern : Read and Write Own Parameters of
//! an IGESEntity.
class IGESSolid_ReadWriteModule : public IGESData_ReadWriteModule
{

public:
  //! Creates a ReadWriteModule & puts it into ReaderLib & WriterLib
  Standard_EXPORT IGESSolid_ReadWriteModule();

  //! Defines Case Numbers for Entities of IGESSolid
  Standard_EXPORT int CaseIGES(const int typenum, const int formnum) const override;

  //! Reads own parameters from file for an Entity of IGESSolid
  Standard_EXPORT void ReadOwnParams(const int                                   CN,
                                     const occ::handle<IGESData_IGESEntity>&     ent,
                                     const occ::handle<IGESData_IGESReaderData>& IR,
                                     IGESData_ParamReader&                       PR) const override;

  //! Writes own parameters to IGESWriter
  Standard_EXPORT void WriteOwnParams(const int                               CN,
                                      const occ::handle<IGESData_IGESEntity>& ent,
                                      IGESData_IGESWriter&                    IW) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_ReadWriteModule, IGESData_ReadWriteModule)
};
