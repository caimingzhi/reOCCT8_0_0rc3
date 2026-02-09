#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
class TopoDS_Shape;
class VrmlConverter_Drawer;

class VrmlConverter_WFShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(Standard_OStream&                        anOStream,
                                  const TopoDS_Shape&                      aShape,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);
};
