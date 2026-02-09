#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepFeat_PerfSelection.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Face.hpp>
#include <BRepFeat_StatusError.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Edge;
class Geom_Plane;
class gp_Dir;
class Geom_Curve;
class TopoDS_Vertex;
class LocOpe_Gluer;
class BRepAlgoAPI_BooleanOperation;

class BRepFeat_RibSlot : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& F) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& F) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& FirstShape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& LastShape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& FacesForDraft() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& NewEdges() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& TgtEdges() const;

  Standard_EXPORT static double IntPar(const occ::handle<Geom_Curve>& C, const gp_Pnt& P);

  Standard_EXPORT static TopoDS_Face ChoiceOfFaces(NCollection_List<TopoDS_Shape>& faces,
                                                   const occ::handle<Geom_Curve>&  cc,
                                                   const double                    par,
                                                   const double                    bnd,
                                                   const occ::handle<Geom_Plane>&  Pln);

  Standard_EXPORT BRepFeat_StatusError CurrentStatusError() const;

protected:
  BRepFeat_RibSlot();

  Standard_EXPORT void LFPerform();

  Standard_EXPORT gp_Pnt CheckPoint(const TopoDS_Edge&             e,
                                    const double                   bnd,
                                    const occ::handle<Geom_Plane>& Pln);

  Standard_EXPORT gp_Dir Normal(const TopoDS_Face& F, const gp_Pnt& P);

  Standard_EXPORT void EdgeExtention(TopoDS_Edge& e, const double bnd, const bool FirstLast);

  Standard_EXPORT double HeightMax(const TopoDS_Shape& theSbase,
                                   const TopoDS_Shape& theSUntil,
                                   gp_Pnt&             p1,
                                   gp_Pnt&             p2);

  Standard_EXPORT bool ExtremeFaces(const bool                     RevolRib,
                                    const double                   bnd,
                                    const occ::handle<Geom_Plane>& Pln,
                                    TopoDS_Edge&                   FirstEdge,
                                    TopoDS_Edge&                   LastEdge,
                                    TopoDS_Face&                   FirstFace,
                                    TopoDS_Face&                   LastFace,
                                    TopoDS_Vertex&                 FirstVertex,
                                    TopoDS_Vertex&                 LastVertex,
                                    bool&                          OnFirstFace,
                                    bool&                          OnLastFace,
                                    bool&                          PtOnFirstEdge,
                                    bool&                          PtOnLastEdge,
                                    TopoDS_Edge&                   OnFirstEdge,
                                    TopoDS_Edge&                   OnLastEdge);

  Standard_EXPORT void PtOnEdgeVertex(const bool           RevolRib,
                                      const TopoDS_Shape&  shape,
                                      const gp_Pnt&        point,
                                      const TopoDS_Vertex& FirstVertex,
                                      const TopoDS_Vertex& LastVertex,
                                      bool&                PtOnEdge,
                                      TopoDS_Edge&         OnEdge,
                                      bool&                PtOnVertex,
                                      TopoDS_Vertex&       OnVertex);

  Standard_EXPORT bool SlidingProfile(TopoDS_Face&                   Prof,
                                      const bool                     RevolRib,
                                      const double                   myTol,
                                      int&                           Concavite,
                                      const occ::handle<Geom_Plane>& myPln,
                                      const TopoDS_Face&             BndFace,
                                      const gp_Pnt&                  CheckPnt,
                                      const TopoDS_Face&             FirstFace,
                                      const TopoDS_Face&             LastFace,
                                      const TopoDS_Vertex&           FirstVertex,
                                      const TopoDS_Vertex&           LastVertex,
                                      const TopoDS_Edge&             FirstEdge,
                                      const TopoDS_Edge&             LastEdge);

  Standard_EXPORT bool NoSlidingProfile(TopoDS_Face&                   Prof,
                                        const bool                     RevolRib,
                                        const double                   myTol,
                                        int&                           Concavite,
                                        const occ::handle<Geom_Plane>& myPln,
                                        const double                   bnd,
                                        const TopoDS_Face&             BndFace,
                                        const gp_Pnt&                  CheckPnt,
                                        const TopoDS_Face&             FirstFace,
                                        const TopoDS_Face&             LastFace,
                                        const TopoDS_Vertex&           FirstVertex,
                                        const TopoDS_Vertex&           LastVertex,
                                        const TopoDS_Edge&             FirstEdge,
                                        const TopoDS_Edge&             LastEdge,
                                        const bool                     OnFirstFace,
                                        const bool                     OnLastFace);

  Standard_EXPORT void UpdateDescendants(const LocOpe_Gluer& G);

  Standard_EXPORT void UpdateDescendants(const BRepAlgoAPI_BooleanOperation& aBOP,
                                         const TopoDS_Shape&                 SResult,
                                         const bool                          SkipFace = false);

  gp_Pnt myFirstPnt;
  gp_Pnt myLastPnt;
  bool   myFuse;
  bool   mySliding;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                           myLFMap;
  TopoDS_Shape                                                             myFShape;
  TopoDS_Shape                                                             myLShape;
  BRepFeat_PerfSelection                                                   myPerfSelection;
  TopoDS_Wire                                                              myWire;
  TopoDS_Shape                                                             mySbase;
  TopoDS_Face                                                              mySkface;
  TopoDS_Face                                                              myPbase;
  TopoDS_Shape                                                             myGShape;
  TopoDS_Shape                                                             mySUntil;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myGluedF;
  NCollection_List<TopoDS_Shape>                                           myNewEdges;
  NCollection_List<TopoDS_Shape>                                           myTgtEdges;
  NCollection_List<TopoDS_Shape>                                           myFacesForDraft;
  BRepFeat_StatusError                                                     myStatusError;
};

inline BRepFeat_RibSlot::BRepFeat_RibSlot()
    : myFuse(false),
      mySliding(false),
      myStatusError(BRepFeat_OK)
{
}
