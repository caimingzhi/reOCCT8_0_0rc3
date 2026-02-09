#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_Orientation.hpp>
#include <Standard_OStream.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_State.hpp>

class TopAbs
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopAbs_Orientation Compose(const TopAbs_Orientation Or1,
                                                    const TopAbs_Orientation Or2);

  Standard_EXPORT static TopAbs_Orientation Reverse(const TopAbs_Orientation Or);

  Standard_EXPORT static TopAbs_Orientation Complement(const TopAbs_Orientation Or);

  static Standard_OStream& Print(const TopAbs_ShapeEnum theShapeType, Standard_OStream& theStream)
  {
    return (theStream << ShapeTypeToString(theShapeType));
  }

  static Standard_OStream& Print(const TopAbs_Orientation theOrientation,
                                 Standard_OStream&        theStream)
  {
    return (theStream << ShapeOrientationToString(theOrientation));
  }

  Standard_EXPORT static Standard_OStream& Print(const TopAbs_State St, Standard_OStream& S);

  Standard_EXPORT static const char* ShapeTypeToString(TopAbs_ShapeEnum theType);

  static TopAbs_ShapeEnum ShapeTypeFromString(const char* theTypeString)
  {
    TopAbs_ShapeEnum aType = TopAbs_SHAPE;
    ShapeTypeFromString(theTypeString, aType);
    return aType;
  }

  Standard_EXPORT static bool ShapeTypeFromString(const char*       theTypeString,
                                                  TopAbs_ShapeEnum& theType);

  Standard_EXPORT static const char* ShapeOrientationToString(TopAbs_Orientation theOrientation);

  static TopAbs_Orientation ShapeOrientationFromString(const char* theOrientationString)
  {
    TopAbs_Orientation aType = TopAbs_FORWARD;
    ShapeOrientationFromString(theOrientationString, aType);
    return aType;
  }

  Standard_EXPORT static bool ShapeOrientationFromString(const char*         theOrientationString,
                                                         TopAbs_Orientation& theOrientation);
};
