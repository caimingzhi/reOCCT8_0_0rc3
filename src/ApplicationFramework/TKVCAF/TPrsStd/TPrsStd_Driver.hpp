#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TDF_Label;
class AIS_InteractiveObject;

class TPrsStd_Driver : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool Update(const TDF_Label&                    L,
                                      occ::handle<AIS_InteractiveObject>& ais) = 0;

  DEFINE_STANDARD_RTTIEXT(TPrsStd_Driver, Standard_Transient)

protected:
  Standard_EXPORT TPrsStd_Driver();
};
