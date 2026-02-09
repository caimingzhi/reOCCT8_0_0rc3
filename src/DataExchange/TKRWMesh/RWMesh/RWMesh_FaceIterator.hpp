#pragma once

#include <RWMesh_ShapeIterator.hpp>

#include <BRepLProp_SLProps.hpp>
#include <Poly_Triangulation.hpp>
#include <TopoDS_Face.hpp>

#include <algorithm>

class TDF_Label;

class RWMesh_FaceIterator : public RWMesh_ShapeIterator
{
public:
  Standard_EXPORT RWMesh_FaceIterator(const TDF_Label&       theLabel,
                                      const TopLoc_Location& theLocation,
                                      const bool             theToMapColors = false,
                                      const XCAFPrs_Style&   theStyle       = XCAFPrs_Style());

  Standard_EXPORT RWMesh_FaceIterator(const TopoDS_Shape&  theShape,
                                      const XCAFPrs_Style& theStyle = XCAFPrs_Style());

  bool More() const override { return !myPolyTriang.IsNull(); }

  Standard_EXPORT void Next() override;

  const TopoDS_Face& Face() const { return myFace; }

  const TopoDS_Shape& Shape() const override { return myFace; }

  const occ::handle<Poly_Triangulation>& Triangulation() const { return myPolyTriang; }

  bool IsEmptyMesh() const { return IsEmpty(); }

  bool IsEmpty() const override
  {
    return myPolyTriang.IsNull()
           || (myPolyTriang->NbNodes() < 1 && myPolyTriang->NbTriangles() < 1);
  }

public:
  const XCAFPrs_Style& FaceStyle() const { return myStyle; }

  bool HasFaceColor() const { return myHasColor; }

  const Quantity_ColorRGBA& FaceColor() const { return myColor; }

public:
  int NbTriangles() const { return myPolyTriang->NbTriangles(); }

  int ElemLower() const override { return 1; }

  int ElemUpper() const override { return myPolyTriang->NbTriangles(); }

  Poly_Triangle TriangleOriented(int theElemIndex) const
  {
    Poly_Triangle aTri = triangle(theElemIndex);
    if ((myFace.Orientation() == TopAbs_REVERSED) ^ myIsMirrored)
    {
      return Poly_Triangle(aTri.Value(1), aTri.Value(3), aTri.Value(2));
    }
    return aTri;
  }

public:
  bool HasNormals() const { return myHasNormals; }

  bool HasTexCoords() const { return !myPolyTriang.IsNull() && myPolyTriang->HasUVNodes(); }

  gp_Dir NormalTransformed(int theNode) const
  {
    gp_Dir aNorm = normal(theNode);
    if (myTrsf.Form() != gp_Identity)
    {
      aNorm.Transform(myTrsf);
    }
    if (myFace.Orientation() == TopAbs_REVERSED)
    {
      aNorm.Reverse();
    }
    return aNorm;
  }

  int NbNodes() const override { return !myPolyTriang.IsNull() ? myPolyTriang->NbNodes() : 0; }

  int NodeLower() const override { return 1; }

  int NodeUpper() const override { return myPolyTriang->NbNodes(); }

  gp_Pnt2d NodeTexCoord(const int theNode) const
  {
    return myPolyTriang->HasUVNodes() ? myPolyTriang->UVNode(theNode) : gp_Pnt2d();
  }

public:
  gp_Pnt node(const int theNode) const override { return myPolyTriang->Node(theNode); }

  Standard_EXPORT gp_Dir normal(int theNode) const;

  Poly_Triangle triangle(int theElemIndex) const { return myPolyTriang->Triangle(theElemIndex); }

private:
  void resetFace()
  {
    myPolyTriang.Nullify();
    myFace.Nullify();
    myHasNormals = false;
    resetShape();
  }

  void initFace();

private:
  TopoDS_Face                     myFace;
  occ::handle<Poly_Triangulation> myPolyTriang;
  mutable BRepLProp_SLProps       mySLTool;
  BRepAdaptor_Surface             myFaceAdaptor;
  bool                            myHasNormals;
  bool                            myIsMirrored;
};
