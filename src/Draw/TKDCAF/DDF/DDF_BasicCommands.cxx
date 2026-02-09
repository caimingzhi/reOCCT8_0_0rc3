#include <DDF.hpp>

#include <TDF_ComparisonTool.hpp>

#include <DDF_Data.hpp>

#include <Draw_Appli.hpp>
#include <Draw_Interpretor.hpp>
#include <Standard_NotImplemented.hpp>

#include <TCollection_AsciiString.hpp>

#include <TDF_AttributeIterator.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_Data.hpp>
#include <TDF_IDFilter.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>
#include <TDF_DerivedAttribute.hpp>

static int DDF_Children(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<TDF_Data>   DF;
  TCollection_AsciiString entry;

  if (!DDF::GetDF(a[1], DF))
    return 1;

  TDF_Label lab;
  if (n == 3)
    TDF_Tool::Label(DF, a[2], lab);

  if (lab.IsNull())
  {
    di << "0";
  }
  else
  {
    for (TDF_ChildIterator itr(lab); itr.More(); itr.Next())
    {
      TDF_Tool::Entry(itr.Value(), entry);

      di << entry.ToCString() << " ";
    }
  }
  return 0;
}

static int DDF_Attributes(Draw_Interpretor& di, int n, const char** a)
{
  if (n != 3)
    return 1;

  occ::handle<TDF_Data> DF;

  if (!DDF::GetDF(a[1], DF))
    return 1;

  TDF_Label lab;
  TDF_Tool::Label(DF, a[2], lab);

  if (lab.IsNull())
    return 1;

  for (TDF_AttributeIterator itr(lab); itr.More(); itr.Next())
  {
    di << itr.Value()->DynamicType()->Name() << " ";
  }
  return 0;
}

static int DDF_SetEmptyAttribute(Draw_Interpretor& di, int n, const char** a)
{
  if (n != 4)
    return 1;

  occ::handle<TDF_Data> DF;

  if (!DDF::GetDF(a[1], DF))
    return 1;

  TDF_Label lab;
  TDF_Tool::Label(DF, a[2], lab);

  if (lab.IsNull())
    return 1;

  occ::handle<TDF_Attribute> anAttrByType = TDF_DerivedAttribute::Attribute(a[3]);
  if (anAttrByType.IsNull())
  {
    di << "DDF: Not registered attribute type '" << a[3] << "'\n";
    return 1;
  }

  lab.AddAttribute(anAttrByType);

  return 0;
}

static int DDF_ForgetAll(Draw_Interpretor&, int n, const char** a)
{
  if (n != 3)
    return 1;

  occ::handle<TDF_Data> DF;

  if (!DDF::GetDF(a[1], DF))
    return 1;

  TDF_Label label;
  TDF_Tool::Label(DF, a[2], label);
  if (label.IsNull())
    return 1;
  label.ForgetAllAttributes();

  return 0;
}

static int DDF_ForgetAttribute(Draw_Interpretor& di, int n, const char** a)
{
  if (n != 4)
    return 1;
  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(a[1], DF))
    return 1;

  TDF_Label aLabel;
  TDF_Tool::Label(DF, a[2], aLabel);
  if (aLabel.IsNull())
    return 1;
  if (!Standard_GUID::CheckGUIDFormat(a[3]))
  {

    occ::handle<TDF_Attribute> anAttrByType = TDF_DerivedAttribute::Attribute(a[3]);
    if (!anAttrByType.IsNull())
    {
      aLabel.ForgetAttribute(anAttrByType->ID());
      return 0;
    }
    di << "DDF: The format of GUID is invalid\n";
    return 1;
  }
  Standard_GUID guid(a[3]);
  aLabel.ForgetAttribute(guid);
  return 0;
}

static int DDF_SetTagger(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 3)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(arg[1], DF))
      return 1;
    TDF_Label L;
    DDF::AddLabel(DF, arg[2], L);
    TDF_TagSource::Set(L);
    return 0;
  }
  di << "DDF_SetTagger : Error\n";
  return 1;
}

static int DDF_NewTag(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 3)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(arg[1], DF))
      return 1;
    occ::handle<TDF_TagSource> A;
    if (!DDF::Find(DF, arg[2], TDF_TagSource::GetID(), A))
      return 1;
    di << A->NewTag();
    return 0;
  }
  di << "DDF_NewTag : Error\n";
  return 1;
}

static int DDF_NewChild(Draw_Interpretor& di, int nb, const char** arg)
{
  occ::handle<TDF_Data> DF;
  if (nb >= 2)
  {
    if (!DDF::GetDF(arg[1], DF))
      return 1;
    if (nb == 2)
    {
      TDF_Label free = TDF_TagSource::NewChild(DF->Root());
      di << free.Tag();
      return 0;
    }
    else if (nb == 3)
    {
      TDF_Label fatherlabel;
      if (!DDF::FindLabel(DF, arg[2], fatherlabel))
        return 1;
      TDF_Label free = TDF_TagSource::NewChild(fatherlabel);
      di << arg[2] << ":" << free.Tag();
      return 0;
    }
  }
  di << "DDF_NewChild : Error\n";
  return 1;
}

static int DDF_Label(Draw_Interpretor& di, int n, const char** a)
{
  if (n == 3)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(a[1], DF))
      return 1;
    TDF_Label L;
    if (!DDF::FindLabel(DF, a[2], L, false))
    {
      DDF::AddLabel(DF, a[2], L);
    }

    DDF::ReturnLabel(di, L);
    return 0;
  }
  di << "DDF_Label : Error\n";
  return 1;
}

void DDF::BasicCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  const char* g = "DF basic commands";

  theCommands.Add("SetTagger", "SetTagger (DF, entry)", __FILE__, DDF_SetTagger, g);

  theCommands.Add("NewTag", "NewTag (DF, tagger)", __FILE__, DDF_NewTag, g);

  theCommands.Add("NewChild", "NewChild (DF, [tagger])", __FILE__, DDF_NewChild, g);

  theCommands.Add("Children",
                  " Returns the list of label children: Children DF label",
                  __FILE__,
                  DDF_Children,
                  g);

  theCommands.Add("Attributes",
                  " Returns the list of label attributes: Attributes DF label",
                  __FILE__,
                  DDF_Attributes,
                  g);

  theCommands.Add(
    "SetEmptyAttribute",
    "Sets an empty attribute by its type (like TDataStd_Tick): SetEmptyAttribute DF label type",
    __FILE__,
    DDF_SetEmptyAttribute,
    g);

  theCommands.Add("ForgetAll",
                  "Forgets all attributes from the label: ForgetAll DF Label",
                  __FILE__,
                  DDF_ForgetAll,
                  g);

  theCommands.Add("ForgetAtt",
                  "Forgets the specified by guid attribute or type from the label: ForgetAtt DF "
                  "Label guid_or_type",
                  __FILE__,
                  DDF_ForgetAttribute,
                  g);

  theCommands.Add("Label", "Label DF entry", __FILE__, DDF_Label, g);
}
