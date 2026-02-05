#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESDraw_ConnectPoint.hpp>
#include <IGESGraph_TextDisplayTemplate.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_ConnectPoint, IGESData_IGESEntity)

IGESDraw_ConnectPoint::IGESDraw_ConnectPoint() = default;

void IGESDraw_ConnectPoint::Init(
  const gp_XYZ&                                     aPoint,
  const occ::handle<IGESData_IGESEntity>&           aDisplaySymbol,
  const int                                         aTypeFlag,
  const int                                         aFunctionFlag,
  const occ::handle<TCollection_HAsciiString>&      aFunctionIdentifier,
  const occ::handle<IGESGraph_TextDisplayTemplate>& anIdentifierTemplate,
  const occ::handle<TCollection_HAsciiString>&      aFunctionName,
  const occ::handle<IGESGraph_TextDisplayTemplate>& aFunctionTemplate,
  const int                                         aPointIdentifier,
  const int                                         aFunctionCode,
  const int                                         aSwapFlag,
  const occ::handle<IGESData_IGESEntity>&           anOwnerSubfigure)
{
  thePoint              = aPoint;
  theDisplaySymbol      = aDisplaySymbol;
  theTypeFlag           = aTypeFlag;
  theFunctionFlag       = aFunctionFlag;
  theFunctionIdentifier = aFunctionIdentifier;
  theIdentifierTemplate = anIdentifierTemplate;
  theFunctionName       = aFunctionName;
  theFunctionTemplate   = aFunctionTemplate;
  thePointIdentifier    = aPointIdentifier;
  theFunctionCode       = aFunctionCode;
  theSwapFlag           = aSwapFlag != 0;
  theOwnerSubfigure     = anOwnerSubfigure;
  InitTypeAndForm(132, 0);
}

gp_Pnt IGESDraw_ConnectPoint::Point() const
{
  gp_Pnt tempPoint(thePoint);
  return tempPoint;
}

gp_Pnt IGESDraw_ConnectPoint::TransformedPoint() const
{
  gp_XYZ tempPoint = thePoint;
  if (HasTransf())
    Location().Transforms(tempPoint);
  gp_Pnt tempRes(tempPoint);

  return (tempRes);
}

bool IGESDraw_ConnectPoint::HasDisplaySymbol() const
{
  return (!theDisplaySymbol.IsNull());
}

occ::handle<IGESData_IGESEntity> IGESDraw_ConnectPoint::DisplaySymbol() const
{
  return theDisplaySymbol;
}

int IGESDraw_ConnectPoint::TypeFlag() const
{
  return theTypeFlag;
}

int IGESDraw_ConnectPoint::FunctionFlag() const
{
  return theFunctionFlag;
}

occ::handle<TCollection_HAsciiString> IGESDraw_ConnectPoint::FunctionIdentifier() const
{
  return theFunctionIdentifier;
}

bool IGESDraw_ConnectPoint::HasIdentifierTemplate() const
{
  return (!theIdentifierTemplate.IsNull());
}

occ::handle<IGESGraph_TextDisplayTemplate> IGESDraw_ConnectPoint::IdentifierTemplate() const
{
  return theIdentifierTemplate;
}

occ::handle<TCollection_HAsciiString> IGESDraw_ConnectPoint::FunctionName() const
{
  return theFunctionName;
}

bool IGESDraw_ConnectPoint::HasFunctionTemplate() const
{
  return (!theFunctionTemplate.IsNull());
}

occ::handle<IGESGraph_TextDisplayTemplate> IGESDraw_ConnectPoint::FunctionTemplate() const
{
  return theFunctionTemplate;
}

int IGESDraw_ConnectPoint::PointIdentifier() const
{
  return thePointIdentifier;
}

int IGESDraw_ConnectPoint::FunctionCode() const
{
  return theFunctionCode;
}

bool IGESDraw_ConnectPoint::SwapFlag() const
{
  return theSwapFlag;
}

bool IGESDraw_ConnectPoint::HasOwnerSubfigure() const
{
  return (!theOwnerSubfigure.IsNull());
}

occ::handle<IGESData_IGESEntity> IGESDraw_ConnectPoint::OwnerSubfigure() const
{
  return theOwnerSubfigure;
}
