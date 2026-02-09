#pragma once

#include <Standard.hpp>

#include <IGESDimen_GeneralNote.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <IGESAppli_Node.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESBasic_HArray1OfHArray1OfXYZ;
class IGESDimen_GeneralNote;
class IGESAppli_Node;
class gp_XYZ;

class IGESAppli_NodalDisplAndRot : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_NodalDisplAndRot();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_GeneralNote>>>& allNotes,
    const occ::handle<NCollection_HArray1<int>>&                                allIdentifiers,
    const occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>>&        allNodes,
    const occ::handle<IGESBasic_HArray1OfHArray1OfXYZ>&                         allRotParams,
    const occ::handle<IGESBasic_HArray1OfHArray1OfXYZ>&                         allTransParams);

  Standard_EXPORT int NbCases() const;

  Standard_EXPORT int NbNodes() const;

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note(const int Index) const;

  Standard_EXPORT int NodeIdentifier(const int Index) const;

  Standard_EXPORT occ::handle<IGESAppli_Node> Node(const int Index) const;

  Standard_EXPORT gp_XYZ TranslationParameter(const int NodeNum, const int CaseNum) const;

  Standard_EXPORT gp_XYZ RotationalParameter(const int NodeNum, const int CaseNum) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_NodalDisplAndRot, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESDimen_GeneralNote>>> theNotes;
  occ::handle<NCollection_HArray1<int>>                                theNodeIdentifiers;
  occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>>        theNodes;
  occ::handle<IGESBasic_HArray1OfHArray1OfXYZ>                         theTransParam;
  occ::handle<IGESBasic_HArray1OfHArray1OfXYZ>                         theRotParam;
};
