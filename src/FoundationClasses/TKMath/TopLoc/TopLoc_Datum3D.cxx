#include <Standard_ConstructionError.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Standard_Type.hpp>
#include <Standard_Dump.hpp>
#include <TopLoc_Datum3D.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopLoc_Datum3D, Standard_Transient)

TopLoc_Datum3D::TopLoc_Datum3D() = default;

TopLoc_Datum3D::TopLoc_Datum3D(const gp_Trsf& T)
    : myTrsf(T)
{
}

void TopLoc_Datum3D::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myTrsf)
}

void TopLoc_Datum3D::ShallowDump(Standard_OStream& S) const
{
  S << " TopLoc_Datum3D " << (void*)this << std::endl;
  int     i;
  gp_Trsf T = myTrsf;
  for (i = 1; i <= 3; i++)
  {
    S << "  ( " << std::setw(10) << T.Value(i, 1);
    S << "," << std::setw(10) << T.Value(i, 2);
    S << "," << std::setw(10) << T.Value(i, 3);
    S << "," << std::setw(10) << T.Value(i, 4);
    S << ")\n";
  }
  S << std::endl;
}
