

#include <IFSelect_Transformer.hpp>
#include <Interface_CheckIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_Transformer, Standard_Transient)

bool IFSelect_Transformer::ChangeProtocol(occ::handle<Interface_Protocol>&) const
{
  return false;
}
