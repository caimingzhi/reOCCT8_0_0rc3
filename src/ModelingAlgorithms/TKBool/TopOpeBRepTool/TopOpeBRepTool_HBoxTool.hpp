#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Transient.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Shape;
class Bnd_Box;

class TopOpeBRepTool_HBoxTool : public Standard_Transient
{

public:
  Standard_EXPORT TopOpeBRepTool_HBoxTool();

  Standard_EXPORT void Clear();

  Standard_EXPORT void AddBoxes(const TopoDS_Shape&    S,
                                const TopAbs_ShapeEnum TS,
                                const TopAbs_ShapeEnum TA = TopAbs_SHAPE);

  Standard_EXPORT void AddBox(const TopoDS_Shape& S);

  Standard_EXPORT static void ComputeBox(const TopoDS_Shape& S, Bnd_Box& B);

  Standard_EXPORT static void ComputeBoxOnVertices(const TopoDS_Shape& S, Bnd_Box& B);

  Standard_EXPORT static void DumpB(const Bnd_Box& B);

  Standard_EXPORT const Bnd_Box& Box(const TopoDS_Shape& S);

  Standard_EXPORT const Bnd_Box& Box(const int I) const;

  Standard_EXPORT bool HasBox(const TopoDS_Shape& S) const;

  Standard_EXPORT const TopoDS_Shape& Shape(const int I) const;

  Standard_EXPORT int Index(const TopoDS_Shape& S) const;

  Standard_EXPORT int Extent() const;

  Standard_EXPORT NCollection_IndexedDataMap<TopoDS_Shape, Bnd_Box>& ChangeIMS();

  Standard_EXPORT const NCollection_IndexedDataMap<TopoDS_Shape, Bnd_Box>& IMS() const;

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepTool_HBoxTool, Standard_Transient)

private:
  NCollection_IndexedDataMap<TopoDS_Shape, Bnd_Box> myIMS;
};

