#pragma once

#include <CSLib_DerivativeStatus.hpp>
#include <CSLib_NormalStatus.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <gp_Vec.hpp>
#include <NCollection_Array2.hpp>

class gp_Dir;
class gp_Vec;

class CSLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Normal(const gp_Vec&           theD1U,
                                     const gp_Vec&           theD1V,
                                     double                  theSinTol,
                                     CSLib_DerivativeStatus& theStatus,
                                     gp_Dir&                 theNormal);

  Standard_EXPORT static void Normal(const gp_Vec&       theD1U,
                                     const gp_Vec&       theD1V,
                                     const gp_Vec&       theD2U,
                                     const gp_Vec&       theD2V,
                                     const gp_Vec&       theD2UV,
                                     double              theSinTol,
                                     bool&               theDone,
                                     CSLib_NormalStatus& theStatus,
                                     gp_Dir&             theNormal);

  Standard_EXPORT static void Normal(const gp_Vec&       theD1U,
                                     const gp_Vec&       theD1V,
                                     double              theMagTol,
                                     CSLib_NormalStatus& theStatus,
                                     gp_Dir&             theNormal);

  Standard_EXPORT static void Normal(int                               theMaxOrder,
                                     const NCollection_Array2<gp_Vec>& theDerNUV,
                                     double                            theMagTol,
                                     double                            theU,
                                     double                            theV,
                                     double                            theUmin,
                                     double                            theUmax,
                                     double                            theVmin,
                                     double                            theVmax,
                                     CSLib_NormalStatus&               theStatus,
                                     gp_Dir&                           theNormal,
                                     int&                              theOrderU,
                                     int&                              theOrderV);

  Standard_EXPORT static gp_Vec DNNUV(int                               theNu,
                                      int                               theNv,
                                      const NCollection_Array2<gp_Vec>& theDerSurf);

  Standard_EXPORT static gp_Vec DNNUV(int                               theNu,
                                      int                               theNv,
                                      const NCollection_Array2<gp_Vec>& theDerSurf1,
                                      const NCollection_Array2<gp_Vec>& theDerSurf2);

  Standard_EXPORT static gp_Vec DNNormal(int                               theNu,
                                         int                               theNv,
                                         const NCollection_Array2<gp_Vec>& theDerNUV,
                                         int                               theIduref = 0,
                                         int                               theIdvref = 0);
};
