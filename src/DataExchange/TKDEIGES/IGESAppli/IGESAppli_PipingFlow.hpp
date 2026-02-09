#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESDraw_ConnectPoint.hpp>
#include <TCollection_HAsciiString.hpp>
#include <IGESGraph_TextDisplayTemplate.hpp>
class IGESDraw_ConnectPoint;
class TCollection_HAsciiString;
class IGESGraph_TextDisplayTemplate;

class IGESAppli_PipingFlow : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_PipingFlow();

  Standard_EXPORT void Init(
    const int                                                                      nbContextFlags,
    const int                                                                      aFlowType,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&      allFlowAssocs,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDraw_ConnectPoint>>>&    allConnectPoints,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&      allJoins,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& allFlowNames,
    const occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextDisplayTemplate>>>&
                                                                              allTextDisps,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allContFlowAssocs);

  Standard_EXPORT bool OwnCorrect();

  Standard_EXPORT int NbContextFlags() const;

  Standard_EXPORT int NbFlowAssociativities() const;

  Standard_EXPORT int NbConnectPoints() const;

  Standard_EXPORT int NbJoins() const;

  Standard_EXPORT int NbFlowNames() const;

  Standard_EXPORT int NbTextDisplayTemplates() const;

  Standard_EXPORT int NbContFlowAssociativities() const;

  Standard_EXPORT int TypeOfFlow() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> FlowAssociativity(const int Index) const;

  Standard_EXPORT occ::handle<IGESDraw_ConnectPoint> ConnectPoint(const int Index) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Join(const int Index) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FlowName(const int Index) const;

  Standard_EXPORT occ::handle<IGESGraph_TextDisplayTemplate> TextDisplayTemplate(
    const int Index) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> ContFlowAssociativity(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_PipingFlow, IGESData_IGESEntity)

private:
  int                                                                     theNbContextFlags;
  int                                                                     theTypeOfFlow;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>      theFlowAssociativities;
  occ::handle<NCollection_HArray1<occ::handle<IGESDraw_ConnectPoint>>>    theConnectPoints;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>      theJoins;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theFlowNames;
  occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextDisplayTemplate>>>
                                                                     theTextDisplayTemplates;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theContFlowAssociativities;
};
