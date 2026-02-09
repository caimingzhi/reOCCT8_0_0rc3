#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class Adaptor3d_Curve;
class VrmlConverter_Drawer;

class VrmlConverter_DeflectionCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(Standard_OStream&                        anOStream,
                                  Adaptor3d_Curve&                         aCurve,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);

  Standard_EXPORT static void Add(Standard_OStream&                        anOStream,
                                  Adaptor3d_Curve&                         aCurve,
                                  const double                             U1,
                                  const double                             U2,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);

  Standard_EXPORT static void Add(Standard_OStream& anOStream,
                                  Adaptor3d_Curve&  aCurve,
                                  const double      aDeflection,
                                  const double      aLimit);

  Standard_EXPORT static void Add(Standard_OStream&                        anOStream,
                                  Adaptor3d_Curve&                         aCurve,
                                  const double                             aDeflection,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);

  Standard_EXPORT static void Add(Standard_OStream& anOStream,
                                  Adaptor3d_Curve&  aCurve,
                                  const double      U1,
                                  const double      U2,
                                  const double      aDeflection);

  Standard_EXPORT static void Add(Standard_OStream&                               anOStream,
                                  const Adaptor3d_Curve&                          aCurve,
                                  const occ::handle<NCollection_HArray1<double>>& aParams,
                                  const int                                       aNbNodes,
                                  const occ::handle<VrmlConverter_Drawer>&        aDrawer);
};
