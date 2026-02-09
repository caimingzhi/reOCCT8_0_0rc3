#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Boolean.hpp>
class GeomInt_TheMultiLineOfWLApprox;
class ApproxInt_SvSurfaces;

class GeomInt_TheMultiLineToolOfWLApprox
{
public:
  DEFINE_STANDARD_ALLOC

  static int FirstPoint(const GeomInt_TheMultiLineOfWLApprox& ML);

  static int LastPoint(const GeomInt_TheMultiLineOfWLApprox& ML);

  static int NbP2d(const GeomInt_TheMultiLineOfWLApprox& ML);

  static int NbP3d(const GeomInt_TheMultiLineOfWLApprox& ML);

  static void Value(const GeomInt_TheMultiLineOfWLApprox& ML,
                    const int                             MPointIndex,
                    NCollection_Array1<gp_Pnt>&           tabPt);

  static void Value(const GeomInt_TheMultiLineOfWLApprox& ML,
                    const int                             MPointIndex,
                    NCollection_Array1<gp_Pnt2d>&         tabPt2d);

  static void Value(const GeomInt_TheMultiLineOfWLApprox& ML,
                    const int                             MPointIndex,
                    NCollection_Array1<gp_Pnt>&           tabPt,
                    NCollection_Array1<gp_Pnt2d>&         tabPt2d);

  static bool Tangency(const GeomInt_TheMultiLineOfWLApprox& ML,
                       const int                             MPointIndex,
                       NCollection_Array1<gp_Vec>&           tabV);

  static bool Tangency(const GeomInt_TheMultiLineOfWLApprox& ML,
                       const int                             MPointIndex,
                       NCollection_Array1<gp_Vec2d>&         tabV2d);

  static bool Tangency(const GeomInt_TheMultiLineOfWLApprox& ML,
                       const int                             MPointIndex,
                       NCollection_Array1<gp_Vec>&           tabV,
                       NCollection_Array1<gp_Vec2d>&         tabV2d);

  static bool Curvature(const GeomInt_TheMultiLineOfWLApprox& ML,
                        const int                             MPointIndex,
                        NCollection_Array1<gp_Vec>&           tabV);

  static bool Curvature(const GeomInt_TheMultiLineOfWLApprox& ML,
                        const int                             MPointIndex,
                        NCollection_Array1<gp_Vec2d>&         tabV2d);

  static bool Curvature(const GeomInt_TheMultiLineOfWLApprox& ML,
                        const int                             MPointIndex,
                        NCollection_Array1<gp_Vec>&           tabV,
                        NCollection_Array1<gp_Vec2d>&         tabV2d);

  static GeomInt_TheMultiLineOfWLApprox MakeMLBetween(const GeomInt_TheMultiLineOfWLApprox& ML,
                                                      const int                             I1,
                                                      const int                             I2,
                                                      const int                             NbPMin);

  static bool MakeMLOneMorePoint(const GeomInt_TheMultiLineOfWLApprox& ML,
                                 const int                             I1,
                                 const int                             I2,
                                 const int                             indbad,
                                 GeomInt_TheMultiLineOfWLApprox&       OtherLine);

  static Approx_Status WhatStatus(const GeomInt_TheMultiLineOfWLApprox& ML,
                                  const int                             I1,
                                  const int                             I2);

  static void Dump(const GeomInt_TheMultiLineOfWLApprox& ML);
};

#define TheMultiLine GeomInt_TheMultiLineOfWLApprox
#define TheMultiLine_hxx <GeomInt_TheMultiLineOfWLApprox.hpp>
#define TheMultiMPoint ApproxInt_SvSurfaces
#define TheMultiMPoint_hxx <ApproxInt_SvSurfaces.hpp>
#define ApproxInt_MultiLineTool GeomInt_TheMultiLineToolOfWLApprox
#define ApproxInt_MultiLineTool_hxx <GeomInt_TheMultiLineToolOfWLApprox.hpp>

#include <ApproxInt_MultiLineTool.hpp>

#undef TheMultiLine
#undef TheMultiLine_hxx
#undef TheMultiMPoint
#undef TheMultiMPoint_hxx
#undef ApproxInt_MultiLineTool
#undef ApproxInt_MultiLineTool_hxx
