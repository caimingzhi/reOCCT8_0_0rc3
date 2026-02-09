

#include <Vrml_Sphere.hpp>

Vrml_Sphere::Vrml_Sphere(const double aRadius)
{
  myRadius = aRadius;
}

void Vrml_Sphere::SetRadius(const double aRadius)
{
  myRadius = aRadius;
}

double Vrml_Sphere::Radius() const
{
  return myRadius;
}

Standard_OStream& Vrml_Sphere::Print(Standard_OStream& anOStream) const
{
  anOStream << "Sphere {\n";

  if (std::abs(myRadius - 1) > 0.0001)
  {
    anOStream << "    radius\t";
    anOStream << myRadius << "\n";
  }

  anOStream << "}\n";
  return anOStream;
}
