#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Transient.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <Standard_Integer.hpp>
class StepData_StepModel;
class TopoDS_Shape;
class StepShape_TopologicalRepresentationItem;

class TopoDSToStep_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_Tool(const occ::handle<StepData_StepModel>& theModel);

  Standard_EXPORT TopoDSToStep_Tool(const NCollection_DataMap<TopoDS_Shape,
                                                              occ::handle<Standard_Transient>,
                                                              TopTools_ShapeMapHasher>& M,
                                    const bool FacetedContext,
                                    int        theSurfCurveMode);

  Standard_EXPORT void Init(const NCollection_DataMap<TopoDS_Shape,
                                                      occ::handle<Standard_Transient>,
                                                      TopTools_ShapeMapHasher>& M,
                            const bool                                          FacetedContext,
                            int                                                 theSurfCurveMode);

  Standard_EXPORT bool IsBound(const TopoDS_Shape& S);

  Standard_EXPORT void Bind(const TopoDS_Shape&                                         S,
                            const occ::handle<StepShape_TopologicalRepresentationItem>& T);

  Standard_EXPORT occ::handle<StepShape_TopologicalRepresentationItem> Find(const TopoDS_Shape& S);

  Standard_EXPORT bool Faceted() const;

  Standard_EXPORT void SetCurrentShell(const TopoDS_Shell& S);

  Standard_EXPORT const TopoDS_Shell& CurrentShell() const;

  Standard_EXPORT void SetCurrentFace(const TopoDS_Face& F);

  Standard_EXPORT const TopoDS_Face& CurrentFace() const;

  Standard_EXPORT void SetCurrentWire(const TopoDS_Wire& W);

  Standard_EXPORT const TopoDS_Wire& CurrentWire() const;

  Standard_EXPORT void SetCurrentEdge(const TopoDS_Edge& E);

  Standard_EXPORT const TopoDS_Edge& CurrentEdge() const;

  Standard_EXPORT void SetCurrentVertex(const TopoDS_Vertex& V);

  Standard_EXPORT const TopoDS_Vertex& CurrentVertex() const;

  Standard_EXPORT double Lowest3DTolerance() const;

  Standard_EXPORT void SetSurfaceReversed(const bool B);

  Standard_EXPORT bool SurfaceReversed() const;

  Standard_EXPORT const NCollection_DataMap<TopoDS_Shape,
                                            occ::handle<Standard_Transient>,
                                            TopTools_ShapeMapHasher>&
                        Map() const;

  Standard_EXPORT int PCurveMode() const;

private:
  NCollection_DataMap<TopoDS_Shape, occ::handle<Standard_Transient>, TopTools_ShapeMapHasher>
                myDataMap;
  bool          myFacetedContext;
  double        myLowestTol;
  TopoDS_Shell  myCurrentShell;
  TopoDS_Face   myCurrentFace;
  TopoDS_Wire   myCurrentWire;
  TopoDS_Edge   myCurrentEdge;
  TopoDS_Vertex myCurrentVertex;
  bool          myReversedSurface;
  int           myPCurveMode;
};
