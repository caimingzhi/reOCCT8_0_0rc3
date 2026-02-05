#include <Draw_Display.hpp>
#include <DrawDim_Dimension.hpp>
#include <gp_Pnt.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawDim_Dimension, Draw_Drawable3D)

//=================================================================================================

DrawDim_Dimension::DrawDim_Dimension()
    : is_valued(false),
      myValue(0.0),
      myTextColor(Draw_blanc)
{
}

//=================================================================================================

void DrawDim_Dimension::SetValue(const double avalue)
{
  is_valued = true;
  myValue   = avalue;
}

//=================================================================================================

double DrawDim_Dimension::GetValue() const
{
  if (!is_valued)
    throw Standard_DomainError();
  return myValue;
}

//=================================================================================================

bool DrawDim_Dimension::IsValued() const
{
  return is_valued;
}

//=================================================================================================

Draw_Color DrawDim_Dimension::TextColor() const
{
  return myTextColor;
}

//=================================================================================================

void DrawDim_Dimension::TextColor(const Draw_Color& C)
{
  myTextColor = C;
}

//=================================================================================================

void DrawDim_Dimension::DrawText(const gp_Pnt& P, Draw_Display& D) const
{
  TCollection_AsciiString t = Name();
  if (is_valued)
  {
    t += "=";
    int l = t.Length();
    t += myValue;
    for (int i = l; i <= t.Length(); i++)
    {
      if (t.Value(i) == '.')
      {
        t.Trunc(i + 2);
        break;
      }
    }
  }

  D.SetColor(myTextColor);
  D.DrawString(P, t.ToCString());
}
