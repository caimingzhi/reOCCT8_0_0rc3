#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESBasic_SubfigureDef;

//! defines SingularSubfigure, Type <408> Form <0>
//! in package IGESBasic
//! Defines the occurrence of a single instance of the
//! defined Subfigure.
class IGESBasic_SingularSubfigure : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_SingularSubfigure();

  //! This method is used to set the fields of the class
  //! SingularSubfigure
  //! - aSubfigureDef : the Subfigure Definition entity
  //! - aTranslation  : used to store the X,Y,Z coord
  //! - hasScale      : Indicates the presence of scale factor
  //! - aScale        : Used to store the scale factor
  Standard_EXPORT void Init(const occ::handle<IGESBasic_SubfigureDef>& aSubfigureDef,
                            const gp_XYZ&                              aTranslation,
                            const bool                                 hasScale,
                            const double                               aScale);

  //! returns the subfigure definition entity
  Standard_EXPORT occ::handle<IGESBasic_SubfigureDef> Subfigure() const;

  //! returns the X, Y, Z coordinates
  Standard_EXPORT gp_XYZ Translation() const;

  //! returns the scale factor
  //! if hasScaleFactor is False, returns 1.0 (default)
  Standard_EXPORT double ScaleFactor() const;

  //! returns a boolean indicating whether scale factor
  //! is present or not
  Standard_EXPORT bool HasScaleFactor() const;

  //! returns the Translation after transformation
  Standard_EXPORT gp_XYZ TransformedTranslation() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_SingularSubfigure, IGESData_IGESEntity)

private:
  occ::handle<IGESBasic_SubfigureDef> theSubfigureDef;
  gp_XYZ                              theTranslation;
  double                              theScaleFactor;
  bool                                hasScaleFactor;
};
