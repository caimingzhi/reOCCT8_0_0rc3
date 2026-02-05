#pragma once

typedef enum
{
  Aspect_POM_Off   = 0x00, /* all polygon offset modes disabled                     */
  Aspect_POM_Fill  = 0x01, /* GL_POLYGON_OFFSET_FILL enabled (shaded polygons)      */
  Aspect_POM_Line  = 0x02, /* GL_POLYGON_OFFSET_LINE enabled (polygons as outlines) */
  Aspect_POM_Point = 0x04, /* GL_POLYGON_OFFSET_POINT enabled (polygons as vertices)*/
  Aspect_POM_All   = Aspect_POM_Fill | Aspect_POM_Line | Aspect_POM_Point,
  Aspect_POM_None  = 0x08, /* do not change current polygon offset mode             */
  Aspect_POM_Mask  = Aspect_POM_All | Aspect_POM_None
} Aspect_PolygonOffsetMode;

#include <Standard_OStream.hpp>
#include <Standard_Integer.hpp>

//! Polygon offset parameters.
struct Graphic3d_PolygonOffset
{
  Aspect_PolygonOffsetMode Mode;
  float                    Factor;
  float                    Units;

  //! Empty constructor.
  Graphic3d_PolygonOffset()
      : Mode(Aspect_POM_Fill),
        Factor(1.0f),
        Units(1.0f)
  {
  }

  //! Equality comparison.
  bool operator==(const Graphic3d_PolygonOffset& theOther) const
  {
    return Mode == theOther.Mode && Factor == theOther.Factor && Units == theOther.Units;
  }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;
};
