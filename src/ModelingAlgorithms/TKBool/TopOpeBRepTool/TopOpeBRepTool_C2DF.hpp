#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Face.hpp>
class Geom2d_Curve;

class TopOpeBRepTool_C2DF
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_C2DF();

  Standard_EXPORT TopOpeBRepTool_C2DF(const occ::handle<Geom2d_Curve>& PC,
                                      const double                     f2d,
                                      const double                     l2d,
                                      const double                     tol,
                                      const TopoDS_Face&               F);

  Standard_EXPORT void SetPC(const occ::handle<Geom2d_Curve>& PC,
                             const double                     f2d,
                             const double                     l2d,
                             const double                     tol);

  Standard_EXPORT void SetFace(const TopoDS_Face& F);

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PC(double& f2d, double& l2d, double& tol) const;

  Standard_EXPORT const TopoDS_Face& Face() const;

  Standard_EXPORT bool IsPC(const occ::handle<Geom2d_Curve>& PC) const;

  Standard_EXPORT bool IsFace(const TopoDS_Face& F) const;

private:
  occ::handle<Geom2d_Curve> myPC;
  double                    myf2d;
  double                    myl2d;
  double                    mytol;
  TopoDS_Face               myFace;
};
