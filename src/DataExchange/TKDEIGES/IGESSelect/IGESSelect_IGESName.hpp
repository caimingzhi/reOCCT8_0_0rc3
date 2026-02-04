#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Signature.hpp>
#include <Standard_CString.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

//! IGESName is a Signature specific to IGESNorm :
//! it considers the Name of an IGESEntity as being its ShortLabel
//! (some sending systems use name, not to identify entities, but
//! ratjer to classify them)
class IGESSelect_IGESName : public IFSelect_Signature
{

public:
  //! Creates a Signature for IGES Name (reduced to ShortLabel,
  //! without SubscriptLabel or Long Name)
  Standard_EXPORT IGESSelect_IGESName();

  //! Returns the ShortLabel as being the Name of an IGESEntity
  //! If <ent> has no name, it returns empty string ""
  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_IGESName, IFSelect_Signature)
};

