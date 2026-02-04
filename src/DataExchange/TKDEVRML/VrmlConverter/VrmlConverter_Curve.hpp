#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
#include <Standard_Integer.hpp>
class Adaptor3d_Curve;
class VrmlConverter_Drawer;

//! Curve - computes the presentation of objects to be
//! seen as curves (the computation will be made
//! with a constant number of points), converts this one
//! into VRML objects and writes (adds) them into
//! anOStream. All requested properties of the
//! representation are specify in aDrawer of Drawer
//! class (VrmlConverter).
//! This kind of the presentation is converted into
//! IndexedLineSet (VRML).
class VrmlConverter_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  //! adds to the OStream the drawing of the curve aCurve.
  //! The aspect is defined by LineAspect in aDrawer.
  Standard_EXPORT static void Add(const Adaptor3d_Curve&                   aCurve,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer,
                                  Standard_OStream&                        anOStream);

  //! adds to the OStream the drawing of the curve aCurve.
  //! The aspect is defined by LineAspect in aDrawer.
  //! The drawing will be limited between the points of parameter
  //! U1 and U2.
  Standard_EXPORT static void Add(const Adaptor3d_Curve&                   aCurve,
                                  const double                             U1,
                                  const double                             U2,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer,
                                  Standard_OStream&                        anOStream);

  //! adds to the OStream the drawing of the curve aCurve.
  //! The aspect is the current aspect.
  //! The drawing will be limited between the points of parameter
  //! U1 and U2. aNbPoints defines number of points on one interval.
  Standard_EXPORT static void Add(const Adaptor3d_Curve& aCurve,
                                  const double           U1,
                                  const double           U2,
                                  Standard_OStream&      anOStream,
                                  const int              aNbPoints);
};

