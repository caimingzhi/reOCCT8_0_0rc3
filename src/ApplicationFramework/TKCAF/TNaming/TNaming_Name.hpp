#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TNaming_NameType.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TNaming_NamedShape.hpp>
#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <TDF_Label.hpp>
#include <TopAbs_Orientation.hpp>
#include <NCollection_Map.hpp>
class TNaming_NamedShape;
class TDF_RelocationTable;

class TNaming_Name
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TNaming_Name();

  Standard_EXPORT void Type(const TNaming_NameType aType);

  Standard_EXPORT void ShapeType(const TopAbs_ShapeEnum aType);

  Standard_EXPORT void Shape(const TopoDS_Shape& theShape);

  Standard_EXPORT void Append(const occ::handle<TNaming_NamedShape>& arg);

  Standard_EXPORT void StopNamedShape(const occ::handle<TNaming_NamedShape>& arg);

  Standard_EXPORT void Index(const int I);

  Standard_EXPORT void ContextLabel(const TDF_Label& theLab);

  Standard_EXPORT void Orientation(const TopAbs_Orientation theOrientation);

  Standard_EXPORT TNaming_NameType Type() const;

  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const;

  Standard_EXPORT TopoDS_Shape Shape() const;

  Standard_EXPORT const NCollection_List<occ::handle<TNaming_NamedShape>>& Arguments() const;

  Standard_EXPORT occ::handle<TNaming_NamedShape> StopNamedShape() const;

  Standard_EXPORT int Index() const;

  Standard_EXPORT const TDF_Label& ContextLabel() const;

  TopAbs_Orientation Orientation() const { return myOrientation; }

  Standard_EXPORT bool Solve(const TDF_Label& aLab, const NCollection_Map<TDF_Label>& Valid) const;

  Standard_EXPORT void Paste(TNaming_Name& into, const occ::handle<TDF_RelocationTable>& RT) const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  TNaming_NameType                                  myType;
  TopAbs_ShapeEnum                                  myShapeType;
  NCollection_List<occ::handle<TNaming_NamedShape>> myArgs;
  occ::handle<TNaming_NamedShape>                   myStop;
  int                                               myIndex;
  TopoDS_Shape                                      myShape;
  TDF_Label                                         myContextLabel;
  TopAbs_Orientation                                myOrientation;
};
