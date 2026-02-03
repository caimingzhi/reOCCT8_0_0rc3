// Created on: 1999-05-13
// Created by: data exchange team
// Copyright (c) 1999 Matra Datavision
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

#ifndef _ShapeUpgrade_ConvertCurve3dToBezier_HeaderFile
#define _ShapeUpgrade_ConvertCurve3dToBezier_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <ShapeUpgrade_SplitCurve3d.hpp>

//! converts/splits a 3d curve of any type to a list of beziers
class ShapeUpgrade_ConvertCurve3dToBezier : public ShapeUpgrade_SplitCurve3d
{

public:
  //! Empty constructor
  Standard_EXPORT ShapeUpgrade_ConvertCurve3dToBezier();

  //! Sets mode for conversion Geom_Line to bezier.
  void SetLineMode(const bool mode);

  //! Returns the Geom_Line conversion mode.
  bool GetLineMode() const;

  //! Sets mode for conversion Geom_Circle to bezier.
  void SetCircleMode(const bool mode);

  //! Returns the Geom_Circle conversion mode.
  bool GetCircleMode() const;

  //! Returns the Geom_Conic conversion mode.
  void SetConicMode(const bool mode);

  //! Performs converting and computes the resulting shape.
  bool GetConicMode() const;

  //! Converts curve into a list of beziers, and stores the
  //! splitting parameters on original curve.
  Standard_EXPORT void Compute() override;

  //! Splits a list of beziers computed by Compute method according
  //! the split values and splitting parameters.
  Standard_EXPORT void Build(const bool Segment) override;

  //! Returns the list of split parameters in original curve parametrisation.
  Standard_EXPORT occ::handle<NCollection_HSequence<double>> SplitParams() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_ConvertCurve3dToBezier, ShapeUpgrade_SplitCurve3d)

private:
  //! Returns the list of bezier curves correspondent to original
  //! curve.
  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Geom_Curve>>> Segments() const;

  occ::handle<NCollection_HSequence<occ::handle<Geom_Curve>>> mySegments;
  occ::handle<NCollection_HSequence<double>>                  mySplitParams;
  bool                                                        myLineMode;
  bool                                                        myCircleMode;
  bool                                                        myConicMode;
};
// Created on: 1999-06-22
// Created by: data exchange team
// Copyright (c) 1999-1999 Matra Datavision
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

//=================================================================================================

inline void ShapeUpgrade_ConvertCurve3dToBezier::SetLineMode(const bool mode)
{
  myLineMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ConvertCurve3dToBezier::GetLineMode() const
{
  return myLineMode;
}

//=================================================================================================

inline void ShapeUpgrade_ConvertCurve3dToBezier::SetCircleMode(const bool mode)
{
  myCircleMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ConvertCurve3dToBezier::GetCircleMode() const
{
  return myCircleMode;
}

//=================================================================================================

inline void ShapeUpgrade_ConvertCurve3dToBezier::SetConicMode(const bool mode)
{
  myConicMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ConvertCurve3dToBezier::GetConicMode() const
{
  return myConicMode;
}


#endif // _ShapeUpgrade_ConvertCurve3dToBezier_HeaderFile
