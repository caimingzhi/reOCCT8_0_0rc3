#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IFSelect_Signature.hpp>
#include <Standard_CString.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

//! Gives Color attached to an entity
//! Several forms are possible, according to <mode>
//! 1 : number : "Dnn" for entity, "Snn" for standard, "(none)" for 0
//! 2 : name : Of standard color, or of the color entity, or "(none)"
//! (if the color entity has no name, its label is taken)
//! 3 : RGB values, form R:nn,G:nn,B:nn
//! 4 : RED value   : an integer
//! 5 : GREEN value : an integer
//! 6 : BLUE value  : an integer
//! Other computable values can be added if needed :
//! CMY values, Percentages for Hue, Lightness, Saturation
class IGESSelect_SignColor : public IFSelect_Signature
{

public:
  //! Creates a SignColor
  //! mode : see above for the meaning
  //! modes 4,5,6 give a numeric integer value
  //! Name is initialised according to the mode
  Standard_EXPORT IGESSelect_SignColor(const int mode);

  //! Returns the value (see above)
  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SignColor, IFSelect_Signature)

private:
  int themode;
};

