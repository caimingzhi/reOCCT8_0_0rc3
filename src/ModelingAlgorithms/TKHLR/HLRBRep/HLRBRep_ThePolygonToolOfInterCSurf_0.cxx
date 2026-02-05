#include <HLRBRep_ThePolygonToolOfInterCSurf.hpp>

#include <Standard_OutOfRange.hpp>
#include <gp_Pnt.hpp>
#include <HLRBRep_ThePolygonOfInterCSurf.hpp>
#include <Bnd_Box.hpp>

#include <iostream>

void HLRBRep_ThePolygonToolOfInterCSurf::Dump(const HLRBRep_ThePolygonOfInterCSurf& L)
{
  static int num = 0;
  num++;
  int nbs = HLRBRep_ThePolygonToolOfInterCSurf::NbSegments(L);
  std::cout << "\npol2d " << num << " " << nbs << std::endl;
  std::cout << "Deflection " << HLRBRep_ThePolygonToolOfInterCSurf::DeflectionOverEstimation(L)
            << std::endl;

  for (int i = 1; i <= nbs; i++)
  {
    gp_Pnt P(HLRBRep_ThePolygonToolOfInterCSurf::BeginOfSeg(L, i));
    std::cout << "pnt " << num << " " << i << " " << P.X() << " " << P.Y() << " " << P.Z()
              << std::endl;
  }
  gp_Pnt PF(HLRBRep_ThePolygonToolOfInterCSurf::EndOfSeg(L, nbs));
  std::cout << "pnt " << num << " " << nbs << " " << PF.X() << " " << PF.Y() << " " << PF.Z()
            << std::endl;
}
