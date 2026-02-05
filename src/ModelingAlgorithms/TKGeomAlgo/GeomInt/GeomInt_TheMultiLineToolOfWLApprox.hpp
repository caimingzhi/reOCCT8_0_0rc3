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

  //! Returns the number of multipoints of the TheMultiLine.
  static int FirstPoint(const GeomInt_TheMultiLineOfWLApprox& ML);

  //! Returns the number of multipoints of the TheMultiLine.
  static int LastPoint(const GeomInt_TheMultiLineOfWLApprox& ML);

  //! Returns the number of 2d points of a TheMultiLine.
  static int NbP2d(const GeomInt_TheMultiLineOfWLApprox& ML);

  //! Returns the number of 3d points of a TheMultiLine.
  static int NbP3d(const GeomInt_TheMultiLineOfWLApprox& ML);

  //! returns the 3d points of the multipoint <MPointIndex>
  //! when only 3d points exist.
  static void Value(const GeomInt_TheMultiLineOfWLApprox& ML,
                    const int                             MPointIndex,
                    NCollection_Array1<gp_Pnt>&           tabPt);

  //! returns the 2d points of the multipoint <MPointIndex>
  //! when only 2d points exist.
  static void Value(const GeomInt_TheMultiLineOfWLApprox& ML,
                    const int                             MPointIndex,
                    NCollection_Array1<gp_Pnt2d>&         tabPt2d);

  //! returns the 3d and 2d points of the multipoint
  //! <MPointIndex>.
  static void Value(const GeomInt_TheMultiLineOfWLApprox& ML,
                    const int                             MPointIndex,
                    NCollection_Array1<gp_Pnt>&           tabPt,
                    NCollection_Array1<gp_Pnt2d>&         tabPt2d);

  //! returns the 3d points of the multipoint <MPointIndex>
  //! when only 3d points exist.
  static bool Tangency(const GeomInt_TheMultiLineOfWLApprox& ML,
                       const int                             MPointIndex,
                       NCollection_Array1<gp_Vec>&           tabV);

  //! returns the 2d tangency points of the multipoint
  //! <MPointIndex> only when 2d points exist.
  static bool Tangency(const GeomInt_TheMultiLineOfWLApprox& ML,
                       const int                             MPointIndex,
                       NCollection_Array1<gp_Vec2d>&         tabV2d);

  //! returns the 3d and 2d points of the multipoint
  //! <MPointIndex>.
  static bool Tangency(const GeomInt_TheMultiLineOfWLApprox& ML,
                       const int                             MPointIndex,
                       NCollection_Array1<gp_Vec>&           tabV,
                       NCollection_Array1<gp_Vec2d>&         tabV2d);

  //! returns the 3d curvature of the multipoint <MPointIndex>
  //! when only 3d points exist.
  static bool Curvature(const GeomInt_TheMultiLineOfWLApprox& ML,
                        const int                             MPointIndex,
                        NCollection_Array1<gp_Vec>&           tabV);

  //! returns the 2d curvature points of the multipoint
  //! <MPointIndex> only when 2d points exist.
  static bool Curvature(const GeomInt_TheMultiLineOfWLApprox& ML,
                        const int                             MPointIndex,
                        NCollection_Array1<gp_Vec2d>&         tabV2d);

  //! returns the 3d and 2d curvature of the multipoint
  //! <MPointIndex>.
  static bool Curvature(const GeomInt_TheMultiLineOfWLApprox& ML,
                        const int                             MPointIndex,
                        NCollection_Array1<gp_Vec>&           tabV,
                        NCollection_Array1<gp_Vec2d>&         tabV2d);

  //! Is called if WhatStatus returned "PointsAdded".
  static GeomInt_TheMultiLineOfWLApprox MakeMLBetween(const GeomInt_TheMultiLineOfWLApprox& ML,
                                                      const int                             I1,
                                                      const int                             I2,
                                                      const int                             NbPMin);

  //! Is called when the Bezier curve contains a loop
  static bool MakeMLOneMorePoint(const GeomInt_TheMultiLineOfWLApprox& ML,
                                 const int                             I1,
                                 const int                             I2,
                                 const int                             indbad,
                                 GeomInt_TheMultiLineOfWLApprox&       OtherLine);

  static Approx_Status WhatStatus(const GeomInt_TheMultiLineOfWLApprox& ML,
                                  const int                             I1,
                                  const int                             I2);

  //! Dump of the current multi-line.
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
