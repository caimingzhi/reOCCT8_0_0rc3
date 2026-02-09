#pragma once

#include <Graphic3d_Aspects.hpp>

class Graphic3d_AspectFillArea3d : public Graphic3d_Aspects
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_AspectFillArea3d, Graphic3d_Aspects)
public:
  Standard_EXPORT Graphic3d_AspectFillArea3d();

  Standard_EXPORT Graphic3d_AspectFillArea3d(const Aspect_InteriorStyle      theInterior,
                                             const Quantity_Color&           theInteriorColor,
                                             const Quantity_Color&           theEdgeColor,
                                             const Aspect_TypeOfLine         theEdgeLineType,
                                             const double                    theEdgeWidth,
                                             const Graphic3d_MaterialAspect& theFrontMaterial,
                                             const Graphic3d_MaterialAspect& theBackMaterial);

public:
  Standard_DEPRECATED("Deprecated method, ToDrawEdges() should be used instead")

  bool Edge() const { return ToDrawEdges(); }
};
