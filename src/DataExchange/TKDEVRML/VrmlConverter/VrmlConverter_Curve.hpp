#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
#include <Standard_Integer.hpp>
class Adaptor3d_Curve;
class VrmlConverter_Drawer;

class VrmlConverter_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const Adaptor3d_Curve&                   aCurve,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer,
                                  Standard_OStream&                        anOStream);

  Standard_EXPORT static void Add(const Adaptor3d_Curve&                   aCurve,
                                  const double                             U1,
                                  const double                             U2,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer,
                                  Standard_OStream&                        anOStream);

  Standard_EXPORT static void Add(const Adaptor3d_Curve& aCurve,
                                  const double           U1,
                                  const double           U2,
                                  Standard_OStream&      anOStream,
                                  const int              aNbPoints);
};
