#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

enum Vrml_SeparatorRenderCulling
{
  Vrml_OFF,
  Vrml_ON,
  Vrml_AUTO
};

#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>

class Vrml_Separator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Separator(const Vrml_SeparatorRenderCulling aRenderCulling);

  Standard_EXPORT Vrml_Separator();

  Standard_EXPORT void SetRenderCulling(const Vrml_SeparatorRenderCulling aRenderCulling);

  Standard_EXPORT Vrml_SeparatorRenderCulling RenderCulling() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream);

private:
  Vrml_SeparatorRenderCulling myRenderCulling;
  bool                        myFlagPrint;
};
