#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
class TopoDS_Shape;
class VrmlConverter_Drawer;
class VrmlConverter_Projector;

//! HLRShape - computes the presentation of objects
//! with removal of their hidden lines for a specific
//! projector, converts them into VRML objects and
//! writes (adds) them into anOStream. All requested
//! properties of the representation are specify in
//! aDrawer of Drawer class. This kind of the presentation
//! is converted into IndexedLineSet and if they are defined
//! in Projector info:
//! PerspectiveCamera,
//! OrthographicCamera,
//! DirectionLight,
//! PointLight,
//! SpotLight
//! from Vrml package.
class VrmlConverter_HLRShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(Standard_OStream&                           anOStream,
                                  const TopoDS_Shape&                         aShape,
                                  const occ::handle<VrmlConverter_Drawer>&    aDrawer,
                                  const occ::handle<VrmlConverter_Projector>& aProjector);
};
