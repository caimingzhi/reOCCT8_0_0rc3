#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec2d.hpp>
class gp_Ax2;
class gp_Vec;
class gp_Pnt;
class gp_Pnt2d;
class gp_Lin;

class HLRAlgo_Projector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRAlgo_Projector();

  Standard_EXPORT HLRAlgo_Projector(const gp_Ax2& CS);

  Standard_EXPORT HLRAlgo_Projector(const gp_Ax2& CS, const double Focus);

  Standard_EXPORT HLRAlgo_Projector(const gp_Trsf& T, const bool Persp, const double Focus);

  Standard_EXPORT HLRAlgo_Projector(const gp_Trsf&  T,
                                    const bool      Persp,
                                    const double    Focus,
                                    const gp_Vec2d& v1,
                                    const gp_Vec2d& v2,
                                    const gp_Vec2d& v3);

  Standard_EXPORT void Set(const gp_Trsf& T, const bool Persp, const double Focus);

  void Directions(gp_Vec2d& D1, gp_Vec2d& D2, gp_Vec2d& D3) const;

  Standard_EXPORT void Scaled(const bool On = false);

  bool Perspective() const;

  Standard_EXPORT const gp_Trsf& Transformation() const;

  const gp_Trsf& InvertedTransformation() const;

  const gp_Trsf& FullTransformation() const;

  double Focus() const;

  void Transform(gp_Vec& D) const;

  void Transform(gp_Pnt& Pnt) const;

  Standard_EXPORT void Project(const gp_Pnt& P, gp_Pnt2d& Pout) const;

  Standard_EXPORT void Project(const gp_Pnt& P, double& X, double& Y, double& Z) const;

  Standard_EXPORT void Project(const gp_Pnt& P,
                               const gp_Vec& D1,
                               gp_Pnt2d&     Pout,
                               gp_Vec2d&     D1out) const;

  Standard_EXPORT gp_Lin Shoot(const double X, const double Y) const;

private:
  Standard_EXPORT void SetDirection();

  int      myType;
  bool     myPersp;
  double   myFocus;
  gp_Trsf  myScaledTrsf;
  gp_Trsf  myTrsf;
  gp_Trsf  myInvTrsf;
  gp_Vec2d myD1;
  gp_Vec2d myD2;
  gp_Vec2d myD3;
};

#include <Standard_NoSuchObject.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt.hpp>

inline void HLRAlgo_Projector::Directions(gp_Vec2d& D1, gp_Vec2d& D2, gp_Vec2d& D3) const
{
  D1 = myD1;
  D2 = myD2;
  D3 = myD3;
}

inline bool HLRAlgo_Projector::Perspective() const
{
  return myPersp;
}

inline const gp_Trsf& HLRAlgo_Projector::InvertedTransformation() const
{
  return myInvTrsf;
}

inline const gp_Trsf& HLRAlgo_Projector::FullTransformation() const
{
  return myScaledTrsf;
}

inline double HLRAlgo_Projector::Focus() const
{
  Standard_NoSuchObject_Raise_if(!myPersp, "HLRAlgo_Projector::Not a Perspective");
  return myFocus;
}

inline void HLRAlgo_Projector::Transform(gp_Vec& D) const
{
  D.Transform(myTrsf);
}

inline void HLRAlgo_Projector::Transform(gp_Pnt& Pnt) const
{
  Pnt.Transform(myTrsf);
}
