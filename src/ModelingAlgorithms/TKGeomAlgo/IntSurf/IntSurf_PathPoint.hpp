#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir2d.hpp>
#include <gp_XY.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>

class IntSurf_PathPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntSurf_PathPoint();

  Standard_EXPORT IntSurf_PathPoint(const gp_Pnt& P, const double U, const double V);

  Standard_EXPORT void SetValue(const gp_Pnt& P, const double U, const double V);

  void AddUV(const double U, const double V);

  void SetDirections(const gp_Vec& V, const gp_Dir2d& D);

  void SetTangency(const bool Tang);

  void SetPassing(const bool Pass);

  const gp_Pnt& Value() const;

  void Value2d(double& U, double& V) const;

  bool IsPassingPnt() const;

  bool IsTangent() const;

  const gp_Vec& Direction3d() const;

  const gp_Dir2d& Direction2d() const;

  int Multiplicity() const;

  void Parameters(const int Index, double& U, double& V) const;

private:
  gp_Pnt                                    pt;
  bool                                      ispass;
  bool                                      istgt;
  gp_Vec                                    vectg;
  gp_Dir2d                                  dirtg;
  occ::handle<NCollection_HSequence<gp_XY>> sequv;
};

#include <StdFail_UndefinedDerivative.hpp>
#include <gp_XY.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

inline void IntSurf_PathPoint::AddUV(const double U, const double V)
{
  sequv->Append(gp_XY(U, V));
}

inline void IntSurf_PathPoint::SetDirections(const gp_Vec& V, const gp_Dir2d& D)
{

  istgt = false;
  vectg = V;
  dirtg = D;
}

inline void IntSurf_PathPoint::SetTangency(const bool Tang)
{

  istgt = Tang;
}

inline void IntSurf_PathPoint::SetPassing(const bool Pass)
{

  ispass = Pass;
}

inline const gp_Pnt& IntSurf_PathPoint::Value() const
{
  return pt;
}

inline void IntSurf_PathPoint::Value2d(double& U, double& V) const
{
  gp_XY uv(sequv->Sequence().First());
  U = uv.X();
  V = uv.Y();
}

inline bool IntSurf_PathPoint::IsPassingPnt() const
{

  return ispass;
}

inline bool IntSurf_PathPoint::IsTangent() const
{

  return istgt;
}

inline const gp_Vec& IntSurf_PathPoint::Direction3d() const
{

  if (istgt)
  {
    throw StdFail_UndefinedDerivative();
  }
  return vectg;
}

inline const gp_Dir2d& IntSurf_PathPoint::Direction2d() const
{

  if (istgt)
  {
    throw StdFail_UndefinedDerivative();
  }
  return dirtg;
}

inline int IntSurf_PathPoint::Multiplicity() const
{

  return (sequv->Length() - 1);
}

inline void IntSurf_PathPoint::Parameters(const int Index, double& U, double& V) const
{
  gp_XY uv(sequv->Value(Index + 1));
  U = uv.X();
  V = uv.Y();
}
