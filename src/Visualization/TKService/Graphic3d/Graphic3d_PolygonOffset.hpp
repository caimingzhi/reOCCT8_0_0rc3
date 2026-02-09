#pragma once

typedef enum
{
  Aspect_POM_Off   = 0x00,
  Aspect_POM_Fill  = 0x01,
  Aspect_POM_Line  = 0x02,
  Aspect_POM_Point = 0x04,
  Aspect_POM_All   = Aspect_POM_Fill | Aspect_POM_Line | Aspect_POM_Point,
  Aspect_POM_None  = 0x08,
  Aspect_POM_Mask  = Aspect_POM_All | Aspect_POM_None
} Aspect_PolygonOffsetMode;

#include <Standard_OStream.hpp>
#include <Standard_Integer.hpp>

struct Graphic3d_PolygonOffset
{
  Aspect_PolygonOffsetMode Mode;
  float                    Factor;
  float                    Units;

  Graphic3d_PolygonOffset()
      : Mode(Aspect_POM_Fill),
        Factor(1.0f),
        Units(1.0f)
  {
  }

  bool operator==(const Graphic3d_PolygonOffset& theOther) const
  {
    return Mode == theOther.Mode && Factor == theOther.Factor && Units == theOther.Units;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;
};
