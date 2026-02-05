#include <BRepBuilderAPI_Sewing.hpp>
#include <BRepOffsetAPI_FindContigousEdges.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_OutOfRange.hpp>
#include <TopoDS_Shape.hpp>

//=================================================================================================

BRepOffsetAPI_FindContigousEdges::BRepOffsetAPI_FindContigousEdges(const double tolerance,
                                                                   const bool   option)
{
  mySewing = new BRepBuilderAPI_Sewing;
  Init(tolerance, option);
}

//=================================================================================================

void BRepOffsetAPI_FindContigousEdges::Init(const double tolerance, const bool option)
{
  mySewing->Init(tolerance, option, false, true);
}

//=================================================================================================

void BRepOffsetAPI_FindContigousEdges::Add(const TopoDS_Shape& aShape)
{
  mySewing->Add(aShape);
}

//=================================================================================================

void BRepOffsetAPI_FindContigousEdges::Perform()
{
  mySewing->Perform();
}

//=================================================================================================

int BRepOffsetAPI_FindContigousEdges::NbContigousEdges() const
{
  return mySewing->NbContigousEdges();
}

//=================================================================================================

const TopoDS_Edge& BRepOffsetAPI_FindContigousEdges::ContigousEdge(const int index) const
{
  Standard_OutOfRange_Raise_if(index < 0 || index > NbContigousEdges(),
                               "BRepOffsetAPI_FindContigousEdges::ContigousEdge");
  return mySewing->ContigousEdge(index);
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& BRepOffsetAPI_FindContigousEdges::ContigousEdgeCouple(
  const int index) const
{
  Standard_OutOfRange_Raise_if(index < 0 || index > NbContigousEdges(),
                               "BRepOffsetAPI_FindContigousEdges::ContigousEdgeCouple");
  return mySewing->ContigousEdgeCouple(index);
}

//=================================================================================================

const TopoDS_Edge& BRepOffsetAPI_FindContigousEdges::SectionToBoundary(
  const TopoDS_Edge& section) const
{
  Standard_NoSuchObject_Raise_if(!mySewing->IsSectionBound(section),
                                 "BRepOffsetAPI_FindContigousEdges::SectionToBoundary");
  return mySewing->SectionToBoundary(section);
}

//=================================================================================================

int BRepOffsetAPI_FindContigousEdges::NbDegeneratedShapes() const
{
  return mySewing->NbDegeneratedShapes();
}

//=================================================================================================

const TopoDS_Shape& BRepOffsetAPI_FindContigousEdges::DegeneratedShape(const int index) const
{
  Standard_OutOfRange_Raise_if(index < 0 || index > NbDegeneratedShapes(),
                               "BRepOffsetAPI_FindContigousEdges::DegereratedShape");
  return mySewing->DegeneratedShape(index);
}

//=================================================================================================

bool BRepOffsetAPI_FindContigousEdges::IsDegenerated(const TopoDS_Shape& aShape) const
{
  return mySewing->IsDegenerated(aShape);
}

//=================================================================================================

bool BRepOffsetAPI_FindContigousEdges::IsModified(const TopoDS_Shape& aShape) const
{
  return mySewing->IsModified(aShape);
}

//=================================================================================================

const TopoDS_Shape& BRepOffsetAPI_FindContigousEdges::Modified(const TopoDS_Shape& aShape) const
{
  Standard_NoSuchObject_Raise_if(!IsModified(aShape), "BRepOffsetAPI_FindContigousEdges::Modified");
  return mySewing->Modified(aShape);
}

//=================================================================================================

void BRepOffsetAPI_FindContigousEdges::Dump() const
{
  mySewing->Dump();
}
