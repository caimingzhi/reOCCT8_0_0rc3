#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <Approx_Status.hpp>
class AppDef_MultiLine;

//! Example of MultiLine tool corresponding to the tools of the packages AppParCurves and Approx.
//! For Approx, the tool will not add points if the algorithms want some.
class AppDef_MyLineTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the first index of multipoints of the MultiLine.
  Standard_EXPORT static int FirstPoint(const AppDef_MultiLine& ML);

  //! Returns the last index of multipoints of the MultiLine.
  Standard_EXPORT static int LastPoint(const AppDef_MultiLine& ML);

  //! Returns the number of 2d points of a MultiLine.
  Standard_EXPORT static int NbP2d(const AppDef_MultiLine& ML);

  //! Returns the number of 3d points of a MultiLine.
  Standard_EXPORT static int NbP3d(const AppDef_MultiLine& ML);

  //! returns the 3d points of the multipoint <MPointIndex>
  //! when only 3d points exist.
  Standard_EXPORT static void Value(const AppDef_MultiLine&     ML,
                                    const int                   MPointIndex,
                                    NCollection_Array1<gp_Pnt>& tabPt);

  //! returns the 2d points of the multipoint <MPointIndex>
  //! when only 2d points exist.
  Standard_EXPORT static void Value(const AppDef_MultiLine&       ML,
                                    const int                     MPointIndex,
                                    NCollection_Array1<gp_Pnt2d>& tabPt2d);

  //! returns the 3d and 2d points of the multipoint
  //! <MPointIndex>.
  Standard_EXPORT static void Value(const AppDef_MultiLine&       ML,
                                    const int                     MPointIndex,
                                    NCollection_Array1<gp_Pnt>&   tabPt,
                                    NCollection_Array1<gp_Pnt2d>& tabPt2d);

  //! returns the 3d points of the multipoint <MPointIndex>
  //! when only 3d points exist.
  Standard_EXPORT static bool Tangency(const AppDef_MultiLine&     ML,
                                       const int                   MPointIndex,
                                       NCollection_Array1<gp_Vec>& tabV);

  //! returns the 2d tangency points of the multipoint
  //! <MPointIndex> only when 2d points exist.
  Standard_EXPORT static bool Tangency(const AppDef_MultiLine&       ML,
                                       const int                     MPointIndex,
                                       NCollection_Array1<gp_Vec2d>& tabV2d);

  //! returns the 3d and 2d points of the multipoint
  //! <MPointIndex>.
  Standard_EXPORT static bool Tangency(const AppDef_MultiLine&       ML,
                                       const int                     MPointIndex,
                                       NCollection_Array1<gp_Vec>&   tabV,
                                       NCollection_Array1<gp_Vec2d>& tabV2d);

  //! returns the 3d curvatures of the multipoint <MPointIndex>
  //! when only 3d points exist.
  Standard_EXPORT static bool Curvature(const AppDef_MultiLine&     ML,
                                        const int                   MPointIndex,
                                        NCollection_Array1<gp_Vec>& tabV);

  //! returns the 2d curvatures of the multipoint
  //! <MPointIndex> only when 2d points exist.
  Standard_EXPORT static bool Curvature(const AppDef_MultiLine&       ML,
                                        const int                     MPointIndex,
                                        NCollection_Array1<gp_Vec2d>& tabV2d);

  //! returns the 3d and 2d curvatures of the multipoint
  //! <MPointIndex>.
  Standard_EXPORT static bool Curvature(const AppDef_MultiLine&       ML,
                                        const int                     MPointIndex,
                                        NCollection_Array1<gp_Vec>&   tabV,
                                        NCollection_Array1<gp_Vec2d>& tabV2d);

  //! returns NoPointsAdded
  Standard_EXPORT static Approx_Status WhatStatus(const AppDef_MultiLine& ML,
                                                  const int               I1,
                                                  const int               I2);

  //! Is never called in the algorithms.
  //! Nothing is done.
  Standard_EXPORT static AppDef_MultiLine MakeMLBetween(const AppDef_MultiLine& ML,
                                                        const int               I1,
                                                        const int               I2,
                                                        const int               NbPMin);

  //! Is never called in the algorithms.
  //! Nothing is done.
  Standard_EXPORT static bool MakeMLOneMorePoint(const AppDef_MultiLine& ML,
                                                 const int               I1,
                                                 const int               I2,
                                                 const int               indbad,
                                                 AppDef_MultiLine&       OtherLine);
};

