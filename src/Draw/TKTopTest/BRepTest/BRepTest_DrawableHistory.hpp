#pragma once

#include <Standard.hpp>

#include <BRepTools_History.hpp>

#include <Draw_Drawable3D.hpp>
#include <Draw_Interpretor.hpp>

#include <Standard_OStream.hpp>

//! Drawable History object.
//! Allows keeping histories of the algorithms in Draw.
class BRepTest_DrawableHistory : public Draw_Drawable3D
{
  DEFINE_STANDARD_RTTIEXT(BRepTest_DrawableHistory, Draw_Drawable3D)

public:
  //! Creation of the Drawable history.
  BRepTest_DrawableHistory(const occ::handle<BRepTools_History>& theHistory)
  {
    myHistory = theHistory;
  }

  //! Returns the history.
  const occ::handle<BRepTools_History>& History() const { return myHistory; }

  //! Drawing is not available.
  Standard_EXPORT void DrawOn(Draw_Display&) const override;

  //! Dumps the history.
  Standard_EXPORT void Dump(Standard_OStream& theS) const override;

  //! Prints the type of the history object.
  Standard_EXPORT void Whatis(Draw_Interpretor& theDI) const override;

private:
  occ::handle<BRepTools_History> myHistory; //!< Tool for tracking History of shape's modification
};
