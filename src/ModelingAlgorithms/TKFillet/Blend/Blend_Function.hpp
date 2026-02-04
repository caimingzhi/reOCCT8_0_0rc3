#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Blend_AppFunction.hpp>
#include <Standard_Boolean.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
class gp_Pnt;
class gp_Vec;
class gp_Vec2d;
class Blend_Point;

//! Deferred class for a function used to compute a blending
//! surface between two surfaces, using a guide line.
//! The vector <X> used in Value, Values and Derivatives methods
//! has to be the vector of the parametric coordinates U1,V1,
//! U2,V2, of the extremities of a section on the first and
//! second surface.
class Blend_Function : public Blend_AppFunction
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns 4.
  Standard_EXPORT int NbVariables() const override;

  //! Returns the point on the first support.
  Standard_EXPORT const gp_Pnt& Pnt1() const override;

  //! Returns the point on the second support.
  Standard_EXPORT const gp_Pnt& Pnt2() const override;

  //! Returns the point on the first surface, at parameter
  //! Sol(1),Sol(2) (Sol is the vector used in the call of
  //! IsSolution.
  Standard_EXPORT virtual const gp_Pnt& PointOnS1() const = 0;

  //! Returns the point on the second surface, at parameter
  //! Sol(3),Sol(4) (Sol is the vector used in the call of
  //! IsSolution.
  Standard_EXPORT virtual const gp_Pnt& PointOnS2() const = 0;

  //! Returns True when it is not possible to compute
  //! the tangent vectors at PointOnS1 and/or PointOnS2.
  Standard_EXPORT virtual bool IsTangencyPoint() const = 0;

  //! Returns the tangent vector at PointOnS1, in 3d space.
  Standard_EXPORT virtual const gp_Vec& TangentOnS1() const = 0;

  //! Returns the tangent vector at PointOnS1, in the
  //! parametric space of the first surface.
  Standard_EXPORT virtual const gp_Vec2d& Tangent2dOnS1() const = 0;

  //! Returns the tangent vector at PointOnS2, in 3d space.
  Standard_EXPORT virtual const gp_Vec& TangentOnS2() const = 0;

  //! Returns the tangent vector at PointOnS2, in the
  //! parametric space of the second surface.
  Standard_EXPORT virtual const gp_Vec2d& Tangent2dOnS2() const = 0;

  //! Returns the tangent vector at the section,
  //! at the beginning and the end of the section, and
  //! returns the normal (of the surfaces) at
  //! these points.
  Standard_EXPORT virtual void Tangent(const double U1,
                                       const double V1,
                                       const double U2,
                                       const double V2,
                                       gp_Vec&      TgFirst,
                                       gp_Vec&      TgLast,
                                       gp_Vec&      NormFirst,
                                       gp_Vec&      NormLast) const = 0;

  Standard_EXPORT virtual bool TwistOnS1() const;

  Standard_EXPORT virtual bool TwistOnS2() const;

  Standard_EXPORT void Section(const Blend_Point&            P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<double>&   Weigths) override = 0;

  //! Used for the first and last section
  //! The method returns true if the derivatives
  //! are computed, otherwise it returns false
  Standard_EXPORT bool Section(const Blend_Point&            P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Vec>&   DPoles,
                               NCollection_Array1<gp_Vec>&   D2Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<gp_Vec2d>& DPoles2d,
                               NCollection_Array1<gp_Vec2d>& D2Poles2d,
                               NCollection_Array1<double>&   Weigths,
                               NCollection_Array1<double>&   DWeigths,
                               NCollection_Array1<double>&   D2Weigths) override;
};

