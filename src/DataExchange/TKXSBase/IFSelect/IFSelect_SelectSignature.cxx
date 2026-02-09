

#include <IFSelect_SelectSignature.hpp>
#include <IFSelect_Signature.hpp>
#include <IFSelect_SignCounter.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectSignature, IFSelect_SelectExtract)

static int multsign(const TCollection_AsciiString&                 signtext,
                    NCollection_Sequence<TCollection_AsciiString>& signlist,
                    NCollection_Sequence<int>&                     signmode)
{
  int i, nb = signtext.Length(), mode = 0;
  for (i = 1; i <= nb; i++)
  {
    char unsign = signtext.Value(i);
    if (unsign == '|' || unsign == '!' || unsign == '=')
    {
      mode = 1;
      break;
    }
    if (unsign == '<' || unsign == '>')
    {
      mode = 1;
      break;
    }
  }
  if (mode == 0)
    return mode;

  TCollection_AsciiString item;
  int                     imod = 1;
  for (i = 1; i <= nb; i++)
  {
    char unsign = signtext.Value(i);
    if (unsign == '|' || unsign == '!')
    {
      if (item.Length() > 0)
      {
        signlist.Append(item);
        signmode.Append(imod);
        item.Clear();
        mode++;
      }
      imod = (unsign == '|' ? 1 : 2);
    }
    else if (unsign == '<')
      imod += 16;
    else if (unsign == '>')
      imod += 32;
    else if (unsign == '=')
    {
      if (imod < 8)
        imod += 2;
      else
        imod += 8;
    }
    else
      item.AssignCat(unsign);
  }
  if (item.Length() > 0)
  {
    signlist.Append(item);
    signmode.Append(imod);
  }
  return mode;
}

IFSelect_SelectSignature::IFSelect_SelectSignature(const occ::handle<IFSelect_Signature>& matcher,
                                                   const TCollection_AsciiString&         signtext,
                                                   const bool                             exact)
    : thematcher(matcher),
      thesigntext(signtext),
      theexact(exact ? -1 : 0)
{
  if (!exact)
    theexact = multsign(thesigntext, thesignlist, thesignmode);
}

IFSelect_SelectSignature::IFSelect_SelectSignature(const occ::handle<IFSelect_Signature>& matcher,
                                                   const char*                            signtext,
                                                   const bool                             exact)
    : thematcher(matcher),
      thesigntext(signtext),
      theexact(exact ? -1 : 0)
{
  if (!exact)
    theexact = multsign(thesigntext, thesignlist, thesignmode);
}

IFSelect_SelectSignature::IFSelect_SelectSignature(const occ::handle<IFSelect_SignCounter>& counter,
                                                   const char* signtext,
                                                   const bool  exact)
    : thecounter(counter),
      thesigntext(signtext),
      theexact(exact ? -1 : 0)
{
  if (!exact)
    theexact = multsign(thesigntext, thesignlist, thesignmode);
}

occ::handle<IFSelect_Signature> IFSelect_SelectSignature::Signature() const
{
  return thematcher;
}

occ::handle<IFSelect_SignCounter> IFSelect_SelectSignature::Counter() const
{
  return thecounter;
}

bool IFSelect_SelectSignature::SortInGraph(const int,
                                           const occ::handle<Standard_Transient>& ent,
                                           const Interface_Graph&                 G) const
{
  bool                                         res;
  const char*                                  txt;
  const occ::handle<Interface_InterfaceModel>& model = G.Model();
  if (theexact <= 0)
  {
    if (!thematcher.IsNull())
      return thematcher->Matches(ent, model, thesigntext, (theexact < 0));
    txt = thecounter->ComputedSign(ent, G);
    return IFSelect_Signature::MatchValue(txt, thesigntext, (theexact < 0));
  }

  int hmod = thesignmode.Value(1);
  int jmod = hmod / 8;
  int imod = hmod - (jmod * 8);
  res      = (imod == 2 || imod == 4);
  for (int i = 1; i <= theexact; i++)
  {
    const char* signtext = thesignlist.Value(i).ToCString();
    hmod                 = thesignmode.Value(i);
    jmod                 = hmod / 8;
    imod                 = hmod - (jmod * 8);
    bool quid;
    if (jmod == 0)
    {
      if (!thematcher.IsNull())
        quid = thematcher->Matches(ent, model, signtext, (imod > 2));
      else
        quid =
          IFSelect_Signature::MatchValue(thecounter->ComputedSign(ent, G), signtext, (imod > 2));
    }
    else
    {
      if (!thematcher.IsNull())
        txt = thematcher->Value(ent, model);
      else
        txt = thecounter->ComputedSign(ent, G);

      int val = atoi(txt);
      int lav = atoi(signtext);
      switch (jmod)
      {
        case 2:
          quid = (val < lav);
          break;
        case 3:
          quid = (val <= lav);
          break;
        case 4:
          quid = (val > lav);
          break;
        case 5:
          quid = (val >= lav);
          break;
        default:
          quid = false;
          break;
      }
    }
    if ((imod == 1 || imod == 3) && quid)
      res = true;
    if ((imod == 2 || imod == 4) && quid)
      res = false;
  }
  return res;
}

bool IFSelect_SelectSignature::Sort(const int,
                                    const occ::handle<Standard_Transient>&,
                                    const occ::handle<Interface_InterfaceModel>&) const
{
  return true;
}

const TCollection_AsciiString& IFSelect_SelectSignature::SignatureText() const
{
  return thesigntext;
}

bool IFSelect_SelectSignature::IsExact() const
{
  return (theexact < 0);
}

TCollection_AsciiString IFSelect_SelectSignature::ExtractLabel() const
{
  TCollection_AsciiString lab;
  if (!thematcher.IsNull())
    lab.AssignCat(thematcher->Name());
  else
    lab.AssignCat(thecounter->Name());
  if (theexact < 0)
    lab.AssignCat(" matching ");
  else if (theexact == 0)
    lab.AssignCat(" containing ");
  else
    lab.AssignCat(" matching list ");
  lab.AssignCat(thesigntext);
  return lab;
}
