

#include <Standard_Type.hpp>
#include <Vrml_Coordinate3.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Vrml_Coordinate3, Standard_Transient)

Vrml_Coordinate3::Vrml_Coordinate3(const occ::handle<NCollection_HArray1<gp_Vec>>& aPoint)
{
  myPoint = aPoint;
}

Vrml_Coordinate3::Vrml_Coordinate3()
{
  gp_Vec Tmp_Vec;

  myPoint = new NCollection_HArray1<gp_Vec>(1, 1);
  Tmp_Vec.SetX(0);
  Tmp_Vec.SetY(0);
  Tmp_Vec.SetZ(0);
  myPoint->SetValue(1, Tmp_Vec);
}

void Vrml_Coordinate3::SetPoint(const occ::handle<NCollection_HArray1<gp_Vec>>& aPoint)
{
  myPoint = aPoint;
}

occ::handle<NCollection_HArray1<gp_Vec>> Vrml_Coordinate3::Point() const
{
  return myPoint;
}

Standard_OStream& Vrml_Coordinate3::Print(Standard_OStream& anOStream) const
{
  int i;

  anOStream << "Coordinate3 {\n";

  i = myPoint->Lower();
  if (myPoint->Length() == 1 && std::abs(myPoint->Value(i).X() - 0) < 0.0001
      && std::abs(myPoint->Value(i).Y() - 0) < 0.0001
      && std::abs(myPoint->Value(i).Z() - 0) < 0.0001)
  {
    anOStream << "}\n";
    return anOStream;
  }
  else
  {
    anOStream << "    point [\n\t";
    for (i = myPoint->Lower(); i <= myPoint->Upper(); i++)
    {
      anOStream << myPoint->Value(i).X() << ' ' << myPoint->Value(i).Y() << ' '
                << myPoint->Value(i).Z();
      if (i < myPoint->Length())
        anOStream << ",\n\t";
    }
    anOStream << " ]\n";
  }
  anOStream << "}\n";

  return anOStream;
}
