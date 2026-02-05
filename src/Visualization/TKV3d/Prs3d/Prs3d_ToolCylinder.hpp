#pragma once

#include <Prs3d_ToolQuadric.hpp>

//! Standard presentation algorithm that outputs graphical primitives for cylindrical surface.
class Prs3d_ToolCylinder : public Prs3d_ToolQuadric
{
public:
  //! Generate primitives for 3D quadric surface and return a filled array.
  //! @param[in] theBottomRad  cylinder bottom radius
  //! @param[in] theTopRad     cylinder top radius
  //! @param[in] theHeight     cylinder height
  //! @param[in] theNbSlices   number of slices within U parameter
  //! @param[in] theNbStacks   number of stacks within V parameter
  //! @param[in] theTrsf       optional transformation to apply
  //! @return generated triangulation
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfTriangles> Create(const double   theBottomRad,
                                                                        const double   theTopRad,
                                                                        const double   theHeight,
                                                                        const int      theNbSlices,
                                                                        const int      theNbStacks,
                                                                        const gp_Trsf& theTrsf);

public:
  //! Initializes the algorithm creating a cylinder.
  //! @param[in] theBottomRad  cylinder bottom radius
  //! @param[in] theTopRad     cylinder top radius
  //! @param[in] theHeight     cylinder height
  //! @param[in] theNbSlices   number of slices within U parameter
  //! @param[in] theNbStacks   number of stacks within V parameter
  Standard_EXPORT Prs3d_ToolCylinder(const double theBottomRad,
                                     const double theTopRad,
                                     const double theHeight,
                                     const int    theNbSlices,
                                     const int    theNbStacks);

protected:
  //! Computes vertex at given parameter location of the surface.
  Standard_EXPORT gp_Pnt Vertex(const double theU, const double theV) const override;

  //! Computes normal at given parameter location of the surface.
  Standard_EXPORT gp_Dir Normal(const double theU, const double theV) const override;

protected:
  double myBottomRadius; //!< cylinder bottom radius
  double myTopRadius;    //!< cylinder top radius
  double myHeight;       //!< cylinder height
};
