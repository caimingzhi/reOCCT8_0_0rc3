#include <GeomFill_Line.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_Line, Standard_Transient)

GeomFill_Line::GeomFill_Line()
{
  myNbPoints = 0;
}

GeomFill_Line::GeomFill_Line(const int NbPoints)
    : myNbPoints(NbPoints)
{
}
