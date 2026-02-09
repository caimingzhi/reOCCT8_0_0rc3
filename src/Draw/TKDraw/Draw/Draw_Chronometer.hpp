#pragma once

#include <Draw_Drawable3D.hpp>
#include <OSD_Timer.hpp>

class Draw_Chronometer : public Draw_Drawable3D
{
  DEFINE_STANDARD_RTTIEXT(Draw_Chronometer, Draw_Drawable3D)
public:
  Standard_EXPORT Draw_Chronometer();

  OSD_Timer& Timer() { return myTimer; }

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

private:
  OSD_Timer myTimer;
};
