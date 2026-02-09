#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Real.hpp>
class gp_Pnt;
class gp_Ax1;
class gp_Ax2;
class gp_Vec;
class gp_Trsf;

class Geom_Geometry : public Standard_Transient
{

public:
  Standard_EXPORT void Mirror(const gp_Pnt& P);

  Standard_EXPORT void Mirror(const gp_Ax1& A1);

  Standard_EXPORT void Mirror(const gp_Ax2& A2);

  Standard_EXPORT void Rotate(const gp_Ax1& A1, const double Ang);

  Standard_EXPORT void Scale(const gp_Pnt& P, const double S);

  Standard_EXPORT void Translate(const gp_Vec& V);

  Standard_EXPORT void Translate(const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT virtual void Transform(const gp_Trsf& T) = 0;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Geometry> Mirrored(const gp_Pnt& P) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Geometry> Mirrored(const gp_Ax1& A1) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Geometry> Mirrored(const gp_Ax2& A2) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Geometry> Rotated(const gp_Ax1& A1,
                                                                   const double  Ang) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Geometry> Scaled(const gp_Pnt& P,
                                                                  const double  S) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Geometry> Transformed(const gp_Trsf& T) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Geometry> Translated(const gp_Vec& V) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Geometry> Translated(const gp_Pnt& P1,
                                                                      const gp_Pnt& P2) const;

  Standard_EXPORT virtual occ::handle<Geom_Geometry> Copy() const = 0;

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(Geom_Geometry, Standard_Transient)
};
