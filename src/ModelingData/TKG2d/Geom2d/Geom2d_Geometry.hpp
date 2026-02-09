#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Real.hpp>
class gp_Pnt2d;
class gp_Ax2d;
class gp_Vec2d;
class gp_Trsf2d;

class Geom2d_Geometry : public Standard_Transient
{

public:
  Standard_EXPORT void Mirror(const gp_Pnt2d& P);

  Standard_EXPORT void Mirror(const gp_Ax2d& A);

  Standard_EXPORT void Rotate(const gp_Pnt2d& P, const double Ang);

  Standard_EXPORT void Scale(const gp_Pnt2d& P, const double S);

  Standard_EXPORT void Translate(const gp_Vec2d& V);

  Standard_EXPORT void Translate(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT virtual void Transform(const gp_Trsf2d& T) = 0;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Geometry> Mirrored(const gp_Pnt2d& P) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Geometry> Mirrored(const gp_Ax2d& A) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Geometry> Rotated(const gp_Pnt2d& P,
                                                                     const double    Ang) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Geometry> Scaled(const gp_Pnt2d& P,
                                                                    const double    S) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Geometry> Transformed(const gp_Trsf2d& T) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Geometry> Translated(const gp_Vec2d& V) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Geometry> Translated(const gp_Pnt2d& P1,
                                                                        const gp_Pnt2d& P2) const;

  Standard_EXPORT virtual occ::handle<Geom2d_Geometry> Copy() const = 0;

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Geometry, Standard_Transient)
};
