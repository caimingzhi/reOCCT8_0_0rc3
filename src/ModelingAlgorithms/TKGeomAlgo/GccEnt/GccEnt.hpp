#pragma once

#include <GccEnt_Position.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_OStream.hpp>

class GccEnt_QualifiedLin;
class gp_Lin2d;
class GccEnt_QualifiedCirc;
class gp_Circ2d;

class GccEnt
{
public:
  DEFINE_STANDARD_ALLOC

  static Standard_OStream& Print(const GccEnt_Position thePosition, Standard_OStream& theStream)
  {
    return (theStream << PositionToString(thePosition));
  }

  Standard_EXPORT static const char* PositionToString(GccEnt_Position thePosition);

  static GccEnt_Position PositionFromString(const char* thePositionString)
  {
    GccEnt_Position aPosition = GccEnt_unqualified;
    PositionFromString(thePositionString, aPosition);
    return aPosition;
  }

  Standard_EXPORT static bool PositionFromString(const char*      thePositionString,
                                                 GccEnt_Position& thePosition);

  Standard_EXPORT static GccEnt_QualifiedLin Unqualified(const gp_Lin2d& Obj);

  Standard_EXPORT static GccEnt_QualifiedCirc Unqualified(const gp_Circ2d& Obj);

  Standard_EXPORT static GccEnt_QualifiedCirc Enclosing(const gp_Circ2d& Obj);

  Standard_EXPORT static GccEnt_QualifiedLin Enclosed(const gp_Lin2d& Obj);

  Standard_EXPORT static GccEnt_QualifiedCirc Enclosed(const gp_Circ2d& Obj);

  Standard_EXPORT static GccEnt_QualifiedLin Outside(const gp_Lin2d& Obj);

  Standard_EXPORT static GccEnt_QualifiedCirc Outside(const gp_Circ2d& Obj);
};
