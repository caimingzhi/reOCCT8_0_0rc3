#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_SpecificModule.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class IGESData_IGESDumper;

//! Defines Services attached to IGES Entities : Dump, for IGESDefs
class IGESDefs_SpecificModule : public IGESData_SpecificModule
{

public:
  //! Creates a SpecificModule from IGESDefs & puts it into SpecificLib
  Standard_EXPORT IGESDefs_SpecificModule();

  //! Specific Dump (own parameters) for IGESDefs
  Standard_EXPORT void OwnDump(const int                               CN,
                               const occ::handle<IGESData_IGESEntity>& ent,
                               const IGESData_IGESDumper&              dumper,
                               Standard_OStream&                       S,
                               const int                               own) const override;

  DEFINE_STANDARD_RTTIEXT(IGESDefs_SpecificModule, IGESData_SpecificModule)
};
