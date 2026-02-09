#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Macro.hpp>
#include <Standard_ShortReal.hpp>
#include <Standard_OStream.hpp>

class Graphic3d_Vertex
{
public:
  DEFINE_STANDARD_ALLOC

  Graphic3d_Vertex() { SetCoord(0.0f, 0.0f, 0.0f); }

  Graphic3d_Vertex(const float theX, const float theY, const float theZ)
  {
    SetCoord(theX, theY, theZ);
  }

  Graphic3d_Vertex(const double theX, const double theY, const double theZ)
  {
    SetCoord(theX, theY, theZ);
  }

  void SetCoord(const float theX, const float theY, const float theZ)
  {
    xyz[0] = theX;
    xyz[1] = theY;
    xyz[2] = theZ;
  }

  void SetCoord(const double theX, const double theY, const double theZ)
  {
    xyz[0] = float(theX);
    xyz[1] = float(theY);
    xyz[2] = float(theZ);
  }

  void Coord(float& theX, float& theY, float& theZ) const
  {
    theX = xyz[0];
    theY = xyz[1];
    theZ = xyz[2];
  }

  void Coord(double& theX, double& theY, double& theZ) const
  {
    theX = xyz[0];
    theY = xyz[1];
    theZ = xyz[2];
  }

  float X() const { return xyz[0]; }

  float Y() const { return xyz[1]; }

  float Z() const { return xyz[2]; }

  Standard_EXPORT float Distance(const Graphic3d_Vertex& theOther) const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  float xyz[3];
};
