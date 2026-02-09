

#include <IFSelect_SelectSignedSharing.hpp>
#include <IFSelect_Signature.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectSignedSharing, IFSelect_SelectExplore)

IFSelect_SelectSignedSharing::IFSelect_SelectSignedSharing(
  const occ::handle<IFSelect_Signature>& matcher,
  const char*                            signtext,
  const bool                             exact,
  const int                              level)
    : IFSelect_SelectExplore(level),
      thematcher(matcher),
      thesigntext(signtext),
      theexact(exact)
{
}

occ::handle<IFSelect_Signature> IFSelect_SelectSignedSharing::Signature() const
{
  return thematcher;
}

const TCollection_AsciiString& IFSelect_SelectSignedSharing::SignatureText() const
{
  return thesigntext;
}

bool IFSelect_SelectSignedSharing::IsExact() const
{
  return theexact;
}

bool IFSelect_SelectSignedSharing::Explore(const int                              level,
                                           const occ::handle<Standard_Transient>& ent,
                                           const Interface_Graph&                 G,
                                           Interface_EntityIterator&              explored) const
{
  if (thematcher->Matches(ent, G.Model(), thesigntext, theexact))
    return true;

  Interface_EntityIterator list = G.Sharings(ent);

  if (list.NbEntities() == 0)
    return false;

  if (level < Level())
  {
    explored = list;
    return true;
  }
  for (list.Start(); list.More(); list.Next())
  {
    if (thematcher->Matches(list.Value(), G.Model(), thesigntext, theexact))
      explored.AddItem(list.Value());
  }
  return true;
}

TCollection_AsciiString IFSelect_SelectSignedSharing::ExploreLabel() const
{
  TCollection_AsciiString lab("Sharing,");
  lab.AssignCat(thematcher->Name());
  if (theexact)
    lab.AssignCat(" matching ");
  else
    lab.AssignCat(" containing ");
  lab.AssignCat(thesigntext);
  return lab;
}
