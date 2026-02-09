#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Contap_Line.hpp>
#include <NCollection_Sequence.hpp>
#include <Contap_TheSearch.hpp>
#include <Contap_TheSearchInside.hpp>
#include <Contap_SurfFunction.hpp>
#include <Contap_ArcFunction.hpp>

class gp_Vec;
class gp_Pnt;
class Adaptor3d_TopolTool;

class Contap_Contour
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Contap_Contour();

  Standard_EXPORT Contap_Contour(const gp_Vec& Direction);

  Standard_EXPORT Contap_Contour(const gp_Vec& Direction, const double Angle);

  Standard_EXPORT Contap_Contour(const gp_Pnt& Eye);

  Standard_EXPORT Contap_Contour(const occ::handle<Adaptor3d_Surface>&   Surf,
                                 const occ::handle<Adaptor3d_TopolTool>& Domain,
                                 const gp_Vec&                           Direction);

  Standard_EXPORT Contap_Contour(const occ::handle<Adaptor3d_Surface>&   Surf,
                                 const occ::handle<Adaptor3d_TopolTool>& Domain,
                                 const gp_Vec&                           Direction,
                                 const double                            Angle);

  Standard_EXPORT Contap_Contour(const occ::handle<Adaptor3d_Surface>&   Surf,
                                 const occ::handle<Adaptor3d_TopolTool>& Domain,
                                 const gp_Pnt&                           Eye);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Surf,
                               const occ::handle<Adaptor3d_TopolTool>& Domain);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Surf,
                               const occ::handle<Adaptor3d_TopolTool>& Domain,
                               const gp_Vec&                           Direction);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Surf,
                               const occ::handle<Adaptor3d_TopolTool>& Domain,
                               const gp_Vec&                           Direction,
                               const double                            Angle);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Surf,
                               const occ::handle<Adaptor3d_TopolTool>& Domain,
                               const gp_Pnt&                           Eye);

  Standard_EXPORT void Init(const gp_Vec& Direction);

  Standard_EXPORT void Init(const gp_Vec& Direction, const double Angle);

  Standard_EXPORT void Init(const gp_Pnt& Eye);

  bool IsDone() const;

  bool IsEmpty() const;

  int NbLines() const;

  const Contap_Line& Line(const int Index) const;

  Contap_SurfFunction& SurfaceFunction();

private:
  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_TopolTool>& Domain);

  Standard_EXPORT void PerformAna(const occ::handle<Adaptor3d_TopolTool>& Domain);

  bool                              done;
  NCollection_Sequence<Contap_Line> slin;
  Contap_TheSearch                  solrst;
  Contap_TheSearchInside            solins;
  Contap_SurfFunction               mySFunc;
  Contap_ArcFunction                myAFunc;
  bool                              modeset;
};

#include <StdFail_NotDone.hpp>

inline bool Contap_Contour::IsDone() const
{
  return done;
}

inline bool Contap_Contour::IsEmpty() const
{
  return NbLines() == 0;
}

inline int Contap_Contour::NbLines() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return slin.Length();
}

inline const Contap_Line& Contap_Contour::Line(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return slin(Index);
}

inline Contap_SurfFunction& Contap_Contour::SurfaceFunction()
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return mySFunc;
}
