#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <TopOpeBRepTool_ShapeExplorer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_OStream.hpp>

class TopOpeBRepBuild_ShapeSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_ShapeSet(const TopAbs_ShapeEnum SubShapeType,
                                           const bool             checkshape = true);

  Standard_EXPORT virtual ~TopOpeBRepBuild_ShapeSet();

  Standard_EXPORT virtual void AddShape(const TopoDS_Shape& S);

  Standard_EXPORT virtual void AddStartElement(const TopoDS_Shape& S);

  Standard_EXPORT virtual void AddElement(const TopoDS_Shape& S);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& StartElements() const;

  Standard_EXPORT void InitShapes();

  Standard_EXPORT bool MoreShapes() const;

  Standard_EXPORT void NextShape();

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT void InitStartElements();

  Standard_EXPORT bool MoreStartElements() const;

  Standard_EXPORT void NextStartElement();

  Standard_EXPORT const TopoDS_Shape& StartElement() const;

  Standard_EXPORT virtual void InitNeighbours(const TopoDS_Shape& S);

  Standard_EXPORT bool MoreNeighbours();

  Standard_EXPORT void NextNeighbour();

  Standard_EXPORT const TopoDS_Shape& Neighbour() const;

  Standard_EXPORT NCollection_List<TopoDS_Shape>& ChangeStartShapes();

  Standard_EXPORT virtual void FindNeighbours();

  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& MakeNeighboursList(
    const TopoDS_Shape& E,
    const TopoDS_Shape& V);

  Standard_EXPORT int MaxNumberSubShape(const TopoDS_Shape& Shape);

  Standard_EXPORT void CheckShape(const bool checkshape);

  Standard_EXPORT bool CheckShape() const;

  Standard_EXPORT bool CheckShape(const TopoDS_Shape& S, const bool checkgeom = false);

  Standard_EXPORT void DumpName(Standard_OStream& OS, const TCollection_AsciiString& str) const;

  Standard_EXPORT void DumpCheck(Standard_OStream&              OS,
                                 const TCollection_AsciiString& str,
                                 const TopoDS_Shape&            S,
                                 const bool                     chk) const;

  Standard_EXPORT virtual void DumpSS();

  Standard_EXPORT virtual void DumpBB();

  Standard_EXPORT void DEBName(const TCollection_AsciiString& N);

  Standard_EXPORT const TCollection_AsciiString& DEBName() const;

  Standard_EXPORT void DEBNumber(const int I);

  Standard_EXPORT int DEBNumber() const;

  Standard_EXPORT virtual TCollection_AsciiString SName(
    const TopoDS_Shape&            S,
    const TCollection_AsciiString& sb = "",
    const TCollection_AsciiString& sa = "") const;

  Standard_EXPORT virtual TCollection_AsciiString SNameori(
    const TopoDS_Shape&            S,
    const TCollection_AsciiString& sb = "",
    const TCollection_AsciiString& sa = "") const;

  Standard_EXPORT virtual TCollection_AsciiString SName(
    const NCollection_List<TopoDS_Shape>& S,
    const TCollection_AsciiString&        sb = "",
    const TCollection_AsciiString&        sa = "") const;

  Standard_EXPORT virtual TCollection_AsciiString SNameori(
    const NCollection_List<TopoDS_Shape>& S,
    const TCollection_AsciiString&        sb = "",
    const TCollection_AsciiString&        sa = "") const;

protected:
  Standard_EXPORT void ProcessAddShape(const TopoDS_Shape& S);

  Standard_EXPORT void ProcessAddStartElement(const TopoDS_Shape& S);

  Standard_EXPORT void ProcessAddElement(const TopoDS_Shape& S);

  TopAbs_ShapeEnum                         myShapeType;
  TopAbs_ShapeEnum                         mySubShapeType;
  TopOpeBRepTool_ShapeExplorer             mySubShapeExplorer;
  NCollection_List<TopoDS_Shape>           myStartShapes;
  NCollection_List<TopoDS_Shape>::Iterator myStartShapesIter;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                           mySubShapeMap;
  NCollection_List<TopoDS_Shape>::Iterator myIncidentShapesIter;
  NCollection_List<TopoDS_Shape>           myShapes;
  NCollection_List<TopoDS_Shape>::Iterator myShapesIter;
  TopoDS_Shape                             myCurrentShape;
  NCollection_List<TopoDS_Shape>           myCurrentShapeNeighbours;
  int                                      myDEBNumber;
  TCollection_AsciiString                  myDEBName;
  NCollection_IndexedMap<TopoDS_Shape>     myOMSS;
  NCollection_IndexedMap<TopoDS_Shape>     myOMES;
  NCollection_IndexedMap<TopoDS_Shape>     myOMSH;
  bool                                     myCheckShape;
};
