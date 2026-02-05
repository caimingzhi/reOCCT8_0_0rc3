#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_SpecificModule.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class IGESData_IGESDumper;

//! Defines Services attached to IGES Entities :
//! Dump & OwnCorrect, for IGESDraw
class IGESDraw_SpecificModule : public IGESData_SpecificModule
{

public:
  //! Creates a SpecificModule from IGESDraw & puts it into SpecificLib
  Standard_EXPORT IGESDraw_SpecificModule();

  //! Specific Dump (own parameters) for IGESDraw
  Standard_EXPORT void OwnDump(const int                               CN,
                               const occ::handle<IGESData_IGESEntity>& ent,
                               const IGESData_IGESDumper&              dumper,
                               Standard_OStream&                       S,
                               const int                               own) const override;

  //! Performs non-ambiguous Corrections on Entities which support
  //! them (Planar)
  Standard_EXPORT bool OwnCorrect(const int                               CN,
                                  const occ::handle<IGESData_IGESEntity>& ent) const override;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_SpecificModule, IGESData_SpecificModule)
};
