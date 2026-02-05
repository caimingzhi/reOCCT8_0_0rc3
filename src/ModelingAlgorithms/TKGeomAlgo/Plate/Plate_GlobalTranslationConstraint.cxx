#include <Plate_GlobalTranslationConstraint.hpp>
#include <Plate_LinearXYZConstraint.hpp>

Plate_GlobalTranslationConstraint::Plate_GlobalTranslationConstraint(
  const NCollection_Sequence<gp_XY>& SOfXY)
    : myLXYZC(SOfXY.Length() - 1, SOfXY.Length())
{
  int i;
  for (i = 1; i <= SOfXY.Length(); i++)
  {
    myLXYZC.SetPPC(i, Plate_PinpointConstraint(SOfXY(i), gp_XYZ(0., 0., 0.), 0, 0));
  }
  for (i = 1; i <= SOfXY.Length() - 1; i++)
  {
    myLXYZC.SetCoeff(i, 1, -1.);
    for (int j = 2; j <= SOfXY.Length(); j++)
    {
      if (j == (i + 1))
        myLXYZC.SetCoeff(i, j, 1.);
      else
        myLXYZC.SetCoeff(i, j, 0.);
    }
  }
}
