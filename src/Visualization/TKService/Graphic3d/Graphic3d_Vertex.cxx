#include <Graphic3d_Vertex.hpp>

#include <gp_XYZ.hpp>
#include <Standard_Dump.hpp>

#include <cmath>

float Graphic3d_Vertex::Distance(const Graphic3d_Vertex& AOther) const
{
  return std::sqrt((X() - AOther.X()) * (X() - AOther.X()) + (Y() - AOther.Y()) * (Y() - AOther.Y())
                   + (Z() - AOther.Z()) * (Z() - AOther.Z()));
}

//=================================================================================================

void Graphic3d_Vertex::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  gp_XYZ aCoord(xyz[0], xyz[1], xyz[2]);
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &aCoord)
}
