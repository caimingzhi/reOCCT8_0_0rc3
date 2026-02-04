#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TPrsStd_Driver.hpp>
class TDF_Label;
class AIS_InteractiveObject;

//! An implementation of TPrsStd_Driver for named shapes.
class TPrsStd_NamedShapeDriver : public TPrsStd_Driver
{

public:
  //! Constructs an empty named shape driver.
  Standard_EXPORT TPrsStd_NamedShapeDriver();

  //! Build the AISObject (if null) or update it.
  //! No compute is done.
  //! Returns <True> if information was found
  //! and AISObject updated.
  Standard_EXPORT bool Update(const TDF_Label&                    aLabel,
                              occ::handle<AIS_InteractiveObject>& anAISObject) override;

  DEFINE_STANDARD_RTTIEXT(TPrsStd_NamedShapeDriver, TPrsStd_Driver)
};

