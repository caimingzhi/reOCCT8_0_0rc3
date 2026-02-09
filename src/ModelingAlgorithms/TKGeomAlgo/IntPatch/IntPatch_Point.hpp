#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntSurf_PntOn2S.hpp>
#include <IntSurf_Transition.hpp>
#include <Adaptor2d_Curve2d.hpp>

class Adaptor3d_HVertex;
class gp_Pnt;

class IntPatch_Point
{
public:
  DEFINE_STANDARD_ALLOC

  IntPatch_Point();

  Standard_EXPORT void SetValue(const gp_Pnt& Pt, const double Tol, const bool Tangent);

  void SetValue(const gp_Pnt& Pt);

  void SetValue(const IntSurf_PntOn2S& thePOn2S);

  void SetTolerance(const double Tol);

  void SetParameters(const double U1, const double V1, const double U2, const double V2);

  void SetParameter(const double Para);

  Standard_EXPORT void SetVertex(const bool OnFirst, const occ::handle<Adaptor3d_HVertex>& V);

  Standard_EXPORT void SetArc(const bool                            OnFirst,
                              const occ::handle<Adaptor2d_Curve2d>& A,
                              const double                          Param,
                              const IntSurf_Transition&             TLine,
                              const IntSurf_Transition&             TArc);

  void SetMultiple(const bool IsMult);

  const gp_Pnt& Value() const;

  double ParameterOnLine() const;

  double Tolerance() const;

  bool IsTangencyPoint() const;

  void ParametersOnS1(double& U1, double& V1) const;

  void ParametersOnS2(double& U2, double& V2) const;

  bool IsMultiple() const;

  bool IsOnDomS1() const;

  bool IsVertexOnS1() const;

  const occ::handle<Adaptor3d_HVertex>& VertexOnS1() const;

  const occ::handle<Adaptor2d_Curve2d>& ArcOnS1() const;

  const IntSurf_Transition& TransitionLineArc1() const;

  const IntSurf_Transition& TransitionOnS1() const;

  double ParameterOnArc1() const;

  bool IsOnDomS2() const;

  bool IsVertexOnS2() const;

  const occ::handle<Adaptor3d_HVertex>& VertexOnS2() const;

  const occ::handle<Adaptor2d_Curve2d>& ArcOnS2() const;

  const IntSurf_Transition& TransitionLineArc2() const;

  const IntSurf_Transition& TransitionOnS2() const;

  double ParameterOnArc2() const;

  const IntSurf_PntOn2S& PntOn2S() const;

  void Parameters(double& U1, double& V1, double& U2, double& V2) const;

  Standard_EXPORT void ReverseTransition();

  Standard_EXPORT void Dump() const;

private:
  IntSurf_PntOn2S pt;
  double          para;
  double          tol;
  bool            tgt;

  bool mult;

  bool                           onS1;
  bool                           vtxonS1;
  occ::handle<Adaptor3d_HVertex> vS1;
  occ::handle<Adaptor2d_Curve2d> arcS1;
  IntSurf_Transition             traline1;
  IntSurf_Transition             tra1;
  double                         prm1;
  bool                           onS2;
  bool                           vtxonS2;
  occ::handle<Adaptor3d_HVertex> vS2;
  occ::handle<Adaptor2d_Curve2d> arcS2;
  IntSurf_Transition             traline2;
  IntSurf_Transition             tra2;
  double                         prm2;
};

inline IntPatch_Point::IntPatch_Point()
    : para(0.0),
      tol(0.0),
      tgt(false),
      mult(false),
      onS1(false),
      vtxonS1(false),
      prm1(0.0),
      onS2(false),
      vtxonS2(false),
      prm2(0.0)
{
}

inline void IntPatch_Point::SetValue(const gp_Pnt& Pt)
{
  pt.SetValue(Pt);
}

inline void IntPatch_Point::SetValue(const IntSurf_PntOn2S& thePOn2S)
{
  pt = thePOn2S;
}

inline void IntPatch_Point::SetTolerance(const double Tol)
{
  tol = Tol;
}

inline void IntPatch_Point::SetParameters(const double U1,
                                          const double V1,
                                          const double U2,
                                          const double V2)
{
  pt.SetValue(U1, V1, U2, V2);
}

inline void IntPatch_Point::SetParameter(const double Para)
{
  para = Para;
}

inline void IntPatch_Point::SetMultiple(const bool IsMult)
{
  mult = IsMult;
}

inline const gp_Pnt& IntPatch_Point::Value() const
{
  return pt.Value();
}

inline double IntPatch_Point::Tolerance() const
{
  return tol;
}

inline double IntPatch_Point::ParameterOnLine() const
{
  return para;
}

inline bool IntPatch_Point::IsTangencyPoint() const
{
  return tgt;
}

inline void IntPatch_Point::ParametersOnS1(double& U1, double& V1) const
{
  pt.ParametersOnS1(U1, V1);
}

inline void IntPatch_Point::ParametersOnS2(double& U2, double& V2) const
{
  pt.ParametersOnS2(U2, V2);
}

inline bool IntPatch_Point::IsMultiple() const
{
  return mult;
}

inline bool IntPatch_Point::IsOnDomS1() const
{
  return onS1;
}

inline bool IntPatch_Point::IsVertexOnS1() const
{
  return vtxonS1;
}

inline const occ::handle<Adaptor3d_HVertex>& IntPatch_Point::VertexOnS1() const
{
  if (!vtxonS1)
  {
    throw Standard_DomainError();
  }
  return vS1;
}

inline const occ::handle<Adaptor2d_Curve2d>& IntPatch_Point::ArcOnS1() const
{
  if (!onS1)
  {
    throw Standard_DomainError();
  }
  return arcS1;
}

inline const IntSurf_Transition& IntPatch_Point::TransitionLineArc1() const
{
  if (!onS1)
  {
    throw Standard_DomainError();
  }
  return traline1;
}

inline const IntSurf_Transition& IntPatch_Point::TransitionOnS1() const
{
  if (!onS1)
  {
    throw Standard_DomainError();
  }
  return tra1;
}

inline double IntPatch_Point::ParameterOnArc1() const
{
  if (!onS1)
  {
    throw Standard_DomainError();
  }
  return prm1;
}

inline bool IntPatch_Point::IsOnDomS2() const
{
  return onS2;
}

inline bool IntPatch_Point::IsVertexOnS2() const
{
  return vtxonS2;
}

inline const occ::handle<Adaptor3d_HVertex>& IntPatch_Point::VertexOnS2() const
{
  if (!vtxonS2)
  {
    throw Standard_DomainError();
  }
  return vS2;
}

inline const occ::handle<Adaptor2d_Curve2d>& IntPatch_Point::ArcOnS2() const
{
  if (!onS2)
  {
    throw Standard_DomainError();
  }
  return arcS2;
}

inline const IntSurf_Transition& IntPatch_Point::TransitionLineArc2() const
{
  if (!onS2)
  {
    throw Standard_DomainError();
  }
  return traline2;
}

inline const IntSurf_Transition& IntPatch_Point::TransitionOnS2() const
{
  if (!onS2)
  {
    throw Standard_DomainError();
  }
  return tra2;
}

inline double IntPatch_Point::ParameterOnArc2() const
{
  if (!onS2)
  {
    throw Standard_DomainError();
  }
  return prm2;
}

inline const IntSurf_PntOn2S& IntPatch_Point::PntOn2S() const
{
  return pt;
}

inline void IntPatch_Point::Parameters(double& U1, double& V1, double& U2, double& V2) const
{
  pt.Parameters(U1, V1, U2, V2);
}
