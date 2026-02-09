#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_SpecificModule.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class IGESData_IGESDumper;

class IGESSolid_SpecificModule : public IGESData_SpecificModule
{

public:
  Standard_EXPORT IGESSolid_SpecificModule();

  Standard_EXPORT void OwnDump(const int                               CN,
                               const occ::handle<IGESData_IGESEntity>& ent,
                               const IGESData_IGESDumper&              dumper,
                               Standard_OStream&                       S,
                               const int                               own) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SpecificModule, IGESData_SpecificModule)
};
