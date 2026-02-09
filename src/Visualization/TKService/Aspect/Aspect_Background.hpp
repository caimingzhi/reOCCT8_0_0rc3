#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Quantity_Color.hpp>

class Aspect_Background
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Aspect_Background();

  Standard_EXPORT Aspect_Background(const Quantity_Color& AColor);

  Standard_EXPORT void SetColor(const Quantity_Color& AColor);

  Standard_EXPORT Quantity_Color Color() const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  Quantity_Color MyColor;
};
