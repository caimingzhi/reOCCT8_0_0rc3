

#include <StepVisual_DirectionCountSelect.hpp>

StepVisual_DirectionCountSelect::StepVisual_DirectionCountSelect()
    : theUDirectionCount(0),
      theVDirectionCount(0),
      theTypeOfContent(0)
{
}

void StepVisual_DirectionCountSelect::SetTypeOfContent(const int aType)
{
  theTypeOfContent = aType;
}

int StepVisual_DirectionCountSelect::TypeOfContent() const
{
  return theTypeOfContent;
}

int StepVisual_DirectionCountSelect::UDirectionCount() const
{
  return theUDirectionCount;
}

void StepVisual_DirectionCountSelect::SetUDirectionCount(const int aUDirectionCount)
{
  theUDirectionCount = aUDirectionCount;
  theTypeOfContent   = 1;
}

int StepVisual_DirectionCountSelect::VDirectionCount() const
{
  return theUDirectionCount;
}

void StepVisual_DirectionCountSelect::SetVDirectionCount(const int aVDirectionCount)
{
  theVDirectionCount = aVDirectionCount;
  theTypeOfContent   = 2;
}
