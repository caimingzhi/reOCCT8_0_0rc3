#pragma once

#include <Standard.hpp>

#include <BRepTools_History.hpp>

#include <Draw_Drawable3D.hpp>
#include <Draw_Interpretor.hpp>

#include <Standard_OStream.hpp>

class BRepTest_DrawableHistory : public Draw_Drawable3D
{
  DEFINE_STANDARD_RTTIEXT(BRepTest_DrawableHistory, Draw_Drawable3D)

public:
  BRepTest_DrawableHistory(const occ::handle<BRepTools_History>& theHistory)
  {
    myHistory = theHistory;
  }

  const occ::handle<BRepTools_History>& History() const { return myHistory; }

  Standard_EXPORT void DrawOn(Draw_Display&) const override;

  Standard_EXPORT void Dump(Standard_OStream& theS) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& theDI) const override;

private:
  occ::handle<BRepTools_History> myHistory;
};
