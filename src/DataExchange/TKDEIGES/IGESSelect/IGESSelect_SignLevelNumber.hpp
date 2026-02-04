#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Signature.hpp>
#include <Standard_CString.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

//! Gives D.E. Level Number under two possible forms :
//! * for counter : "LEVEL nnnnnnn", " NO LEVEL", " LEVEL LIST"
//! * for selection : "/nnn/", "/0/", "/1/2/nnn/"
//!
//! For matching, giving /nn/ gets any entity attached to level nn
//! whatever simple or in a level list
class IGESSelect_SignLevelNumber : public IFSelect_Signature
{

public:
  //! Creates a SignLevelNumber
  //! <countmode> True : values are naturally displayed
  //! <countmode> False: values are separated by slashes
  //! in order to allow selection by signature by Draw or C++
  Standard_EXPORT IGESSelect_SignLevelNumber(const bool countmode);

  //! Returns the value (see above)
  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SignLevelNumber, IFSelect_Signature)

private:
  bool thecountmode;
};

