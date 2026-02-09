

#include <Vrml_Cone.hpp>

Vrml_Cone::Vrml_Cone(const Vrml_ConeParts aParts, const double aBottomRadius, const double aHeight)
{
  myParts        = aParts;
  myBottomRadius = aBottomRadius;
  myHeight       = aHeight;
}

void Vrml_Cone::SetParts(const Vrml_ConeParts aParts)
{
  myParts = aParts;
}

Vrml_ConeParts Vrml_Cone::Parts() const
{
  return myParts;
}

void Vrml_Cone::SetBottomRadius(const double aBottomRadius)
{
  myBottomRadius = aBottomRadius;
}

double Vrml_Cone::BottomRadius() const
{
  return myBottomRadius;
}

void Vrml_Cone::SetHeight(const double aHeight)
{
  myHeight = aHeight;
}

double Vrml_Cone::Height() const
{
  return myHeight;
}

Standard_OStream& Vrml_Cone::Print(Standard_OStream& anOStream) const
{
  anOStream << "Cone {\n";

  switch (myParts)
  {
    case Vrml_ConeALL:
      break;
    case Vrml_ConeSIDES:
      anOStream << "    parts\t\tSIDES\n";
      break;
    case Vrml_ConeBOTTOM:
      anOStream << "    parts\t\tBOTTOM\n";
      break;
  }

  if (std::abs(myBottomRadius - 1) > 0.0001)
  {
    anOStream << "    bottomRadius\t";
    anOStream << myBottomRadius << "\n";
  }

  if (std::abs(myHeight - 2) > 0.0001)
  {
    anOStream << "    height\t\t";
    anOStream << myHeight << "\n";
  }

  anOStream << "}\n";
  return anOStream;
}
