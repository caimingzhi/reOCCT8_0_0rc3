#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <HLRAlgo_Projector.hpp>
#include <HLRBRep_ShapeBounds.hpp>
#include <NCollection_Sequence.hpp>
#include <TopoDS_Shape.hpp>
#include <BRepTopAdaptor_Tool.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class HLRBRep_Data;
class HLRTopoBRep_OutLiner;
class HLRBRep_ShapeBounds;

class HLRBRep_InternalAlgo : public Standard_Transient
{

public:
  Standard_EXPORT HLRBRep_InternalAlgo();

  Standard_EXPORT HLRBRep_InternalAlgo(const occ::handle<HLRBRep_InternalAlgo>& A);

  Standard_EXPORT void Projector(const HLRAlgo_Projector& P);

  Standard_EXPORT HLRAlgo_Projector& Projector();

  Standard_EXPORT void Update();

  Standard_EXPORT void Load(const occ::handle<HLRTopoBRep_OutLiner>& S,
                            const occ::handle<Standard_Transient>&   SData,
                            const int                                nbIso = 0);

  Standard_EXPORT void Load(const occ::handle<HLRTopoBRep_OutLiner>& S, const int nbIso = 0);

  Standard_EXPORT int Index(const occ::handle<HLRTopoBRep_OutLiner>& S) const;

  Standard_EXPORT void Remove(const int I);

  Standard_EXPORT void ShapeData(const int I, const occ::handle<Standard_Transient>& SData);

  Standard_EXPORT NCollection_Sequence<HLRBRep_ShapeBounds>& SeqOfShapeBounds();

  Standard_EXPORT int NbShapes() const;

  Standard_EXPORT HLRBRep_ShapeBounds& ShapeBounds(const int I);

  Standard_EXPORT void InitEdgeStatus();

  Standard_EXPORT void Select();

  Standard_EXPORT void Select(const int I);

  Standard_EXPORT void SelectEdge(const int I);

  Standard_EXPORT void SelectFace(const int I);

  Standard_EXPORT void ShowAll();

  Standard_EXPORT void ShowAll(const int I);

  Standard_EXPORT void HideAll();

  Standard_EXPORT void HideAll(const int I);

  Standard_EXPORT void PartialHide();

  Standard_EXPORT void Hide();

  Standard_EXPORT void Hide(const int I);

  Standard_EXPORT void Hide(const int I, const int J);

  Standard_EXPORT void Debug(const bool deb);

  Standard_EXPORT bool Debug() const;

  Standard_EXPORT occ::handle<HLRBRep_Data> DataStructure() const;

  DEFINE_STANDARD_RTTIEXT(HLRBRep_InternalAlgo, Standard_Transient)

private:
  Standard_EXPORT void HideSelected(const int I, const bool SideFace);

  occ::handle<HLRBRep_Data>                                                       myDS;
  HLRAlgo_Projector                                                               myProj;
  NCollection_Sequence<HLRBRep_ShapeBounds>                                       myShapes;
  NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher> myMapOfShapeTool;
  bool                                                                            myDebug;
};
