#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Intf_Interference.hpp>
#include <gp_Lin.hpp>
#include <NCollection_Array1.hpp>
class IntCurveSurface_ThePolygonOfHInter;
class IntCurveSurface_ThePolygonToolOfHInter;
class IntCurveSurface_ThePolyhedronOfHInter;
class IntCurveSurface_ThePolyhedronToolOfHInter;
class gp_Lin;
class Bnd_BoundSortBox;
class gp_Pnt;
class gp_XYZ;

class IntCurveSurface_TheInterferenceOfHInter : public Intf_Interference
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurveSurface_TheInterferenceOfHInter();

  Standard_EXPORT IntCurveSurface_TheInterferenceOfHInter(
    const IntCurveSurface_ThePolygonOfHInter&    thePolyg,
    const IntCurveSurface_ThePolyhedronOfHInter& thePolyh);

  Standard_EXPORT IntCurveSurface_TheInterferenceOfHInter(
    const gp_Lin&                                theLin,
    const IntCurveSurface_ThePolyhedronOfHInter& thePolyh);

  Standard_EXPORT IntCurveSurface_TheInterferenceOfHInter(
    const NCollection_Array1<gp_Lin>&            theLins,
    const IntCurveSurface_ThePolyhedronOfHInter& thePolyh);

  Standard_EXPORT void Perform(const IntCurveSurface_ThePolygonOfHInter&    thePolyg,
                               const IntCurveSurface_ThePolyhedronOfHInter& thePolyh);

  Standard_EXPORT void Perform(const gp_Lin&                                theLin,
                               const IntCurveSurface_ThePolyhedronOfHInter& thePolyh);

  Standard_EXPORT void Perform(const NCollection_Array1<gp_Lin>&            theLins,
                               const IntCurveSurface_ThePolyhedronOfHInter& thePolyh);

  Standard_EXPORT IntCurveSurface_TheInterferenceOfHInter(
    const IntCurveSurface_ThePolygonOfHInter&    thePolyg,
    const IntCurveSurface_ThePolyhedronOfHInter& thePolyh,
    Bnd_BoundSortBox&                            theBoundSB);

  Standard_EXPORT IntCurveSurface_TheInterferenceOfHInter(
    const gp_Lin&                                theLin,
    const IntCurveSurface_ThePolyhedronOfHInter& thePolyh,
    Bnd_BoundSortBox&                            theBoundSB);

  Standard_EXPORT IntCurveSurface_TheInterferenceOfHInter(
    const NCollection_Array1<gp_Lin>&            theLins,
    const IntCurveSurface_ThePolyhedronOfHInter& thePolyh,
    Bnd_BoundSortBox&                            theBoundSB);

  Standard_EXPORT void Perform(const IntCurveSurface_ThePolygonOfHInter&    thePolyg,
                               const IntCurveSurface_ThePolyhedronOfHInter& thePolyh,
                               Bnd_BoundSortBox&                            theBoundSB);

  Standard_EXPORT void Perform(const gp_Lin&                                theLin,
                               const IntCurveSurface_ThePolyhedronOfHInter& thePolyh,
                               Bnd_BoundSortBox&                            theBoundSB);

  Standard_EXPORT void Perform(const NCollection_Array1<gp_Lin>&            theLins,
                               const IntCurveSurface_ThePolyhedronOfHInter& thePolyh,
                               Bnd_BoundSortBox&                            theBoundSB);

  Standard_EXPORT void Interference(const IntCurveSurface_ThePolygonOfHInter&    thePolyg,
                                    const IntCurveSurface_ThePolyhedronOfHInter& thePolyh,
                                    Bnd_BoundSortBox&                            theBoundSB);

  Standard_EXPORT void Interference(const IntCurveSurface_ThePolygonOfHInter&    thePolyg,
                                    const IntCurveSurface_ThePolyhedronOfHInter& thePolyh);

private:
  Standard_EXPORT void Intersect(const gp_Pnt&                                BegO,
                                 const gp_Pnt&                                EndO,
                                 const bool                                   Infinite,
                                 const int                                    TTri,
                                 const IntCurveSurface_ThePolyhedronOfHInter& thePolyh);

  Standard_EXPORT void Intersect(const gp_Pnt&                                BegO,
                                 const gp_Pnt&                                EndO,
                                 const bool                                   Infinite,
                                 const int                                    TTri,
                                 const IntCurveSurface_ThePolyhedronOfHInter& thePolyh,
                                 const gp_XYZ&                                TriNormal,
                                 const double                                 TriDp,
                                 const double                                 dBegTri,
                                 const double                                 dEndTri);

  bool BeginOfClosedPolygon;
  int  iLin;
};
