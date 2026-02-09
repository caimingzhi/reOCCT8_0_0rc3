#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bnd_Box.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_Shape.hpp>

class BOPDS_ShapeInfo
{
public:
  DEFINE_STANDARD_ALLOC

  BOPDS_ShapeInfo();

  virtual ~BOPDS_ShapeInfo();

  BOPDS_ShapeInfo(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  void SetShape(const TopoDS_Shape& theS);

  const TopoDS_Shape& Shape() const;

  void SetShapeType(const TopAbs_ShapeEnum theType);

  TopAbs_ShapeEnum ShapeType() const;

  void SetBox(const Bnd_Box& theBox);

  const Bnd_Box& Box() const;

  Bnd_Box& ChangeBox();

  const NCollection_List<int>& SubShapes() const;

  NCollection_List<int>& ChangeSubShapes();

  bool HasSubShape(const int theI) const;

  bool HasReference() const;

  void SetReference(const int theI);

  int Reference() const;

  bool HasBRep() const;

  bool IsInterfering() const;

  bool HasFlag() const;

  bool HasFlag(int& theFlag) const;

  void SetFlag(const int theI);

  int Flag() const;

  Standard_EXPORT void Dump() const;

protected:
  TopoDS_Shape          myShape;
  TopAbs_ShapeEnum      myType;
  Bnd_Box               myBox;
  NCollection_List<int> mySubShapes;
  int                   myReference;
  int                   myFlag;
};

#include <BOPDS_Tools.hpp>

inline BOPDS_ShapeInfo::BOPDS_ShapeInfo()
    :

      myType(TopAbs_SHAPE),
      myReference(-1),
      myFlag(-1)
{
}

inline BOPDS_ShapeInfo::BOPDS_ShapeInfo(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : myType(TopAbs_SHAPE),
      mySubShapes(theAllocator),
      myReference(-1),
      myFlag(-1)
{
}

inline BOPDS_ShapeInfo::~BOPDS_ShapeInfo() = default;

inline void BOPDS_ShapeInfo::SetShape(const TopoDS_Shape& theS)
{
  myShape = theS;
}

inline const TopoDS_Shape& BOPDS_ShapeInfo::Shape() const
{
  return myShape;
}

inline void BOPDS_ShapeInfo::SetShapeType(const TopAbs_ShapeEnum theType)
{
  myType = theType;
}

inline TopAbs_ShapeEnum BOPDS_ShapeInfo::ShapeType() const
{
  return myType;
}

inline void BOPDS_ShapeInfo::SetBox(const Bnd_Box& theBox)
{
  myBox = theBox;
}

inline const Bnd_Box& BOPDS_ShapeInfo::Box() const
{
  return myBox;
}

inline Bnd_Box& BOPDS_ShapeInfo::ChangeBox()
{
  return myBox;
}

inline const NCollection_List<int>& BOPDS_ShapeInfo::SubShapes() const
{
  return mySubShapes;
}

inline NCollection_List<int>& BOPDS_ShapeInfo::ChangeSubShapes()
{
  return mySubShapes;
}

inline bool BOPDS_ShapeInfo::HasSubShape(const int theI) const
{
  return mySubShapes.Contains(theI);
}

inline bool BOPDS_ShapeInfo::HasReference() const
{
  return (myReference >= 0);
}

inline void BOPDS_ShapeInfo::SetReference(const int theI)
{
  myReference = theI;
}

inline int BOPDS_ShapeInfo::Reference() const
{
  return myReference;
}

inline bool BOPDS_ShapeInfo::HasBRep() const
{
  return (BOPDS_Tools::HasBRep(myType));
}

inline bool BOPDS_ShapeInfo::IsInterfering() const
{
  return (HasBRep() || myType == TopAbs_SOLID);
}

inline bool BOPDS_ShapeInfo::HasFlag() const
{
  return (myFlag >= 0);
}

inline bool BOPDS_ShapeInfo::HasFlag(int& theFlag) const
{
  theFlag = myFlag;
  return (myFlag >= 0);
}

inline void BOPDS_ShapeInfo::SetFlag(const int theFlag)
{
  myFlag = theFlag;
}

inline int BOPDS_ShapeInfo::Flag() const
{
  return myFlag;
}
