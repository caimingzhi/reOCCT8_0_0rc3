#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>

//! defines DrilledHole, Type <406> Form <6>
//! in package IGESAppli
//! Identifies an entity representing a drilled hole
//! through a printed circuit board.
class IGESAppli_DrilledHole : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_DrilledHole();

  //! This method is used to set the fields of the class
  //! DrilledHole
  //! - nbPropVal    : Number of property values = 5
  //! - aSize        : Drill diameter size
  //! - anotherSize  : Finish diameter size
  //! - aPlating     : Plating indication flag
  //! False = not plating
  //! True  = is plating
  //! - aLayer       : Lower numbered layer
  //! - anotherLayer : Higher numbered layer
  Standard_EXPORT void Init(const int    nbPropVal,
                            const double aSize,
                            const double anotherSize,
                            const int    aPlating,
                            const int    aLayer,
                            const int    anotherLayer);

  //! is always 5
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the drill diameter size
  Standard_EXPORT double DrillDiaSize() const;

  //! returns the finish diameter size
  Standard_EXPORT double FinishDiaSize() const;

  //! Returns Plating Status:
  //! False = not plating / True = is plating
  Standard_EXPORT bool IsPlating() const;

  //! returns the lower numbered layer
  Standard_EXPORT int NbLowerLayer() const;

  //! returns the higher numbered layer
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
