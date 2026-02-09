

#include <GccEnt.hpp>
#include <GccEnt_QualifiedCirc.hpp>
#include <GccEnt_QualifiedLin.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
#include <TCollection_AsciiString.hpp>

namespace
{
  static const char* GccEnt_Table_PrintPosition[5] = {"UNQUALIFIED",
                                                      "ENCLOSING",
                                                      "ENCLOSED",
                                                      "OUTSIDE",
                                                      "NOQUALIFIER"};
}

const char* GccEnt::PositionToString(GccEnt_Position thePosition)
{
  return GccEnt_Table_PrintPosition[thePosition];
}

bool GccEnt::PositionFromString(const char* thePositionString, GccEnt_Position& thePosition)
{
  TCollection_AsciiString aName(thePositionString);
  aName.UpperCase();
  for (int aTypeIter = 0; aTypeIter <= GccEnt_noqualifier; ++aTypeIter)
  {
    const char* aTypeName = GccEnt_Table_PrintPosition[aTypeIter];
    if (aName == aTypeName)
    {
      thePosition = GccEnt_Position(aTypeIter);
      return true;
    }
  }
  return false;
}

GccEnt_QualifiedLin GccEnt::Unqualified(const gp_Lin2d& Line)
{
  return GccEnt_QualifiedLin(Line, GccEnt_unqualified);
}

GccEnt_QualifiedCirc GccEnt::Unqualified(const gp_Circ2d& Circle)
{
  return GccEnt_QualifiedCirc(Circle, GccEnt_unqualified);
}

GccEnt_QualifiedCirc GccEnt::Enclosing(const gp_Circ2d& Circle)
{
  return GccEnt_QualifiedCirc(Circle, GccEnt_enclosing);
}

GccEnt_QualifiedLin GccEnt::Enclosed(const gp_Lin2d& Line)
{
  return GccEnt_QualifiedLin(Line, GccEnt_enclosed);
}

GccEnt_QualifiedCirc GccEnt::Enclosed(const gp_Circ2d& Circle)
{
  return GccEnt_QualifiedCirc(Circle, GccEnt_enclosed);
}

GccEnt_QualifiedCirc GccEnt::Outside(const gp_Circ2d& Circle)
{
  return GccEnt_QualifiedCirc(Circle, GccEnt_outside);
}

GccEnt_QualifiedLin GccEnt::Outside(const gp_Lin2d& Line)
{
  return GccEnt_QualifiedLin(Line, GccEnt_outside);
}
