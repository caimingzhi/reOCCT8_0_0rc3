#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_SpecificModule.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class IGESData_IGESDumper;

class IGESGraph_SpecificModule : public IGESData_SpecificModule
{

public:
  Standard_EXPORT IGESGraph_SpecificModule();

  Standard_EXPORT void OwnDump(const int                               CN,
                               const occ::handle<IGESData_IGESEntity>& ent,
                               const IGESData_IGESDumper&              dumper,
                               Standard_OStream&                       S,
                               const int                               own) const override;

  Standard_EXPORT bool OwnCorrect(const int                               CN,
                                  const occ::handle<IGESData_IGESEntity>& ent) const override;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_SpecificModule, IGESData_SpecificModule)
};
