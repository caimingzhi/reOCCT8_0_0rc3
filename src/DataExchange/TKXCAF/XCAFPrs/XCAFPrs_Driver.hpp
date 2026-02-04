#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TPrsStd_Driver.hpp>
class TDF_Label;
class AIS_InteractiveObject;
class Standard_GUID;

//! Implements a driver for presentation of shapes in DECAF
//! document. Its the only purpose is to initialize and return
//! XCAFPrs_AISObject object on request
class XCAFPrs_Driver : public TPrsStd_Driver
{

public:
  Standard_EXPORT bool Update(const TDF_Label& L, occ::handle<AIS_InteractiveObject>& ais) override;

  //! returns GUID of the driver
  Standard_EXPORT static const Standard_GUID& GetID();

  DEFINE_STANDARD_RTTIEXT(XCAFPrs_Driver, TPrsStd_Driver)
};

