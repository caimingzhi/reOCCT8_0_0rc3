#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Transfer_Binder.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_ShapeEnum.hpp>
class TopoDS_Shape;
class TopoDS_Vertex;
class TopoDS_Edge;
class TopoDS_Wire;
class TopoDS_Face;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_CompSolid;
class TopoDS_Compound;

//! This binder binds several (a list of) shapes with a starting
//! entity, when this entity itself corresponds to a simple list
//! of shapes. Each part is not seen as a sub-result of an
//! independent component, but as an item of a built-in list
class TransferBRep_ShapeListBinder : public Transfer_Binder
{

public:
  Standard_EXPORT TransferBRep_ShapeListBinder();

  Standard_EXPORT TransferBRep_ShapeListBinder(
    const occ::handle<NCollection_HSequence<TopoDS_Shape>>& list);

  Standard_EXPORT bool IsMultiple() const override;

  Standard_EXPORT occ::handle<Standard_Type> ResultType() const override;

  Standard_EXPORT const char* ResultTypeName() const override;

  //! Adds an item to the result list
  Standard_EXPORT void AddResult(const TopoDS_Shape& res);

  Standard_EXPORT occ::handle<NCollection_HSequence<TopoDS_Shape>> Result() const;

  //! Changes an already defined sub-result
  Standard_EXPORT void SetResult(const int num, const TopoDS_Shape& res);

  Standard_EXPORT int NbShapes() const;

  Standard_EXPORT const TopoDS_Shape& Shape(const int num) const;

  Standard_EXPORT TopAbs_ShapeEnum ShapeType(const int num) const;

  Standard_EXPORT TopoDS_Vertex Vertex(const int num) const;

  Standard_EXPORT TopoDS_Edge Edge(const int num) const;

  Standard_EXPORT TopoDS_Wire Wire(const int num) const;

  Standard_EXPORT TopoDS_Face Face(const int num) const;

  Standard_EXPORT TopoDS_Shell Shell(const int num) const;

  Standard_EXPORT TopoDS_Solid Solid(const int num) const;

  Standard_EXPORT TopoDS_CompSolid CompSolid(const int num) const;

  Standard_EXPORT TopoDS_Compound Compound(const int num) const;

  DEFINE_STANDARD_RTTIEXT(TransferBRep_ShapeListBinder, Transfer_Binder)

private:
  occ::handle<NCollection_HSequence<TopoDS_Shape>> theres;
};
