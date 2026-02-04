#pragma once


#include <Prs3d_ToolQuadric.hpp>

//! Standard presentation algorithm that outputs graphical primitives for torus surface.
class Prs3d_ToolTorus : public Prs3d_ToolQuadric
{
public:
  //! Generate primitives for 3D quadric surface (complete torus).
  //! @param[in] theMajorRad  distance from the center of the pipe to the center of the torus
  //! @param[in] theMinorRad  radius of the pipe
  //! @param[in] theNbSlices  number of slices within U parameter
  //! @param[in] theNbStacks  number of stacks within V parameter
  //! @param[in] theTrsf      optional transformation to apply
  //! @return generated triangulation
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

  //! Generate primitives for 3D quadric surface (torus segment).
  //! @param[in] theMajorRad  distance from the center of the pipe to the center of the torus
  //! @param[in] theMinorRad  radius of the pipe
  //! @param[in] theAngle     angle to create a torus pipe segment
  //! @param[in] theNbSlices  number of slices within U parameter
  //! @param[in] theNbStacks  number of stacks within V parameter
  //! @param[in] theTrsf      optional transformation to apply
  //! @return generated triangulation
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

  //! Generate primitives for 3D quadric surface (torus ring segment).
  //! @param[in] theMajorRad  distance from the center of the pipe to the center of the torus
  //! @param[in] theMinorRad  radius of the pipe
  //! @param[in] theAngle1    first  angle to create a torus ring segment
  //! @param[in] theAngle2    second angle to create a torus ring segment
  //! @param[in] theNbSlices  number of slices within U parameter
  //! @param[in] theNbStacks  number of stacks within V parameter
  //! @param[in] theTrsf      optional transformation to apply
  //! @return generated triangulation
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

  //! Generate primitives for 3D quadric surface (segment of the torus ring segment).
  //! @param[in] theMajorRad  distance from the center of the pipe to the center of the torus
  //! @param[in] theMinorRad  radius of the pipe
  //! @param[in] theAngle1    first  angle to create a torus ring segment
  //! @param[in] theAngle2    second angle to create a torus ring segment
  //! @param[in] theAngle     angle to create a torus pipe segment
  //! @param[in] theNbSlices  number of slices within U parameter
  //! @param[in] theNbStacks  number of stacks within V parameter
  //! @param[in] theTrsf      optional transformation to apply
  //! @return generated triangulation
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfTriangles> Create(const double   theMajorRad,
                                                                        const double   theMinorRad,
                                                                        const double   theAngle1,
                                                                        const double   theAngle2,
                                                                        const double   theAngle,
                                                                        const int      theNbSlices,
                                                                        const int      theNbStacks,
                                                                        const gp_Trsf& theTrsf);

public:
  //! Initializes the algorithm creating a complete torus.
  //! @param[in] theMajorRad  distance from the center of the pipe to the center of the torus
  //! @param[in] theMinorRad  radius of the pipe
  //! @param[in] theNbSlices  number of slices within U parameter
  //! @param[in] theNbStacks  number of stacks within V parameter
  Prs3d_ToolTorus(const double theMajorRad,
                  const double theMinorRad,
                  const int    theNbSlices,
                  const int    theNbStacks)
  {
    init(theMajorRad, theMinorRad, 0.0, M_PI * 2.0, M_PI * 2.0, theNbSlices, theNbStacks);
  }

  //! Initializes the algorithm creating a torus pipe segment.
  //! @param[in] theMajorRad  distance from the center of the pipe to the center of the torus
  //! @param[in] theMinorRad  radius of the pipe
  //! @param[in] theAngle     angle to create a torus pipe segment
  //! @param[in] theNbSlices  number of slices within U parameter
  //! @param[in] theNbStacks  number of stacks within V parameter
  Prs3d_ToolTorus(const double theMajorRad,
                  const double theMinorRad,
                  const double theAngle,
                  const int    theNbSlices,
                  const int    theNbStacks)
  {
    init(theMajorRad, theMinorRad, 0.0, M_PI * 2.0, theAngle, theNbSlices, theNbStacks);
  }

  //! Initializes the algorithm creating a torus ring segment.
  //! @param[in] theMajorRad  distance from the center of the pipe to the center of the torus
  //! @param[in] theMinorRad  radius of the pipe
  //! @param[in] theAngle1    first  angle to create a torus ring segment
  //! @param[in] theAngle2    second angle to create a torus ring segment
  //! @param[in] theNbSlices  number of slices within U parameter
  //! @param[in] theNbStacks  number of stacks within V parameter
  Prs3d_ToolTorus(const double theMajorRad,
                  const double theMinorRad,
                  const double theAngle1,
                  const double theAngle2,
                  const int    theNbSlices,
                  const int    theNbStacks)
  {
    init(theMajorRad, theMinorRad, theAngle1, theAngle2, M_PI * 2.0, theNbSlices, theNbStacks);
  }

  //! Initializes the algorithm creating a torus ring segment.
  //! @param[in] theMajorRad  distance from the center of the pipe to the center of the torus
  //! @param[in] theMinorRad  radius of the pipe
  //! @param[in] theAngle1    first  angle to create a torus ring segment
  //! @param[in] theAngle2    second angle to create a torus ring segment
  //! @param[in] theAngle     angle to create a torus pipe segment
  //! @param[in] theNbSlices  number of slices within U parameter
  //! @param[in] theNbStacks  number of stacks within V parameter
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
  //! Initialisation
  //! @param[in] theMajorRad  distance from the center of the pipe to the center of the torus
  //! @param[in] theMinorRad  radius of the pipe
  //! @param[in] theAngle1    first  angle to create a torus ring segment
  //! @param[in] theAngle2    second angle to create a torus ring segment
  //! @param[in] theAngle     angle to create a torus pipe segment
  //! @param[in] theNbSlices  number of slices within U parameter
  //! @param[in] theNbStacks  number of stacks within V parameter
  Standard_EXPORT void init(const double theMajorRad,
                            const double theMinorRad,
                            const double theAngle1,
                            const double theAngle2,
                            const double theAngle,
                            const int    theNbSlices,
                            const int    theNbStacks);

protected:
  //! Computes vertex at given parameter location of the surface.
  Standard_EXPORT gp_Pnt Vertex(const double theU, const double theV) const override;

  //! Computes normal at given parameter location of the surface.
  Standard_EXPORT gp_Dir Normal(const double theU, const double theV) const override;

protected:
  // clang-format off
  double myMajorRadius; //!< distance from the center of the pipe to the center of the torus
  // clang-format on
  double myMinorRadius; //!< radius of the pipe
  double myAngle;       //!< angle to create a torus pipe segment
  double myVMin;        //!< first angle to create a torus ring segment
  double myVMax;        //!< second angle to create a torus ring segment
};

