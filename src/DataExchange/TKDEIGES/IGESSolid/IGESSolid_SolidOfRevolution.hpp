#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class gp_Dir;

//! defines SolidOfRevolution, Type <162> Form Number <0,1>
//! in package IGESSolid
//! This entity is defined by revolving the area determined
//! by a planar curve about a specified axis through a given
//! fraction of full rotation.
class IGESSolid_SolidOfRevolution : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SolidOfRevolution();

  //! This method is used to set the fields of the class
  //! SolidOfRevolution
  //! - aCurve     : the curve entity that is to be revolved
  //! - aFract     : the fraction of full rotation (default 1.0)
  //! - aAxisPnt   : the point on the axis
  //! - aDirection : the direction of the axis
  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>& aCurve,
                            const double                            aFract,
                            const gp_XYZ&                           aAxisPnt,
                            const gp_XYZ&                           aDirection);

  //! Sets the Curve to be by default, Closed to Axis (Form 0)
  //! if <mode> is True, Closed to Itself (Form 1) else
  Standard_EXPORT void SetClosedToAxis(const bool mode);

  //! Returns True if Form Number = 0
  //! if Form no is 0, then the curve is closed to axis
  //! if 1, the curve is closed to itself.
  Standard_EXPORT bool IsClosedToAxis() const;

  //! returns the curve entity that is to be revolved
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Curve() const;

  //! returns the fraction of full rotation that the curve is to
  //! be rotated
  Standard_EXPORT double Fraction() const;

  //! returns the point on the axis
  Standard_EXPORT gp_Pnt AxisPoint() const;

  //! returns the point on the axis after applying Trans.Matrix
  Standard_EXPORT gp_Pnt TransformedAxisPoint() const;

  //! returns the direction of the axis
  Standard_EXPORT gp_Dir Axis() const;

  //! returns the direction of the axis after applying
  //! TransformationMatrix
  Standard_EXPORT gp_Dir TransformedAxis() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SolidOfRevolution, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity> theCurve;
  double                           theFraction;
  gp_XYZ                           theAxisPoint;
  gp_XYZ                           theAxis;
};

