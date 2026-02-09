

#include <IFSelect_BasicDumper.hpp>
#include <IFSelect_SessionDumper.hpp>
#include <IFSelect_SessionFile.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SessionDumper, Standard_Transient)

static occ::handle<IFSelect_SessionDumper> thefirst;
static int                                 cefait = 0;

IFSelect_SessionDumper::IFSelect_SessionDumper()
{
  if (!cefait)
  {
    cefait                                = 1;
    occ::handle<IFSelect_BasicDumper> bid = new IFSelect_BasicDumper;
  }
  else
    thenext = thefirst;
  thefirst = this;
}

occ::handle<IFSelect_SessionDumper> IFSelect_SessionDumper::First()
{
  return thefirst;
}

occ::handle<IFSelect_SessionDumper> IFSelect_SessionDumper::Next() const
{
  return thenext;
}
