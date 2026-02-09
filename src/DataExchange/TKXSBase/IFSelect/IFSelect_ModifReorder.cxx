

#include <IFSelect_ContextModif.hpp>
#include <IFSelect_ModifReorder.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_ModifReorder, IFSelect_Modifier)

IFSelect_ModifReorder::IFSelect_ModifReorder(const bool rootlast)
    : IFSelect_Modifier(true)
{
  thertl = rootlast;
}

void IFSelect_ModifReorder::Perform(IFSelect_ContextModif&                       ctx,
                                    const occ::handle<Interface_InterfaceModel>& target,
                                    const occ::handle<Interface_Protocol>&,
                                    Interface_CopyTool&) const
{
  Interface_ShareTool      sht(ctx.OriginalGraph());
  Interface_EntityIterator list = sht.All(ctx.OriginalModel(), thertl);
  target->ClearEntities();
  for (list.Start(); list.More(); list.Next())
    target->AddEntity(list.Value());
}

TCollection_AsciiString IFSelect_ModifReorder::Label() const
{
  const char* astr = (const char*)(thertl ? "Reorder, Roots last" : "Reorder, Roots first");
  return TCollection_AsciiString(astr);
}
