

#include <Vrml_PointSet.hpp>

Vrml_PointSet::Vrml_PointSet(const int aStartIndex, const int aNumPoints)
{
  myStartIndex = aStartIndex;
  myNumPoints  = aNumPoints;
}

void Vrml_PointSet::SetStartIndex(const int aStartIndex)
{
  myStartIndex = aStartIndex;
}

int Vrml_PointSet::StartIndex() const
{
  return myStartIndex;
}

void Vrml_PointSet::SetNumPoints(const int aNumPoints)
{
  myNumPoints = aNumPoints;
}

int Vrml_PointSet::NumPoints() const
{
  return myNumPoints;
}

Standard_OStream& Vrml_PointSet::Print(Standard_OStream& anOStream) const
{
  anOStream << "PointSet {\n";
  if (myStartIndex != 0 || myNumPoints != -1)
  {
    if (myStartIndex != 0)
    {
      anOStream << "    startIndex\t";
      anOStream << myStartIndex << "\n";
    }
    if (myNumPoints != 0)
    {
      anOStream << "    numPoints\t";
      anOStream << myNumPoints << "\n";
    }
  }
  anOStream << "}\n";
  return anOStream;
}
