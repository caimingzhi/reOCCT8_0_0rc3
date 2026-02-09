

#include <gp_XYZ.hpp>

#include <gp_Mat.hpp>
#include <Standard_Dump.hpp>

void gp_XYZ::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_VECTOR_CLASS(theOStream, "gp_XYZ", 3, x, y, z)
}

bool gp_XYZ::InitFromJson(const Standard_SStream& theSStream, int& theStreamPos)
{
  int aPos = theStreamPos;
  OCCT_INIT_VECTOR_CLASS(Standard_Dump::Text(theSStream), "gp_XYZ", aPos, 3, &x, &y, &z)

  theStreamPos = aPos;
  return true;
}
