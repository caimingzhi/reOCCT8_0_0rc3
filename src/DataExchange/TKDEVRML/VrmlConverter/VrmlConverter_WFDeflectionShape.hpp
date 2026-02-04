#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
class TopoDS_Shape;
class VrmlConverter_Drawer;

//! WFDeflectionShape - computes the wireframe
//! presentation of compound set of faces, edges and
//! vertices by displaying a given number of U and/or
//! V isoparametric curves, converts this one into VRML
//! objects and writes (adds) them into anOStream.
//! All requested properties of the representation are
//! specify in aDrawer.
//! This kind of the presentation is converted into
//! IndexedLineSet and PointSet (VRML).
class VrmlConverter_WFDeflectionShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(Standard_OStream&                        anOStream,
                                  const TopoDS_Shape&                      aShape,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);
};

