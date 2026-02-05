#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

//! defines IGESCompositeCurve, Type <102> Form <0>
//! in package IGESGeom
//! A composite curve is defined as an ordered list of entities
//! consisting of a point, connect point and parametrised curve
//! entities (excluding the CompositeCurve entity).
class IGESGeom_CompositeCurve : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_CompositeCurve();

  //! This method is used to set the fields of the class
  //! CompositeCurve
  //! - allEntities : Constituent Entities of the composite curve
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allEntities);

  //! returns the number of curves contained in the CompositeCurve
  Standard_EXPORT int NbCurves() const;

  //! returns Component of the CompositeCurve (a curve or a point)
  //! raises exception if Index <= 0 or Index > NbCurves()
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Curve(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_CompositeCurve, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theEntities;
};
