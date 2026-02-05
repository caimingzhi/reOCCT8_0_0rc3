#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepVisual_DirectionCountSelect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_DirectionCountSelect();

  Standard_EXPORT void SetTypeOfContent(const int aTypeOfContent);

  Standard_EXPORT int TypeOfContent() const;

  Standard_EXPORT int UDirectionCount() const;

  Standard_EXPORT void SetUDirectionCount(const int aUDirectionCount);

  Standard_EXPORT int VDirectionCount() const;

  Standard_EXPORT void SetVDirectionCount(const int aUDirectionCount);

private:
  int theUDirectionCount;
  int theVDirectionCount;
  int theTypeOfContent;
};
