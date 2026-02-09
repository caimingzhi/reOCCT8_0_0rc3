#pragma once

#include <VrmlData_Geometry.hpp>
#include <VrmlData_Group.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Shape.hpp>

class VrmlData_Scene;
class VrmlData_Coordinate;
class TopoDS_Face;
class Poly_Polygon3D;
class Poly_Triangulation;
class XCAFPrs_Style;
class TDocStd_Document;
class TDF_Label;

class VrmlData_ShapeConvert
{
public:
  typedef struct
  {
    TCollection_AsciiString    Name;
    TopoDS_Shape               Shape;
    occ::handle<VrmlData_Node> Node;
  } ShapeData;

  inline VrmlData_ShapeConvert(VrmlData_Scene& theScene, const double theScale = 1.)
      : myScene(theScene),
        myScale(theScale),
        myDeflection(0.0),
        myDeflAngle(0.0)
  {
  }

  Standard_EXPORT void AddShape(const TopoDS_Shape& theShape, const char* theName = nullptr);

  Standard_EXPORT void Convert(const bool   theExtractFaces,
                               const bool   theExtractEdges,
                               const double theDeflection = 0.01,
                               const double theDeflAngle  = 20. * M_PI / 180.);

  Standard_EXPORT void ConvertDocument(const occ::handle<TDocStd_Document>& theDoc);

protected:
  occ::handle<VrmlData_Geometry> triToIndexedFaceSet(const occ::handle<Poly_Triangulation>&,
                                                     const TopoDS_Face&,
                                                     const occ::handle<VrmlData_Coordinate>&);

  occ::handle<VrmlData_Geometry> polToIndexedLineSet(const occ::handle<Poly_Polygon3D>&);

  occ::handle<VrmlData_Appearance> defaultMaterialFace() const;

  occ::handle<VrmlData_Appearance> defaultMaterialEdge() const;

  occ::handle<VrmlData_Geometry> makeTShapeNode(const TopoDS_Shape&    theShape,
                                                const TopAbs_ShapeEnum theShapeType,
                                                TopLoc_Location&       theLoc);

  void addAssembly(const occ::handle<VrmlData_Group>&   theParent,
                   const TDF_Label&                     theLabel,
                   const occ::handle<TDocStd_Document>& theDoc,
                   const bool                           theNeedCreateGroup);

  void addInstance(const occ::handle<VrmlData_Group>&   theParent,
                   const TDF_Label&                     theLabel,
                   const occ::handle<TDocStd_Document>& theDoc);

  void addShape(const occ::handle<VrmlData_Group>&   theParent,
                const TDF_Label&                     theLabel,
                const occ::handle<TDocStd_Document>& theDoc);

  occ::handle<VrmlData_Appearance> makeMaterialFromStyle(const XCAFPrs_Style& theStyle,
                                                         const TDF_Label&     theAttribLab) const;

private:
  VrmlData_Scene&             myScene;
  double                      myScale;
  NCollection_List<ShapeData> myShapes;

  double                                                            myDeflection;
  double                                                            myDeflAngle;
  NCollection_DataMap<TopoDS_Shape, occ::handle<VrmlData_Geometry>> myRelMap;

  void operator=(const VrmlData_ShapeConvert&) = delete;
};
