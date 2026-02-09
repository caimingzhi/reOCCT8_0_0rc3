#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESDimen_DimensionTolerance : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_DimensionTolerance();

  Standard_EXPORT void Init(const int    nbPropVal,
                            const int    aSecTolFlag,
                            const int    aTolType,
                            const int    aTolPlaceFlag,
                            const double anUpperTol,
                            const double aLowerTol,
                            const bool   aSignFlag,
                            const int    aFracFlag,
                            const int    aPrecision);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int SecondaryToleranceFlag() const;

  Standard_EXPORT int ToleranceType() const;

  Standard_EXPORT int TolerancePlacementFlag() const;

  Standard_EXPORT double UpperTolerance() const;

  Standard_EXPORT double LowerTolerance() const;

  Standard_EXPORT bool SignSuppressionFlag() const;

  Standard_EXPORT int FractionFlag() const;

  Standard_EXPORT int Precision() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_DimensionTolerance, IGESData_IGESEntity)

private:
  int    theNbPropertyValues;
  int    theSecondaryToleranceFlag;
  int    theToleranceType;
  int    theTolerancePlacementFlag;
  double theUpperTolerance;
  double theLowerTolerance;
  bool   theSignSuppressionFlag;
  int    theFractionFlag;
  int    thePrecision;
};
