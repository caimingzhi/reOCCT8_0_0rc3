#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bnd_Box.hpp>
#include <Bnd_BoundSortBox.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TopAbs_ShapeEnum.hpp>
class TopOpeBRepTool_HBoxTool;

class TopOpeBRepTool_BoxSort
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_BoxSort();

  Standard_EXPORT TopOpeBRepTool_BoxSort(const occ::handle<TopOpeBRepTool_HBoxTool>& T);

  Standard_EXPORT void SetHBoxTool(const occ::handle<TopOpeBRepTool_HBoxTool>& T);

  Standard_EXPORT const occ::handle<TopOpeBRepTool_HBoxTool>& HBoxTool() const;

  Standard_EXPORT void Clear();

  Standard_EXPORT void AddBoxes(const TopoDS_Shape&    S,
                                const TopAbs_ShapeEnum TS,
                                const TopAbs_ShapeEnum TA = TopAbs_SHAPE);

  Standard_EXPORT void MakeHAB(const TopoDS_Shape&    S,
                               const TopAbs_ShapeEnum TS,
                               const TopAbs_ShapeEnum TA = TopAbs_SHAPE);

  Standard_EXPORT const occ::handle<NCollection_HArray1<Bnd_Box>>& HAB() const;

  Standard_EXPORT static void MakeHABCOB(const occ::handle<NCollection_HArray1<Bnd_Box>>& HAB,
                                         Bnd_Box&                                         COB);

  Standard_EXPORT const TopoDS_Shape& HABShape(const int I) const;

  Standard_EXPORT void MakeCOB(const TopoDS_Shape&    S,
                               const TopAbs_ShapeEnum TS,
                               const TopAbs_ShapeEnum TA = TopAbs_SHAPE);

  Standard_EXPORT void AddBoxesMakeCOB(const TopoDS_Shape&    S,
                                       const TopAbs_ShapeEnum TS,
                                       const TopAbs_ShapeEnum TA = TopAbs_SHAPE);

  Standard_EXPORT const NCollection_List<int>::Iterator& Compare(const TopoDS_Shape& S);

  Standard_EXPORT const TopoDS_Shape& TouchedShape(const NCollection_List<int>::Iterator& I) const;

  Standard_EXPORT const Bnd_Box& Box(const TopoDS_Shape& S) const;

  Standard_EXPORT ~TopOpeBRepTool_BoxSort();

private:
  Bnd_Box                                   myCOB;
  Bnd_BoundSortBox                          myBSB;
  NCollection_List<int>::Iterator           myIterator;
  TopoDS_Shape                              myLastCompareShape;
  Bnd_Box                                   myLastCompareShapeBox;
  occ::handle<TopOpeBRepTool_HBoxTool>      myHBT;
  occ::handle<NCollection_HArray1<Bnd_Box>> myHAB;
  occ::handle<NCollection_HArray1<int>>     myHAI;
};

