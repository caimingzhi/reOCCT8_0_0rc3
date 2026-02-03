// Created on: 2016-11-14
// Created by: Varvara POSKONINA
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

#ifndef _Graphic3d_HatchStyle_HeaderFile
#define _Graphic3d_HatchStyle_HeaderFile
// Created by: NW,JPB,CAL
// Copyright (c) 1991-1999 Matra Datavision
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

#ifndef _Aspect_HatchStyle_HeaderFile
#define _Aspect_HatchStyle_HeaderFile

//! Definition of all available hatch styles.
enum Aspect_HatchStyle
{
  Aspect_HS_SOLID              = 0,  // TEL_HS_SOLID (no hatching)
  Aspect_HS_HORIZONTAL         = 7,  // TEL_HS_HORIZONTAL
  Aspect_HS_HORIZONTAL_WIDE    = 11, // TEL_HS_HORIZONTAL_SPARSE
  Aspect_HS_VERTICAL           = 8,  // TEL_HS_VERTICAL
  Aspect_HS_VERTICAL_WIDE      = 12, // TEL_HS_VERTICAL_SPARSE
  Aspect_HS_DIAGONAL_45        = 5,  // TEL_HS_DIAG_45
  Aspect_HS_DIAGONAL_45_WIDE   = 9,  // TEL_HS_DIAG_45_SPARSE
  Aspect_HS_DIAGONAL_135       = 6,  // TEL_HS_DIAG_135
  Aspect_HS_DIAGONAL_135_WIDE  = 10, // TEL_HS_DIAG_135_SPARSE
  Aspect_HS_GRID               = 3,  // TEL_HS_GRID
  Aspect_HS_GRID_WIDE          = 4,  // TEL_HS_GRID_SPARSE
  Aspect_HS_GRID_DIAGONAL      = 1,  // TEL_HS_CROSS
  Aspect_HS_GRID_DIAGONAL_WIDE = 2,  // TEL_HS_CROSS_SPARSE
  Aspect_HS_NB                 = 13,
};

#endif // _Aspect_HatchStyle_HeaderFile

#include <Image_PixMap.hpp>
#include <NCollection_Buffer.hpp>

//! A class that provides an API to use standard OCCT hatch styles
//! defined in Aspect_HatchStyle enum or to create custom styles
//! from a user-defined bitmap
class Graphic3d_HatchStyle : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_HatchStyle, Standard_Transient) // Type definition

public:
  //! Creates a new custom hatch style with the given pattern and unique style id
  //! @warning Raises a program error if given pattern image is not a valid 32*32 bitmap
  Standard_EXPORT Graphic3d_HatchStyle(const occ::handle<Image_PixMap>& thePattern);

  //! Creates a new predefined hatch style with the given id in Aspect_HatchStyle enum.
  //! GPU memory for the pattern will not be allocated.
  Graphic3d_HatchStyle(const Aspect_HatchStyle theType)
      : myHatchType(theType)
  {
  }

  //! Returns the pattern of custom hatch style
  Standard_EXPORT const uint8_t* Pattern() const;

  //! In case if predefined OCCT style is used, returns
  //! index in Aspect_HatchStyle enumeration. If the style
  //! is custom, returns unique index of the style
  int HatchType() const { return myHatchType; }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  occ::handle<NCollection_Buffer> myPattern;   //!< Image bitmap with custom hatch pattern
  int                             myHatchType; //!< Index of used style
};

#endif // _Graphic3d_HatchStyle_HeaderFile
