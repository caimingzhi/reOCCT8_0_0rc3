#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_ColorKind.hpp>

class Draw_Color
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Draw_Color();

  Standard_EXPORT Draw_Color(const Draw_ColorKind c);

  Standard_EXPORT Draw_ColorKind ID() const;

private:
  Draw_ColorKind myKind;
};

