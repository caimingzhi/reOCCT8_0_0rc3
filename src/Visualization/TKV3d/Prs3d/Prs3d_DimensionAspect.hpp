#pragma once


#include <Prs3d_ArrowAspect.hpp>
// Created on: 1992-08-26
// Created by: Jean Louis FRENKEL
// Copyright (c) 1992-1999 Matra Datavision
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


//! Specifies dimension arrow location and orientation.
//! DAO_Internal - arrows "inside", pointing outwards.
//! DAO_External - arrows "outside", pointing inwards.
//! DAO_Fit      - arrows oriented inside if value label with arrowtips fit the dimension line,
//! otherwise - externally
enum Prs3d_DimensionArrowOrientation
{
  Prs3d_DAO_Internal,
  Prs3d_DAO_External,
  Prs3d_DAO_Fit
};


// Created on: 1992-08-26
// Created by: Jean Louis FRENKEL
// Copyright (c) 1992-1999 Matra Datavision
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


//! Specifies options for positioning dimension value label in horizontal direction.
//! DTHP_Left   - value label located at left side on dimension extension.
//! DTHP_Right  - value label located at right side on dimension extension.
//! DTHP_Center - value label located at center of dimension line.
//! DTHP_Fit    - value label located automatically at left side if does not fits
//! the dimension space, otherwise the value label is placed at center.
enum Prs3d_DimensionTextHorizontalPosition
{
  Prs3d_DTHP_Left,
  Prs3d_DTHP_Right,
  Prs3d_DTHP_Center,
  Prs3d_DTHP_Fit
};


// Created on: 1992-08-26
// Created by: Jean Louis FRENKEL
// Copyright (c) 1992-1999 Matra Datavision
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


//! Specifies options for positioning dimension value label in vertical direction
//! with respect to dimension (extension) line.
//! DTVP_Above - text label is located above the dimension or extension line.
//! DTVP_Below - text label is located below the dimension or extension line.
//! DTVP_Center - the text label middle-point is in line with dimension or extension line.
enum Prs3d_DimensionTextVerticalPosition
{
  Prs3d_DTVP_Above,
  Prs3d_DTVP_Below,
  Prs3d_DTVP_Center
};


#include <Prs3d_LineAspect.hpp>
#include <Prs3d_TextAspect.hpp>
#include <TCollection_AsciiString.hpp>

//! defines the attributes when drawing a Length Presentation.
class Prs3d_DimensionAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_DimensionAspect, Prs3d_BasicAspect)
public:
  //! Constructs an empty framework to define the display of dimensions.
  Standard_EXPORT Prs3d_DimensionAspect();

  //! Returns the settings for the display of lines used in presentation of dimensions.
  const occ::handle<Prs3d_LineAspect>& LineAspect() const { return myLineAspect; }

  //! Sets the display attributes of lines used in presentation of dimensions.
  void SetLineAspect(const occ::handle<Prs3d_LineAspect>& theAspect) { myLineAspect = theAspect; }

  //! Returns the settings for the display of text used in presentation of dimensions.
  const occ::handle<Prs3d_TextAspect>& TextAspect() const { return myTextAspect; }

  //! Sets the display attributes of text used in presentation of dimensions.
  void SetTextAspect(const occ::handle<Prs3d_TextAspect>& theAspect) { myTextAspect = theAspect; }

  //! Check if text for dimension label is 3d.
  bool IsText3d() const { return myIsText3d; }

  //! Sets type of text.
  void MakeText3d(const bool isText3d) { myIsText3d = isText3d; }

  //! Check if 3d text for dimension label is shaded.
  bool IsTextShaded() const { return myIsTextShaded; }

  //! Turns on/off text shading for 3d text.
  void MakeTextShaded(const bool theIsTextShaded) { myIsTextShaded = theIsTextShaded; }

  //! Gets type of arrows.
  bool IsArrows3d() const { return myIsArrows3d; }

  //! Sets type of arrows.
  void MakeArrows3d(const bool theIsArrows3d) { myIsArrows3d = theIsArrows3d; }

  //! Shows if Units are to be displayed along with dimension value.
  bool IsUnitsDisplayed() const { return myToDisplayUnits; }

  //! Specifies whether the units string should be displayed
  //! along with value label or not.
  void MakeUnitsDisplayed(const bool theIsDisplayed) { myToDisplayUnits = theIsDisplayed; }

  //! Sets orientation of arrows (external or internal).
  //! By default orientation is chosen automatically according to situation and text label size.
  void SetArrowOrientation(const Prs3d_DimensionArrowOrientation theArrowOrient)
  {
    myArrowOrientation = theArrowOrient;
  }

  //! Gets orientation of arrows (external or internal).
  Prs3d_DimensionArrowOrientation ArrowOrientation() const { return myArrowOrientation; }

  //! Sets vertical text alignment for text label.
  void SetTextVerticalPosition(const Prs3d_DimensionTextVerticalPosition thePosition)
  {
    myTextVPosition = thePosition;
  }

  //! Gets vertical text alignment for text label.
  Prs3d_DimensionTextVerticalPosition TextVerticalPosition() const { return myTextVPosition; }

  //! Sets horizontal text alignment for text label.
  void SetTextHorizontalPosition(const Prs3d_DimensionTextHorizontalPosition thePosition)
  {
    myTextHPosition = thePosition;
  }

  //! Gets horizontal text alignment for text label.
  Prs3d_DimensionTextHorizontalPosition TextHorizontalPosition() const { return myTextHPosition; }

  //! Returns the settings for displaying arrows.
  const occ::handle<Prs3d_ArrowAspect>& ArrowAspect() const { return myArrowAspect; }

  //! Sets the display attributes of arrows used in presentation of dimensions.
  void SetArrowAspect(const occ::handle<Prs3d_ArrowAspect>& theAspect)
  {
    myArrowAspect = theAspect;
  }

  //! Sets the same color for all parts of dimension: lines, arrows and text.
  Standard_EXPORT void SetCommonColor(const Quantity_Color& theColor);

  //! Sets extension size.
  void SetExtensionSize(const double theSize) { myExtensionSize = theSize; }

  //! Returns extension size.
  double ExtensionSize() const { return myExtensionSize; }

  //! Set size for arrow tail (extension without text).
  void SetArrowTailSize(const double theSize) { myArrowTailSize = theSize; }

  //! Returns arrow tail size.
  double ArrowTailSize() const { return myArrowTailSize; }

  //! Sets "Sprintf"-syntax format for formatting dimension value labels.
  void SetValueStringFormat(const TCollection_AsciiString& theFormat)
  {
    myValueStringFormat = theFormat;
  }

  //! Returns format.
  const TCollection_AsciiString& ValueStringFormat() const { return myValueStringFormat; }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  occ::handle<Prs3d_LineAspect>         myLineAspect;
  occ::handle<Prs3d_TextAspect>         myTextAspect;
  occ::handle<Prs3d_ArrowAspect>        myArrowAspect;
  TCollection_AsciiString               myValueStringFormat;
  double                                myExtensionSize;
  double                                myArrowTailSize;
  Prs3d_DimensionArrowOrientation       myArrowOrientation;
  Prs3d_DimensionTextHorizontalPosition myTextHPosition;
  Prs3d_DimensionTextVerticalPosition   myTextVPosition;
  bool                                  myToDisplayUnits;
  bool                                  myIsText3d;
  bool                                  myIsTextShaded;
  bool                                  myIsArrows3d;
};

