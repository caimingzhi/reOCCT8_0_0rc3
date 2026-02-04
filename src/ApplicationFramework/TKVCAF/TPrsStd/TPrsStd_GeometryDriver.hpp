#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TPrsStd_Driver.hpp>
class TDF_Label;
class AIS_InteractiveObject;

//! This method is an implementation of TPrsStd_Driver for geometries.
class TPrsStd_GeometryDriver : public TPrsStd_Driver
{

public:
  //! Constructs an empty geometry driver.
  Standard_EXPORT TPrsStd_GeometryDriver();

  //! Build the AISObject (if null) or update it.
  //! No compute is done.
  //! Returns <True> if information was found
  //! and AISObject updated.
  Standard_EXPORT bool Update(const TDF_Label&                    aLabel,
                              occ::handle<AIS_InteractiveObject>& anAISObject) override;

  DEFINE_STANDARD_RTTIEXT(TPrsStd_GeometryDriver, TPrsStd_Driver)
};

