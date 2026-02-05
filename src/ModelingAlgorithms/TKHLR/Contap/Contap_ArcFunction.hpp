#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Contap_TFunction.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <IntSurf_Quadric.hpp>
#include <math_FunctionWithDerivative.hpp>

class Contap_ArcFunction : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Contap_ArcFunction();

  Standard_EXPORT void Set(const occ::handle<Adaptor3d_Surface>& S);

  void Set(const gp_Dir& Direction);

  void Set(const gp_Dir& Direction, const double Angle);

  void Set(const gp_Pnt& Eye);

  void Set(const gp_Pnt& Eye, const double Angle);

  void Set(const occ::handle<Adaptor2d_Curve2d>& A);

  Standard_EXPORT bool Value(const double X, double& F) override;

  Standard_EXPORT bool Derivative(const double X, double& D) override;

  Standard_EXPORT bool Values(const double X, double& F, double& D) override;

  Standard_EXPORT int NbSamples() const;

  Standard_EXPORT int GetStateNumber() override;

  const gp_Pnt& Valpoint(const int Index) const;

  Standard_EXPORT const IntSurf_Quadric& Quadric() const;

  //! Returns mySurf field
  const occ::handle<Adaptor3d_Surface>& Surface() const;

  //! Returns the point, which has been computed
  //! while the last calling Value() method
  const gp_Pnt& LastComputedPoint() const;

private:
  occ::handle<Adaptor2d_Curve2d> myArc;
  occ::handle<Adaptor3d_Surface> mySurf;
  double                         myMean;
  Contap_TFunction               myType;
  gp_Dir                         myDir;
  double                         myCosAng;
  gp_Pnt                         myEye;
  gp_Pnt                         solpt;
  NCollection_Sequence<gp_Pnt>   seqpt;
  IntSurf_Quadric                myQuad;
};

inline void Contap_ArcFunction::Set(const gp_Dir& Direction, const double Angle)
{
  myType   = Contap_DraftStd;
  myDir    = Direction;
  myCosAng = std::cos(M_PI / 2. + Angle);
}

inline void Contap_ArcFunction::Set(const gp_Pnt& Eye, const double Angle)
{
  myType   = Contap_DraftPrs;
  myEye    = Eye;
  myCosAng = std::cos(M_PI / 2. + Angle);
}

inline void Contap_ArcFunction::Set(const gp_Dir& Direction)
{
  myType = Contap_ContourStd;
  myDir  = Direction;
}

inline void Contap_ArcFunction::Set(const gp_Pnt& Eye)
{
  myType = Contap_ContourPrs;
  myEye  = Eye;
}

inline void Contap_ArcFunction::Set(const occ::handle<Adaptor2d_Curve2d>& A)
{
  myArc = A;
  seqpt.Clear();
}

inline const gp_Pnt& Contap_ArcFunction::Valpoint(const int Index) const
{
  return seqpt(Index);
}

inline const occ::handle<Adaptor3d_Surface>& Contap_ArcFunction::Surface() const
{
  return (mySurf);
}

inline const gp_Pnt& Contap_ArcFunction::LastComputedPoint() const
{
  return solpt;
}
