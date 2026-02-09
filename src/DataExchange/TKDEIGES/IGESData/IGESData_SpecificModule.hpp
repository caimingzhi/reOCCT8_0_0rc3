#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class IGESData_IGESDumper;

class IGESData_SpecificModule : public Standard_Transient
{

public:
  Standard_EXPORT virtual void OwnDump(const int                               CN,
                                       const occ::handle<IGESData_IGESEntity>& ent,
                                       const IGESData_IGESDumper&              dumper,
                                       Standard_OStream&                       S,
                                       const int                               own) const = 0;

  Standard_EXPORT virtual bool OwnCorrect(const int                               CN,
                                          const occ::handle<IGESData_IGESEntity>& ent) const;

  DEFINE_STANDARD_RTTIEXT(IGESData_SpecificModule, Standard_Transient)
};
