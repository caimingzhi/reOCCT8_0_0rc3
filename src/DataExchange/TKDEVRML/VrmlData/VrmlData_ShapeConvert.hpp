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

/**
 * Algorithm converting one shape or a set of shapes to VrmlData_Scene.
 */

class VrmlData_ShapeConvert
{
public:
  typedef struct
  {
    TCollection_AsciiString    Name;
    TopoDS_Shape               Shape;
    occ::handle<VrmlData_Node> Node;
  } ShapeData;

  // ---------- PUBLIC METHODS ----------

  /**
   * Constructor.
   * @param theScene
   *   Scene receiving all Vrml data.
   * @param theScale
   *   Scale factor, considering that VRML standard specifies coordinates in
   *   meters. So if your data are in mm, you should provide theScale=0.001
   */
  inline VrmlData_ShapeConvert(VrmlData_Scene& theScene, const double theScale = 1.)
      : myScene(theScene),
        myScale(theScale),
        myDeflection(0.0),
        myDeflAngle(0.0)
  {
  }

  /**
   * Add one shape to the internal list, may be called several times with
   * different shapes.
   */
  Standard_EXPORT void AddShape(const TopoDS_Shape& theShape, const char* theName = nullptr);

  /**
   * Convert all accumulated shapes and store them in myScene.
   * The internal data structures are cleared in the end of conversion.
   * @param theExtractFaces
   *   If True,  converter extracst faces from the shapes.
   * @param theExtractEdges
   *   If True,  converter extracts edges from the shapes.
   * @param theDeflection
   *   Deflection for tessellation of geometrical lines/surfaces. Existing mesh
   *   is used if its deflection is smaller than the one given by this
   *   parameter.
   * @param theDeflAngle
   *   Angular deflection for tessellation of geometrical lines.
   */
  Standard_EXPORT void Convert(const bool   theExtractFaces,
                               const bool   theExtractEdges,
                               const double theDeflection = 0.01,
                               const double theDeflAngle  = 20. * M_PI / 180.);
  // this value of theDeflAngle is used by default
  // for tessellation while shading (Drawer->HLRAngle())

  /**
   * Add all shapes start from given document with colors and names to the internal structure
   */
  Standard_EXPORT void ConvertDocument(const occ::handle<TDocStd_Document>& theDoc);

protected:
  // ---------- PROTECTED METHODS ----------

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
  // ---------- PRIVATE FIELDS ----------

  VrmlData_Scene&             myScene;
  double                      myScale;
  NCollection_List<ShapeData> myShapes;

  double                                                            myDeflection;
  double                                                            myDeflAngle;
  NCollection_DataMap<TopoDS_Shape, occ::handle<VrmlData_Geometry>> myRelMap;

  // ---------- PRIVATE METHODS ----------
  void operator=(const VrmlData_ShapeConvert&) = delete;
};

