#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XY.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

//! defines WitnessLine, Type <106> Form <40>
//! in package IGESDimen
//! Contains one or more straight line segments associated
//! with drafting entities of various types
class IGESDimen_WitnessLine : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_WitnessLine();

  //! This method is used to set the fields of the class
  //! WitnessLine
  //! - dataType   : Interpretation Flag, always = 1
  //! - aDispl     : Common z displacement
  //! - dataPoints : Data points
  Standard_EXPORT void Init(const int                                      dataType,
                            const double                                   aDisp,
                            const occ::handle<NCollection_HArray1<gp_XY>>& dataPoints);

  //! returns Interpretation Flag, always = 1
  Standard_EXPORT int Datatype() const;

  //! returns number of Data Points
  Standard_EXPORT int NbPoints() const;

  //! returns common Z displacement
  Standard_EXPORT double ZDisplacement() const;

  //! returns Index'th. data point
  //! raises exception if Index <= 0 or Index > NbPoints
  Standard_EXPORT gp_Pnt Point(const int Index) const;

  //! returns data point after Transformation.
  //! raises exception if Index <= 0 or Index > NbPoints
  Standard_EXPORT gp_Pnt TransformedPoint(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_WitnessLine, IGESData_IGESEntity)

private:
  int                                     theDatatype;
  double                                  theZDisplacement;
  occ::handle<NCollection_HArray1<gp_XY>> theDataPoints;
};

