#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <gp_Pnt.hpp>

class Adaptor3d_HVertex;
class Standard_DomainError;
class gp_Pnt;

class IntPatch_ThePathPointOfTheSOnBounds
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_ThePathPointOfTheSOnBounds();

  Standard_EXPORT IntPatch_ThePathPointOfTheSOnBounds(const gp_Pnt&                         P,
                                                      const double                          Tol,
                                                      const occ::handle<Adaptor3d_HVertex>& V,
                                                      const occ::handle<Adaptor2d_Curve2d>& A,
                                                      const double Parameter);

  Standard_EXPORT IntPatch_ThePathPointOfTheSOnBounds(const gp_Pnt&                         P,
                                                      const double                          Tol,
                                                      const occ::handle<Adaptor2d_Curve2d>& A,
                                                      const double Parameter);

  void SetValue(const gp_Pnt&                         P,
                const double                          Tol,
                const occ::handle<Adaptor3d_HVertex>& V,
                const occ::handle<Adaptor2d_Curve2d>& A,
                const double                          Parameter);

  void SetValue(const gp_Pnt&                         P,
                const double                          Tol,
                const occ::handle<Adaptor2d_Curve2d>& A,
                const double                          Parameter);

  const gp_Pnt& Value() const;

  double Tolerance() const;

  bool IsNew() const;

  const occ::handle<Adaptor3d_HVertex>& Vertex() const;

  const occ::handle<Adaptor2d_Curve2d>& Arc() const;

  double Parameter() const;

private:
  gp_Pnt                         point;
  double                         tol;
  bool                           isnew;
  occ::handle<Adaptor3d_HVertex> vtx;
  occ::handle<Adaptor2d_Curve2d> arc;
  double                         param;
};

inline void IntPatch_ThePathPointOfTheSOnBounds::SetValue(const gp_Pnt&                         P,
                                                          const double                          Tol,
                                                          const occ::handle<Adaptor3d_HVertex>& V,
                                                          const occ::handle<Adaptor2d_Curve2d>& A,
                                                          const double Parameter)
{
  isnew = false;
  point = P;
  tol   = Tol;
  vtx   = V;
  arc   = A;
  param = Parameter;
}

inline void IntPatch_ThePathPointOfTheSOnBounds::SetValue(const gp_Pnt&                         P,
                                                          const double                          Tol,
                                                          const occ::handle<Adaptor2d_Curve2d>& A,
                                                          const double Parameter)
{
  isnew = true;
  point = P;
  tol   = Tol;
  arc   = A;
  param = Parameter;
}

inline const gp_Pnt& IntPatch_ThePathPointOfTheSOnBounds::Value() const
{
  return point;
}

inline double IntPatch_ThePathPointOfTheSOnBounds::Tolerance() const
{
  return tol;
}

inline bool IntPatch_ThePathPointOfTheSOnBounds::IsNew() const
{
  return isnew;
}

inline const occ::handle<Adaptor3d_HVertex>& IntPatch_ThePathPointOfTheSOnBounds::Vertex() const
{
  if (isnew)
  {
    throw Standard_DomainError();
  }
  return vtx;
}

inline const occ::handle<Adaptor2d_Curve2d>& IntPatch_ThePathPointOfTheSOnBounds::Arc() const
{
  return arc;
}

inline double IntPatch_ThePathPointOfTheSOnBounds::Parameter() const
{
  return param;
}
