// Copyright (c) 2015 OPEN CASCADE SAS
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

#ifndef _StdObject_Shape_HeaderFile
#define _StdObject_Shape_HeaderFile

#include <StdObject_Location.hpp>
// Copyright (c) 2015 OPEN CASCADE SAS
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

#ifndef _StdPersistent_TopoDS_HeaderFile
#define _StdPersistent_TopoDS_HeaderFile

#include <StdObjMgt_SharedObject.hpp>
#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_WriteData.hpp>

#include <TopoDS_TShape.hpp>

class StdPersistent_TopoDS : protected StdObjMgt_SharedObject
{
protected:
  class pTShape : public Standard_Transient
  {
    friend class ShapePersistent_TopoDS;

    DEFINE_STANDARD_RTTI_INLINE(pTShape, Standard_Transient)

  public:
    pTShape()
        : myFlags(0)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData) { theReadData >> myShapes >> myFlags; }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myShapes << myFlags;
    }

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myShapes);
    }

    inline const char* PName() const { return "PTopoDS_TShape"; }

  protected:
    occ::handle<StdObjMgt_Persistent> myShapes;
    int                               myFlags;
  };

public:
  typedef IgnoreData<StdObjMgt_Persistent, pTShape, TopoDS_TShape> TShape;
};

#endif


#include <TopoDS_Shape.hpp>

class StdObject_Shape
{
  friend class ShapePersistent_TopoDS;

public:
  //! Empty constructor.
  StdObject_Shape()
      : myOrient(0)
  {
  }

  //! Import transient object from the persistent data.
  Standard_EXPORT TopoDS_Shape Import() const;

  Standard_EXPORT void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const;

protected:
  //! Read persistent data from a file.
  inline void read(StdObjMgt_ReadData& theReadData)
  {
    theReadData >> myTShape >> myLocation >> myOrient;
  }

  //! Write persistent data to a file.
  inline void write(StdObjMgt_WriteData& theWriteData) const
  {
    theWriteData << myTShape << myLocation << myOrient;
  }

protected:
  Handle(StdPersistent_TopoDS::TShape) myTShape;
  StdObject_Location                   myLocation;
  int                                  myOrient;

  friend StdObjMgt_ReadData&  operator>>(StdObjMgt_ReadData&, StdObject_Shape&);
  friend StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData&, const StdObject_Shape&);
};

//! Read persistent data from a file.
inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, StdObject_Shape& theShape)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);
  theShape.read(theReadData);
  return theReadData;
}

//! Write persistent data to a file.
inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData&   theWriteData,
                                       const StdObject_Shape& theShape)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);
  theShape.write(theWriteData);
  return theWriteData;
}

#endif
