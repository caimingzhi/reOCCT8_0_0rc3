

#include <IFSelect_SelectSignedShared.hpp>
#include <IFSelect_Signature.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectSignedShared, IFSelect_SelectExplore)

IFSelect_SelectSignedShared::IFSelect_SelectSignedShared(
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

occ::handle<IFSelect_Signature> IFSelect_SelectSignedShared::Signature() const
{
  return thematcher;
}

const TCollection_AsciiString& IFSelect_SelectSignedShared::SignatureText() const
{
  return thesigntext;
}

bool IFSelect_SelectSignedShared::IsExact() const
{
  return theexact;
}

bool IFSelect_SelectSignedShared::Explore(const int                              level,
                                          const occ::handle<Standard_Transient>& ent,
                                          const Interface_Graph&                 G,
                                          Interface_EntityIterator&              explored) const
{
  if (thematcher->Matches(ent, G.Model(), thesigntext, theexact))
    return true;

  Interface_EntityIterator list = G.Shareds(ent);

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

TCollection_AsciiString IFSelect_SelectSignedShared::ExploreLabel() const
{
  TCollection_AsciiString lab("Shared,");
  lab.AssignCat(thematcher->Name());
  if (theexact)
    lab.AssignCat(" matching ");
  else
    lab.AssignCat(" containing ");
  lab.AssignCat(thesigntext);
  return lab;
}
