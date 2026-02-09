

#include <Standard_Type.hpp>
#include <Vrml_TextureCoordinate2.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Vrml_TextureCoordinate2, Standard_Transient)

Vrml_TextureCoordinate2::Vrml_TextureCoordinate2()
{
  gp_Vec2d tmpVec(0, 0);
  myPoint = new NCollection_HArray1<gp_Vec2d>(1, 1, tmpVec);
}

Vrml_TextureCoordinate2::Vrml_TextureCoordinate2(
  const occ::handle<NCollection_HArray1<gp_Vec2d>>& aPoint)
{
  myPoint = aPoint;
}

void Vrml_TextureCoordinate2::SetPoint(const occ::handle<NCollection_HArray1<gp_Vec2d>>& aPoint)
{
  myPoint = aPoint;
}

occ::handle<NCollection_HArray1<gp_Vec2d>> Vrml_TextureCoordinate2::Point() const
{
  return myPoint;
}

Standard_OStream& Vrml_TextureCoordinate2::Print(Standard_OStream& anOStream) const
{
  int i;
  anOStream << "TextureCoordinate2 {\n";

  if (myPoint->Length() != 1 || std::abs(myPoint->Value(myPoint->Lower()).X() - 0) > 0.0001
      || std::abs(myPoint->Value(myPoint->Lower()).Y() - 0) > 0.0001)
  {
    anOStream << "    point [\n\t";
    for (i = myPoint->Lower(); i <= myPoint->Upper(); i++)
    {
      anOStream << myPoint->Value(i).X() << " " << myPoint->Value(i).Y();

      if (i < myPoint->Length())
        anOStream << ",\n\t";
    }
    anOStream << " ]\n";
  }
  anOStream << "}\n";
  return anOStream;
}
