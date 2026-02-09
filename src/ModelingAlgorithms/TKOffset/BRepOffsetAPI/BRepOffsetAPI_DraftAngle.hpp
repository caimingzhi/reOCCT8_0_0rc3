#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <BRepBuilderAPI_ModifyShape.hpp>
#include <Draft_ErrorStatus.hpp>
#include <BRepTools_ReShape.hpp>

class TopoDS_Shape;
class TopoDS_Face;
class gp_Dir;
class gp_Pln;

#ifdef Status
  #undef Status
#endif

class BRepOffsetAPI_DraftAngle : public BRepBuilderAPI_ModifyShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_DraftAngle();

  Standard_EXPORT BRepOffsetAPI_DraftAngle(const TopoDS_Shape& S);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT void Add(const TopoDS_Face& F,
                           const gp_Dir&      Direction,
                           const double       Angle,
                           const gp_Pln&      NeutralPlane,
                           const bool         Flag = true);

  Standard_EXPORT bool AddDone() const;

  Standard_EXPORT void Remove(const TopoDS_Face& F);

  Standard_EXPORT const TopoDS_Shape& ProblematicShape() const;

  Standard_EXPORT Draft_ErrorStatus Status() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ConnectedFaces(const TopoDS_Face& F) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ModifiedFaces() const;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT void CorrectWires();

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& S) override;

  Standard_EXPORT TopoDS_Shape ModifiedShape(const TopoDS_Shape& S) const override;

private:
  Standard_EXPORT void CorrectVertexTol();

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myVtxToReplace;
  BRepTools_ReShape                                                        mySubs;
};
