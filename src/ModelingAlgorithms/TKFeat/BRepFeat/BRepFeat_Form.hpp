#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepFeat_PerfSelection.hpp>
#include <TopoDS_Face.hpp>
#include <BRepFeat_StatusError.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
class Geom_Curve;
class LocOpe_Gluer;
class BRepAlgoAPI_BooleanOperation;

class BRepFeat_Form : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& F) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& S) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& FirstShape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& LastShape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& NewEdges() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& TgtEdges() const;

  void BasisShapeValid();

  void GeneratedShapeValid();

  void ShapeFromValid();

  void ShapeUntilValid();

  void GluedFacesValid();

  void SketchFaceValid();

  void PerfSelectionValid();

  Standard_EXPORT virtual void Curves(NCollection_Sequence<occ::handle<Geom_Curve>>& S) = 0;

  Standard_EXPORT virtual occ::handle<Geom_Curve> BarycCurve() = 0;

  Standard_EXPORT BRepFeat_StatusError CurrentStatusError() const;

protected:
  BRepFeat_Form();

  Standard_EXPORT void GlobalPerform();

  Standard_EXPORT void UpdateDescendants(const LocOpe_Gluer& G);

  Standard_EXPORT void UpdateDescendants(const BRepAlgoAPI_BooleanOperation& aBOP,
                                         const TopoDS_Shape&                 SResult,
                                         const bool                          SkipFace = false);

  Standard_EXPORT bool TransformShapeFU(const int flag);

  bool myFuse;
  bool myModify;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
  TopoDS_Shape                                                             myFShape;
  TopoDS_Shape                                                             myLShape;
  NCollection_List<TopoDS_Shape>                                           myNewEdges;
  NCollection_List<TopoDS_Shape>                                           myTgtEdges;
  BRepFeat_PerfSelection                                                   myPerfSelection;
  bool                                                                     myJustGluer;
  bool                                                                     myJustFeat;
  TopoDS_Shape                                                             mySbase;
  TopoDS_Face                                                              mySkface;
  TopoDS_Shape                                                             myGShape;
  TopoDS_Shape                                                             mySFrom;
  TopoDS_Shape                                                             mySUntil;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myGluedF;

private:
  bool                 mySbOK;
  bool                 mySkOK;
  bool                 myGSOK;
  bool                 mySFOK;
  bool                 mySUOK;
  bool                 myGFOK;
  bool                 myPSOK;
  BRepFeat_StatusError myStatusError;
};

inline BRepFeat_Form::BRepFeat_Form()
    : myFuse(false),
      myModify(false),
      myPerfSelection(BRepFeat_NoSelection),
      myJustGluer(false),
      myJustFeat(false),
      mySbOK(false),
      mySkOK(false),
      myGSOK(false),
      mySFOK(false),
      mySUOK(false),
      myGFOK(false),
      myPSOK(false),
      myStatusError(BRepFeat_NotInitialized)

{
}

inline void BRepFeat_Form::BasisShapeValid()
{
  mySbOK = true;
}

inline void BRepFeat_Form::PerfSelectionValid()
{
  myPSOK = true;
}

inline void BRepFeat_Form::GeneratedShapeValid()
{
  myGSOK = true;
}

inline void BRepFeat_Form::ShapeFromValid()
{
  mySFOK = true;
}

inline void BRepFeat_Form::ShapeUntilValid()
{
  mySUOK = true;
}

inline void BRepFeat_Form::GluedFacesValid()
{
  myGFOK = true;
}

inline void BRepFeat_Form::SketchFaceValid()
{
  mySkOK = true;
}
