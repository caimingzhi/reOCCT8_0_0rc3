#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

//! A SelectErrorEntities sorts the Entities which are qualified
//! as "Error" (their Type has not been recognized) during reading
//! a File. This does not concern Entities which are syntactically
//! correct, but with incorrect data (for integrity constraints).
class IFSelect_SelectErrorEntities : public IFSelect_SelectExtract
{

public:
  //! Creates a SelectErrorEntities
  Standard_EXPORT IFSelect_SelectErrorEntities();

  //! Returns True for an Entity which is qualified as "Error", i.e.
  //! if <model> explicitly knows <ent> (through its Number) as
  //! Erroneous
  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Returns a text defining the criterium : "Error Entities"
  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectErrorEntities, IFSelect_SelectExtract)
};

