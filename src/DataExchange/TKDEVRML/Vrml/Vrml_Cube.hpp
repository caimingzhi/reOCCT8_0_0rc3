#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>

class Vrml_Cube
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Cube(const double aWidth  = 2,
                            const double aHeight = 2,
                            const double aDepth  = 2);

  Standard_EXPORT void SetWidth(const double aWidth);

  Standard_EXPORT double Width() const;

  Standard_EXPORT void SetHeight(const double aHeight);

  Standard_EXPORT double Height() const;

  Standard_EXPORT void SetDepth(const double aDepth);

  Standard_EXPORT double Depth() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  double myWidth;
  double myHeight;
  double myDepth;
};
