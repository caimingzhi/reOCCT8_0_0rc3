#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class CDF_MetaDataDriver;

class CDF_MetaDataDriverFactory : public Standard_Transient
{

public:
  Standard_EXPORT virtual occ::handle<CDF_MetaDataDriver> Build() const = 0;

  DEFINE_STANDARD_RTTIEXT(CDF_MetaDataDriverFactory, Standard_Transient)
};

