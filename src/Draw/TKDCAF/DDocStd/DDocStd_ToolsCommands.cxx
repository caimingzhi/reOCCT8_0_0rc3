#include <DDocStd.hpp>

#include <Draw.hpp>
#include <Draw_Interpretor.hpp>
#include <TDocStd_Document.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDF_Tool.hpp>
#include <TDF_AttributeDelta.hpp>
#include <TDF_Delta.hpp>
#include <TDF_DeltaOnAddition.hpp>
#include <TDF_DeltaOnForget.hpp>
#include <TDF_DeltaOnResume.hpp>
#include <TDF_DeltaOnRemoval.hpp>
#include <TDF_DeltaOnModification.hpp>
#include <NCollection_List.hpp>
#include <Standard_DomainError.hpp>

static int DDocStd_UpdateXLinks(Draw_Interpretor&, int n, const char** a)
{
  if (n < 3)
    return 1;
  occ::handle<TDocStd_Document> D;
  if (!DDocStd::GetDocument(a[1], D))
    return 1;
  TCollection_AsciiString Entry(a[2]);
  D->UpdateReferences(Entry);

  return 0;
}

static int DDocStd_DumpCommand(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 2)
  {
    occ::handle<TDocStd_Document> D;
    if (!DDocStd::GetDocument(arg[1], D))
      return 1;

    NCollection_List<occ::handle<TDF_AttributeDelta>> added, forgoten, resumed, removed, modified;
    occ::handle<TDF_AttributeDelta>                   AD;
    if (D->GetUndos().IsEmpty())
    {
      di << "no UNDO available\n";
      return 0;
    }
    occ::handle<TDF_Delta>                                      DELTA = D->GetUndos().Last();
    NCollection_List<occ::handle<TDF_AttributeDelta>>::Iterator it(DELTA->AttributeDeltas());
    for (; it.More(); it.Next())
    {
      AD = it.Value();
      if (AD->IsKind(STANDARD_TYPE(TDF_DeltaOnAddition)))
      {
        added.Append(AD);
      }
      else if (AD->IsKind(STANDARD_TYPE(TDF_DeltaOnForget)))
      {
        forgoten.Append(AD);
      }
      else if (AD->IsKind(STANDARD_TYPE(TDF_DeltaOnResume)))
      {
        resumed.Append(AD);
      }
      else if (AD->IsKind(STANDARD_TYPE(TDF_DeltaOnRemoval)))
      {
        removed.Append(AD);
      }
      else if (AD->IsKind(STANDARD_TYPE(TDF_DeltaOnModification)))
      {
        modified.Append(AD);
      }
      else
      {
        throw Standard_DomainError("DDocStd_DumpCommand : unknown delta");
      }
    }

    TCollection_AsciiString string;

    TCollection_AsciiString name;
    di << "ADDED    :";
    it.Initialize(added);
    if (it.More())
      di << "\n";
    else
      di << " empty\n";
    for (; it.More(); it.Next())
    {
      TDF_Tool::Entry(it.Value()->Label(), string);
      di << "- " << string.ToCString() << " ";
      di << it.Value()->Attribute()->DynamicType()->Name();
      di << "\n";
    }

    di << "FORGOTEN :";
    it.Initialize(forgoten);
    if (it.More())
      di << "\n";
    else
      di << " empty\n";
    for (; it.More(); it.Next())
    {
      TDF_Tool::Entry(it.Value()->Label(), string);
      di << "- " << string.ToCString() << " ";
      di << it.Value()->Attribute()->DynamicType()->Name();
      di << "\n";
    }

    di << "RESUMED  :";
    it.Initialize(resumed);
    if (it.More())
      di << "\n";
    else
      di << " empty\n";
    for (; it.More(); it.Next())
    {
      TDF_Tool::Entry(it.Value()->Label(), string);
      di << "- " << string.ToCString() << " ";
      di << it.Value()->Attribute()->DynamicType()->Name();
      di << "\n";
    }

    di << "REMOVED  :";
    it.Initialize(removed);
    if (it.More())
      di << "\n";
    else
      di << " empty\n";
    for (; it.More(); it.Next())
    {
      TDF_Tool::Entry(it.Value()->Label(), string);
      di << "- " << string.ToCString() << " ";
      di << it.Value()->Attribute()->DynamicType()->Name();
      di << "\n";
    }

    di << "MODIFIED :";
    it.Initialize(modified);
    if (it.More())
      di << "\n";
    else
      di << " empty\n";
    for (; it.More(); it.Next())
    {
      TDF_Tool::Entry(it.Value()->Label(), string);
      di << "- " << string.ToCString() << " ";
      di << it.Value()->Attribute()->DynamicType()->Name();
      di << "\n";
    }
    return 0;
  }
  di << "TDocStd_DumpCommand : Error\n";
  return 1;
}

void DDocStd::ToolsCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  const char* g = "DDocStd commands";

  theCommands.Add("UpdateXLinks",
                  "UpdateXLinks DocName DocEntry",
                  __FILE__,
                  DDocStd_UpdateXLinks,
                  g);

  theCommands.Add("DumpCommand", "DumpCommand (DOC)", __FILE__, DDocStd_DumpCommand, g);
}
