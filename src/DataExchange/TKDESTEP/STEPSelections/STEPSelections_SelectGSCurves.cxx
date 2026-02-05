#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepGeom_CompositeCurve.hpp>
#include <StepGeom_CompositeCurveSegment.hpp>
#include <StepGeom_Curve.hpp>
#include <STEPSelections_SelectGSCurves.hpp>
#include <StepShape_GeometricSet.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPSelections_SelectGSCurves, IFSelect_SelectExplore)

namespace
{
  thread_local int flag;
} // namespace

STEPSelections_SelectGSCurves::STEPSelections_SelectGSCurves()
    : IFSelect_SelectExplore(-1)
{
  flag = 1;
}

bool STEPSelections_SelectGSCurves::Explore(const int /*level*/,
                                            const occ::handle<Standard_Transient>& start,
                                            const Interface_Graph&                 G,
                                            Interface_EntityIterator&              explored) const
{
  if (start.IsNull())
    return false;

  if (start->IsKind(STANDARD_TYPE(StepGeom_Curve)))
  {
    if (start->IsKind(STANDARD_TYPE(StepGeom_CompositeCurve)))
    {
      Interface_EntityIterator subs        = G.Sharings(start);
      bool                     isInGeomSet = false;
      for (subs.Start(); subs.More() && !isInGeomSet; subs.Next())
        if (subs.Value()->IsKind(STANDARD_TYPE(StepShape_GeometricSet)))
        {
          if (flag)
          {
            explored.AddItem(subs.Value());
            flag = 0;
          }
          isInGeomSet = true;
        }
      if (isInGeomSet)
      {
        Interface_EntityIterator aSubsShareds = G.Shareds(start);
        aSubsShareds.Start();
        bool isSome = aSubsShareds.More();
        for (; aSubsShareds.More(); aSubsShareds.Next())
          explored.AddItem(aSubsShareds.Value());
        return isSome;
      }
      else
        return false;
    }
    else
    {
      Interface_EntityIterator subs = G.Sharings(start);
      for (subs.Start(); subs.More(); subs.Next())
      {
        if (subs.Value()->IsKind(STANDARD_TYPE(StepShape_GeometricSet))
            || subs.Value()->IsKind(STANDARD_TYPE(StepGeom_CompositeCurveSegment)))
          return true;
      }
    }
  }

  Interface_EntityIterator subs = G.Shareds(start);
  subs.Start();
  bool isSome = subs.More();
  for (; subs.More(); subs.Next())
    explored.AddItem(subs.Value());

  return isSome;
}

TCollection_AsciiString STEPSelections_SelectGSCurves::ExploreLabel() const
{
  return TCollection_AsciiString("Curves in GS");
}
