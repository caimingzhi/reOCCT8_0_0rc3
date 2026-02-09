

#include <Vrml_Cylinder.hpp>

Vrml_Cylinder::Vrml_Cylinder(const Vrml_CylinderParts aParts,
                             const double             aRadius,
                             const double             aHeight)
{
  myParts  = aParts;
  myRadius = aRadius;
  myHeight = aHeight;
}

void Vrml_Cylinder::SetParts(const Vrml_CylinderParts aParts)
{
  myParts = aParts;
}

Vrml_CylinderParts Vrml_Cylinder::Parts() const
{
  return myParts;
}

void Vrml_Cylinder::SetRadius(const double aRadius)
{
  myRadius = aRadius;
}

double Vrml_Cylinder::Radius() const
{
  return myRadius;
}

void Vrml_Cylinder::SetHeight(const double aHeight)
{
  myHeight = aHeight;
}

double Vrml_Cylinder::Height() const
{
  return myHeight;
}

Standard_OStream& Vrml_Cylinder::Print(Standard_OStream& anOStream) const
{
  anOStream << "Cylinder {\n";

  switch (myParts)
  {
    case Vrml_CylinderALL:
      break;
    case Vrml_CylinderSIDES:
      anOStream << "    parts\tSIDES\n";
      break;
    case Vrml_CylinderTOP:
      anOStream << "    parts\tTOP\n";
      break;
    case Vrml_CylinderBOTTOM:
      anOStream << "    parts\tBOTTOM\n";
      break;
  }

  if (std::abs(myRadius - 1) > 0.0001)
  {
    anOStream << "    radius\t";
    anOStream << myRadius << "\n";
  }

  if (std::abs(myHeight - 2) > 0.0001)
  {
    anOStream << "    height\t";
    anOStream << myHeight << "\n";
  }

  anOStream << "}\n";
  return anOStream;
}
