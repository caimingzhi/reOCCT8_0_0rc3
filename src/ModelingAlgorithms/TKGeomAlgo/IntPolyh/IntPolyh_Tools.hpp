#pragma once

#include <Adaptor3d_Surface.hpp>
#include <NCollection_Array1.hpp>
#include <IntPolyh_ArrayOfPointNormal.hpp>

class IntPolyh_Tools
{
public:
  Standard_EXPORT static void IsEnlargePossible(const occ::handle<Adaptor3d_Surface>& theSurf,
                                                bool&                                 theUEnlarge,
                                                bool&                                 theVEnlarge);

  Standard_EXPORT static void MakeSampling(const occ::handle<Adaptor3d_Surface>& theSurf,
                                           const int                             theNbSU,
                                           const int                             theNbSV,
                                           const bool                            theEnlargeZone,
                                           NCollection_Array1<double>&           theUPars,
                                           NCollection_Array1<double>&           theVPars);

  Standard_EXPORT static double ComputeDeflection(const occ::handle<Adaptor3d_Surface>& theSurf,
                                                  const NCollection_Array1<double>&     theUPars,
                                                  const NCollection_Array1<double>&     theVPars);

  Standard_EXPORT static void FillArrayOfPointNormal(const occ::handle<Adaptor3d_Surface>& theSurf,
                                                     const NCollection_Array1<double>&     theUPars,
                                                     const NCollection_Array1<double>&     theVPars,
                                                     IntPolyh_ArrayOfPointNormal& thePoints);
};
