#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <gp_Pnt2d.hpp>
#include <TopAbs_Orientation.hpp>

class Adaptor3d_HVertex : public Standard_Transient
{

public:
  Standard_EXPORT Adaptor3d_HVertex();

  Standard_EXPORT Adaptor3d_HVertex(const gp_Pnt2d&          P,
                                    const TopAbs_Orientation Ori,
                                    const double             Resolution);

  Standard_EXPORT virtual gp_Pnt2d Value();

  Standard_EXPORT virtual double Parameter(const occ::handle<Adaptor2d_Curve2d>& C);

  Standard_EXPORT virtual double Resolution(const occ::handle<Adaptor2d_Curve2d>& C);

  Standard_EXPORT virtual TopAbs_Orientation Orientation();

  Standard_EXPORT virtual bool IsSame(const occ::handle<Adaptor3d_HVertex>& Other);

  DEFINE_STANDARD_RTTIEXT(Adaptor3d_HVertex, Standard_Transient)

private:
  gp_Pnt2d           myPnt;
  double             myTol;
  TopAbs_Orientation myOri;
};
