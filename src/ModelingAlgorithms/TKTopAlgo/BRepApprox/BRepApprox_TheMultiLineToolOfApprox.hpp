#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Boolean.hpp>
class BRepApprox_TheMultiLineOfApprox;
class ApproxInt_SvSurfaces;

class BRepApprox_TheMultiLineToolOfApprox
{
public:
  DEFINE_STANDARD_ALLOC

  static int FirstPoint(const BRepApprox_TheMultiLineOfApprox& ML);

  static int LastPoint(const BRepApprox_TheMultiLineOfApprox& ML);

  static int NbP2d(const BRepApprox_TheMultiLineOfApprox& ML);

  static int NbP3d(const BRepApprox_TheMultiLineOfApprox& ML);

  static void Value(const BRepApprox_TheMultiLineOfApprox& ML,
                    const int                              MPointIndex,
                    NCollection_Array1<gp_Pnt>&            tabPt);

  static void Value(const BRepApprox_TheMultiLineOfApprox& ML,
                    const int                              MPointIndex,
                    NCollection_Array1<gp_Pnt2d>&          tabPt2d);

  static void Value(const BRepApprox_TheMultiLineOfApprox& ML,
                    const int                              MPointIndex,
                    NCollection_Array1<gp_Pnt>&            tabPt,
                    NCollection_Array1<gp_Pnt2d>&          tabPt2d);

  static bool Tangency(const BRepApprox_TheMultiLineOfApprox& ML,
                       const int                              MPointIndex,
                       NCollection_Array1<gp_Vec>&            tabV);

  static bool Tangency(const BRepApprox_TheMultiLineOfApprox& ML,
                       const int                              MPointIndex,
                       NCollection_Array1<gp_Vec2d>&          tabV2d);

  static bool Tangency(const BRepApprox_TheMultiLineOfApprox& ML,
                       const int                              MPointIndex,
                       NCollection_Array1<gp_Vec>&            tabV,
                       NCollection_Array1<gp_Vec2d>&          tabV2d);

  static bool Curvature(const BRepApprox_TheMultiLineOfApprox& ML,
                        const int                              MPointIndex,
                        NCollection_Array1<gp_Vec>&            tabV);

  static bool Curvature(const BRepApprox_TheMultiLineOfApprox& ML,
                        const int                              MPointIndex,
                        NCollection_Array1<gp_Vec2d>&          tabV2d);

  static bool Curvature(const BRepApprox_TheMultiLineOfApprox& ML,
                        const int                              MPointIndex,
                        NCollection_Array1<gp_Vec>&            tabV,
                        NCollection_Array1<gp_Vec2d>&          tabV2d);

  static BRepApprox_TheMultiLineOfApprox MakeMLBetween(const BRepApprox_TheMultiLineOfApprox& ML,
                                                       const int                              I1,
                                                       const int                              I2,
                                                       const int NbPMin);

  static bool MakeMLOneMorePoint(const BRepApprox_TheMultiLineOfApprox& ML,
                                 const int                              I1,
                                 const int                              I2,
                                 const int                              indbad,
                                 BRepApprox_TheMultiLineOfApprox&       OtherLine);

  static Approx_Status WhatStatus(const BRepApprox_TheMultiLineOfApprox& ML,
                                  const int                              I1,
                                  const int                              I2);

  static void Dump(const BRepApprox_TheMultiLineOfApprox& ML);
};

#define TheMultiLine BRepApprox_TheMultiLineOfApprox
#define TheMultiLine_hxx <BRepApprox_TheMultiLineOfApprox.hpp>
#define TheMultiMPoint ApproxInt_SvSurfaces
#define TheMultiMPoint_hxx <ApproxInt_SvSurfaces.hpp>
#define ApproxInt_MultiLineTool BRepApprox_TheMultiLineToolOfApprox
#define ApproxInt_MultiLineTool_hxx <BRepApprox_TheMultiLineToolOfApprox.hpp>

#include <ApproxInt_MultiLineTool.hpp>

#undef TheMultiLine
#undef TheMultiLine_hxx
#undef TheMultiMPoint
#undef TheMultiMPoint_hxx
#undef ApproxInt_MultiLineTool
#undef ApproxInt_MultiLineTool_hxx
