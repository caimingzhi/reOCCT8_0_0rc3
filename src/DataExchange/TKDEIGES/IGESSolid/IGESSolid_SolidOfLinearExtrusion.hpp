#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Dir;

//! defines SolidOfLinearExtrusion, Type <164> Form Number <0>
//! in package IGESSolid
//! Solid of linear extrusion is defined by translating an
//! area determined by a planar curve
class IGESSolid_SolidOfLinearExtrusion : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SolidOfLinearExtrusion();

  //! This method is used to set the fields of the class
  //! SolidOfLinearExtrusion
  //! - aCurve     : the planar curve that is to be translated
  //! - aLength    : the length of extrusion
  //! - aDirection : the vector specifying the direction of extrusion
  //! default (0,0,1)
  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>& aCurve,
                            const double                            aLength,
                            const gp_XYZ&                           aDirection);

  //! returns the planar curve that is to be translated
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Curve() const;

  //! returns the Extrusion Length
  Standard_EXPORT double ExtrusionLength() const;

  //! returns the Extrusion direction
  Standard_EXPORT gp_Dir ExtrusionDirection() const;

  //! returns ExtrusionDirection after applying TransformationMatrix
  Standard_EXPORT gp_Dir TransformedExtrusionDirection() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SolidOfLinearExtrusion, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity> theCurve;
  double                           theLength;
  gp_XYZ                           theDirection;
};
