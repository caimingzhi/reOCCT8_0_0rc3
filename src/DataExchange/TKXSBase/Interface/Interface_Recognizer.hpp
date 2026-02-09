#include <Standard_NoSuchObject.hpp>

Interface_Recognizer::Interface_Recognizer()
{
  hasnext = false;
}

bool Interface_Recognizer::Evaluate(const TheKey& akey, occ::handle<TheResul>& res)
{
  theres.Nullify();
  Eval(akey);
  if (!theres.IsNull())
  {
    res = theres;
    return true;
  }
  else if (hasnext)
    return thenext->Evaluate(akey, res);
  return false;
}

occ::handle<TheResul> Interface_Recognizer::Result() const
{
  if (!theres.IsNull())
    return theres;
  if (hasnext)
    return thenext->Result();
  throw Standard_NoSuchObject("Recognizer evaluation has failed");
}

void Interface_Recognizer::Add(const occ::handle<Interface_Recognizer>& reco)
{
  thenext = reco;
  hasnext = true;
}

void Interface_Recognizer::SetOK(const occ::handle<TheResul>& aresult)
{
  theres = aresult;
}

void Interface_Recognizer::SetKO()
{
  theres.Nullify();
}
