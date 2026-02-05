#include <Draw_Chronometer.hpp>

#include <Draw_Display.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Chronometer, Draw_Drawable3D)

//=================================================================================================

Draw_Chronometer::Draw_Chronometer() = default;

//=================================================================================================

void Draw_Chronometer::DrawOn(Draw_Display&) const {}

//=================================================================================================

occ::handle<Draw_Drawable3D> Draw_Chronometer::Copy() const
{
  occ::handle<Draw_Chronometer> C = new Draw_Chronometer();
  return C;
}

//=================================================================================================

void Draw_Chronometer::Dump(Standard_OStream& S) const
{
  S << "Chronometer, ";
  myTimer.Show(S);
}

//=================================================================================================

void Draw_Chronometer::Whatis(Draw_Interpretor& i) const
{
  i << "chronometer";
}
