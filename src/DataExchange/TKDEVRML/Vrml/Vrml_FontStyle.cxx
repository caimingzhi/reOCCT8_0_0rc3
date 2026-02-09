

#include <Vrml_FontStyle.hpp>

Vrml_FontStyle::Vrml_FontStyle(const double               aSize,
                               const Vrml_FontStyleFamily aFamily,
                               const Vrml_FontStyleStyle  aStyle)
{
  mySize   = aSize;
  myFamily = aFamily;
  myStyle  = aStyle;
}

void Vrml_FontStyle::SetSize(const double aSize)
{
  mySize = aSize;
}

double Vrml_FontStyle::Size() const
{
  return mySize;
}

void Vrml_FontStyle::SetFamily(const Vrml_FontStyleFamily aFamily)
{
  myFamily = aFamily;
}

Vrml_FontStyleFamily Vrml_FontStyle::Family() const
{
  return myFamily;
}

void Vrml_FontStyle::SetStyle(const Vrml_FontStyleStyle aStyle)
{
  myStyle = aStyle;
}

Vrml_FontStyleStyle Vrml_FontStyle::Style() const
{
  return myStyle;
}

Standard_OStream& Vrml_FontStyle::Print(Standard_OStream& anOStream) const
{
  anOStream << "FontStyle {\n";

  if (std::abs(mySize - 10) > 0.0001)
  {
    anOStream << "    size\t";
    anOStream << mySize << "\n";
  }

  switch (myFamily)
  {
    case Vrml_SERIF:
      break;
    case Vrml_SANS:
      anOStream << "    family\tSANS\n";
      break;
    case Vrml_TYPEWRITER:
      anOStream << "    family\tTYPEWRITER\n";
      break;
  }

  switch (myStyle)
  {
    case Vrml_NONE:
      break;
    case Vrml_BOLD:
      anOStream << "    style\tBOLD\n";
      break;
    case Vrml_ITALIC:
      anOStream << "    style\tITALIC\n";
      break;
  }

  anOStream << "}\n";
  return anOStream;
}
