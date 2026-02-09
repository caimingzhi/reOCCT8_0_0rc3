#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class gp_GTrsf;

class IGESData_TransfEntity : public IGESData_IGESEntity
{

public:
  Standard_EXPORT virtual gp_GTrsf Value() const = 0;

  DEFINE_STANDARD_RTTIEXT(IGESData_TransfEntity, IGESData_IGESEntity)
};
