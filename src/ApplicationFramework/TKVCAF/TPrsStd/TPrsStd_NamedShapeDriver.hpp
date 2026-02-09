#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TPrsStd_Driver.hpp>
class TDF_Label;
class AIS_InteractiveObject;

class TPrsStd_NamedShapeDriver : public TPrsStd_Driver
{

public:
  Standard_EXPORT TPrsStd_NamedShapeDriver();

  Standard_EXPORT bool Update(const TDF_Label&                    aLabel,
                              occ::handle<AIS_InteractiveObject>& anAISObject) override;

  DEFINE_STANDARD_RTTIEXT(TPrsStd_NamedShapeDriver, TPrsStd_Driver)
};
