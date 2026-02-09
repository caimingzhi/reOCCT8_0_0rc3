#pragma once

#include <StdObject_Location.hpp>

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

#include <TopoDS_Shape.hpp>

class StdObject_Shape
{
  friend class ShapePersistent_TopoDS;

public:
  StdObject_Shape()
      : myOrient(0)
  {
  }

  Standard_EXPORT TopoDS_Shape Import() const;

  Standard_EXPORT void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const;

protected:
  inline void read(StdObjMgt_ReadData& theReadData)
  {
    theReadData >> myTShape >> myLocation >> myOrient;
  }

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

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, StdObject_Shape& theShape)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);
  theShape.read(theReadData);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData&   theWriteData,
                                       const StdObject_Shape& theShape)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);
  theShape.write(theWriteData);
  return theWriteData;
}
