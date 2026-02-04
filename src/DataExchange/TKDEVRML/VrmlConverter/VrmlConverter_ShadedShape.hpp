#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
#include <gp_Dir.hpp>
#include <NCollection_Array1.hpp>
class TopoDS_Shape;
class VrmlConverter_Drawer;
class TopoDS_Face;
class Poly_Connect;

//! ShadedShape - computes the shading presentation of shapes
//! by triangulation algorithms, converts this one into VRML objects
//! and writes (adds) into anOStream.
//! All requested properties of the representation including
//! the maximal chordial deviation are specify in aDrawer.
//! This kind of the presentation is converted into
//! IndexedFaceSet (VRML).
class VrmlConverter_ShadedShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(Standard_OStream&                        anOStream,
                                  const TopoDS_Shape&                      aShape,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);

  Standard_EXPORT static void ComputeNormal(const TopoDS_Face&          aFace,
                                            Poly_Connect&               pc,
                                            NCollection_Array1<gp_Dir>& Nor);
};

