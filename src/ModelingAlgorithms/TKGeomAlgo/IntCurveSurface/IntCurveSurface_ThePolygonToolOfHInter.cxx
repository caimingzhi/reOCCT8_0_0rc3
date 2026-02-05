#include <IntCurveSurface_ThePolygonToolOfHInter.hpp>

#include <Standard_OutOfRange.hpp>
#include <gp_Pnt.hpp>
#include <IntCurveSurface_ThePolygonOfHInter.hpp>
#include <Bnd_Box.hpp>

#include <iostream>

void IntCurveSurface_ThePolygonToolOfHInter::Dump(const IntCurveSurface_ThePolygonOfHInter& L)
{
  static int num = 0;
  num++;
  int nbs = IntCurveSurface_ThePolygonToolOfHInter::NbSegments(L);
  std::cout << "\npol2d " << num << " " << nbs << std::endl;
  std::cout << "Deflection " << IntCurveSurface_ThePolygonToolOfHInter::DeflectionOverEstimation(L)
            << std::endl;

  for (int i = 1; i <= nbs; i++)
  {
    gp_Pnt P(IntCurveSurface_ThePolygonToolOfHInter::BeginOfSeg(L, i));
    std::cout << "pnt " << num << " " << i << " " << P.X() << " " << P.Y() << " " << P.Z()
              << std::endl;
  }
  gp_Pnt PF(IntCurveSurface_ThePolygonToolOfHInter::EndOfSeg(L, nbs));
  std::cout << "pnt " << num << " " << nbs << " " << PF.X() << " " << PF.Y() << " " << PF.Z()
            << std::endl;
}
