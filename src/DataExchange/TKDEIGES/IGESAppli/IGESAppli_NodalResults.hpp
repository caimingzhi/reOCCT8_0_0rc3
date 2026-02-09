#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESAppli_Node.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESDimen_GeneralNote;
class IGESAppli_Node;

class IGESAppli_NodalResults : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_NodalResults();

  Standard_EXPORT void Init(
    const occ::handle<IGESDimen_GeneralNote>&                            aNote,
    const int                                                            aNumber,
    const double                                                         aTime,
    const occ::handle<NCollection_HArray1<int>>&                         allNodeIdentifiers,
    const occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>>& allNodes,
    const occ::handle<NCollection_HArray2<double>>&                      allData);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT int SubCaseNumber() const;

  Standard_EXPORT double Time() const;

  Standard_EXPORT int NbData() const;

  Standard_EXPORT int NbNodes() const;

  Standard_EXPORT int NodeIdentifier(const int Index) const;

  Standard_EXPORT occ::handle<IGESAppli_Node> Node(const int Index) const;

  Standard_EXPORT double Data(const int NodeNum, const int DataNum) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_NodalResults, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote>                            theNote;
  int                                                           theSubCaseNum;
  double                                                        theTime;
  occ::handle<NCollection_HArray1<int>>                         theNodeIdentifiers;
  occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>> theNodes;
  occ::handle<NCollection_HArray2<double>>                      theData;
};
