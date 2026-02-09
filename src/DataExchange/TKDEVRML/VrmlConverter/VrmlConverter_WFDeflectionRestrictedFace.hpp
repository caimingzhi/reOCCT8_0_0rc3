#pragma once

#include <BRepAdaptor_Surface.hpp>
#include <Standard_OStream.hpp>

class VrmlConverter_Drawer;

class VrmlConverter_WFDeflectionRestrictedFace
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(Standard_OStream&                        anOStream,
                                  const occ::handle<BRepAdaptor_Surface>&  aFace,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);

  Standard_EXPORT static void AddUIso(Standard_OStream&                        anOStream,
                                      const occ::handle<BRepAdaptor_Surface>&  aFace,
                                      const occ::handle<VrmlConverter_Drawer>& aDrawer);

  Standard_EXPORT static void AddVIso(Standard_OStream&                        anOStream,
                                      const occ::handle<BRepAdaptor_Surface>&  aFace,
                                      const occ::handle<VrmlConverter_Drawer>& aDrawer);

  Standard_EXPORT static void Add(Standard_OStream&                        anOStream,
                                  const occ::handle<BRepAdaptor_Surface>&  aFace,
                                  const bool                               DrawUIso,
                                  const bool                               DrawVIso,
                                  const double                             Deflection,
                                  const int                                NBUiso,
                                  const int                                NBViso,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);
};
