#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

//! A SelectAnyType sorts the Entities of which the Type is Kind
//! of a given Type : this Type for Match is specific of each
//! class of SelectAnyType
class IFSelect_SelectAnyType : public IFSelect_SelectExtract
{

public:
  //! Returns the Type which has to be matched for select
  Standard_EXPORT virtual occ::handle<Standard_Type> TypeForMatch() const = 0;

  //! Returns True for an Entity (model->Value(num)) which is kind
  //! of the chosen type, given by the method TypeForMatch.
  //! Criterium is IsKind.
  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectAnyType, IFSelect_SelectExtract)
};

