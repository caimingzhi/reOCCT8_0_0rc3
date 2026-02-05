#include <Draw_Number.hpp>

#include <Draw_Display.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Number, Draw_Drawable3D)

//=================================================================================================

Draw_Number::Draw_Number(const double theV)
    : myValue(theV)
{
}

//=================================================================================================

void Draw_Number::DrawOn(Draw_Display&) const {}

//=================================================================================================

occ::handle<Draw_Drawable3D> Draw_Number::Copy() const
{
  occ::handle<Draw_Number> D = new Draw_Number(myValue);
  return D;
}

//=================================================================================================

void Draw_Number::Dump(Standard_OStream& S) const
{
  S << myValue;
}

//=================================================================================================

void Draw_Number::Save(Standard_OStream& theStream) const
{
  std::ios::fmtflags aFlags = theStream.flags();
  theStream.setf(std::ios::scientific);
  theStream.precision(15);
  theStream.width(30);
  theStream << myValue << "\n";
  theStream.setf(aFlags);
}

//=================================================================================================

occ::handle<Draw_Drawable3D> Draw_Number::Restore(Standard_IStream& theStream)
{
  double aVal = RealLast();
  theStream >> aVal;
  occ::handle<Draw_Number> aNumb = new Draw_Number(aVal);
  return aNumb;
}

//=================================================================================================

void Draw_Number::Whatis(Draw_Interpretor& S) const
{
  S << "numeric";
}
