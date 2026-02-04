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

//! DeflectionCurve - computes the presentation of
//! objects to be seen as curves, converts this one into
//! VRML objects and writes (adds) into
//! anOStream. All requested properties of the
//! representation are specify in aDrawer.
//! This kind of the presentation
//! is converted into IndexedLineSet (VRML).
//! The computation will be made according to a maximal
//! chordial deviation.
class VrmlConverter_DeflectionCurve
{
public:
  DEFINE_STANDARD_ALLOC

  //! adds to the OStream the drawing of the curve aCurve with
  //! respect to the maximal chordial deviation defined
  //! by the drawer aDrawer.
  //! The aspect is defined by LineAspect in aDrawer.
  Standard_EXPORT static void Add(Standard_OStream&                        anOStream,
                                  Adaptor3d_Curve&                         aCurve,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);

  //! adds to the OStream the drawing of the curve aCurve with
  //! respect to the maximal chordial deviation defined
  //! by the drawer aDrawer.
  //! The aspect is defined by LineAspect in aDrawer.
  //! The drawing will be limited between the points of parameter
  //! U1 and U2.
  Standard_EXPORT static void Add(Standard_OStream&                        anOStream,
                                  Adaptor3d_Curve&                         aCurve,
                                  const double                             U1,
                                  const double                             U2,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);

  //! adds to the OStream the drawing of the curve aCurve with
  //! respect to the maximal chordial deviation aDeflection.
  //! The aspect is the current aspect
  Standard_EXPORT static void Add(Standard_OStream& anOStream,
                                  Adaptor3d_Curve&  aCurve,
                                  const double      aDeflection,
                                  const double      aLimit);

  //! adds to the OStream the drawing of the curve aCurve with
  //! respect to the maximal chordial deviation aDeflection.
  //! The aspect is the current aspect
  Standard_EXPORT static void Add(Standard_OStream&                        anOStream,
                                  Adaptor3d_Curve&                         aCurve,
                                  const double                             aDeflection,
                                  const occ::handle<VrmlConverter_Drawer>& aDrawer);

  //! adds to the OStream the drawing of the curve aCurve with
  //! respect to the maximal chordial deviation aDeflection.
  //! The aspect is the current aspect
  //! The drawing will be limited between the points of parameter
  //! U1 and U2.
  Standard_EXPORT static void Add(Standard_OStream& anOStream,
                                  Adaptor3d_Curve&  aCurve,
                                  const double      U1,
                                  const double      U2,
                                  const double      aDeflection);

  //! adds to the OStream the drawing of the curve aCurve with
  //! the array of parameters to retrieve points on curve.
  Standard_EXPORT static void Add(Standard_OStream&                               anOStream,
                                  const Adaptor3d_Curve&                          aCurve,
                                  const occ::handle<NCollection_HArray1<double>>& aParams,
                                  const int                                       aNbNodes,
                                  const occ::handle<VrmlConverter_Drawer>&        aDrawer);
};

