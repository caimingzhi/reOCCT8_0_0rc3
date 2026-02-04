#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_SpecificModule.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class IGESData_IGESDumper;

//! Defines Services attached to IGES Entities :
//! Dump & OwnCorrect, for IGESGeom
class IGESGeom_SpecificModule : public IGESData_SpecificModule
{

public:
  //! Creates a SpecificModule from IGESGeom & puts it into SpecificLib
  Standard_EXPORT IGESGeom_SpecificModule();

  //! Specific Dump (own parameters) for IGESGeom
  Standard_EXPORT void OwnDump(const int                               CN,
                               const occ::handle<IGESData_IGESEntity>& ent,
                               const IGESData_IGESDumper&              dumper,
                               Standard_OStream&                       S,
                               const int                               own) const override;

  //! Performs non-ambiguous Correction on Entities which support
  //! them (Boundary,ConicArc,Flash,OffsetCurve,TransformationMatrix)
  Standard_EXPORT bool OwnCorrect(const int                               CN,
                                  const occ::handle<IGESData_IGESEntity>& ent) const override;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_SpecificModule, IGESData_SpecificModule)
};

