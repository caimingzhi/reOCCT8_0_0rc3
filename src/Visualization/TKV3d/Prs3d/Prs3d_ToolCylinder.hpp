#pragma once

#include <Prs3d_ToolQuadric.hpp>

class Prs3d_ToolCylinder : public Prs3d_ToolQuadric
{
public:
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfTriangles> Create(const double   theBottomRad,
                                                                        const double   theTopRad,
                                                                        const double   theHeight,
                                                                        const int      theNbSlices,
                                                                        const int      theNbStacks,
                                                                        const gp_Trsf& theTrsf);

public:
  Standard_EXPORT Prs3d_ToolCylinder(const double theBottomRad,
                                     const double theTopRad,
                                     const double theHeight,
                                     const int    theNbSlices,
                                     const int    theNbStacks);

protected:
  Standard_EXPORT gp_Pnt Vertex(const double theU, const double theV) const override;

  Standard_EXPORT gp_Dir Normal(const double theU, const double theV) const override;

protected:
  double myBottomRadius;
  double myTopRadius;
  double myHeight;
};
