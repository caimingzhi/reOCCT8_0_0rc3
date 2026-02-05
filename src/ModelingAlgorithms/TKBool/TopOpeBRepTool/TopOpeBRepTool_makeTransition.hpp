#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <gp_Pnt2d.hpp>
#include <TopAbs_State.hpp>

class TopOpeBRepTool_makeTransition
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_makeTransition();

  Standard_EXPORT bool Initialize(const TopoDS_Edge& E,
                                  const double       pbef,
                                  const double       paft,
                                  const double       parE,
                                  const TopoDS_Face& FS,
                                  const gp_Pnt2d&    uv,
                                  const double       factor);

  Standard_EXPORT void Setfactor(const double factor);

  Standard_EXPORT double Getfactor() const;

  Standard_EXPORT bool IsT2d() const;

  Standard_EXPORT bool SetRest(const TopoDS_Edge& ES, const double parES);

  Standard_EXPORT bool HasRest() const;

  Standard_EXPORT bool MkT2donE(TopAbs_State& stb, TopAbs_State& sta) const;

  Standard_EXPORT bool MkT3onE(TopAbs_State& stb, TopAbs_State& sta) const;

  Standard_EXPORT bool MkT3dproj(TopAbs_State& stb, TopAbs_State& sta) const;

  Standard_EXPORT bool MkTonE(TopAbs_State& stb, TopAbs_State& sta);

private:
  TopoDS_Edge myE;
  double      mypb;
  double      mypa;
  double      mypE;
  TopoDS_Face myFS;
  gp_Pnt2d    myuv;
  bool        hasES;
  TopoDS_Edge myES;
  double      mypES;
  bool        isT2d;
  double      myfactor;
};
