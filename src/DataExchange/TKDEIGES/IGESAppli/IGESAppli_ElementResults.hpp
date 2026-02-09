#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESAppli_FiniteElement.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESDimen_GeneralNote;
class IGESBasic_HArray1OfHArray1OfInteger;
class IGESBasic_HArray1OfHArray1OfReal;
class IGESAppli_FiniteElement;

class IGESAppli_ElementResults : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_ElementResults();

  Standard_EXPORT void Init(
    const occ::handle<IGESDimen_GeneralNote>&                                     aNote,
    const int                                                                     aSubCase,
    const double                                                                  aTime,
    const int                                                                     nbResults,
    const int                                                                     aResRepFlag,
    const occ::handle<NCollection_HArray1<int>>&                                  allElementIdents,
    const occ::handle<NCollection_HArray1<occ::handle<IGESAppli_FiniteElement>>>& allFiniteElems,
    const occ::handle<NCollection_HArray1<int>>&                                  allTopTypes,
    const occ::handle<NCollection_HArray1<int>>&                                  nbLayers,
    const occ::handle<NCollection_HArray1<int>>&                                  allDataLayerFlags,
    const occ::handle<NCollection_HArray1<int>>&                                  allnbResDataLocs,
    const occ::handle<IGESBasic_HArray1OfHArray1OfInteger>&                       allResDataLocs,
    const occ::handle<IGESBasic_HArray1OfHArray1OfReal>&                          allResults);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT int SubCaseNumber() const;

  Standard_EXPORT double Time() const;

  Standard_EXPORT int NbResultValues() const;

  Standard_EXPORT int ResultReportFlag() const;

  Standard_EXPORT int NbElements() const;

  Standard_EXPORT int ElementIdentifier(const int Index) const;

  Standard_EXPORT occ::handle<IGESAppli_FiniteElement> Element(const int Index) const;

  Standard_EXPORT int ElementTopologyType(const int Index) const;

  Standard_EXPORT int NbLayers(const int Index) const;

  Standard_EXPORT int DataLayerFlag(const int Index) const;

  Standard_EXPORT int NbResultDataLocs(const int Index) const;

  Standard_EXPORT int ResultDataLoc(const int NElem, const int NLoc) const;

  Standard_EXPORT int NbResults(const int Index) const;

  Standard_EXPORT double ResultData(const int NElem, const int num) const;

  Standard_EXPORT int ResultRank(const int NElem,
                                 const int NVal,
                                 const int NLay,
                                 const int NLoc) const;

  Standard_EXPORT double ResultData(const int NElem,
                                    const int NVal,
                                    const int NLay,
                                    const int NLoc) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> ResultList(const int NElem) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_ElementResults, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote>                                     theNote;
  int                                                                    theSubcaseNumber;
  double                                                                 theTime;
  int                                                                    theNbResultValues;
  int                                                                    theResultReportFlag;
  occ::handle<NCollection_HArray1<int>>                                  theElementIdentifiers;
  occ::handle<NCollection_HArray1<occ::handle<IGESAppli_FiniteElement>>> theElements;
  occ::handle<NCollection_HArray1<int>>                                  theElementTopologyTypes;
  occ::handle<NCollection_HArray1<int>>                                  theNbLayers;
  occ::handle<NCollection_HArray1<int>>                                  theDataLayerFlags;
  occ::handle<NCollection_HArray1<int>>                                  theNbResultDataLocs;
  occ::handle<IGESBasic_HArray1OfHArray1OfInteger>                       theResultDataLocs;
  occ::handle<IGESBasic_HArray1OfHArray1OfReal>                          theResultData;
};
