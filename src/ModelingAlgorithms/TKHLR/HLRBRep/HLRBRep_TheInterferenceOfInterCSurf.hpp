#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Intf_Interference.hpp>
#include <gp_Lin.hpp>
#include <NCollection_Array1.hpp>
class HLRBRep_ThePolygonOfInterCSurf;
class HLRBRep_ThePolygonToolOfInterCSurf;
class HLRBRep_ThePolyhedronOfInterCSurf;
class HLRBRep_ThePolyhedronToolOfInterCSurf;
class gp_Lin;
class Bnd_BoundSortBox;
class gp_Pnt;
class gp_XYZ;

class HLRBRep_TheInterferenceOfInterCSurf : public Intf_Interference
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_TheInterferenceOfInterCSurf();

  Standard_EXPORT HLRBRep_TheInterferenceOfInterCSurf(
    const HLRBRep_ThePolygonOfInterCSurf&    thePolyg,
    const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh);

  Standard_EXPORT HLRBRep_TheInterferenceOfInterCSurf(
    const gp_Lin&                            theLin,
    const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh);

  Standard_EXPORT HLRBRep_TheInterferenceOfInterCSurf(
    const NCollection_Array1<gp_Lin>&        theLins,
    const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh);

  Standard_EXPORT void Perform(const HLRBRep_ThePolygonOfInterCSurf&    thePolyg,
                               const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh);

  Standard_EXPORT void Perform(const gp_Lin&                            theLin,
                               const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh);

  Standard_EXPORT void Perform(const NCollection_Array1<gp_Lin>&        theLins,
                               const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh);

  Standard_EXPORT HLRBRep_TheInterferenceOfInterCSurf(
    const HLRBRep_ThePolygonOfInterCSurf&    thePolyg,
    const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh,
    Bnd_BoundSortBox&                        theBoundSB);

  Standard_EXPORT HLRBRep_TheInterferenceOfInterCSurf(
    const gp_Lin&                            theLin,
    const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh,
    Bnd_BoundSortBox&                        theBoundSB);

  Standard_EXPORT HLRBRep_TheInterferenceOfInterCSurf(
    const NCollection_Array1<gp_Lin>&        theLins,
    const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh,
    Bnd_BoundSortBox&                        theBoundSB);

  Standard_EXPORT void Perform(const HLRBRep_ThePolygonOfInterCSurf&    thePolyg,
                               const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh,
                               Bnd_BoundSortBox&                        theBoundSB);

  Standard_EXPORT void Perform(const gp_Lin&                            theLin,
                               const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh,
                               Bnd_BoundSortBox&                        theBoundSB);

  Standard_EXPORT void Perform(const NCollection_Array1<gp_Lin>&        theLins,
                               const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh,
                               Bnd_BoundSortBox&                        theBoundSB);

  Standard_EXPORT void Interference(const HLRBRep_ThePolygonOfInterCSurf&    thePolyg,
                                    const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh,
                                    Bnd_BoundSortBox&                        theBoundSB);

  Standard_EXPORT void Interference(const HLRBRep_ThePolygonOfInterCSurf&    thePolyg,
                                    const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh);

private:
  Standard_EXPORT void Intersect(const gp_Pnt&                            BegO,
                                 const gp_Pnt&                            EndO,
                                 const bool                               Infinite,
                                 const int                                TTri,
                                 const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh);

  Standard_EXPORT void Intersect(const gp_Pnt&                            BegO,
                                 const gp_Pnt&                            EndO,
                                 const bool                               Infinite,
                                 const int                                TTri,
                                 const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh,
                                 const gp_XYZ&                            TriNormal,
                                 const double                             TriDp,
                                 const double                             dBegTri,
                                 const double                             dEndTri);

  bool BeginOfClosedPolygon;
  int  iLin;
};
