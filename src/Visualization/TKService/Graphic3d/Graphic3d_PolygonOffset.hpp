// Copyright (c) 2016 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _Graphic3d_PolygonOffset_HeaderFile
#define _Graphic3d_PolygonOffset_HeaderFile
// Created on: 2004-03-22
// Created by: Sergey ANIKIN
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef Aspect_PolygonOffsetMode_HeaderFile
#define Aspect_PolygonOffsetMode_HeaderFile

// Enumeration for polygon offset modes

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

#endif

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

#endif // _Graphic3d_PolygonOffset_HeaderFile
