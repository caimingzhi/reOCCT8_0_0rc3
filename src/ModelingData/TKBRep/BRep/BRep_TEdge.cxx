#include <BRep_CurveOn2Surfaces.hpp>
#include <BRep_CurveRepresentation.hpp>
#include <BRep_GCurve.hpp>
#include <BRep_TEdge.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_TEdge, TopoDS_TEdge)

static const int ParameterMask   = 1;
static const int RangeMask       = 2;
static const int DegeneratedMask = 4;

BRep_TEdge::BRep_TEdge()
    : myTolerance(RealEpsilon()),
      myFlags(0)
{
  SameParameter(true);
  SameRange(true);
}

bool BRep_TEdge::SameParameter() const
{
  return (myFlags & ParameterMask) != 0;
}

void BRep_TEdge::SameParameter(const bool S)
{
  if (S)
    myFlags |= ParameterMask;
  else
    myFlags &= ~ParameterMask;
}

bool BRep_TEdge::SameRange() const
{
  return (myFlags & RangeMask) != 0;
}

void BRep_TEdge::SameRange(const bool S)
{
  if (S)
    myFlags |= RangeMask;
  else
    myFlags &= ~RangeMask;
}

bool BRep_TEdge::Degenerated() const
{
  return (myFlags & DegeneratedMask) != 0;
}

void BRep_TEdge::Degenerated(const bool S)
{
  if (S)
    myFlags |= DegeneratedMask;
  else
    myFlags &= ~DegeneratedMask;
}

occ::handle<TopoDS_TShape> BRep_TEdge::EmptyCopy() const
{
  occ::handle<BRep_TEdge> TE = new BRep_TEdge();
  TE->Tolerance(myTolerance);

  NCollection_List<occ::handle<BRep_CurveRepresentation>>&          l = TE->ChangeCurves();
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itr(myCurves);

  while (itr.More())
  {

    if (itr.Value()->IsKind(STANDARD_TYPE(BRep_GCurve))
        || itr.Value()->IsKind(STANDARD_TYPE(BRep_CurveOn2Surfaces)))
    {
      l.Append(itr.Value()->Copy());
    }
    itr.Next();
  }

  TE->Degenerated(Degenerated());
  TE->SameParameter(SameParameter());
  TE->SameRange(SameRange());

  return TE;
}

void BRep_TEdge::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TopoDS_TEdge)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myTolerance)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myFlags)

  for (NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itr(myCurves); itr.More();
       itr.Next())
  {
    const occ::handle<BRep_CurveRepresentation>& aCurveRepresentation = itr.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, aCurveRepresentation.get())
  }
}
