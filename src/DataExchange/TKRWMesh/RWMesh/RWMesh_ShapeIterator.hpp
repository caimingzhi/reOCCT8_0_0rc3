#pragma once

#include <BRepLProp_SLProps.hpp>
#include <NCollection_DataMap.hpp>
#include <Poly_Triangulation.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Edge.hpp>
#include <XCAFPrs_Style.hpp>
#include <gp_Trsf.hpp>

#include <algorithm>

class TDF_Label;

class RWMesh_ShapeIterator
{
public:
  const TopoDS_Shape& ExploredShape() const { return myIter.ExploredShape(); }

  Standard_EXPORT virtual const TopoDS_Shape& Shape() const = 0;

  Standard_EXPORT virtual bool More() const = 0;

  Standard_EXPORT virtual void Next() = 0;

  Standard_EXPORT virtual bool IsEmpty() const = 0;

  const XCAFPrs_Style& Style() const { return myStyle; }

  bool HasColor() const { return myHasColor; }

  const Quantity_ColorRGBA& Color() const { return myColor; }

  Standard_EXPORT virtual int ElemLower() const = 0;

  Standard_EXPORT virtual int ElemUpper() const = 0;

  Standard_EXPORT virtual int NbNodes() const = 0;

  Standard_EXPORT virtual int NodeLower() const = 0;

  Standard_EXPORT virtual int NodeUpper() const = 0;

  gp_Pnt NodeTransformed(const int theNode) const
  {
    gp_Pnt aNode = node(theNode);
    aNode.Transform(myTrsf);
    return aNode;
  }

protected:
  virtual gp_Pnt node(const int theNode) const = 0;

  RWMesh_ShapeIterator(const TDF_Label&       theLabel,
                       const TopLoc_Location& theLocation,
                       const TopAbs_ShapeEnum theShapeTypeFind,
                       const TopAbs_ShapeEnum theShapeTypeAvoid,
                       const bool             theToMapColors = false,
                       const XCAFPrs_Style&   theStyle       = XCAFPrs_Style());

  RWMesh_ShapeIterator(const TopoDS_Shape&    theShape,
                       const TopAbs_ShapeEnum theShapeTypeFind,
                       const TopAbs_ShapeEnum theShapeTypeAvoid,
                       const XCAFPrs_Style&   theStyle = XCAFPrs_Style());

  void dispatchStyles(const TDF_Label&       theLabel,
                      const TopLoc_Location& theLocation,
                      const XCAFPrs_Style&   theStyle);

  void resetShape()
  {
    myHasColor = false;
    myColor    = Quantity_ColorRGBA();
    myStyle    = XCAFPrs_Style();
  }

  void initShape();

protected:
  NCollection_DataMap<TopoDS_Shape, XCAFPrs_Style, TopTools_ShapeMapHasher> myStyles;
  XCAFPrs_Style                                                             myDefStyle;
  bool                                                                      myToMapColors;

  TopExp_Explorer    myIter;
  TopLoc_Location    myLocation;
  gp_Trsf            myTrsf;
  XCAFPrs_Style      myStyle;
  Quantity_ColorRGBA myColor;
  TopAbs_ShapeEnum   myShapeType;
  bool               myHasColor;
};
