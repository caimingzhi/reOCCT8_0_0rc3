

#include <Standard_Type.hpp>
#include <Vrml_AsciiText.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Vrml_AsciiText, Standard_Transient)

Vrml_AsciiText::Vrml_AsciiText()
{
  TCollection_AsciiString tmpS("");
  myString = new NCollection_HArray1<TCollection_AsciiString>(1, 1, tmpS);

  mySpacing       = 1;
  myJustification = Vrml_LEFT;
  myWidth         = 0;
}

Vrml_AsciiText::Vrml_AsciiText(
  const occ::handle<NCollection_HArray1<TCollection_AsciiString>>& aString,
  const double                                                     aSpacing,
  const Vrml_AsciiTextJustification                                aJustification,
  const double                                                     aWidth)
{
  myString        = aString;
  mySpacing       = aSpacing;
  myJustification = aJustification;
  myWidth         = aWidth;
}

void Vrml_AsciiText::SetString(
  const occ::handle<NCollection_HArray1<TCollection_AsciiString>>& aString)
{
  myString = aString;
}

occ::handle<NCollection_HArray1<TCollection_AsciiString>> Vrml_AsciiText::String() const
{
  return myString;
}

void Vrml_AsciiText::SetSpacing(const double aSpacing)
{
  mySpacing = aSpacing;
}

double Vrml_AsciiText::Spacing() const
{
  return mySpacing;
}

void Vrml_AsciiText::SetJustification(const Vrml_AsciiTextJustification aJustification)
{
  myJustification = aJustification;
}

Vrml_AsciiTextJustification Vrml_AsciiText::Justification() const
{
  return myJustification;
}

void Vrml_AsciiText::SetWidth(const double aWidth)
{
  myWidth = aWidth;
}

double Vrml_AsciiText::Width() const
{
  return myWidth;
}

Standard_OStream& Vrml_AsciiText::Print(Standard_OStream& anOStream) const
{
  int i;

  anOStream << "AsciiText {\n";

  i = myString->Lower();

  if (myString->Length() != 1 || myString->Value(i) != "")
  {
    anOStream << "    string [\n\t";

    for (i = myString->Lower(); i <= myString->Upper(); i++)
    {
      anOStream << '"' << myString->Value(i) << '"';
      if (i < myString->Length())
        anOStream << ",\n\t";
    }
    anOStream << " ]\n";
  }

  if (std::abs(mySpacing - 1) > 0.0001)
  {
    anOStream << "    spacing\t\t";
    anOStream << mySpacing << "\n";
  }

  switch (myJustification)
  {
    case Vrml_LEFT:
      break;
    case Vrml_CENTER:
      anOStream << "    justification\tCENTER\n";
      break;
    case Vrml_RIGHT:
      anOStream << "    justification\tRIGHT\n";
      break;
  }

  if (std::abs(myWidth - 0) > 0.0001)
  {
    anOStream << "    width\t\t";
    anOStream << myWidth << "\n";
  }

  anOStream << "}\n";
  return anOStream;
}
