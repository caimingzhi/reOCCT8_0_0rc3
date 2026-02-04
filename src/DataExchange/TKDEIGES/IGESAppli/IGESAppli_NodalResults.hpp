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

//! defines NodalResults, Type <146>
//! in package IGESAppli
//! Used to store the Analysis Data results per FEM Node
class IGESAppli_NodalResults : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_NodalResults();

  //! This method is used to set the fields of the class
  //! NodalResults
  //! - aNote              : General Note that describes the
  //! analysis case
  //! - aNumber            : Analysis Subcase number
  //! - aTime              : Analysis time
  //! - allNodeIdentifiers : Node identifiers for the nodes
  //! - allNodes           : List of FEM Node Entities
  //! - allData            : Values of the Finite Element analysis
  //! result data
  //! raises exception if Lengths of allNodeIdentifiers, allNodes and
  //! allData (Cols) are not same
  Standard_EXPORT void Init(
    const occ::handle<IGESDimen_GeneralNote>&                            aNote,
    const int                                                            aNumber,
    const double                                                         aTime,
    const occ::handle<NCollection_HArray1<int>>&                         allNodeIdentifiers,
    const occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>>& allNodes,
    const occ::handle<NCollection_HArray2<double>>&                      allData);

  //! Changes the FormNumber (which indicates Type of Result)
  //! Error if not in range [0-34]
  Standard_EXPORT void SetFormNumber(const int form);

  //! returns the General Note Entity that describes the analysis case
  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  //! returns zero if there is no subcase
  Standard_EXPORT int SubCaseNumber() const;

  //! returns the Analysis time value for this subcase. It is the time
  //! at which transient analysis results occur in the mathematical
  //! FEM model.
  Standard_EXPORT double Time() const;

  //! returns number of real values in array V for a FEM node
  Standard_EXPORT int NbData() const;

  //! returns number of FEM nodes for which data is to be read.
  Standard_EXPORT int NbNodes() const;

  //! returns FEM node number identifier for the (Index)th node
  //! raises exception if Index <= 0 or Index > NbNodes
  Standard_EXPORT int NodeIdentifier(const int Index) const;

  //! returns the node as specified by the Index
  //! raises exception if Index <= 0 or Index > NbNodes
  Standard_EXPORT occ::handle<IGESAppli_Node> Node(const int Index) const;

  //! returns the finite element analysis result value
  //! raises exception if (NodeNum <= 0 or NodeNum > NbNodes()) or
  //! if (DataNum <=0 or DataNum > NbData())
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

