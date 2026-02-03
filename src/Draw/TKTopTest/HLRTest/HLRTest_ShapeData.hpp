// Created on: 1992-08-21
// Created by: Christophe MARION
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

#ifndef _HLRTest_ShapeData_HeaderFile
#define _HLRTest_ShapeData_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Draw_Color.hpp>
#include <Standard_Transient.hpp>

//! Contains the colors of a shape.
class HLRTest_ShapeData : public Standard_Transient
{

public:
  Standard_EXPORT HLRTest_ShapeData(const Draw_Color& CVis,
                                    const Draw_Color& COVis,
                                    const Draw_Color& CIVis,
                                    const Draw_Color& CHid,
                                    const Draw_Color& COHid,
                                    const Draw_Color& CIHid);

  void VisibleColor(const Draw_Color& CVis);

  void VisibleOutLineColor(const Draw_Color& COVis);

  void VisibleIsoColor(const Draw_Color& CIVis);

  void HiddenColor(const Draw_Color& CHid);

  void HiddenOutLineColor(const Draw_Color& COHid);

  void HiddenIsoColor(const Draw_Color& CIHid);

  Draw_Color VisibleColor() const;

  Draw_Color VisibleOutLineColor() const;

  Draw_Color VisibleIsoColor() const;

  Draw_Color HiddenColor() const;

  Draw_Color HiddenOutLineColor() const;

  Draw_Color HiddenIsoColor() const;

  DEFINE_STANDARD_RTTIEXT(HLRTest_ShapeData, Standard_Transient)

private:
  Draw_Color myVColor;
  Draw_Color myVOColor;
  Draw_Color myVIColor;
  Draw_Color myHColor;
  Draw_Color myHOColor;
  Draw_Color myHIColor;
};
// Created on: 1992-08-25
// Created by: Christophe MARION
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

//=================================================================================================

inline void HLRTest_ShapeData::VisibleColor(const Draw_Color& CVis)
{
  myVColor = CVis;
}

//=================================================================================================

inline void HLRTest_ShapeData::VisibleOutLineColor(const Draw_Color& COVis)
{
  myVOColor = COVis;
}

//=================================================================================================

inline void HLRTest_ShapeData::VisibleIsoColor(const Draw_Color& CIVis)
{
  myVIColor = CIVis;
}

//=================================================================================================

inline void HLRTest_ShapeData::HiddenColor(const Draw_Color& CHid)
{
  myHColor = CHid;
}

//=================================================================================================

inline void HLRTest_ShapeData::HiddenOutLineColor(const Draw_Color& COHid)
{
  myHOColor = COHid;
}

//=================================================================================================

inline void HLRTest_ShapeData::HiddenIsoColor(const Draw_Color& CIHid)
{
  myHIColor = CIHid;
}

//=================================================================================================

inline Draw_Color HLRTest_ShapeData::VisibleColor() const
{
  return myVColor;
}

//=================================================================================================

inline Draw_Color HLRTest_ShapeData::VisibleOutLineColor() const
{
  return myVOColor;
}

//=================================================================================================

inline Draw_Color HLRTest_ShapeData::VisibleIsoColor() const
{
  return myVIColor;
}

//=================================================================================================

inline Draw_Color HLRTest_ShapeData::HiddenColor() const
{
  return myHColor;
}

//=================================================================================================

inline Draw_Color HLRTest_ShapeData::HiddenOutLineColor() const
{
  return myHOColor;
}

//=================================================================================================

inline Draw_Color HLRTest_ShapeData::HiddenIsoColor() const
{
  return myHIColor;
}


#endif // _HLRTest_ShapeData_HeaderFile
