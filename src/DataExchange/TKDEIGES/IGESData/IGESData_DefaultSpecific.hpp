#pragma once

#include <Standard.hpp>

#include <IGESData_SpecificModule.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class IGESData_IGESDumper;

class IGESData_DefaultSpecific : public IGESData_SpecificModule
{

public:
  Standard_EXPORT IGESData_DefaultSpecific();

  Standard_EXPORT void OwnDump(const int                               CN,
                               const occ::handle<IGESData_IGESEntity>& ent,
                               const IGESData_IGESDumper&              dumper,
                               Standard_OStream&                       S,
                               const int                               own) const override;

  DEFINE_STANDARD_RTTIEXT(IGESData_DefaultSpecific, IGESData_SpecificModule)
};
