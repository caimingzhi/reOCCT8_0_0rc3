#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepRepr_MappedItem.hpp>
#include <StepRepr_NextAssemblyUsageOccurrence.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <STEPSelections_SelectAssembly.hpp>
#include <StepShape_ContextDependentShapeRepresentation.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPSelections_SelectAssembly, IFSelect_SelectExplore)

STEPSelections_SelectAssembly::STEPSelections_SelectAssembly()
    : IFSelect_SelectExplore(-1)
{
}

bool STEPSelections_SelectAssembly::Explore(const int /*level*/,
                                            const occ::handle<Standard_Transient>& start,
                                            const Interface_Graph&                 G,
                                            Interface_EntityIterator&              explored) const
{
  if (start.IsNull())
    return false;

  if (start->IsKind(STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation)))
  {
    DeclareAndCast(StepShape_ContextDependentShapeRepresentation, sdsr, start);
    occ::handle<StepRepr_ProductDefinitionShape> pds = sdsr->RepresentedProductRelation();
    if (pds.IsNull())
      return false;
    occ::handle<Standard_Transient> ent = pds->Definition().ProductDefinitionRelationship();
    if (ent.IsNull())
      return false;
    return (ent->IsKind(STANDARD_TYPE(StepRepr_NextAssemblyUsageOccurrence)));
  }

  if (start->IsKind(STANDARD_TYPE(StepRepr_MappedItem)))
  {
    DeclareAndCast(StepRepr_MappedItem, mapped, start);
    Interface_EntityIterator                   subs = G.Sharings(mapped);
    occ::handle<StepShape_ShapeRepresentation> shrep;
    for (subs.Start(); subs.More() && shrep.IsNull(); subs.Next())
      if (subs.Value()->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation)))
        shrep = occ::down_cast<StepShape_ShapeRepresentation>(subs.Value());
    if (shrep.IsNull())
      return false;

    subs = G.Sharings(shrep);
    occ::handle<StepShape_ShapeDefinitionRepresentation> shdefrep;
    for (subs.Start(); subs.More() && shdefrep.IsNull(); subs.Next())
      if (subs.Value()->IsKind(STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation)))
        shdefrep = occ::down_cast<StepShape_ShapeDefinitionRepresentation>(subs.Value());
    if (shdefrep.IsNull())
      return false;

    occ::handle<StepRepr_ProductDefinitionShape> pds =
      occ::down_cast<StepRepr_ProductDefinitionShape>(shdefrep->Definition().PropertyDefinition());
    if (pds.IsNull())
      return false;
    occ::handle<Standard_Transient> ent = pds->Definition().ProductDefinitionRelationship();
    if (ent.IsNull())
      return false;
    return (ent->IsKind(STANDARD_TYPE(StepRepr_NextAssemblyUsageOccurrence)));
  }

  Interface_EntityIterator subs = G.Shareds(start);
  subs.Start();
  bool isSome = subs.More();
  for (; subs.More(); subs.Next())
    explored.AddItem(subs.Value());

  return isSome;
}

TCollection_AsciiString STEPSelections_SelectAssembly::ExploreLabel() const
{
  return TCollection_AsciiString("Assembly components");
}
