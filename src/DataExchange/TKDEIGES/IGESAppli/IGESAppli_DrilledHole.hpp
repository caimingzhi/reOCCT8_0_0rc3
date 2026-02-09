#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESAppli_DrilledHole : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_DrilledHole();

  Standard_EXPORT void Init(const int    nbPropVal,
                            const double aSize,
                            const double anotherSize,
                            const int    aPlating,
                            const int    aLayer,
                            const int    anotherLayer);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT double DrillDiaSize() const;

  Standard_EXPORT double FinishDiaSize() const;

  Standard_EXPORT bool IsPlating() const;

  Standard_EXPORT int NbLowerLayer() const;

  Standard_EXPORT int NbHigherLayer() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_DrilledHole, IGESData_IGESEntity)

private:
  int    theNbPropertyValues;
  double theDrillDiaSize;
  double theFinishDiaSize;
  int    thePlatingFlag;
  int    theNbLowerLayer;
  int    theNbHigherLayer;
};
