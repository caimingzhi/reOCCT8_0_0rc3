#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepFill_ThruSectionErrorStatus.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <TopoDS_Face.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <GeomAbs_Shape.hpp>
#include <Approx_ParametrizationType.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Handle.hpp>

class TopoDS_Wire;
class TopoDS_Vertex;
class TopoDS_Shape;
class Geom_BSplineSurface;
class BRepFill_Generator;

class BRepOffsetAPI_ThruSections : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_ThruSections(const bool   isSolid = false,
                                             const bool   ruled   = false,
                                             const double pres3d  = 1.0e-06);

  Standard_EXPORT void Init(const bool   isSolid = false,
                            const bool   ruled   = false,
                            const double pres3d  = 1.0e-06);

  Standard_EXPORT void AddWire(const TopoDS_Wire& wire);

  Standard_EXPORT void AddVertex(const TopoDS_Vertex& aVertex);

  Standard_EXPORT void CheckCompatibility(const bool check = true);

  Standard_EXPORT void SetSmoothing(const bool UseSmoothing);

  Standard_EXPORT void SetParType(const Approx_ParametrizationType ParType);

  Standard_EXPORT void SetContinuity(const GeomAbs_Shape C);

  Standard_EXPORT void SetCriteriumWeight(const double W1, const double W2, const double W3);

  Standard_EXPORT void SetMaxDegree(const int MaxDeg);

  Standard_EXPORT Approx_ParametrizationType ParType() const;

  Standard_EXPORT GeomAbs_Shape Continuity() const;

  Standard_EXPORT int MaxDegree() const;

  Standard_EXPORT bool UseSmoothing() const;

  Standard_EXPORT void CriteriumWeight(double& W1, double& W2, double& W3) const;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT const TopoDS_Shape& FirstShape() const;

  Standard_EXPORT const TopoDS_Shape& LastShape() const;

  Standard_EXPORT TopoDS_Shape GeneratedFace(const TopoDS_Shape& Edge) const;

  Standard_EXPORT void SetMutableInput(const bool theIsMutableInput);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  const NCollection_List<TopoDS_Shape>& Wires() const { return myInputWires; }

  Standard_EXPORT bool IsMutableInput() const;

  BRepFill_ThruSectionErrorStatus GetStatus() const { return myStatus; }

private:
  Standard_EXPORT void CreateRuled();

  Standard_EXPORT void CreateSmoothed();

  Standard_EXPORT occ::handle<Geom_BSplineSurface> TotalSurf(
    const NCollection_Array1<TopoDS_Shape>& shapes,
    const int                               NbSect,
    const int                               NbEdges,
    const bool                              w1Point,
    const bool                              w2Point,
    const bool                              vClosed) const;

  NCollection_List<TopoDS_Shape>     myInputWires;
  NCollection_Sequence<TopoDS_Shape> myWires;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<int>, TopTools_ShapeMapHasher>
                                                                           myEdgeNewIndices;
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>          myVertexIndex;
  int                                                                      myNbEdgesInSection;
  bool                                                                     myIsSolid;
  bool                                                                     myIsRuled;
  bool                                                                     myWCheck;
  double                                                                   myPres3d;
  TopoDS_Face                                                              myFirst;
  TopoDS_Face                                                              myLast;
  bool                                                                     myDegen1;
  bool                                                                     myDegen2;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myEdgeFace;
  GeomAbs_Shape                                                            myContinuity;
  Approx_ParametrizationType                                               myParamType;
  int                                                                      myDegMax;
  double                                                                   myCritWeights[3];
  bool                                                                     myUseSmoothing;
  bool                                                                     myMutableInput;
  NCollection_Handle<BRepFill_Generator>                                   myBFGenerator;
  BRepFill_ThruSectionErrorStatus                                          myStatus;
};
