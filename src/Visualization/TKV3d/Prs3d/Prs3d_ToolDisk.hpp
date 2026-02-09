#pragma once

#include <Prs3d_ToolQuadric.hpp>

class Prs3d_ToolDisk : public Prs3d_ToolQuadric
{
public:
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfTriangles> Create(const double theInnerRadius,
                                                                        const double theOuterRadius,
                                                                        const int    theNbSlices,
                                                                        const int    theNbStacks,
                                                                        const gp_Trsf& theTrsf);

public:
  Standard_EXPORT Prs3d_ToolDisk(const double theInnerRadius,
                                 const double theOuterRadius,
                                 const int    theNbSlices,
                                 const int    theNbStacks);

  void SetAngleRange(double theStartAngle, double theEndAngle)
  {
    myStartAngle = theStartAngle;
    myEndAngle   = theEndAngle;
  }

protected:
  Standard_EXPORT gp_Pnt Vertex(const double theU, const double theV) const override;

  gp_Dir Normal(const double, const double) const override { return gp_Dir(gp_Dir::D::NZ); }

protected:
  double myInnerRadius;
  double myOuterRadius;
  double myStartAngle;
  double myEndAngle;
};
