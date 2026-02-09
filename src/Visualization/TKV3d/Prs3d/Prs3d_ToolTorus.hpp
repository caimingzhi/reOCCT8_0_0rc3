#pragma once

#include <Prs3d_ToolQuadric.hpp>

class Prs3d_ToolTorus : public Prs3d_ToolQuadric
{
public:
  static occ::handle<Graphic3d_ArrayOfTriangles> Create(const double   theMajorRad,
                                                        const double   theMinorRad,
                                                        const int      theNbSlices,
                                                        const int      theNbStacks,
                                                        const gp_Trsf& theTrsf)
  {
    return Create(theMajorRad,
                  theMinorRad,
                  0.0,
                  M_PI * 2.0,
                  M_PI * 2.0,
                  theNbSlices,
                  theNbStacks,
                  theTrsf);
  }

  static occ::handle<Graphic3d_ArrayOfTriangles> Create(const double   theMajorRad,
                                                        const double   theMinorRad,
                                                        const double   theAngle,
                                                        const int      theNbSlices,
                                                        const int      theNbStacks,
                                                        const gp_Trsf& theTrsf)
  {
    return Create(theMajorRad,
                  theMinorRad,
                  0.0,
                  M_PI * 2.0,
                  theAngle,
                  theNbSlices,
                  theNbStacks,
                  theTrsf);
  }

  static occ::handle<Graphic3d_ArrayOfTriangles> Create(const double   theMajorRad,
                                                        const double   theMinorRad,
                                                        const double   theAngle1,
                                                        const double   theAngle2,
                                                        const int      theNbSlices,
                                                        const int      theNbStacks,
                                                        const gp_Trsf& theTrsf)
  {
    return Create(theMajorRad,
                  theMinorRad,
                  theAngle1,
                  theAngle2,
                  M_PI * 2.0,
                  theNbSlices,
                  theNbStacks,
                  theTrsf);
  }

  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfTriangles> Create(const double   theMajorRad,
                                                                        const double   theMinorRad,
                                                                        const double   theAngle1,
                                                                        const double   theAngle2,
                                                                        const double   theAngle,
                                                                        const int      theNbSlices,
                                                                        const int      theNbStacks,
                                                                        const gp_Trsf& theTrsf);

public:
  Prs3d_ToolTorus(const double theMajorRad,
                  const double theMinorRad,
                  const int    theNbSlices,
                  const int    theNbStacks)
  {
    init(theMajorRad, theMinorRad, 0.0, M_PI * 2.0, M_PI * 2.0, theNbSlices, theNbStacks);
  }

  Prs3d_ToolTorus(const double theMajorRad,
                  const double theMinorRad,
                  const double theAngle,
                  const int    theNbSlices,
                  const int    theNbStacks)
  {
    init(theMajorRad, theMinorRad, 0.0, M_PI * 2.0, theAngle, theNbSlices, theNbStacks);
  }

  Prs3d_ToolTorus(const double theMajorRad,
                  const double theMinorRad,
                  const double theAngle1,
                  const double theAngle2,
                  const int    theNbSlices,
                  const int    theNbStacks)
  {
    init(theMajorRad, theMinorRad, theAngle1, theAngle2, M_PI * 2.0, theNbSlices, theNbStacks);
  }

  Prs3d_ToolTorus(const double theMajorRad,
                  const double theMinorRad,
                  const double theAngle1,
                  const double theAngle2,
                  const double theAngle,
                  const int    theNbSlices,
                  const int    theNbStacks)
  {
    init(theMajorRad, theMinorRad, theAngle1, theAngle2, theAngle, theNbSlices, theNbStacks);
  }

private:
  Standard_EXPORT void init(const double theMajorRad,
                            const double theMinorRad,
                            const double theAngle1,
                            const double theAngle2,
                            const double theAngle,
                            const int    theNbSlices,
                            const int    theNbStacks);

protected:
  Standard_EXPORT gp_Pnt Vertex(const double theU, const double theV) const override;

  Standard_EXPORT gp_Dir Normal(const double theU, const double theV) const override;

protected:
  double myMajorRadius;

  double myMinorRadius;
  double myAngle;
  double myVMin;
  double myVMax;
};
