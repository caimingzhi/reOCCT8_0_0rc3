#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_SpecificModule.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class IGESData_IGESDumper;

//! Defines Services attached to IGES Entities :
//! Dump & OwnCorrect, for IGESGraph
class IGESGraph_SpecificModule : public IGESData_SpecificModule
{

public:
  //! Creates a SpecificModule from IGESGraph & puts it into SpecificLib
  Standard_EXPORT IGESGraph_SpecificModule();

  //! Specific Dump (own parameters) for IGESGraph
  Standard_EXPORT void OwnDump(const int                               CN,
                               const occ::handle<IGESData_IGESEntity>& ent,
                               const IGESData_IGESDumper&              dumper,
                               Standard_OStream&                       S,
                               const int                               own) const override;

  //! Performs non-ambiguous Corrections on Entities which support
  //! them (DrawingSize,DrawingUnits,HighLight,IntercharacterSpacing,
  //! LineFontPredefined,NominalSize,Pick,UniformRectGrid)
  Standard_EXPORT bool OwnCorrect(const int                               CN,
                                  const occ::handle<IGESData_IGESEntity>& ent) const override;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_SpecificModule, IGESData_SpecificModule)
};

