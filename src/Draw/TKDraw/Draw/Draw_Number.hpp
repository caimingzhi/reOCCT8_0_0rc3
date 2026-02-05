#pragma once

#include <Draw_Drawable3D.hpp>

//! To store numbers in variables.
class Draw_Number : public Draw_Drawable3D
{
  DEFINE_STANDARD_RTTIEXT(Draw_Number, Draw_Drawable3D)
  Draw_Drawable3D_FACTORY
public:
  Standard_EXPORT Draw_Number(const double theV);

  double Value() const { return myValue; }

  void Value(const double theV) { myValue = theV; }

  //! Does nothing,
  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  //! Returns TRUE if object can be displayed.
  bool IsDisplayable() const override { return false; }

  //! For variable copy.
  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  //! For variable dump.
  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  //! Save drawable into stream.
  Standard_EXPORT void Save(Standard_OStream& theStream) const override;

  //! For variable whatis command. Set as a result the type of the variable.
  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

private:
  double myValue;
};
