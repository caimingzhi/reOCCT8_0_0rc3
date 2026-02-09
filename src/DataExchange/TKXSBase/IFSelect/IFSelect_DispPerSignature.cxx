

#include <IFGraph_SubPartsIterator.hpp>
#include <IFSelect_DispPerSignature.hpp>
#include <IFSelect_Selection.hpp>
#include <IFSelect_SignCounter.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Transient.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IFSelect_DispPerSignature, IFSelect_Dispatch)

IFSelect_DispPerSignature::IFSelect_DispPerSignature() = default;

occ::handle<IFSelect_SignCounter> IFSelect_DispPerSignature::SignCounter() const
{
  return thesign;
}

void IFSelect_DispPerSignature::SetSignCounter(const occ::handle<IFSelect_SignCounter>& sign)
{
  thesign = sign;
  thesign->SetList(true);
}

const char* IFSelect_DispPerSignature::SignName() const
{
  return (const char*)(thesign.IsNull() ? "???" : thesign->Name());
}

TCollection_AsciiString IFSelect_DispPerSignature::Label() const
{
  char lab[50];
  Sprintf(lab, "One File per Signature %s", SignName());
  return TCollection_AsciiString(lab);
}

bool IFSelect_DispPerSignature::LimitedMax(const int nbent, int& max) const
{
  max = nbent;
  return true;
}

void IFSelect_DispPerSignature::Packets(const Interface_Graph&    G,
                                        IFGraph_SubPartsIterator& packs) const
{
  if (thesign.IsNull())
  {
    packs.AddPart();
    packs.GetFromIter(FinalSelection()->RootResult(G));
    return;
  }

  thesign->Clear();
  thesign->AddList(FinalSelection()->RootResult(G).Content(), G.Model());
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> list = thesign->List();
  int                                   i, nb, is, nbs = list->Length();
  occ::handle<TCollection_HAsciiString> asign;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> ents;
  for (is = 1; is <= nbs; is++)
  {
    asign = list->Value(is);
    ents  = thesign->Entities(asign->ToCString());
    if (ents.IsNull())
      continue;
    packs.AddPart();
    nb = ents->Length();
    for (i = 1; i <= nb; i++)
      packs.GetFromEntity(ents->Value(i), false);
  }
}
