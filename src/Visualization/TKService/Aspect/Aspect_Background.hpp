#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Quantity_Color.hpp>

//! This class allows the definition of
//! a window background.
class Aspect_Background
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a window background.
  //! Default color : NOC_MATRAGRAY.
  Standard_EXPORT Aspect_Background();

  //! Creates a window background with the colour <AColor>.
  Standard_EXPORT Aspect_Background(const Quantity_Color& AColor);

  //! Modifies the colour of the window background <me>.
  Standard_EXPORT void SetColor(const Quantity_Color& AColor);

  //! Returns the colour of the window background <me>.
  Standard_EXPORT Quantity_Color Color() const;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  Quantity_Color MyColor;
};
