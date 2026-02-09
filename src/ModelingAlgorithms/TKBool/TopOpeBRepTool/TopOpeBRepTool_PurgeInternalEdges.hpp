#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Integer.hpp>

class TopOpeBRepTool_PurgeInternalEdges
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_PurgeInternalEdges(const TopoDS_Shape& theShape,
                                                    const bool          PerformNow = true);

  Standard_EXPORT void Faces(
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      theMapFacLstEdg);

  Standard_EXPORT TopoDS_Shape& Shape();

  Standard_EXPORT int NbEdges() const;

  bool IsDone() const { return myIsDone; }

  Standard_EXPORT void Perform();

protected:
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myMapEdgLstFac;

private:
  Standard_EXPORT void BuildList();

private:
  TopoDS_Shape myShape;
  bool         myIsDone;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myMapFacLstEdg;
};
