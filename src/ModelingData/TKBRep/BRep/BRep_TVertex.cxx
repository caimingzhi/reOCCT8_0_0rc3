#include <BRep_TVertex.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_TVertex, TopoDS_TVertex)

BRep_TVertex::BRep_TVertex()
    : myTolerance(RealEpsilon())
{
}

occ::handle<TopoDS_TShape> BRep_TVertex::EmptyCopy() const
{
  occ::handle<BRep_TVertex> TV = new BRep_TVertex();
  TV->Pnt(myPnt);
  TV->Tolerance(myTolerance);
  return TV;
}

void BRep_TVertex::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TopoDS_TVertex)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myPnt)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myTolerance)
  for (NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itr(myPoints); itr.More();
       itr.Next())
  {
    const occ::handle<BRep_PointRepresentation>& aPointRepresentation = itr.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, aPointRepresentation.get())
  }
}
