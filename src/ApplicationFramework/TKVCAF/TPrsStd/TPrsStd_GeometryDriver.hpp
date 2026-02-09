#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TPrsStd_Driver.hpp>
class TDF_Label;
class AIS_InteractiveObject;

class TPrsStd_GeometryDriver : public TPrsStd_Driver
{

public:
  Standard_EXPORT TPrsStd_GeometryDriver();

  Standard_EXPORT bool Update(const TDF_Label&                    aLabel,
                              occ::handle<AIS_InteractiveObject>& anAISObject) override;

  DEFINE_STANDARD_RTTIEXT(TPrsStd_GeometryDriver, TPrsStd_Driver)
};
