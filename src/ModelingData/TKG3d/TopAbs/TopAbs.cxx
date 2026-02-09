#include <TopAbs.hpp>

#include <TCollection_AsciiString.hpp>

namespace
{
  static const char* TopAbs_Table_PrintShapeEnum[9] =
    {"COMPOUND", "COMPSOLID", "SOLID", "SHELL", "FACE", "WIRE", "EDGE", "VERTEX", "SHAPE"};

  static const char* TopAbs_Table_PrintOrientation[4] = {"FORWARD",
                                                         "REVERSED",
                                                         "INTERNAL",
                                                         "EXTERNAL"};
} // namespace

const char* TopAbs::ShapeTypeToString(TopAbs_ShapeEnum theType)
{
  return TopAbs_Table_PrintShapeEnum[theType];
}

bool TopAbs::ShapeTypeFromString(const char* theTypeString, TopAbs_ShapeEnum& theType)
{
  TCollection_AsciiString aName(theTypeString);
  aName.UpperCase();
  for (int aTypeIter = 0; aTypeIter <= TopAbs_SHAPE; ++aTypeIter)
  {
    const char* aTypeName = TopAbs_Table_PrintShapeEnum[aTypeIter];
    if (aName == aTypeName)
    {
      theType = TopAbs_ShapeEnum(aTypeIter);
      return true;
    }
  }
  return false;
}

const char* TopAbs::ShapeOrientationToString(TopAbs_Orientation theOrientation)
{
  return TopAbs_Table_PrintOrientation[theOrientation];
}

bool TopAbs::ShapeOrientationFromString(const char*         theOrientationString,
                                        TopAbs_Orientation& theOrientation)
{
  TCollection_AsciiString aName(theOrientationString);
  aName.UpperCase();
  for (int anOrientationIter = 0; anOrientationIter <= TopAbs_EXTERNAL; ++anOrientationIter)
  {
    const char* anOrientationName = TopAbs_Table_PrintOrientation[anOrientationIter];
    if (aName == anOrientationName)
    {
      theOrientation = TopAbs_Orientation(anOrientationIter);
      return true;
    }
  }
  return false;
}

TopAbs_Orientation TopAbs::Compose(const TopAbs_Orientation O1, const TopAbs_Orientation O2)
{

  static const TopAbs_Orientation TopAbs_Table_Compose[4][4] = {
    {TopAbs_FORWARD, TopAbs_REVERSED, TopAbs_INTERNAL, TopAbs_EXTERNAL},
    {TopAbs_REVERSED, TopAbs_FORWARD, TopAbs_INTERNAL, TopAbs_EXTERNAL},
    {TopAbs_INTERNAL, TopAbs_INTERNAL, TopAbs_INTERNAL, TopAbs_INTERNAL},
    {TopAbs_EXTERNAL, TopAbs_EXTERNAL, TopAbs_EXTERNAL, TopAbs_EXTERNAL}};
  return TopAbs_Table_Compose[(int)O2][(int)O1];
}

TopAbs_Orientation TopAbs::Reverse(const TopAbs_Orientation Ori)
{
  static const TopAbs_Orientation TopAbs_Table_Reverse[4] = {TopAbs_REVERSED,
                                                             TopAbs_FORWARD,
                                                             TopAbs_INTERNAL,
                                                             TopAbs_EXTERNAL};
  return TopAbs_Table_Reverse[(int)Ori];
}

TopAbs_Orientation TopAbs::Complement(const TopAbs_Orientation Ori)
{
  static const TopAbs_Orientation TopAbs_Table_Complement[4] = {TopAbs_REVERSED,
                                                                TopAbs_FORWARD,
                                                                TopAbs_EXTERNAL,
                                                                TopAbs_INTERNAL};
  return TopAbs_Table_Complement[(int)Ori];
}

Standard_OStream& TopAbs::Print(const TopAbs_State st, Standard_OStream& s)
{
  static const char* TopAbs_Table_PrintState[4] = {"ON", "IN", "OUT", "UNKNOWN"};
  return (s << TopAbs_Table_PrintState[(int)st]);
}
