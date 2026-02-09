#include <IntPatch_Polygo.hpp>

IntPatch_Polygo::IntPatch_Polygo(const double theError)
    : myError(theError)
{
}

void IntPatch_Polygo::Dump() const
{
  static int num = 0;
  num++;
  std::cout << "\n#------------- D u m p     B o x 2 d   (" << num << ")" << std::endl;
  Bounding().Dump();
  std::cout << "\n#-----------------------------------------------" << std::endl;

  const int nbs = NbSegments();
  std::cout << "\npol2d " << num << " " << nbs << " ";
  std::cout << DeflectionOverEstimation() << std::endl;

  gp_Pnt2d P, PF;
  for (int i = 1; i <= nbs; i++)
  {
    Segment(i, P, PF);
    std::cout << "pnt2d " << num << "  " << P.X() << " " << P.Y() << std::endl;
  }
  std::cout << "pnt2d " << num << "  " << PF.X() << " " << PF.Y() << std::endl;
}
