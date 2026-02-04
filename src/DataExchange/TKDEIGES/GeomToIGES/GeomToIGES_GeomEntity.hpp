#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class IGESData_IGESModel;

//! provides methods to transfer Geom entity from CASCADE to IGES.
class GeomToIGES_GeomEntity
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a tool GeomEntity
  Standard_EXPORT GeomToIGES_GeomEntity();

  //! Creates a tool ready to run and sets its
  //! fields as GE's.
  Standard_EXPORT GeomToIGES_GeomEntity(const GeomToIGES_GeomEntity& GE);

  //! Set the value of "TheModel"
  Standard_EXPORT void SetModel(const occ::handle<IGESData_IGESModel>& model);

  //! Returns the value of "TheModel"
  Standard_EXPORT occ::handle<IGESData_IGESModel> GetModel() const;

  //! Sets the value of the UnitFlag
  Standard_EXPORT void SetUnit(const double unit);

  //! Returns the value of the UnitFlag of the header of the model
  //! in meters.
  Standard_EXPORT double GetUnit() const;

private:
  occ::handle<IGESData_IGESModel> TheModel;
  double                          TheUnitFactor;
};

