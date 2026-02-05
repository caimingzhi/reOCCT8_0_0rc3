#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <TopAbs_Orientation.hpp>
#include <LocOpe_Operation.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
class TopoDS_Face;
class TopoDS_Edge;

class LocOpe_Gluer
{
public:
  DEFINE_STANDARD_ALLOC

  LocOpe_Gluer();

  LocOpe_Gluer(const TopoDS_Shape& Sbase, const TopoDS_Shape& Snew);

  Standard_EXPORT void Init(const TopoDS_Shape& Sbase, const TopoDS_Shape& Snew);

  Standard_EXPORT void Bind(const TopoDS_Face& Fnew, const TopoDS_Face& Fbase);

  Standard_EXPORT void Bind(const TopoDS_Edge& Enew, const TopoDS_Edge& Ebase);

  LocOpe_Operation OpeType() const;

  Standard_EXPORT void Perform();

  bool IsDone() const;

  const TopoDS_Shape& ResultingShape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& DescendantFaces(const TopoDS_Face& F) const;

  const TopoDS_Shape& BasisShape() const;

  const TopoDS_Shape& GluedShape() const;

  const NCollection_List<TopoDS_Shape>& Edges() const;

  const NCollection_List<TopoDS_Shape>& TgtEdges() const;

private:
  Standard_EXPORT void AddEdges();

  bool                                                                            myDone;
  TopoDS_Shape                                                                    mySb;
  TopoDS_Shape                                                                    mySn;
  TopoDS_Shape                                                                    myRes;
  TopAbs_Orientation                                                              myOri;
  LocOpe_Operation                                                                myOpe;
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMapEF;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>        myMapEE;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                 myDescF;
  NCollection_List<TopoDS_Shape> myEdges;
  NCollection_List<TopoDS_Shape> myTgtEdges;
};

#include <StdFail_NotDone.hpp>

//=================================================================================================

inline LocOpe_Gluer::LocOpe_Gluer()
    : myDone(false),
      myOri(TopAbs_INTERNAL),
      myOpe(LocOpe_INVALID)
{
}

//=================================================================================================

inline LocOpe_Gluer::LocOpe_Gluer(const TopoDS_Shape& Sbase, const TopoDS_Shape& Snew)
    : myDone(false),
      mySb(Sbase),
      mySn(Snew),
      myOri(TopAbs_INTERNAL),
      myOpe(LocOpe_INVALID)
{
}

//=================================================================================================

inline bool LocOpe_Gluer::IsDone() const
{
  return myDone;
}

//=================================================================================================

inline const TopoDS_Shape& LocOpe_Gluer::ResultingShape() const
{
  if (!myDone)
  {
    throw StdFail_NotDone();
  }
  return myRes;
}

//=================================================================================================

inline const TopoDS_Shape& LocOpe_Gluer::BasisShape() const
{
  return mySb;
}

//=================================================================================================

inline const TopoDS_Shape& LocOpe_Gluer::GluedShape() const
{
  return mySn;
}

//=================================================================================================

inline LocOpe_Operation LocOpe_Gluer::OpeType() const
{
  return myOpe;
}

//=================================================================================================

inline const NCollection_List<TopoDS_Shape>& LocOpe_Gluer::Edges() const
{
  return myEdges;
}

//=================================================================================================

inline const NCollection_List<TopoDS_Shape>& LocOpe_Gluer::TgtEdges() const
{
  return myTgtEdges;
}
