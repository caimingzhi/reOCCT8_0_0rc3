#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESSolid_BooleanTree.hpp>
#include <IGESSolid_SelectedComponent.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_SelectedComponent, IGESData_IGESEntity)

IGESSolid_SelectedComponent::IGESSolid_SelectedComponent() = default;

void IGESSolid_SelectedComponent::Init(const occ::handle<IGESSolid_BooleanTree>& anEntity,
                                       const gp_XYZ&                             SelectPnt)
{
  theEntity      = anEntity;
  theSelectPoint = SelectPnt;
  InitTypeAndForm(182, 0);
}

occ::handle<IGESSolid_BooleanTree> IGESSolid_SelectedComponent::Component() const
{
  return theEntity;
}

gp_Pnt IGESSolid_SelectedComponent::SelectPoint() const
{
  return gp_Pnt(theSelectPoint);
}

gp_Pnt IGESSolid_SelectedComponent::TransformedSelectPoint() const
{
  if (!HasTransf())
    return gp_Pnt(theSelectPoint);
  else
  {
    gp_XYZ tmp = theSelectPoint;
    Location().Transforms(tmp);
    return gp_Pnt(tmp);
  }
}
