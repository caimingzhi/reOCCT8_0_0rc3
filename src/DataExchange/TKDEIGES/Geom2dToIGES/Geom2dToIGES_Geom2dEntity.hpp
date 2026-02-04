#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESData_IGESModel;

//! provides methods to transfer Geom2d entity from CASCADE to IGES.
class Geom2dToIGES_Geom2dEntity
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a tool Geom2dEntity
  Standard_EXPORT Geom2dToIGES_Geom2dEntity();

  //! Creates a tool ready to run and sets its
  //! fields as GE's.
  Standard_EXPORT Geom2dToIGES_Geom2dEntity(const Geom2dToIGES_Geom2dEntity& GE);

  //! Set the value of "TheModel"
  Standard_EXPORT void SetModel(const occ::handle<IGESData_IGESModel>& model);

  //! Returns the value of "TheModel"
  Standard_EXPORT occ::handle<IGESData_IGESModel> GetModel() const;

  //! Sets the value of the UnitFlag
  Standard_EXPORT void SetUnit(const double unit);

  //! Returns the value of the UnitFlag of the header of the model
  //! in millimeters.
  Standard_EXPORT double GetUnit() const;

private:
  occ::handle<IGESData_IGESModel> TheModel;
  double                          TheUnitFactor;
};

