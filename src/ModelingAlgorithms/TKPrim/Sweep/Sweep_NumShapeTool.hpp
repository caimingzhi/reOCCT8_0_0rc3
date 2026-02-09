#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Sweep_NumShape.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>

class Sweep_NumShapeTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Sweep_NumShapeTool(const Sweep_NumShape& aShape);

  Standard_EXPORT int NbShapes() const;

  Standard_EXPORT int Index(const Sweep_NumShape& aShape) const;

  Standard_EXPORT Sweep_NumShape Shape(const int anIndex) const;

  Standard_EXPORT TopAbs_ShapeEnum Type(const Sweep_NumShape& aShape) const;

  Standard_EXPORT TopAbs_Orientation Orientation(const Sweep_NumShape& aShape) const;

  Standard_EXPORT bool HasFirstVertex() const;

  Standard_EXPORT bool HasLastVertex() const;

  Standard_EXPORT Sweep_NumShape FirstVertex() const;

  Standard_EXPORT Sweep_NumShape LastVertex() const;

private:
  Sweep_NumShape myNumShape;
};
