#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XY.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

//! defines Section, Type <106> Form <31-38>
//! in package IGESDimen
//! Contains information to display sectioned sides
class IGESDimen_Section : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_Section();

  //! This method is used to set the fields of the class
  //! Section
  //! - dataType   : Interpretation Flag, always = 1
  //! - aDisp      : Common z displacement
  //! - dataPoints : Data points
  Standard_EXPORT void Init(const int                                      dataType,
                            const double                                   aDisp,
                            const occ::handle<NCollection_HArray1<gp_XY>>& dataPoints);

  //! Changes FormNumber (indicates the Type of the Hatches)
  //! Error if not in range [31-38]
  Standard_EXPORT void SetFormNumber(const int form);

  //! returns Interpretation Flag, always = 1
  Standard_EXPORT int Datatype() const;

  //! returns number of Data Points
  Standard_EXPORT int NbPoints() const;

  //! returns common Z displacement
  Standard_EXPORT double ZDisplacement() const;

  //! returns Index'th data point
  //! raises exception if Index <= 0 or Index > NbPoints()
  Standard_EXPORT gp_Pnt Point(const int Index) const;

  //! returns Index'th data point after Transformation
  //! raises exception if Index <= 0 or Index > NbPoints()
  Standard_EXPORT gp_Pnt TransformedPoint(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_Section, IGESData_IGESEntity)

private:
  int                                     theDatatype;
  double                                  theZDisplacement;
  occ::handle<NCollection_HArray1<gp_XY>> theDataPoints;
};

