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

  //! Returns the number of multipoints of the TheMultiLine.
  static int FirstPoint(const BRepApprox_TheMultiLineOfApprox& ML);

  //! Returns the number of multipoints of the TheMultiLine.
  static int LastPoint(const BRepApprox_TheMultiLineOfApprox& ML);

  //! Returns the number of 2d points of a TheMultiLine.
  static int NbP2d(const BRepApprox_TheMultiLineOfApprox& ML);

  //! Returns the number of 3d points of a TheMultiLine.
  static int NbP3d(const BRepApprox_TheMultiLineOfApprox& ML);

  //! returns the 3d points of the multipoint <MPointIndex>
  //! when only 3d points exist.
  static void Value(const BRepApprox_TheMultiLineOfApprox& ML,
                    const int                              MPointIndex,
                    NCollection_Array1<gp_Pnt>&            tabPt);

  //! returns the 2d points of the multipoint <MPointIndex>
  //! when only 2d points exist.
  static void Value(const BRepApprox_TheMultiLineOfApprox& ML,
                    const int                              MPointIndex,
                    NCollection_Array1<gp_Pnt2d>&          tabPt2d);

  //! returns the 3d and 2d points of the multipoint
  //! <MPointIndex>.
  static void Value(const BRepApprox_TheMultiLineOfApprox& ML,
                    const int                              MPointIndex,
                    NCollection_Array1<gp_Pnt>&            tabPt,
                    NCollection_Array1<gp_Pnt2d>&          tabPt2d);

  //! returns the 3d points of the multipoint <MPointIndex>
  //! when only 3d points exist.
  static bool Tangency(const BRepApprox_TheMultiLineOfApprox& ML,
                       const int                              MPointIndex,
                       NCollection_Array1<gp_Vec>&            tabV);

  //! returns the 2d tangency points of the multipoint
  //! <MPointIndex> only when 2d points exist.
  static bool Tangency(const BRepApprox_TheMultiLineOfApprox& ML,
                       const int                              MPointIndex,
                       NCollection_Array1<gp_Vec2d>&          tabV2d);

  //! returns the 3d and 2d points of the multipoint
  //! <MPointIndex>.
  static bool Tangency(const BRepApprox_TheMultiLineOfApprox& ML,
                       const int                              MPointIndex,
                       NCollection_Array1<gp_Vec>&            tabV,
                       NCollection_Array1<gp_Vec2d>&          tabV2d);

  //! returns the 3d curvature of the multipoint <MPointIndex>
  //! when only 3d points exist.
  static bool Curvature(const BRepApprox_TheMultiLineOfApprox& ML,
                        const int                              MPointIndex,
                        NCollection_Array1<gp_Vec>&            tabV);

  //! returns the 2d curvature points of the multipoint
  //! <MPointIndex> only when 2d points exist.
  static bool Curvature(const BRepApprox_TheMultiLineOfApprox& ML,
                        const int                              MPointIndex,
                        NCollection_Array1<gp_Vec2d>&          tabV2d);

  //! returns the 3d and 2d curvature of the multipoint
  //! <MPointIndex>.
  static bool Curvature(const BRepApprox_TheMultiLineOfApprox& ML,
                        const int                              MPointIndex,
                        NCollection_Array1<gp_Vec>&            tabV,
                        NCollection_Array1<gp_Vec2d>&          tabV2d);

  //! Is called if WhatStatus returned "PointsAdded".
  static BRepApprox_TheMultiLineOfApprox MakeMLBetween(const BRepApprox_TheMultiLineOfApprox& ML,
                                                       const int                              I1,
                                                       const int                              I2,
                                                       const int NbPMin);

  //! Is called when the Bezier curve contains a loop
  static bool MakeMLOneMorePoint(const BRepApprox_TheMultiLineOfApprox& ML,
                                 const int                              I1,
                                 const int                              I2,
                                 const int                              indbad,
                                 BRepApprox_TheMultiLineOfApprox&       OtherLine);

  static Approx_Status WhatStatus(const BRepApprox_TheMultiLineOfApprox& ML,
                                  const int                              I1,
                                  const int                              I2);

  //! Dump of the current multi-line.
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

