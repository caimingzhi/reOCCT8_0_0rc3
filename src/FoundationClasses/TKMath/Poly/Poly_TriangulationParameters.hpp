#pragma once

#include <Standard_Transient.hpp>
#include <Standard_DefineHandle.hpp>

class Poly_TriangulationParameters : public Standard_Transient
{
public:
  Poly_TriangulationParameters(const double theDeflection = -1.,
                               const double theAngle      = -1.,
                               const double theMinSize    = -1.)
      : myDeflection(theDeflection),
        myAngle(theAngle),
        myMinSize(theMinSize)
  {
  }

  ~Poly_TriangulationParameters() override = default;

  bool HasDeflection() const { return !(myDeflection < 0.); }

  bool HasAngle() const { return !(myAngle < 0.); }

  bool HasMinSize() const { return !(myMinSize < 0.); }

  double Deflection() const { return myDeflection; }

  double Angle() const { return myAngle; }

  double MinSize() const { return myMinSize; }

  DEFINE_STANDARD_RTTIEXT(Poly_TriangulationParameters, Standard_Transient)

private:
  double myDeflection;
  double myAngle;
  double myMinSize;
};
