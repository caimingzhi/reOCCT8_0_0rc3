#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Macro.hpp>
#include <Standard_ShortReal.hpp>
#include <Standard_OStream.hpp>

//! This class represents a graphical 3D point.
class Graphic3d_Vertex
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a point with 0.0, 0.0, 0.0 coordinates.
  Graphic3d_Vertex() { SetCoord(0.0f, 0.0f, 0.0f); }

  //! Creates a point with theX, theY and theZ coordinates.
  Graphic3d_Vertex(const float theX, const float theY, const float theZ)
  {
    SetCoord(theX, theY, theZ);
  }

  //! Creates a point with theX, theY and theZ coordinates.
  Graphic3d_Vertex(const double theX, const double theY, const double theZ)
  {
    SetCoord(theX, theY, theZ);
  }

  //! Modifies the coordinates.
  void SetCoord(const float theX, const float theY, const float theZ)
  {
    xyz[0] = theX;
    xyz[1] = theY;
    xyz[2] = theZ;
  }

  //! Modifies the coordinates.
  void SetCoord(const double theX, const double theY, const double theZ)
  {
    xyz[0] = float(theX);
    xyz[1] = float(theY);
    xyz[2] = float(theZ);
  }

  //! Returns the coordinates.
  void Coord(float& theX, float& theY, float& theZ) const
  {
    theX = xyz[0];
    theY = xyz[1];
    theZ = xyz[2];
  }

  //! Returns the coordinates.
  void Coord(double& theX, double& theY, double& theZ) const
  {
    theX = xyz[0];
    theY = xyz[1];
    theZ = xyz[2];
  }

  //! Returns the X coordinates.
  float X() const { return xyz[0]; }

  //! Returns the Y coordinate.
  float Y() const { return xyz[1]; }

  //! Returns the Z coordinate.
  float Z() const { return xyz[2]; }

  //! Returns the distance between two points.
  Standard_EXPORT float Distance(const Graphic3d_Vertex& theOther) const;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  float xyz[3];
};
