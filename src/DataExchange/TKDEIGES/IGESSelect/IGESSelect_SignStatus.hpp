#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Signature.hpp>
#include <Standard_CString.hpp>
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

//! Gives D.E. Status under the form i,j,k,l (4 figures)
//! i for BlankStatus
//! j for SubordinateStatus
//! k for UseFlag
//! l for Hierarchy
//!
//! For matching, allowed shortcuts
//! B(Blanked) or V(Visible) are allowed instead of i
//! I(Independant=0), P(Physically Dep.=1), L(Logically Dep.=2) or
//! D(Dependant=3) are allowed instead of j
//! These letters must be given in their good position
//! For non-exact matching :
//! a letter (see above), no comma : only this status is checked
//! nothing or a star between commas : this status is OK
class IGESSelect_SignStatus : public IFSelect_Signature
{

public:
  Standard_EXPORT IGESSelect_SignStatus();

  //! Returns the value (see above)
  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Performs the match rule (see above)
  Standard_EXPORT bool Matches(const occ::handle<Standard_Transient>&       ent,
                               const occ::handle<Interface_InterfaceModel>& model,
                               const TCollection_AsciiString&               text,
                               const bool                                   exact) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SignStatus, IFSelect_Signature)
};
