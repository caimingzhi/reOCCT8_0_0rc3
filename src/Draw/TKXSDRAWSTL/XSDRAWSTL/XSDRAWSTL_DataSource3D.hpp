#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <MeshVS_DataSource.hpp>
#include <MeshVS_EntityType.hpp>
#include <NCollection_Sequence.hpp>

class XSDRAWSTL_DataSource3D : public MeshVS_DataSource
{

public:
  Standard_EXPORT XSDRAWSTL_DataSource3D();

  Standard_EXPORT bool GetGeom(const int                   theID,
                               const bool                  theIsElement,
                               NCollection_Array1<double>& theCoords,
                               int&                        theNbNodes,
                               MeshVS_EntityType&          theType) const override;

  Standard_EXPORT bool Get3DGeom(
    const int                                                    theID,
    int&                                                         theNbNodes,
    occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>& theData) const override;

  Standard_EXPORT bool GetGeomType(const int          theID,
                                   const bool         theIsElement,
                                   MeshVS_EntityType& theType) const override;

  Standard_EXPORT void* GetAddr(const int theID, const bool theIsElement) const override;

  Standard_EXPORT bool GetNodesByElement(const int                theID,
                                         NCollection_Array1<int>& theNodeIDs,
                                         int&                     theNbNodes) const override;

  Standard_EXPORT const TColStd_PackedMapOfInteger& GetAllNodes() const override;

  Standard_EXPORT const TColStd_PackedMapOfInteger& GetAllElements() const override;

  Standard_EXPORT bool GetNormal(const int theID,
                                 const int theMax,
                                 double&   theNx,
                                 double&   theNy,
                                 double&   theNz) const override;

  DEFINE_STANDARD_RTTIEXT(XSDRAWSTL_DataSource3D, MeshVS_DataSource)

private:
  TColStd_PackedMapOfInteger               myNodes;
  TColStd_PackedMapOfInteger               myElements;
  occ::handle<NCollection_HArray1<int>>    myElemNbNodes;
  occ::handle<NCollection_HArray2<double>> myNodeCoords;
  occ::handle<NCollection_HArray2<int>>    myElemNodes;
};
