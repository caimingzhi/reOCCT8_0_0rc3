#include <TopOpeBRepTool.hpp>

//=================================================================================================

Standard_OStream& TopOpeBRepTool::Print(const TopOpeBRepTool_OutCurveType t, Standard_OStream& OS)
{
  // #ifdef OCCT_DEBUG
  switch (t)
  {
    case TopOpeBRepTool_BSPLINE1:
      OS << "BSPLINE1";
      break;
    case TopOpeBRepTool_APPROX:
      OS << "APPROX";
      break;
    case TopOpeBRepTool_INTERPOL:
      OS << "INTERPOL";
      break;
    default:
      OS << "UNKNOWN";
      break;
  }
  // #endif
  return OS;
}
