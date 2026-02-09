#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>
#include <GeomAbs_JoinType.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class gp_Ax3;
class BRepMAT2d_BisectingLocus;
class BRepMAT2d_LinkTopoBilo;
class BRepTools_Quilt;
class TopLoc_Location;
class TopoDS_Edge;
class TopoDS_Vertex;

class BRepFill_Evolved
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_Evolved();

  Standard_EXPORT BRepFill_Evolved(const TopoDS_Wire&     Spine,
                                   const TopoDS_Wire&     Profile,
                                   const gp_Ax3&          AxeProf,
                                   const GeomAbs_JoinType Join  = GeomAbs_Arc,
                                   const bool             Solid = false);

  Standard_EXPORT BRepFill_Evolved(const TopoDS_Face&     Spine,
                                   const TopoDS_Wire&     Profile,
                                   const gp_Ax3&          AxeProf,
                                   const GeomAbs_JoinType Join  = GeomAbs_Arc,
                                   const bool             Solid = false);

  Standard_EXPORT void Perform(const TopoDS_Wire&     Spine,
                               const TopoDS_Wire&     Profile,
                               const gp_Ax3&          AxeProf,
                               const GeomAbs_JoinType Join  = GeomAbs_Arc,
                               const bool             Solid = false);

  Standard_EXPORT void Perform(const TopoDS_Face&     Spine,
                               const TopoDS_Wire&     Profile,
                               const gp_Ax3&          AxeProf,
                               const GeomAbs_JoinType Join  = GeomAbs_Arc,
                               const bool             Solid = false);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& GeneratedShapes(
    const TopoDS_Shape& SpineShape,
    const TopoDS_Shape& ProfShape) const;

  Standard_EXPORT GeomAbs_JoinType JoinType() const;

  Standard_EXPORT const TopoDS_Shape& Top() const;

  Standard_EXPORT const TopoDS_Shape& Bottom() const;

private:
  Standard_EXPORT void PrivatePerform(const TopoDS_Face&     Spine,
                                      const TopoDS_Wire&     Profile,
                                      const gp_Ax3&          AxeProf,
                                      const GeomAbs_JoinType Join  = GeomAbs_Arc,
                                      const bool             Solid = false);

  Standard_EXPORT void SetWork(const TopoDS_Face& Spine, const TopoDS_Wire& Profile);

  Standard_EXPORT void ElementaryPerform(const TopoDS_Face&              Spine,
                                         const TopoDS_Wire&              Profile,
                                         const BRepMAT2d_BisectingLocus& Locus,
                                         BRepMAT2d_LinkTopoBilo&         Link,
                                         const GeomAbs_JoinType          Join = GeomAbs_Arc);

  Standard_EXPORT void PlanarPerform(const TopoDS_Face&              Spine,
                                     const TopoDS_Wire&              Profile,
                                     const BRepMAT2d_BisectingLocus& Locus,
                                     BRepMAT2d_LinkTopoBilo&         Link,
                                     const GeomAbs_JoinType          Join = GeomAbs_Arc);

  Standard_EXPORT void VerticalPerform(const TopoDS_Face&              Spine,
                                       const TopoDS_Wire&              Profile,
                                       const BRepMAT2d_BisectingLocus& Locus,
                                       BRepMAT2d_LinkTopoBilo&         Link,
                                       const GeomAbs_JoinType          Join = GeomAbs_Arc);

  Standard_EXPORT NCollection_DataMap<
    TopoDS_Shape,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>,
    TopTools_ShapeMapHasher>&
    Generated();

  Standard_EXPORT void Add(BRepFill_Evolved& Vevo, const TopoDS_Wire& Prof, BRepTools_Quilt& Glue);

  Standard_EXPORT TopoDS_Shape& ChangeShape();

  Standard_EXPORT void Transfert(
    BRepFill_Evolved&                                                               Vevo,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& MapProf,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& MapSpine,
    const TopLoc_Location&                                                          LS,
    const TopLoc_Location&                                                          InitLS,
    const TopLoc_Location&                                                          InitLP);

  Standard_EXPORT void PrepareProfile(
    NCollection_List<TopoDS_Shape>&                                           WorkProf,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& MapProf) const;

  Standard_EXPORT void PrepareSpine(
    TopoDS_Face&                                                              WorkSpine,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& SpineProf) const;

  Standard_EXPORT void MakePipe(const TopoDS_Edge& SpineEdge, const gp_Ax3& ProfRef);

  Standard_EXPORT void MakeRevol(const TopoDS_Edge&   SpineEdge,
                                 const TopoDS_Vertex& SpineVertex,
                                 const gp_Ax3&        ProfRef);

  Standard_EXPORT TopLoc_Location FindLocation(const TopoDS_Face& Face) const;

  Standard_EXPORT void TransformInitWork(const TopLoc_Location& LS, const TopLoc_Location& LP);

  Standard_EXPORT void ContinuityOnOffsetEdge(const NCollection_List<TopoDS_Shape>& WorkProf);

  Standard_EXPORT void AddTopAndBottom(BRepTools_Quilt& Glue);

  Standard_EXPORT void MakeSolid();

  TopoDS_Face      mySpine;
  TopoDS_Wire      myProfile;
  TopoDS_Shape     myShape;
  bool             myIsDone;
  bool             mySpineType;
  GeomAbs_JoinType myJoinType;
  NCollection_DataMap<
    TopoDS_Shape,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>,
    TopTools_ShapeMapHasher>
               myMap;
  TopoDS_Shape myTop;
  TopoDS_Shape myBottom;
};
