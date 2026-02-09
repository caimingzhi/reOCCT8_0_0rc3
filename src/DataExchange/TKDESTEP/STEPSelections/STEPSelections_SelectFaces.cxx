#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepGeom_Surface.hpp>
#include <STEPSelections_SelectFaces.hpp>
#include <StepShape_FaceSurface.hpp>
#include <StepShape_GeometricSet.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPSelections_SelectFaces, IFSelect_SelectExplore)

STEPSelections_SelectFaces::STEPSelections_SelectFaces()
    : IFSelect_SelectExplore(-1)
{
}

bool STEPSelections_SelectFaces::Explore(const int,
                                         const occ::handle<Standard_Transient>& start,
                                         const Interface_Graph&                 G,
                                         Interface_EntityIterator&              explored) const
{
  if (start.IsNull())
    return false;

  if (start->IsKind(STANDARD_TYPE(StepShape_FaceSurface)))
    return true;

  bool isInFaceOfInSurface = false;
  if (start->IsKind(STANDARD_TYPE(StepGeom_Surface)))
  {
    Interface_EntityIterator subs = G.Sharings(start);
    for (subs.Start(); subs.More(); subs.Next())
    {
      if (subs.Value()->IsKind(STANDARD_TYPE(StepShape_GeometricSet)))
        return true;
      if (subs.Value()->IsKind(STANDARD_TYPE(StepGeom_Surface)))
        isInFaceOfInSurface = true;
      if (subs.Value()->IsKind(STANDARD_TYPE(StepShape_FaceSurface)))
        isInFaceOfInSurface = true;
    }
    return !isInFaceOfInSurface;
  }
  Interface_EntityIterator subs = G.Shareds(start);
  subs.Start();
  bool isSome = subs.More();
  for (; subs.More(); subs.Next())
    explored.AddItem(subs.Value());

  return isSome;
}

TCollection_AsciiString STEPSelections_SelectFaces::ExploreLabel() const
{
  return TCollection_AsciiString("Faces");
}
