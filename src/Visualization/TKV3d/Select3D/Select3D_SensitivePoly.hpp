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

#ifndef _Select3D_SensitivePoly_HeaderFile
#define _Select3D_SensitivePoly_HeaderFile

#include <gp_Circ.hpp>
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

#ifndef _Select3D_PointData_HeaderFile
#define _Select3D_PointData_HeaderFile
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

#ifndef _Select3D_Pnt_HeaderFile
#define _Select3D_Pnt_HeaderFile

#include <gp_Pnt.hpp>

struct Select3D_Pnt
{
  float x, y, z;

  operator gp_Pnt() const { return gp_Pnt(x, y, z); }

  operator gp_XYZ() const { return gp_XYZ(x, y, z); }

  gp_Pnt operator=(const gp_Pnt& thePnt)
  {
    x = RealToShortReal(thePnt.X());
    y = RealToShortReal(thePnt.Y());
    z = RealToShortReal(thePnt.Z());
    return *this;
  }
};

#endif


// A framework for safe management of Select3D_SensitivePoly polygons of 3D points
class Select3D_PointData
{

public:
  // Constructs internal array of 3D points defined
  // by number of points theNbPoints
  Select3D_PointData(const int theNbPoints)
      : mynbpoints(theNbPoints)
  {
    if (theNbPoints <= 0)
      throw Standard_ConstructionError("Select3D_PointData");

    mypolyg3d = new Select3D_Pnt[mynbpoints];
  }

  // Destructor
  ~Select3D_PointData() { delete[] mypolyg3d; }

  // Sets Select3D_Pnt to internal array
  // of 3D points if theIndex is valid
  void SetPnt(const int theIndex, const Select3D_Pnt& theValue)
  {
    if (theIndex < 0 || theIndex >= mynbpoints)
      throw Standard_OutOfRange("Select3D_PointData::SetPnt");
    mypolyg3d[theIndex] = theValue;
  }

  // Sets gp_Pnt to internal array
  // of 3D points if theIndex is valid
  void SetPnt(const int theIndex, const gp_Pnt& theValue)
  {
    if (theIndex < 0 || theIndex >= mynbpoints)
      throw Standard_OutOfRange("Select3D_PointData::SetPnt");
    mypolyg3d[theIndex] = theValue;
  }

  // Returns 3D point from internal array
  // if theIndex is valid
  const Select3D_Pnt& Pnt(const int theIndex) const
  {
    if (theIndex < 0 || theIndex >= mynbpoints)
      throw Standard_OutOfRange("Select3D_PointData::Pnt");
    return mypolyg3d[theIndex];
  }

  // Returns 3D point from internal array
  // if theIndex is valid
  gp_Pnt Pnt3d(const int theIndex) const
  {
    if (theIndex < 0 || theIndex >= mynbpoints)
      throw Standard_OutOfRange("Select3D_PointData::Pnt");
    return mypolyg3d[theIndex];
  }

  // Returns size of internal arrays
  int Size() const { return mynbpoints; }

private:
  Select3D_PointData(const Select3D_PointData&)            = delete;
  Select3D_PointData& operator=(const Select3D_PointData&) = delete;

private:
  Select3D_Pnt* mypolyg3d;
  int           mynbpoints;
};

#endif

#include <Select3D_SensitiveSet.hpp>
#include <Select3D_TypeOfSensitivity.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>

//! Sensitive Entity to make a face selectable.
//! In some cases this class can raise Standard_ConstructionError and
//! Standard_OutOfRange exceptions from its member Select3D_PointData
//! myPolyg.
class Select3D_SensitivePoly : public Select3D_SensitiveSet
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitivePoly, Select3D_SensitiveSet)
public:
  //! Constructs a sensitive face object defined by the
  //! owner OwnerId, the array of points ThePoints, and
  //! the sensitivity type Sensitivity.
  //! The array of points is the outer polygon of the geometric face.
  Standard_EXPORT Select3D_SensitivePoly(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                         const NCollection_Array1<gp_Pnt>&         thePoints,
                                         const bool                                theIsBVHEnabled);

  //! Constructs a sensitive face object defined by the
  //! owner OwnerId, the array of points ThePoints, and
  //! the sensitivity type Sensitivity.
  //! The array of points is the outer polygon of the geometric face.
  Standard_EXPORT Select3D_SensitivePoly(const occ::handle<SelectMgr_EntityOwner>&       theOwnerId,
                                         const occ::handle<NCollection_HArray1<gp_Pnt>>& thePoints,
                                         const bool theIsBVHEnabled);

  //! Constructs the sensitive arc object defined by the
  //! owner theOwnerId, the circle theCircle, the parameters theU1
  //! and theU2, the boolean theIsFilled and the number of points theNbPnts.
  //! theU1 and theU2 define the first and last points of the arc on theCircle.
  Standard_EXPORT Select3D_SensitivePoly(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                         const gp_Circ&                            theCircle,
                                         const double                              theU1,
                                         const double                              theU2,
                                         const bool theIsFilled = false,
                                         const int  theNbPnts   = 12);

  //! Constructs a sensitive curve or arc object defined by the
  //! owner theOwnerId, the theIsBVHEnabled flag, and the
  //! maximum number of points on the curve: theNbPnts.
  Standard_EXPORT Select3D_SensitivePoly(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                         const bool                                theIsBVHEnabled,
                                         const int                                 theNbPnts = 6);

  //! Checks whether the poly overlaps current selecting volume
  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  //! Returns the amount of segments in poly
  Standard_EXPORT int NbSubElements() const override;

  //! Returns the 3D points of the array used at construction time.
  void Points3D(occ::handle<NCollection_HArray1<gp_Pnt>>& theHArrayOfPnt)
  {
    int aSize      = myPolyg.Size();
    theHArrayOfPnt = new NCollection_HArray1<gp_Pnt>(1, aSize);
    for (int anIndex = 1; anIndex <= aSize; anIndex++)
    {
      theHArrayOfPnt->SetValue(anIndex, myPolyg.Pnt(anIndex - 1));
    }
  }

  //! Return array bounds.
  void ArrayBounds(int& theLow, int& theUp) const
  {
    theLow = 0;
    theUp  = myPolyg.Size() - 1;
  }

  //! Return point.
  gp_Pnt GetPoint3d(const int thePntIdx) const
  {
    return (thePntIdx >= 0 && thePntIdx < myPolyg.Size()) ? myPolyg.Pnt(thePntIdx) : gp_Pnt();
  }

  //! Returns bounding box of a polygon. If location
  //! transformation is set, it will be applied
  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  //! Returns center of the point set. If location transformation
  //! is set, it will be applied
  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  //! Returns the amount of segments of the poly
  Standard_EXPORT int Size() const override;

  //! Returns bounding box of segment with index theIdx
  Standard_EXPORT Select3D_BndBox3d Box(const int theIdx) const override;

  //! Returns geometry center of sensitive entity index theIdx in the vector along
  //! the given axis theAxis
  Standard_EXPORT double Center(const int theIdx, const int theAxis) const override;

  //! Swaps items with indexes theIdx1 and theIdx2 in the vector
  Standard_EXPORT void Swap(const int theIdx1, const int theIdx2) override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  //! Checks whether the segment with index theIdx overlaps the current selecting volume
  Standard_EXPORT bool overlapsElement(SelectBasics_PickResult&             thePickResult,
                                       SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  //! Checks whether the entity with index theIdx is inside the current selecting volume
  Standard_EXPORT bool elementIsInside(SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  //! Calculates distance from the 3d projection of used-picked screen point
  //! to center of the geometry
  Standard_EXPORT double distanceToCOG(SelectBasics_SelectingVolumeManager& theMgr) override;

protected:
  Select3D_PointData                    myPolyg;          //!< Points of the poly
  mutable gp_Pnt                        myCOG;            //!< Center of the poly
  occ::handle<NCollection_HArray1<int>> mySegmentIndexes; //!< Segment indexes for BVH tree build
  Select3D_BndBox3d                     myBndBox;         //!< Bounding box of the poly
  // clang-format off
  Select3D_TypeOfSensitivity       mySensType;       //!< Type of sensitivity: boundary or interior
  mutable bool         myIsComputed;     //!< Is true if all the points and data structures of polygon are initialized
  // clang-format on
};

#endif // _Select3D_SensitivePoly_HeaderFile
