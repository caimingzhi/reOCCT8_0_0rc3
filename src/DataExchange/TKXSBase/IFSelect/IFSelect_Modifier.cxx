

#include <IFSelect_ContextModif.hpp>
#include <IFSelect_Modifier.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_Modifier, IFSelect_GeneralModifier)

IFSelect_Modifier::IFSelect_Modifier(const bool grf)
    : IFSelect_GeneralModifier(grf)
{
}
