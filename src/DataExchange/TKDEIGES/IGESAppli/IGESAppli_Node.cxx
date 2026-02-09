#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESAppli_Node.hpp>
#include <IGESGeom_TransformationMatrix.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_Node, IGESData_IGESEntity)

IGESAppli_Node::IGESAppli_Node() = default;

void IGESAppli_Node::Init(const gp_XYZ&                                     aCoord,
                          const occ::handle<IGESGeom_TransformationMatrix>& aCoordSystem)
{
  theCoord  = aCoord;
  theSystem = aCoordSystem;
  InitTypeAndForm(134, 0);
}

gp_Pnt IGESAppli_Node::Coord() const
{
  return gp_Pnt(theCoord);
}

occ::handle<IGESData_TransfEntity> IGESAppli_Node::System() const
{

  return occ::handle<IGESData_TransfEntity>(theSystem);
}

int IGESAppli_Node::SystemType() const
{
  if (theSystem.IsNull())
    return 0;
  return (theSystem->FormNumber() - 9);
}

gp_Pnt IGESAppli_Node::TransformedNodalCoord() const
{
  gp_XYZ                             tempCoord = Coord().XYZ();
  occ::handle<IGESData_TransfEntity> temp      = System();
  if (!temp.IsNull())
    temp->Value().Transforms(tempCoord);
  return gp_Pnt(tempCoord);
}
