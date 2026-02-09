#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GProp_GProps.hpp>
class BRepGProp_Face;
class BRepGProp_Domain;
class gp_Pln;

class BRepGProp_VinertGK : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  BRepGProp_VinertGK()
      : myErrorReached(0.),
        myAbsolutError(0.)
  {
  }

  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face& theSurface,
                                     const gp_Pnt&   theLocation,
                                     const double    theTolerance = 0.001,
                                     const bool      theCGFlag    = false,
                                     const bool      theIFlag     = false);

  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face& theSurface,
                                     const gp_Pnt&   thePoint,
                                     const gp_Pnt&   theLocation,
                                     const double    theTolerance = 0.001,
                                     const bool      theCGFlag    = false,
                                     const bool      theIFlag     = false);

  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face&   theSurface,
                                     BRepGProp_Domain& theDomain,
                                     const gp_Pnt&     theLocation,
                                     const double      theTolerance = 0.001,
                                     const bool        theCGFlag    = false,
                                     const bool        theIFlag     = false);

  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face&   theSurface,
                                     BRepGProp_Domain& theDomain,
                                     const gp_Pnt&     thePoint,
                                     const gp_Pnt&     theLocation,
                                     const double      theTolerance = 0.001,
                                     const bool        theCGFlag    = false,
                                     const bool        theIFlag     = false);

  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face& theSurface,
                                     const gp_Pln&   thePlane,
                                     const gp_Pnt&   theLocation,
                                     const double    theTolerance = 0.001,
                                     const bool      theCGFlag    = false,
                                     const bool      theIFlag     = false);

  Standard_EXPORT BRepGProp_VinertGK(BRepGProp_Face&   theSurface,
                                     BRepGProp_Domain& theDomain,
                                     const gp_Pln&     thePlane,
                                     const gp_Pnt&     theLocation,
                                     const double      theTolerance = 0.001,
                                     const bool        theCGFlag    = false,
                                     const bool        theIFlag     = false);

  void SetLocation(const gp_Pnt& theLocation) { loc = theLocation; }

  Standard_EXPORT double Perform(BRepGProp_Face& theSurface,
                                 const double    theTolerance = 0.001,
                                 const bool      theCGFlag    = false,
                                 const bool      theIFlag     = false);

  Standard_EXPORT double Perform(BRepGProp_Face& theSurface,
                                 const gp_Pnt&   thePoint,
                                 const double    theTolerance = 0.001,
                                 const bool      theCGFlag    = false,
                                 const bool      theIFlag     = false);

  Standard_EXPORT double Perform(BRepGProp_Face&   theSurface,
                                 BRepGProp_Domain& theDomain,
                                 const double      theTolerance = 0.001,
                                 const bool        theCGFlag    = false,
                                 const bool        theIFlag     = false);

  Standard_EXPORT double Perform(BRepGProp_Face&   theSurface,
                                 BRepGProp_Domain& theDomain,
                                 const gp_Pnt&     thePoint,
                                 const double      theTolerance = 0.001,
                                 const bool        theCGFlag    = false,
                                 const bool        theIFlag     = false);

  Standard_EXPORT double Perform(BRepGProp_Face& theSurface,
                                 const gp_Pln&   thePlane,
                                 const double    theTolerance = 0.001,
                                 const bool      theCGFlag    = false,
                                 const bool      theIFlag     = false);

  Standard_EXPORT double Perform(BRepGProp_Face&   theSurface,
                                 BRepGProp_Domain& theDomain,
                                 const gp_Pln&     thePlane,
                                 const double      theTolerance = 0.001,
                                 const bool        theCGFlag    = false,
                                 const bool        theIFlag     = false);

  double GetErrorReached() const { return myErrorReached; }

  double GetAbsolutError() const;

private:
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
