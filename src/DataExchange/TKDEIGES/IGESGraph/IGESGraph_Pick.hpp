#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESGraph_Pick : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_Pick();

  Standard_EXPORT void Init(const int nbProps, const int aPickStatus);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int PickFlag() const;

  Standard_EXPORT bool IsPickable() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_Pick, IGESData_IGESEntity)

private:
  int theNbPropertyValues;
  int thePick;
};
