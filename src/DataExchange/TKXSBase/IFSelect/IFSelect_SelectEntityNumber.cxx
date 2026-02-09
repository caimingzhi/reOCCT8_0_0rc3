

#include <IFSelect_IntParam.hpp>
#include <IFSelect_SelectEntityNumber.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectEntityNumber, IFSelect_SelectBase)

IFSelect_SelectEntityNumber::IFSelect_SelectEntityNumber() = default;

void IFSelect_SelectEntityNumber::SetNumber(const occ::handle<IFSelect_IntParam>& num)
{
  thenum = num;
}

occ::handle<IFSelect_IntParam> IFSelect_SelectEntityNumber::Number() const
{
  return thenum;
}

Interface_EntityIterator IFSelect_SelectEntityNumber::RootResult(const Interface_Graph& G) const
{
  Interface_EntityIterator iter;
  int                      num = 0;
  if (!thenum.IsNull())
    num = thenum->Value();
  if (num < 1)
    return iter;
  if (num <= G.Size())
    iter.GetOneItem(G.Entity(num));
  return iter;
}

TCollection_AsciiString IFSelect_SelectEntityNumber::Label() const
{
  int num = 0;
  if (!thenum.IsNull())
    num = thenum->Value();
  TCollection_AsciiString labl(num);
  labl.InsertBefore(1, "Entity Number ");
  return labl;
}
