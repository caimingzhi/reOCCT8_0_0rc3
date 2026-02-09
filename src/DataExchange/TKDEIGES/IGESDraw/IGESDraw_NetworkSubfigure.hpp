#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <Standard_Integer.hpp>
#include <IGESDraw_ConnectPoint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESDraw_NetworkSubfigureDef;
class TCollection_HAsciiString;
class IGESGraph_TextDisplayTemplate;
class IGESDraw_ConnectPoint;

class IGESDraw_NetworkSubfigure : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDraw_NetworkSubfigure();

  Standard_EXPORT void Init(
    const occ::handle<IGESDraw_NetworkSubfigureDef>&                            aDefinition,
    const gp_XYZ&                                                               aTranslation,
    const gp_XYZ&                                                               aScaleFactor,
    const int                                                                   aTypeFlag,
    const occ::handle<TCollection_HAsciiString>&                                aDesignator,
    const occ::handle<IGESGraph_TextDisplayTemplate>&                           aTemplate,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDraw_ConnectPoint>>>& allConnectPoints);

  Standard_EXPORT occ::handle<IGESDraw_NetworkSubfigureDef> SubfigureDefinition() const;

  Standard_EXPORT gp_XYZ Translation() const;

  Standard_EXPORT gp_XYZ TransformedTranslation() const;

  Standard_EXPORT gp_XYZ ScaleFactors() const;

  Standard_EXPORT int TypeFlag() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ReferenceDesignator() const;

  Standard_EXPORT bool HasDesignatorTemplate() const;

  Standard_EXPORT occ::handle<IGESGraph_TextDisplayTemplate> DesignatorTemplate() const;

  Standard_EXPORT int NbConnectPoints() const;

  Standard_EXPORT occ::handle<IGESDraw_ConnectPoint> ConnectPoint(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_NetworkSubfigure, IGESData_IGESEntity)

private:
  occ::handle<IGESDraw_NetworkSubfigureDef>                            theSubfigureDefinition;
  gp_XYZ                                                               theTranslation;
  gp_XYZ                                                               theScaleFactor;
  int                                                                  theTypeFlag;
  occ::handle<TCollection_HAsciiString>                                theDesignator;
  occ::handle<IGESGraph_TextDisplayTemplate>                           theDesignatorTemplate;
  occ::handle<NCollection_HArray1<occ::handle<IGESDraw_ConnectPoint>>> theConnectPoints;
};
