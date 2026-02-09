#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Law_BSpFunc.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>

class Law_Interpol : public Law_BSpFunc
{

public:
  Standard_EXPORT Law_Interpol();

  Standard_EXPORT void Set(const NCollection_Array1<gp_Pnt2d>& ParAndRad,
                           const bool                          Periodic = false);

  Standard_EXPORT void SetInRelative(const NCollection_Array1<gp_Pnt2d>& ParAndRad,
                                     const double                        Ud,
                                     const double                        Uf,
                                     const bool                          Periodic = false);

  Standard_EXPORT void Set(const NCollection_Array1<gp_Pnt2d>& ParAndRad,
                           const double                        Dd,
                           const double                        Df,
                           const bool                          Periodic = false);

  Standard_EXPORT void SetInRelative(const NCollection_Array1<gp_Pnt2d>& ParAndRad,
                                     const double                        Ud,
                                     const double                        Uf,
                                     const double                        Dd,
                                     const double                        Df,
                                     const bool                          Periodic = false);

  DEFINE_STANDARD_RTTIEXT(Law_Interpol, Law_BSpFunc)
};
