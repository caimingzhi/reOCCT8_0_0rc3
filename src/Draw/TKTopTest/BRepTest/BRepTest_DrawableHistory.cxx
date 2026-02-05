#include <BRepTest_DrawableHistory.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepTest_DrawableHistory, Draw_Drawable3D)

//=================================================================================================

void BRepTest_DrawableHistory::DrawOn(Draw_Display&) const {}

//=================================================================================================

void BRepTest_DrawableHistory::Dump(Standard_OStream& theS) const
{
  myHistory->Dump(theS);
}

//=================================================================================================

void BRepTest_DrawableHistory::Whatis(Draw_Interpretor& theDI) const
{
  theDI << "history";
}
