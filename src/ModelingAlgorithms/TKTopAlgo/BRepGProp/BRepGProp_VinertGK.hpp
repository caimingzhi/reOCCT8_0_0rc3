#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GProp_GProps.hpp>
class BRepGProp_Face;
class BRepGProp_Domain;
class gp_Pln;

//! Computes the global properties of a geometric solid
//! (3D closed region of space) delimited with :
//! -  a point and a surface
//! -  a plane and a surface
//!
//! The surface can be :
//! -  a surface limited with its parametric values U-V,
//! (naturally restricted)
//! -  a surface limited in U-V space with its boundary
//! curves.
//!
//! The surface's requirements to evaluate the global
//! properties are defined in the template FaceTool class from
//! the package GProp.
//!
//! The adaptive 2D algorithm of Gauss-Kronrod integration of
//! double integral is used.
//!
//! The inner integral is computed along U parameter of
//! surface. The integrand function is encapsulated in the
//! support class UFunction that is defined below.
//!
//! The outer integral is computed along T parameter of a
//! bounding curve. The integrand function is encapsulated in
//! the support class TFunction that is defined below.
class BRepGProp_VinertGK : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  BRepGProp_VinertGK()
      : myErrorReached(0.),
        myAbsolutError(0.)
  {
  }

  //! Constructor. Computes the global properties of a region of
  //! 3D space delimited with the naturally restricted surface
  //! and the point VLocation.
  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face& theSurface,
                                     const gp_Pnt&   theLocation,
                                     const double    theTolerance = 0.001,
                                     const bool      theCGFlag    = false,
                                     const bool      theIFlag     = false);

  //! Constructor. Computes the global properties of a region of
  //! 3D space delimited with the naturally restricted surface
  //! and the point VLocation. The inertia is computed with
  //! respect to thePoint.
  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face& theSurface,
                                     const gp_Pnt&   thePoint,
                                     const gp_Pnt&   theLocation,
                                     const double    theTolerance = 0.001,
                                     const bool      theCGFlag    = false,
                                     const bool      theIFlag     = false);

  //! Constructor. Computes the global properties of a region of
  //! 3D space delimited with the surface bounded by the domain
  //! and the point VLocation.
  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face&   theSurface,
                                     BRepGProp_Domain& theDomain,
                                     const gp_Pnt&     theLocation,
                                     const double      theTolerance = 0.001,
                                     const bool        theCGFlag    = false,
                                     const bool        theIFlag     = false);

  //! Constructor. Computes the global properties of a region of
  //! 3D space delimited with the surface bounded by the domain
  //! and the point VLocation. The inertia is computed with
  //! respect to thePoint.
  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face&   theSurface,
                                     BRepGProp_Domain& theDomain,
                                     const gp_Pnt&     thePoint,
                                     const gp_Pnt&     theLocation,
                                     const double      theTolerance = 0.001,
                                     const bool        theCGFlag    = false,
                                     const bool        theIFlag     = false);

  //! Constructor. Computes the global properties of a region of
  //! 3D space delimited with the naturally restricted surface
  //! and the plane.
  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face& theSurface,
                                     const gp_Pln&   thePlane,
                                     const gp_Pnt&   theLocation,
                                     const double    theTolerance = 0.001,
                                     const bool      theCGFlag    = false,
                                     const bool      theIFlag     = false);

  //! Constructor. Computes the global properties of a region of
  //! 3D space delimited with the surface bounded by the domain
  //! and the plane.
  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face&   theSurface,
                                     BRepGProp_Domain& theDomain,
                                     const gp_Pln&     thePlane,
                                     const gp_Pnt&     theLocation,
                                     const double      theTolerance = 0.001,
                                     const bool        theCGFlag    = false,
                                     const bool        theIFlag     = false);

  //! Sets the vertex that delimit 3D closed region of space.
  void SetLocation(const gp_Pnt& theLocation) { loc = theLocation; }

  //! Computes the global properties of a region of 3D space
  //! delimited with the naturally restricted surface and the
  //! point VLocation.
  Standard_EXPORT double Perform(BRepGProp_Face& theSurface,
                                 const double    theTolerance = 0.001,
                                 const bool      theCGFlag    = false,
                                 const bool      theIFlag     = false);

  //! Computes the global properties of a region of 3D space
  //! delimited with the naturally restricted surface and the
  //! point VLocation. The inertia is computed with respect to
  //! thePoint.
  Standard_EXPORT double Perform(BRepGProp_Face& theSurface,
                                 const gp_Pnt&   thePoint,
                                 const double    theTolerance = 0.001,
                                 const bool      theCGFlag    = false,
                                 const bool      theIFlag     = false);

  //! Computes the global properties of a region of 3D space
  //! delimited with the surface bounded by the domain and the
  //! point VLocation.
  Standard_EXPORT double Perform(BRepGProp_Face&   theSurface,
                                 BRepGProp_Domain& theDomain,
                                 const double      theTolerance = 0.001,
                                 const bool        theCGFlag    = false,
                                 const bool        theIFlag     = false);

  //! Computes the global properties of a region of 3D space
  //! delimited with the surface bounded by the domain and the
  //! point VLocation. The inertia is computed with respect to
  //! thePoint.
  Standard_EXPORT double Perform(BRepGProp_Face&   theSurface,
                                 BRepGProp_Domain& theDomain,
                                 const gp_Pnt&     thePoint,
                                 const double      theTolerance = 0.001,
                                 const bool        theCGFlag    = false,
                                 const bool        theIFlag     = false);

  //! Computes the global properties of a region of 3D space
  //! delimited with the naturally restricted surface and the
  //! plane.
  Standard_EXPORT double Perform(BRepGProp_Face& theSurface,
                                 const gp_Pln&   thePlane,
                                 const double    theTolerance = 0.001,
                                 const bool      theCGFlag    = false,
                                 const bool      theIFlag     = false);

  //! Computes the global properties of a region of 3D space
  //! delimited with the surface bounded by the domain and the
  //! plane.
  Standard_EXPORT double Perform(BRepGProp_Face&   theSurface,
                                 BRepGProp_Domain& theDomain,
                                 const gp_Pln&     thePlane,
                                 const double      theTolerance = 0.001,
                                 const bool        theCGFlag    = false,
                                 const bool        theIFlag     = false);

  //! Returns the relative reached computation error.
  double GetErrorReached() const { return myErrorReached; }

  //! Returns the absolut reached computation error.
  double GetAbsolutError() const;

private:
  //! Main method for computation of the global properties that
  //! is invoked by each Perform method.
  Standard_EXPORT double PrivatePerform(BRepGProp_Face& theSurface,
                                        void* const     thePtrDomain,
                                        const bool      IsByPoint,
                                        const double*   theCoeffs,
                                        const double    theTolerance,
                                        const bool      theCGFlag,
                                        const bool      theIFlag);

  double myErrorReached;
  double myAbsolutError;
};
