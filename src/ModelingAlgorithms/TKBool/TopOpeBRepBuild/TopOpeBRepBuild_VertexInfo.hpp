#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Vertex.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>

class TopOpeBRepBuild_VertexInfo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_VertexInfo();

  Standard_EXPORT void SetVertex(const TopoDS_Vertex& aV);

  Standard_EXPORT const TopoDS_Vertex& Vertex() const;

  Standard_EXPORT void SetSmart(const bool aFlag);

  Standard_EXPORT bool Smart() const;

  Standard_EXPORT int NbCases() const;

  Standard_EXPORT int FoundOut() const;

  Standard_EXPORT void AddIn(const TopoDS_Edge& anE);

  Standard_EXPORT void AddOut(const TopoDS_Edge& anE);

  Standard_EXPORT void SetCurrentIn(const TopoDS_Edge& anE);

  Standard_EXPORT const NCollection_IndexedMap<TopoDS_Shape>& EdgesIn() const;

  Standard_EXPORT const NCollection_IndexedMap<TopoDS_Shape>& EdgesOut() const;

  Standard_EXPORT NCollection_IndexedMap<TopoDS_Shape>& ChangeEdgesOut();

  Standard_EXPORT void Dump() const;

  Standard_EXPORT const TopoDS_Edge& CurrentOut();

  Standard_EXPORT void AppendPassed(const TopoDS_Edge& anE);

  Standard_EXPORT void RemovePassed();

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ListPassed() const;

  Standard_EXPORT void Prepare(const NCollection_List<TopoDS_Shape>& aL);

private:
  TopoDS_Vertex                        myVertex;
  TopoDS_Edge                          myCurrent;
  TopoDS_Edge                          myCurrentIn;
  bool                                 mySmart;
  NCollection_IndexedMap<TopoDS_Shape> myEdgesIn;
  NCollection_IndexedMap<TopoDS_Shape> myEdgesOut;
  NCollection_IndexedMap<TopoDS_Shape> myLocalEdgesOut;
  NCollection_List<TopoDS_Shape>       myEdgesPassed;
  int                                  myFoundOut;
};

