#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

//! A SelectUnknownEntities sorts the Entities which are qualified
//! as "Unknown" (their Type has not been recognized)
class IFSelect_SelectUnknownEntities : public IFSelect_SelectExtract
{

public:
  //! Creates a SelectUnknownEntities
  Standard_EXPORT IFSelect_SelectUnknownEntities();

  //! Returns True for an Entity which is qualified as "Unknown",
  //! i.e. if <model> known <ent> (through its Number) as Unknown
  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Returns a text defining the criterium : "Recognized Entities"
  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectUnknownEntities, IFSelect_SelectExtract)
};
