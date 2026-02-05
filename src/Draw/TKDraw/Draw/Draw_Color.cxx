#include <Draw_Color.hpp>

Draw_Color::Draw_Color()
    : myKind(Draw_blanc)
{
}

Draw_Color::Draw_Color(const Draw_ColorKind c)
    : myKind(c)
{
}

Draw_ColorKind Draw_Color::ID() const
{
  return myKind;
}
