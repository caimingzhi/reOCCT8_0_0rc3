#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESGraph_DrawingSize : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_DrawingSize();

  Standard_EXPORT void Init(const int nbProps, const double aXSize, const double aYSize);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT double XSize() const;

  Standard_EXPORT double YSize() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_DrawingSize, IGESData_IGESEntity)

private:
  int    theNbPropertyValues;
  double theXSize;
  double theYSize;
};
