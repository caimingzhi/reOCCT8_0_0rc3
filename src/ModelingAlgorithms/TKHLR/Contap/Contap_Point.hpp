#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <IntSurf_Transition.hpp>

class Adaptor3d_HVertex;

class Contap_Point
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Contap_Point();

  Standard_EXPORT Contap_Point(const gp_Pnt& Pt, const double U, const double V);

  void SetValue(const gp_Pnt& Pt, const double U, const double V);

  void SetParameter(const double Para);

  void SetVertex(const occ::handle<Adaptor3d_HVertex>& V);

  void SetArc(const occ::handle<Adaptor2d_Curve2d>& A,
              const double                          Param,
              const IntSurf_Transition&             TLine,
              const IntSurf_Transition&             TArc);

  void SetMultiple();

  void SetInternal();

  const gp_Pnt& Value() const;

  double ParameterOnLine() const;

  void Parameters(double& U1, double& V1) const;

  bool IsOnArc() const;

  const occ::handle<Adaptor2d_Curve2d>& Arc() const;

  double ParameterOnArc() const;

  const IntSurf_Transition& TransitionOnLine() const;

  const IntSurf_Transition& TransitionOnArc() const;

  bool IsVertex() const;

  const occ::handle<Adaptor3d_HVertex>& Vertex() const;

  bool IsMultiple() const;

  bool IsInternal() const;

private:
  gp_Pnt                         pt;
  double                         uparam;
  double                         vparam;
  double                         paraline;
  bool                           onarc;
  occ::handle<Adaptor2d_Curve2d> arc;
  IntSurf_Transition             traline;
  IntSurf_Transition             traarc;
  double                         prmarc;
  bool                           isvtx;
  occ::handle<Adaptor3d_HVertex> vtx;
  bool                           ismult;
  bool                           myInternal;
};

#include <Standard_DomainError.hpp>

inline void Contap_Point::SetValue(const gp_Pnt& Pt, const double U, const double V)
{
  pt         = Pt;
  uparam     = U;
  vparam     = V;
  onarc      = false;
  isvtx      = false;
  ismult     = false;
  myInternal = false;
}

inline void Contap_Point::SetParameter(const double Para)
{

  paraline = Para;
}

inline void Contap_Point::SetVertex(const occ::handle<Adaptor3d_HVertex>& V)
{

  isvtx = true;
  vtx   = V;
}

inline void Contap_Point::SetArc(const occ::handle<Adaptor2d_Curve2d>& A,
                                 const double                          Param,
                                 const IntSurf_Transition&             TLine,
                                 const IntSurf_Transition&             TArc)
{

  onarc   = true;
  arc     = A;
  prmarc  = Param;
  traline = TLine;
  traarc  = TArc;
}

inline void Contap_Point::SetMultiple()
{
  ismult = true;
}

inline void Contap_Point::SetInternal()
{
  myInternal = true;
}

inline bool Contap_Point::IsMultiple() const
{
  return ismult;
}

inline bool Contap_Point::IsInternal() const
{
  return myInternal;
}

inline const gp_Pnt& Contap_Point::Value() const
{

  return pt;
}

inline double Contap_Point::ParameterOnLine() const
{

  return paraline;
}

inline void Contap_Point::Parameters(double& U1, double& V1) const
{

  U1 = uparam;
  V1 = vparam;
}

inline bool Contap_Point::IsOnArc() const
{
  return onarc;
}

inline const occ::handle<Adaptor2d_Curve2d>& Contap_Point::Arc() const
{

  if (!onarc)
  {
    throw Standard_DomainError();
  }
  return arc;
}

inline const IntSurf_Transition& Contap_Point::TransitionOnLine() const
{

  if (!onarc)
  {
    throw Standard_DomainError();
  }
  return traline;
}

inline const IntSurf_Transition& Contap_Point::TransitionOnArc() const
{

  if (!onarc)
  {
    throw Standard_DomainError();
  }
  return traarc;
}

inline double Contap_Point::ParameterOnArc() const
{

  if (!onarc)
  {
    throw Standard_DomainError();
  }
  return prmarc;
}

inline bool Contap_Point::IsVertex() const
{
  return isvtx;
}

inline const occ::handle<Adaptor3d_HVertex>& Contap_Point::Vertex() const
{

  if (!isvtx)
  {
    throw Standard_DomainError();
  }
  return vtx;
}
