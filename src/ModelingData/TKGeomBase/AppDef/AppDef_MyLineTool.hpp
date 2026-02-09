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

class AppDef_MyLineTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static int FirstPoint(const AppDef_MultiLine& ML);

  Standard_EXPORT static int LastPoint(const AppDef_MultiLine& ML);

  Standard_EXPORT static int NbP2d(const AppDef_MultiLine& ML);

  Standard_EXPORT static int NbP3d(const AppDef_MultiLine& ML);

  Standard_EXPORT static void Value(const AppDef_MultiLine&     ML,
                                    const int                   MPointIndex,
                                    NCollection_Array1<gp_Pnt>& tabPt);

  Standard_EXPORT static void Value(const AppDef_MultiLine&       ML,
                                    const int                     MPointIndex,
                                    NCollection_Array1<gp_Pnt2d>& tabPt2d);

  Standard_EXPORT static void Value(const AppDef_MultiLine&       ML,
                                    const int                     MPointIndex,
                                    NCollection_Array1<gp_Pnt>&   tabPt,
                                    NCollection_Array1<gp_Pnt2d>& tabPt2d);

  Standard_EXPORT static bool Tangency(const AppDef_MultiLine&     ML,
                                       const int                   MPointIndex,
                                       NCollection_Array1<gp_Vec>& tabV);

  Standard_EXPORT static bool Tangency(const AppDef_MultiLine&       ML,
                                       const int                     MPointIndex,
                                       NCollection_Array1<gp_Vec2d>& tabV2d);

  Standard_EXPORT static bool Tangency(const AppDef_MultiLine&       ML,
                                       const int                     MPointIndex,
                                       NCollection_Array1<gp_Vec>&   tabV,
                                       NCollection_Array1<gp_Vec2d>& tabV2d);

  Standard_EXPORT static bool Curvature(const AppDef_MultiLine&     ML,
                                        const int                   MPointIndex,
                                        NCollection_Array1<gp_Vec>& tabV);

  Standard_EXPORT static bool Curvature(const AppDef_MultiLine&       ML,
                                        const int                     MPointIndex,
                                        NCollection_Array1<gp_Vec2d>& tabV2d);

  Standard_EXPORT static bool Curvature(const AppDef_MultiLine&       ML,
                                        const int                     MPointIndex,
                                        NCollection_Array1<gp_Vec>&   tabV,
                                        NCollection_Array1<gp_Vec2d>& tabV2d);

  Standard_EXPORT static Approx_Status WhatStatus(const AppDef_MultiLine& ML,
                                                  const int               I1,
                                                  const int               I2);

  Standard_EXPORT static AppDef_MultiLine MakeMLBetween(const AppDef_MultiLine& ML,
                                                        const int               I1,
                                                        const int               I2,
                                                        const int               NbPMin);

  Standard_EXPORT static bool MakeMLOneMorePoint(const AppDef_MultiLine& ML,
                                                 const int               I1,
                                                 const int               I2,
                                                 const int               indbad,
                                                 AppDef_MultiLine&       OtherLine);
};
