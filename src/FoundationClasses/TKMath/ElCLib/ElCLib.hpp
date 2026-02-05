#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
class gp_Pnt;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Hypr;
class gp_Parab;
class gp_Vec;
class gp_Lin2d;
class gp_Circ2d;
class gp_Elips2d;
class gp_Hypr2d;
class gp_Parab2d;
class gp_Pnt2d;
class gp_Vec2d;
class gp_Ax1;
class gp_Ax2;
class gp_Ax2d;
class gp_Ax22d;
class gp_Dir;
class gp_Dir2d;

//! Provides functions for basic geometric computations on
//! elementary curves such as conics and lines in 2D and 3D space.
//! This includes:
//! -   calculation of a point or derived vector on a 2D or
//! 3D curve where:
//! -   the curve is provided by the gp package, or
//! defined in reference form (as in the gp package),
//! and
//! -   the point is defined by a parameter,
//! -   evaluation of the parameter corresponding to a point
//! on a 2D or 3D curve from gp,
//! -   various elementary computations which allow you to
//! position parameterized values within the period of a curve.
//! Notes:
//! -   ElCLib stands for Elementary Curves Library.
//! -   If the curves provided by the gp package are not
//! explicitly parameterized, they still have an implicit
//! parameterization, analogous to that which they infer
//! for the equivalent Geom or Geom2d curves.
class ElCLib
{
public:
  DEFINE_STANDARD_ALLOC

  //! Return a value in the range <UFirst, ULast> by
  //! adding or removing the period <ULast - UFirst> to
  //! <U>.
  //! ATTENTION!!!
  //!   It is expected but not checked that (ULast > UFirst)
  Standard_EXPORT static double InPeriod(const double U, const double UFirst, const double ULast);

  //! Adjust U1 and U2 in the parametric range UFirst
  //! Ulast of a periodic curve, where ULast -
  //! UFirst is its period. To do this, this function:
  //! -   sets U1 in the range [ UFirst, ULast ] by
  //! adding/removing the period to/from the value U1, then
  //! -   sets U2 in the range [ U1, U1 + period ] by
  //! adding/removing the period to/from the value U2.
  //! Precision is used to test the equalities.
  Standard_EXPORT static void AdjustPeriodic(const double UFirst,
                                             const double ULast,
                                             const double Precision,
                                             double&      U1,
                                             double&      U2);

  //! For elementary curves (lines, circles and conics) from
  //! the gp package, computes the point of parameter U.
  //! The result is either:
  //! -   a gp_Pnt point for a curve in 3D space, or
  //! -   a gp_Pnt2d point for a curve in 2D space.
  static gp_Pnt Value(const double U, const gp_Lin& L);

  static gp_Pnt Value(const double U, const gp_Circ& C);

  static gp_Pnt Value(const double U, const gp_Elips& E);

  static gp_Pnt Value(const double U, const gp_Hypr& H);

  static gp_Pnt Value(const double U, const gp_Parab& Prb);

  //! For elementary curves (lines, circles and conics) from the
  //! gp package, computes:
  //! -   the point P of parameter U, and
  //! -   the first derivative vector V1 at this point.
  //! The results P and V1 are either:
  //! -   a gp_Pnt point and a gp_Vec vector, for a curve in 3D space, or
  //! -   a gp_Pnt2d point and a gp_Vec2d vector, for a curve in 2D space.
  static void D1(const double U, const gp_Lin& L, gp_Pnt& P, gp_Vec& V1);

  static void D1(const double U, const gp_Circ& C, gp_Pnt& P, gp_Vec& V1);

  static void D1(const double U, const gp_Elips& E, gp_Pnt& P, gp_Vec& V1);

  static void D1(const double U, const gp_Hypr& H, gp_Pnt& P, gp_Vec& V1);

  static void D1(const double U, const gp_Parab& Prb, gp_Pnt& P, gp_Vec& V1);

  //! For elementary curves (circles and conics) from the gp
  //! package, computes:
  //! - the point P of parameter U, and
  //! - the first and second derivative vectors V1 and V2 at this point.
  //! The results, P, V1 and V2, are either:
  //! -   a gp_Pnt point and two gp_Vec vectors, for a curve in 3D space, or
  //! -   a gp_Pnt2d point and two gp_Vec2d vectors, for a curve in 2D space.
  static void D2(const double U, const gp_Circ& C, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2);

  static void D2(const double U, const gp_Elips& E, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2);

  static void D2(const double U, const gp_Hypr& H, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2);

  static void D2(const double U, const gp_Parab& Prb, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2);

  //! For elementary curves (circles, ellipses and hyperbolae)
  //! from the gp package, computes:
  //! -   the point P of parameter U, and
  //! -   the first, second and third derivative vectors V1, V2
  //! and V3 at this point.
  //! The results, P, V1, V2 and V3, are either:
  //! -   a gp_Pnt point and three gp_Vec vectors, for a curve in 3D space, or
  //! -   a gp_Pnt2d point and three gp_Vec2d vectors, for a curve in 2D space.
  static void D3(const double U, const gp_Circ& C, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3);

  static void D3(const double U, const gp_Elips& E, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3);

  static void D3(const double U, const gp_Hypr& H, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3);

  //! For elementary curves (lines, circles and conics) from
  //! the gp package, computes the vector corresponding to
  //! the Nth derivative at the point of parameter U. The result is either:
  //! -   a gp_Vec vector for a curve in 3D space, or
  //! -   a gp_Vec2d vector for a curve in 2D space.
  //! In the following functions N is the order of derivation
  //! and should be greater than 0
  static gp_Vec DN(const double U, const gp_Lin& L, const int N);

  static gp_Vec DN(const double U, const gp_Circ& C, const int N);

  static gp_Vec DN(const double U, const gp_Elips& E, const int N);

  static gp_Vec DN(const double U, const gp_Hypr& H, const int N);

  static gp_Vec DN(const double U, const gp_Parab& Prb, const int N);

  static gp_Pnt2d Value(const double U, const gp_Lin2d& L);

  static gp_Pnt2d Value(const double U, const gp_Circ2d& C);

  static gp_Pnt2d Value(const double U, const gp_Elips2d& E);

  static gp_Pnt2d Value(const double U, const gp_Hypr2d& H);

  static gp_Pnt2d Value(const double U, const gp_Parab2d& Prb);

  static void D1(const double U, const gp_Lin2d& L, gp_Pnt2d& P, gp_Vec2d& V1);

  static void D1(const double U, const gp_Circ2d& C, gp_Pnt2d& P, gp_Vec2d& V1);

  static void D1(const double U, const gp_Elips2d& E, gp_Pnt2d& P, gp_Vec2d& V1);

  static void D1(const double U, const gp_Hypr2d& H, gp_Pnt2d& P, gp_Vec2d& V1);

  static void D1(const double U, const gp_Parab2d& Prb, gp_Pnt2d& P, gp_Vec2d& V1);

  static void D2(const double U, const gp_Circ2d& C, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2);

  static void D2(const double U, const gp_Elips2d& E, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2);

  static void D2(const double U, const gp_Hypr2d& H, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2);

  static void D2(const double U, const gp_Parab2d& Prb, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2);

  static void D3(const double     U,
                 const gp_Circ2d& C,
                 gp_Pnt2d&        P,
                 gp_Vec2d&        V1,
                 gp_Vec2d&        V2,
                 gp_Vec2d&        V3);

  static void D3(const double      U,
                 const gp_Elips2d& E,
                 gp_Pnt2d&         P,
                 gp_Vec2d&         V1,
                 gp_Vec2d&         V2,
                 gp_Vec2d&         V3);

  //! In the following functions N is the order of derivation
  //! and should be greater than 0
  static void D3(const double     U,
                 const gp_Hypr2d& H,
                 gp_Pnt2d&        P,
                 gp_Vec2d&        V1,
                 gp_Vec2d&        V2,
                 gp_Vec2d&        V3);

  static gp_Vec2d DN(const double U, const gp_Lin2d& L, const int N);

  static gp_Vec2d DN(const double U, const gp_Circ2d& C, const int N);

  static gp_Vec2d DN(const double U, const gp_Elips2d& E, const int N);

  static gp_Vec2d DN(const double U, const gp_Hypr2d& H, const int N);

  static gp_Vec2d DN(const double U, const gp_Parab2d& Prb, const int N);

  //! Curve evaluation
  //! The following basis functions compute the derivatives on
  //! elementary curves defined by their geometric characteristics.
  //! These functions can be called without constructing a conic
  //! from package gp. They are called by the previous functions.
  //! Example :
  //! A circle is defined by its position and its radius.
  Standard_EXPORT static gp_Pnt LineValue(const double U, const gp_Ax1& Pos);

  Standard_EXPORT static gp_Pnt CircleValue(const double U, const gp_Ax2& Pos, const double Radius);

  Standard_EXPORT static gp_Pnt EllipseValue(const double  U,
                                             const gp_Ax2& Pos,
                                             const double  MajorRadius,
                                             const double  MinorRadius);

  Standard_EXPORT static gp_Pnt HyperbolaValue(const double  U,
                                               const gp_Ax2& Pos,
                                               const double  MajorRadius,
                                               const double  MinorRadius);

  Standard_EXPORT static gp_Pnt ParabolaValue(const double  U,
                                              const gp_Ax2& Pos,
                                              const double  Focal);

  Standard_EXPORT static void LineD1(const double U, const gp_Ax1& Pos, gp_Pnt& P, gp_Vec& V1);

  Standard_EXPORT static void CircleD1(const double  U,
                                       const gp_Ax2& Pos,
                                       const double  Radius,
                                       gp_Pnt&       P,
                                       gp_Vec&       V1);

  Standard_EXPORT static void EllipseD1(const double  U,
                                        const gp_Ax2& Pos,
                                        const double  MajorRadius,
                                        const double  MinorRadius,
                                        gp_Pnt&       P,
                                        gp_Vec&       V1);

  Standard_EXPORT static void HyperbolaD1(const double  U,
                                          const gp_Ax2& Pos,
                                          const double  MajorRadius,
                                          const double  MinorRadius,
                                          gp_Pnt&       P,
                                          gp_Vec&       V1);

  Standard_EXPORT static void ParabolaD1(const double  U,
                                         const gp_Ax2& Pos,
                                         const double  Focal,
                                         gp_Pnt&       P,
                                         gp_Vec&       V1);

  Standard_EXPORT static void CircleD2(const double  U,
                                       const gp_Ax2& Pos,
                                       const double  Radius,
                                       gp_Pnt&       P,
                                       gp_Vec&       V1,
                                       gp_Vec&       V2);

  Standard_EXPORT static void EllipseD2(const double  U,
                                        const gp_Ax2& Pos,
                                        const double  MajorRadius,
                                        const double  MinorRadius,
                                        gp_Pnt&       P,
                                        gp_Vec&       V1,
                                        gp_Vec&       V2);

  Standard_EXPORT static void HyperbolaD2(const double  U,
                                          const gp_Ax2& Pos,
                                          const double  MajorRadius,
                                          const double  MinorRadius,
                                          gp_Pnt&       P,
                                          gp_Vec&       V1,
                                          gp_Vec&       V2);

  Standard_EXPORT static void ParabolaD2(const double  U,
                                         const gp_Ax2& Pos,
                                         const double  Focal,
                                         gp_Pnt&       P,
                                         gp_Vec&       V1,
                                         gp_Vec&       V2);

  Standard_EXPORT static void CircleD3(const double  U,
                                       const gp_Ax2& Pos,
                                       const double  Radius,
                                       gp_Pnt&       P,
                                       gp_Vec&       V1,
                                       gp_Vec&       V2,
                                       gp_Vec&       V3);

  Standard_EXPORT static void EllipseD3(const double  U,
                                        const gp_Ax2& Pos,
                                        const double  MajorRadius,
                                        const double  MinorRadius,
                                        gp_Pnt&       P,
                                        gp_Vec&       V1,
                                        gp_Vec&       V2,
                                        gp_Vec&       V3);

  Standard_EXPORT static void HyperbolaD3(const double  U,
                                          const gp_Ax2& Pos,
                                          const double  MajorRadius,
                                          const double  MinorRadius,
                                          gp_Pnt&       P,
                                          gp_Vec&       V1,
                                          gp_Vec&       V2,
                                          gp_Vec&       V3);

  //! In the following functions N is the order of derivation
  //! and should be greater than 0
  Standard_EXPORT static gp_Vec LineDN(const double U, const gp_Ax1& Pos, const int N);

  Standard_EXPORT static gp_Vec CircleDN(const double  U,
                                         const gp_Ax2& Pos,
                                         const double  Radius,
                                         const int     N);

  Standard_EXPORT static gp_Vec EllipseDN(const double  U,
                                          const gp_Ax2& Pos,
                                          const double  MajorRadius,
                                          const double  MinorRadius,
                                          const int     N);

  Standard_EXPORT static gp_Vec HyperbolaDN(const double  U,
                                            const gp_Ax2& Pos,
                                            const double  MajorRadius,
                                            const double  MinorRadius,
                                            const int     N);

  Standard_EXPORT static gp_Vec ParabolaDN(const double  U,
                                           const gp_Ax2& Pos,
                                           const double  Focal,
                                           const int     N);

  Standard_EXPORT static gp_Pnt2d LineValue(const double U, const gp_Ax2d& Pos);

  Standard_EXPORT static gp_Pnt2d CircleValue(const double    U,
                                              const gp_Ax22d& Pos,
                                              const double    Radius);

  Standard_EXPORT static gp_Pnt2d EllipseValue(const double    U,
                                               const gp_Ax22d& Pos,
                                               const double    MajorRadius,
                                               const double    MinorRadius);

  Standard_EXPORT static gp_Pnt2d HyperbolaValue(const double    U,
                                                 const gp_Ax22d& Pos,
                                                 const double    MajorRadius,
                                                 const double    MinorRadius);

  Standard_EXPORT static gp_Pnt2d ParabolaValue(const double    U,
                                                const gp_Ax22d& Pos,
                                                const double    Focal);

  Standard_EXPORT static void LineD1(const double U, const gp_Ax2d& Pos, gp_Pnt2d& P, gp_Vec2d& V1);

  Standard_EXPORT static void CircleD1(const double    U,
                                       const gp_Ax22d& Pos,
                                       const double    Radius,
                                       gp_Pnt2d&       P,
                                       gp_Vec2d&       V1);

  Standard_EXPORT static void EllipseD1(const double    U,
                                        const gp_Ax22d& Pos,
                                        const double    MajorRadius,
                                        const double    MinorRadius,
                                        gp_Pnt2d&       P,
                                        gp_Vec2d&       V1);

  Standard_EXPORT static void HyperbolaD1(const double    U,
                                          const gp_Ax22d& Pos,
                                          const double    MajorRadius,
                                          const double    MinorRadius,
                                          gp_Pnt2d&       P,
                                          gp_Vec2d&       V1);

  Standard_EXPORT static void ParabolaD1(const double    U,
                                         const gp_Ax22d& Pos,
                                         const double    Focal,
                                         gp_Pnt2d&       P,
                                         gp_Vec2d&       V1);

  Standard_EXPORT static void CircleD2(const double    U,
                                       const gp_Ax22d& Pos,
                                       const double    Radius,
                                       gp_Pnt2d&       P,
                                       gp_Vec2d&       V1,
                                       gp_Vec2d&       V2);

  Standard_EXPORT static void EllipseD2(const double    U,
                                        const gp_Ax22d& Pos,
                                        const double    MajorRadius,
                                        const double    MinorRadius,
                                        gp_Pnt2d&       P,
                                        gp_Vec2d&       V1,
                                        gp_Vec2d&       V2);

  Standard_EXPORT static void HyperbolaD2(const double    U,
                                          const gp_Ax22d& Pos,
                                          const double    MajorRadius,
                                          const double    MinorRadius,
                                          gp_Pnt2d&       P,
                                          gp_Vec2d&       V1,
                                          gp_Vec2d&       V2);

  Standard_EXPORT static void ParabolaD2(const double    U,
                                         const gp_Ax22d& Pos,
                                         const double    Focal,
                                         gp_Pnt2d&       P,
                                         gp_Vec2d&       V1,
                                         gp_Vec2d&       V2);

  Standard_EXPORT static void CircleD3(const double    U,
                                       const gp_Ax22d& Pos,
                                       const double    Radius,
                                       gp_Pnt2d&       P,
                                       gp_Vec2d&       V1,
                                       gp_Vec2d&       V2,
                                       gp_Vec2d&       V3);

  Standard_EXPORT static void EllipseD3(const double    U,
                                        const gp_Ax22d& Pos,
                                        const double    MajorRadius,
                                        const double    MinorRadius,
                                        gp_Pnt2d&       P,
                                        gp_Vec2d&       V1,
                                        gp_Vec2d&       V2,
                                        gp_Vec2d&       V3);

  //! In the following functions N is the order of derivation
  //! and should be greater than 0
  Standard_EXPORT static void HyperbolaD3(const double    U,
                                          const gp_Ax22d& Pos,
                                          const double    MajorRadius,
                                          const double    MinorRadius,
                                          gp_Pnt2d&       P,
                                          gp_Vec2d&       V1,
                                          gp_Vec2d&       V2,
                                          gp_Vec2d&       V3);

  Standard_EXPORT static gp_Vec2d LineDN(const double U, const gp_Ax2d& Pos, const int N);

  Standard_EXPORT static gp_Vec2d CircleDN(const double    U,
                                           const gp_Ax22d& Pos,
                                           const double    Radius,
                                           const int       N);

  Standard_EXPORT static gp_Vec2d EllipseDN(const double    U,
                                            const gp_Ax22d& Pos,
                                            const double    MajorRadius,
                                            const double    MinorRadius,
                                            const int       N);

  Standard_EXPORT static gp_Vec2d HyperbolaDN(const double    U,
                                              const gp_Ax22d& Pos,
                                              const double    MajorRadius,
                                              const double    MinorRadius,
                                              const int       N);

  //! The following functions compute the parametric value corresponding
  //! to a given point on a elementary curve. The point should be on the
  //! curve.
  Standard_EXPORT static gp_Vec2d ParabolaDN(const double    U,
                                             const gp_Ax22d& Pos,
                                             const double    Focal,
                                             const int       N);

  //! Computes the parameter value of the point P on the given curve.
  //! Note: In its local coordinate system, the parametric
  //! equation of the curve is given by the following:
  //! -   for the line L: P(U) = Po + U*Vo
  //! where Po is the origin and Vo the unit vector of its positioning axis.
  //! -   for the circle C: X(U) = Radius*std::cos(U), Y(U) = Radius*Sin(U)
  //! -   for the ellipse E: X(U) = MajorRadius*std::cos(U). Y(U) = MinorRadius*Sin(U)
  //! -   for the hyperbola H: X(U) = MajorRadius*Ch(U), Y(U) = MinorRadius*Sh(U)
  //! -   for the parabola Prb:
  //! X(U) = U**2 / (2*p)
  //! Y(U) = U
  //! where p is the distance between the focus and the directrix.
  //! Warning
  //! The point P must be on the curve. These functions are
  //! not protected, however, and if point P is not on the
  //! curve, an exception may be raised.
  static double Parameter(const gp_Lin& L, const gp_Pnt& P);

  //! parametrization
  //! P (U) = L.Location() + U * L.Direction()
  static double Parameter(const gp_Lin2d& L, const gp_Pnt2d& P);

  static double Parameter(const gp_Circ& C, const gp_Pnt& P);

  //! parametrization
  //! In the local coordinate system of the circle
  //! X (U) = Radius * Cos (U)
  //! Y (U) = Radius * Sin (U)
  static double Parameter(const gp_Circ2d& C, const gp_Pnt2d& P);

  static double Parameter(const gp_Elips& E, const gp_Pnt& P);

  //! parametrization
  //! In the local coordinate system of the Ellipse
  //! X (U) = MajorRadius * Cos (U)
  //! Y (U) = MinorRadius * Sin (U)
  static double Parameter(const gp_Elips2d& E, const gp_Pnt2d& P);

  static double Parameter(const gp_Hypr& H, const gp_Pnt& P);

  //! parametrization
  //! In the local coordinate system of the Hyperbola
  //! X (U) = MajorRadius * Ch (U)
  //! Y (U) = MinorRadius * Sh (U)
  static double Parameter(const gp_Hypr2d& H, const gp_Pnt2d& P);

  static double Parameter(const gp_Parab& Prb, const gp_Pnt& P);

  //! parametrization
  //! In the local coordinate system of the parabola
  //! Y**2 = (2*P) * X where P is the distance between the focus
  //! and the directrix.
  static double Parameter(const gp_Parab2d& Prb, const gp_Pnt2d& P);

  Standard_EXPORT static double LineParameter(const gp_Ax1& Pos, const gp_Pnt& P);

  //! parametrization
  //! P (U) = L.Location() + U * L.Direction()
  Standard_EXPORT static double LineParameter(const gp_Ax2d& Pos, const gp_Pnt2d& P);

  Standard_EXPORT static double CircleParameter(const gp_Ax2& Pos, const gp_Pnt& P);

  //! Pos is the Axis of the Circle
  //! parametrization
  //! In the local coordinate system of the circle
  //! X (U) = Radius * Cos (U)
  //! Y (U) = Radius * Sin (U)
  Standard_EXPORT static double CircleParameter(const gp_Ax22d& Pos, const gp_Pnt2d& P);

  Standard_EXPORT static double EllipseParameter(const gp_Ax2& Pos,
                                                 const double  MajorRadius,
                                                 const double  MinorRadius,
                                                 const gp_Pnt& P);

  //! Pos is the Axis of the Ellipse
  //! parametrization
  //! In the local coordinate system of the Ellipse
  //! X (U) = MajorRadius * Cos (U)
  //! Y (U) = MinorRadius * Sin (U)
  Standard_EXPORT static double EllipseParameter(const gp_Ax22d& Pos,
                                                 const double    MajorRadius,
                                                 const double    MinorRadius,
                                                 const gp_Pnt2d& P);

  Standard_EXPORT static double HyperbolaParameter(const gp_Ax2& Pos,
                                                   const double  MajorRadius,
                                                   const double  MinorRadius,
                                                   const gp_Pnt& P);

  //! Pos is the Axis of the Hyperbola
  //! parametrization
  //! In the local coordinate system of the Hyperbola
  //! X (U) = MajorRadius * Ch (U)
  //! Y (U) = MinorRadius * Sh (U)
  Standard_EXPORT static double HyperbolaParameter(const gp_Ax22d& Pos,
                                                   const double    MajorRadius,
                                                   const double    MinorRadius,
                                                   const gp_Pnt2d& P);

  Standard_EXPORT static double ParabolaParameter(const gp_Ax2& Pos, const gp_Pnt& P);

  //! Pos is the mirror axis of the parabola
  //! parametrization
  //! In the local coordinate system of the parabola
  //! Y**2 = (2*P) * X where P is the distance between the focus
  //! and the directrix.
  //! The following functions build a 3d curve from a
  //! 2d curve at a given position defined with an Ax2.
  Standard_EXPORT static double ParabolaParameter(const gp_Ax22d& Pos, const gp_Pnt2d& P);

  Standard_EXPORT static gp_Pnt To3d(const gp_Ax2& Pos, const gp_Pnt2d& P);

  Standard_EXPORT static gp_Vec To3d(const gp_Ax2& Pos, const gp_Vec2d& V);

  Standard_EXPORT static gp_Dir To3d(const gp_Ax2& Pos, const gp_Dir2d& V);

  Standard_EXPORT static gp_Ax1 To3d(const gp_Ax2& Pos, const gp_Ax2d& A);

  Standard_EXPORT static gp_Ax2 To3d(const gp_Ax2& Pos, const gp_Ax22d& A);

  Standard_EXPORT static gp_Lin To3d(const gp_Ax2& Pos, const gp_Lin2d& L);

  Standard_EXPORT static gp_Circ To3d(const gp_Ax2& Pos, const gp_Circ2d& C);

  Standard_EXPORT static gp_Elips To3d(const gp_Ax2& Pos, const gp_Elips2d& E);

  Standard_EXPORT static gp_Hypr To3d(const gp_Ax2& Pos, const gp_Hypr2d& H);

  //! These functions build a 3D geometric entity from a 2D geometric entity.
  //! The "X Axis" and the "Y Axis" of the global coordinate
  //! system (i.e. 2D space) are lined up respectively with the
  //! "X Axis" and "Y Axis" of the 3D coordinate system, Pos.
  Standard_EXPORT static gp_Parab To3d(const gp_Ax2& Pos, const gp_Parab2d& Prb);
};

#include <gp_Lin.hpp>
#include <gp_Circ.hpp>
#include <gp_Parab.hpp>
#include <gp_Hypr.hpp>
#include <gp_Elips.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Elips2d.hpp>

inline gp_Pnt ElCLib::Value(const double U, const gp_Lin& L)
{

  return ElCLib::LineValue(U, L.Position());
}

inline gp_Pnt ElCLib::Value(const double U, const gp_Circ& C)
{

  return ElCLib::CircleValue(U, C.Position(), C.Radius());
}

inline void ElCLib::D1(const double U, const gp_Lin& L, gp_Pnt& P, gp_Vec& V1)
{

  ElCLib::LineD1(U, L.Position(), P, V1);
}

inline void ElCLib::D1(const double U, const gp_Circ& C, gp_Pnt& P, gp_Vec& V1)
{

  ElCLib::CircleD1(U, C.Position(), C.Radius(), P, V1);
}

inline void ElCLib::D2(const double U, const gp_Circ& C, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2)
{

  ElCLib::CircleD2(U, C.Position(), C.Radius(), P, V1, V2);
}

inline void ElCLib::D3(const double   U,
                       const gp_Circ& C,
                       gp_Pnt&        P,
                       gp_Vec&        V1,
                       gp_Vec&        V2,
                       gp_Vec&        V3)
{

  ElCLib::CircleD3(U, C.Position(), C.Radius(), P, V1, V2, V3);
}

inline gp_Pnt ElCLib::Value(const double U, const gp_Elips& E)
{
  return ElCLib::EllipseValue(U, E.Position(), E.MajorRadius(), E.MinorRadius());
}

inline void ElCLib::D1(const double U, const gp_Elips& E, gp_Pnt& P, gp_Vec& V1)
{

  ElCLib::EllipseD1(U, E.Position(), E.MajorRadius(), E.MinorRadius(), P, V1);
}

inline void ElCLib::D2(const double U, const gp_Elips& E, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2)
{

  ElCLib::EllipseD2(U, E.Position(), E.MajorRadius(), E.MinorRadius(), P, V1, V2);
}

inline void ElCLib::D3(const double    U,
                       const gp_Elips& E,
                       gp_Pnt&         P,
                       gp_Vec&         V1,
                       gp_Vec&         V2,
                       gp_Vec&         V3)
{

  ElCLib::EllipseD3(U, E.Position(), E.MajorRadius(), E.MinorRadius(), P, V1, V2, V3);
}

inline gp_Pnt ElCLib::Value(const double U, const gp_Hypr& H)
{

  return ElCLib::HyperbolaValue(U, H.Position(), H.MajorRadius(), H.MinorRadius());
}

inline void ElCLib::D1(const double U, const gp_Hypr& H, gp_Pnt& P, gp_Vec& V1)
{

  ElCLib::HyperbolaD1(U, H.Position(), H.MajorRadius(), H.MinorRadius(), P, V1);
}

inline void ElCLib::D2(const double U, const gp_Hypr& H, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2)
{

  ElCLib::HyperbolaD2(U, H.Position(), H.MajorRadius(), H.MinorRadius(), P, V1, V2);
}

inline void ElCLib::D3(const double   U,
                       const gp_Hypr& H,
                       gp_Pnt&        P,
                       gp_Vec&        V1,
                       gp_Vec&        V2,
                       gp_Vec&        V3)
{

  ElCLib::HyperbolaD3(U, H.Position(), H.MajorRadius(), H.MinorRadius(), P, V1, V2, V3);
}

inline gp_Pnt ElCLib::Value(const double U, const gp_Parab& Prb)
{

  return ElCLib::ParabolaValue(U, Prb.Position(), Prb.Focal());
}

inline void ElCLib::D1(const double U, const gp_Parab& Prb, gp_Pnt& P, gp_Vec& V1)
{

  ElCLib::ParabolaD1(U, Prb.Position(), Prb.Focal(), P, V1);
}

inline void ElCLib::D2(const double U, const gp_Parab& Prb, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2)
{

  ElCLib::ParabolaD2(U, Prb.Position(), Prb.Focal(), P, V1, V2);
}

inline gp_Pnt2d ElCLib::Value(const double U, const gp_Lin2d& L)
{

  return ElCLib::LineValue(U, L.Position());
}

inline gp_Pnt2d ElCLib::Value(const double U, const gp_Circ2d& C)
{

  return ElCLib::CircleValue(U, C.Axis(), C.Radius());
}

inline gp_Pnt2d ElCLib::Value(const double U, const gp_Elips2d& E)
{

  return ElCLib::EllipseValue(U, E.Axis(), E.MajorRadius(), E.MinorRadius());
}

inline gp_Pnt2d ElCLib::Value(const double U, const gp_Hypr2d& H)
{

  return ElCLib::HyperbolaValue(U, H.Axis(), H.MajorRadius(), H.MinorRadius());
}

inline gp_Pnt2d ElCLib::Value(const double U, const gp_Parab2d& Prb)
{

  return ElCLib::ParabolaValue(U, Prb.Axis(), Prb.Focal());
}

inline void ElCLib::D1(const double U, const gp_Lin2d& L, gp_Pnt2d& P, gp_Vec2d& V1)
{

  ElCLib::LineD1(U, L.Position(), P, V1);
}

inline void ElCLib::D1(const double U, const gp_Circ2d& C, gp_Pnt2d& P, gp_Vec2d& V1)
{

  ElCLib::CircleD1(U, C.Axis(), C.Radius(), P, V1);
}

inline void ElCLib::D1(const double U, const gp_Elips2d& E, gp_Pnt2d& P, gp_Vec2d& V1)
{

  ElCLib::EllipseD1(U, E.Axis(), E.MajorRadius(), E.MinorRadius(), P, V1);
}

inline void ElCLib::D1(const double U, const gp_Hypr2d& H, gp_Pnt2d& P, gp_Vec2d& V1)
{
  ElCLib::HyperbolaD1(U, H.Axis(), H.MajorRadius(), H.MinorRadius(), P, V1);
}

inline void ElCLib::D1(const double U, const gp_Parab2d& Prb, gp_Pnt2d& P, gp_Vec2d& V1)
{

  ElCLib::ParabolaD1(U, Prb.Axis(), Prb.Focal(), P, V1);
}

inline void ElCLib::D2(const double U, const gp_Circ2d& C, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2)
{

  ElCLib::CircleD2(U, C.Axis(), C.Radius(), P, V1, V2);
}

inline void ElCLib::D2(const double U, const gp_Elips2d& E, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2)
{

  ElCLib::EllipseD2(U, E.Axis(), E.MajorRadius(), E.MinorRadius(), P, V1, V2);
}

inline void ElCLib::D2(const double U, const gp_Hypr2d& H, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2)
{

  ElCLib::HyperbolaD2(U, H.Axis(), H.MajorRadius(), H.MinorRadius(), P, V1, V2);
}

inline void ElCLib::D2(const double      U,
                       const gp_Parab2d& Prb,
                       gp_Pnt2d&         P,
                       gp_Vec2d&         V1,
                       gp_Vec2d&         V2)
{

  ElCLib::ParabolaD2(U, Prb.Axis(), Prb.Focal(), P, V1, V2);
}

inline void ElCLib::D3(const double     U,
                       const gp_Circ2d& C,
                       gp_Pnt2d&        P,
                       gp_Vec2d&        V1,
                       gp_Vec2d&        V2,
                       gp_Vec2d&        V3)
{

  ElCLib::CircleD3(U, C.Axis(), C.Radius(), P, V1, V2, V3);
}

inline void ElCLib::D3(const double      U,
                       const gp_Elips2d& E,
                       gp_Pnt2d&         P,
                       gp_Vec2d&         V1,
                       gp_Vec2d&         V2,
                       gp_Vec2d&         V3)
{

  ElCLib::EllipseD3(U, E.Axis(), E.MajorRadius(), E.MinorRadius(), P, V1, V2, V3);
}

inline void ElCLib::D3(const double     U,
                       const gp_Hypr2d& H,
                       gp_Pnt2d&        P,
                       gp_Vec2d&        V1,
                       gp_Vec2d&        V2,
                       gp_Vec2d&        V3)
{

  ElCLib::HyperbolaD3(U, H.Axis(), H.MajorRadius(), H.MinorRadius(), P, V1, V2, V3);
}

inline gp_Vec ElCLib::DN(const double U, const gp_Lin& L, const int N)
{

  return ElCLib::LineDN(U, L.Position(), N);
}

inline gp_Vec ElCLib::DN(const double U, const gp_Circ& C, const int N)
{

  return ElCLib::CircleDN(U, C.Position(), C.Radius(), N);
}

inline gp_Vec ElCLib::DN(const double U, const gp_Elips& E, const int N)
{

  return ElCLib::EllipseDN(U, E.Position(), E.MajorRadius(), E.MinorRadius(), N);
}

inline gp_Vec ElCLib::DN(const double U, const gp_Hypr& H, const int N)
{

  return ElCLib::HyperbolaDN(U, H.Position(), H.MajorRadius(), H.MinorRadius(), N);
}

inline gp_Vec ElCLib::DN(const double U, const gp_Parab& Prb, const int N)
{

  return ElCLib::ParabolaDN(U, Prb.Position(), Prb.Focal(), N);
}

inline gp_Vec2d ElCLib::DN(const double U, const gp_Lin2d& L, const int N)
{

  return ElCLib::LineDN(U, L.Position(), N);
}

inline gp_Vec2d ElCLib::DN(const double U, const gp_Circ2d& C, const int N)
{

  return ElCLib::CircleDN(U, C.Axis(), C.Radius(), N);
}

inline gp_Vec2d ElCLib::DN(const double U, const gp_Elips2d& E, const int N)
{
  return ElCLib::EllipseDN(U, E.Axis(), E.MajorRadius(), E.MinorRadius(), N);
}

inline gp_Vec2d ElCLib::DN(const double U, const gp_Hypr2d& H, const int N)
{

  return ElCLib::HyperbolaDN(U, H.Axis(), H.MajorRadius(), H.MinorRadius(), N);
}

inline gp_Vec2d ElCLib::DN(const double U, const gp_Parab2d& Prb, const int N)
{

  return ElCLib::ParabolaDN(U, Prb.Axis(), Prb.Focal(), N);
}

inline double ElCLib::Parameter(const gp_Lin& L, const gp_Pnt& P)
{

  return ElCLib::LineParameter(L.Position(), P);
}

inline double ElCLib::Parameter(const gp_Circ& C, const gp_Pnt& P)
{

  return ElCLib::CircleParameter(C.Position(), P);
}

inline double ElCLib::Parameter(const gp_Elips& E, const gp_Pnt& P)
{

  return ElCLib::EllipseParameter(E.Position(), E.MajorRadius(), E.MinorRadius(), P);
}

inline double ElCLib::Parameter(const gp_Hypr& H, const gp_Pnt& P)
{

  return ElCLib::HyperbolaParameter(H.Position(), H.MajorRadius(), H.MinorRadius(), P);
}

inline double ElCLib::Parameter(const gp_Parab& Prb, const gp_Pnt& P)
{

  return ElCLib::ParabolaParameter(Prb.Position(), P);
}

inline double ElCLib::Parameter(const gp_Lin2d& L, const gp_Pnt2d& P)
{

  return ElCLib::LineParameter(L.Position(), P);
}

inline double ElCLib::Parameter(const gp_Circ2d& C, const gp_Pnt2d& P)
{

  return ElCLib::CircleParameter(C.Axis(), P);
}

inline double ElCLib::Parameter(const gp_Elips2d& E, const gp_Pnt2d& P)
{

  return ElCLib::EllipseParameter(E.Axis(), E.MajorRadius(), E.MinorRadius(), P);
}

inline double ElCLib::Parameter(const gp_Hypr2d& H, const gp_Pnt2d& P)
{

  return ElCLib::HyperbolaParameter(H.Axis(), H.MajorRadius(), H.MinorRadius(), P);
}

inline double ElCLib::Parameter(const gp_Parab2d& Prb, const gp_Pnt2d& P)
{

  return ElCLib::ParabolaParameter(Prb.Axis(), P);
}
