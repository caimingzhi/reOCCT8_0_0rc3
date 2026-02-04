#pragma once


#include <Standard.hpp>

#include <TopoDS_Face.hpp>
#include <Draw_Color.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Transient.hpp>
#include <GeomAbs_IsoType.hpp>
#include <Standard_Real.hpp>

//! Display of a face. Face + Array of iso + color.
class DBRep_Face : public Standard_Transient
{

public:
  //! N is the number of iso intervals.
  Standard_EXPORT DBRep_Face(const TopoDS_Face& F, const int N, const Draw_Color& C);

  const TopoDS_Face& Face() const;

  void Face(const TopoDS_Face& F);

  int NbIsos() const;

  void Iso(const int             I,
           const GeomAbs_IsoType T,
           const double          Par,
           const double          T1,
           const double          T2);

  void GetIso(const int I, GeomAbs_IsoType& T, double& Par, double& T1, double& T2) const;

  const Draw_Color& Color() const;

  void Color(const Draw_Color& C);

  DEFINE_STANDARD_RTTIEXT(DBRep_Face, Standard_Transient)

private:
  TopoDS_Face                myFace;
  Draw_Color                 myColor;
  NCollection_Array1<int>    myTypes;
  NCollection_Array1<double> myParams;
};
// Created on: 1993-07-15
// Created by: Remi LEQUETTE
// Copyright (c) 1993-1999 Matra Datavision
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

inline const TopoDS_Face& DBRep_Face::Face() const
{
  return myFace;
}

//=================================================================================================

inline void DBRep_Face::Face(const TopoDS_Face& F)
{
  myFace = F;
}

//=================================================================================================

inline int DBRep_Face::NbIsos() const
{
  return myTypes.Upper();
}

//=================================================================================================

inline void DBRep_Face::Iso(const int             I,
                            const GeomAbs_IsoType T,
                            const double          Par,
                            const double          T1,
                            const double          T2)
{
  myTypes(I)          = (int)T;
  myParams(3 * I - 2) = Par;
  myParams(3 * I - 1) = T1;
  myParams(3 * I)     = T2;
}

//=================================================================================================

inline void DBRep_Face::GetIso(const int        I,
                               GeomAbs_IsoType& T,
                               double&          Par,
                               double&          T1,
                               double&          T2) const
{
  // JR/Hp :
  int IntTyp = myTypes(I);
  T          = (GeomAbs_IsoType)IntTyp;
  //  T   =  (GeomAbs_IsoType) myTypes(I);
  Par = myParams(3 * I - 2);
  T1  = myParams(3 * I - 1);
  T2  = myParams(3 * I);
}

//=================================================================================================

inline const Draw_Color& DBRep_Face::Color() const
{
  return myColor;
}

//=================================================================================================

inline void DBRep_Face::Color(const Draw_Color& C)
{
  myColor = C;
}


