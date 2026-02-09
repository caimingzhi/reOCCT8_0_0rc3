#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESGraph_IntercharacterSpacing : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_IntercharacterSpacing();

  Standard_EXPORT void Init(const int nbProps, const double anISpace);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT double ISpace() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_IntercharacterSpacing, IGESData_IGESEntity)

private:
  int    theNbPropertyValues;
  double theISpace;
};
