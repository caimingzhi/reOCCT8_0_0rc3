#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;
class IGESGraph_TextDisplayTemplate;
class gp_Pnt;

class IGESDraw_ConnectPoint : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDraw_ConnectPoint();

  Standard_EXPORT void Init(const gp_XYZ&                                     aPoint,
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
                            const occ::handle<IGESData_IGESEntity>&           anOwnerSubfigure);

  Standard_EXPORT gp_Pnt Point() const;

  Standard_EXPORT gp_Pnt TransformedPoint() const;

  Standard_EXPORT bool HasDisplaySymbol() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> DisplaySymbol() const;

  Standard_EXPORT int TypeFlag() const;

  Standard_EXPORT int FunctionFlag() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FunctionIdentifier() const;

  Standard_EXPORT bool HasIdentifierTemplate() const;

  Standard_EXPORT occ::handle<IGESGraph_TextDisplayTemplate> IdentifierTemplate() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FunctionName() const;

  Standard_EXPORT bool HasFunctionTemplate() const;

  Standard_EXPORT occ::handle<IGESGraph_TextDisplayTemplate> FunctionTemplate() const;

  Standard_EXPORT int PointIdentifier() const;

  Standard_EXPORT int FunctionCode() const;

  Standard_EXPORT bool SwapFlag() const;

  Standard_EXPORT bool HasOwnerSubfigure() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> OwnerSubfigure() const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_ConnectPoint, IGESData_IGESEntity)

private:
  gp_XYZ                                     thePoint;
  occ::handle<IGESData_IGESEntity>           theDisplaySymbol;
  int                                        theTypeFlag;
  int                                        theFunctionFlag;
  occ::handle<TCollection_HAsciiString>      theFunctionIdentifier;
  occ::handle<IGESGraph_TextDisplayTemplate> theIdentifierTemplate;
  occ::handle<TCollection_HAsciiString>      theFunctionName;
  occ::handle<IGESGraph_TextDisplayTemplate> theFunctionTemplate;
  int                                        thePointIdentifier;
  int                                        theFunctionCode;
  bool                                       theSwapFlag;
  occ::handle<IGESData_IGESEntity>           theOwnerSubfigure;
};
