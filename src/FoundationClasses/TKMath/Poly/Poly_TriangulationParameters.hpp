#pragma once


#include <Standard_Transient.hpp>
#include <Standard_DefineHandle.hpp>

//! Represents initial set of parameters triangulation is built for.
class Poly_TriangulationParameters : public Standard_Transient
{
public:
  //! Constructor.
  //! Initializes object with the given parameters.
  //! @param theDeflection linear deflection
  //! @param theAngle angular deflection
  //! @param theMinSize minimum size
  Poly_TriangulationParameters(const double theDeflection = -1.,
                               const double theAngle      = -1.,
                               const double theMinSize    = -1.)
      : myDeflection(theDeflection),
        myAngle(theAngle),
        myMinSize(theMinSize)
  {
  }

  //! Destructor.
  ~Poly_TriangulationParameters() override = default;

  //! Returns true if linear deflection is defined.
  bool HasDeflection() const { return !(myDeflection < 0.); }

  //! Returns true if angular deflection is defined.
  bool HasAngle() const { return !(myAngle < 0.); }

  //! Returns true if minimum size is defined.
  bool HasMinSize() const { return !(myMinSize < 0.); }

  //! Returns linear deflection or -1 if undefined.
  double Deflection() const { return myDeflection; }

  //! Returns angular deflection or -1 if undefined.
  double Angle() const { return myAngle; }

  //! Returns minimum size or -1 if undefined.
  double MinSize() const { return myMinSize; }

  DEFINE_STANDARD_RTTIEXT(Poly_TriangulationParameters, Standard_Transient)

private:
  double myDeflection;
  double myAngle;
  double myMinSize;
};

