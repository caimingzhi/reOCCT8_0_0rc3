#pragma once


#include <BRepAdaptor_Surface.hpp>
#include <Standard_OStream.hpp>

class VrmlConverter_Drawer;

//! WFRestrictedFace - computes the wireframe
//! presentation of faces with restrictions by
//! displaying a given number of U and/or V
//! isoparametric curves, converts this one into VRML
//! objects and writes (adds) into anOStream.
//! All requested properties of the representation
//! are specify in aDrawer.
//! This kind of the presentation is converted into
//! IndexedLineSet (VRML).
class VrmlConverter_WFRestrictedFace
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
                                  const int                                NBUiso,
                                  const int                                NBViso,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);
};

