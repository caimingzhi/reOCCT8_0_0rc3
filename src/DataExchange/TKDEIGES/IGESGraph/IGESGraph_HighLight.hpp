#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESGraph_HighLight : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_HighLight();

  Standard_EXPORT void Init(const int nbProps, const int aHighLightStatus);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int HighLightStatus() const;

  Standard_EXPORT bool IsHighLighted() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_HighLight, IGESData_IGESEntity)

private:
  int theNbPropertyValues;
  int theHighLight;
};
