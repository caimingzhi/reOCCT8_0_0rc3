#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XY.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

//! defines CenterLine, Type <106> Form <20-21>
//! in package IGESDimen
//! Is an entity appearing as crosshairs or as a
//! construction between 2 positions
class IGESDimen_CenterLine : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_CenterLine();

  //! This method is used to set the fields of the class
  //! CenterLine
  //! - aDataType      : Interpretation Flag, always = 1
  //! - aZDisplacement : Common z displacement
  //! - dataPnts       : Data points (x and y)
  Standard_EXPORT void Init(const int                                      aDataType,
                            const double                                   aZdisp,
                            const occ::handle<NCollection_HArray1<gp_XY>>& dataPnts);

  //! Sets FormNumber to 20 if <mode> is True, 21 else
  Standard_EXPORT void SetCrossHair(const bool mode);

  //! returns Interpretation Flag : IP = 1.
  Standard_EXPORT int Datatype() const;

  //! returns Number of Data Points.
  Standard_EXPORT int NbPoints() const;

  //! returns Common Z displacement.
  Standard_EXPORT double ZDisplacement() const;

  //! returns the data point as Pnt from gp.
  //! raises exception if Index <= 0 or Index > NbPoints()
  Standard_EXPORT gp_Pnt Point(const int Index) const;

  //! returns the data point as Pnt from gp after Transformation.
  //! raises exception if Index <= 0 or Index > NbPoints()
  Standard_EXPORT gp_Pnt TransformedPoint(const int Index) const;

  //! returns True if Form is 20.
  Standard_EXPORT bool IsCrossHair() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_CenterLine, IGESData_IGESEntity)

private:
  int                                     theDatatype;
  double                                  theZDisplacement;
  occ::handle<NCollection_HArray1<gp_XY>> theDataPoints;
};

