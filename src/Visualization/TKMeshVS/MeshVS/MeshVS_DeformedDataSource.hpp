#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_Vec.hpp>
#include <NCollection_DataMap.hpp>
#include <MeshVS_DataSource.hpp>
#include <NCollection_Array1.hpp>
#include <MeshVS_EntityType.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HArray1.hpp>
class gp_Vec;

class MeshVS_DeformedDataSource : public MeshVS_DataSource
{

public:
  Standard_EXPORT MeshVS_DeformedDataSource(const occ::handle<MeshVS_DataSource>& theNonDeformDS,
                                            const double                          theMagnify);

  Standard_EXPORT bool GetGeom(const int                   ID,
                               const bool                  IsElement,
                               NCollection_Array1<double>& Coords,
                               int&                        NbNodes,
                               MeshVS_EntityType&          Type) const override;

  Standard_EXPORT bool GetGeomType(const int          ID,
                                   const bool         IsElement,
                                   MeshVS_EntityType& Type) const override;

  Standard_EXPORT bool Get3DGeom(
    const int                                                    ID,
    int&                                                         NbNodes,
    occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>& Data) const override;

  Standard_EXPORT void* GetAddr(const int ID, const bool IsElement) const override;

  Standard_EXPORT bool GetNodesByElement(const int                ID,
                                         NCollection_Array1<int>& NodeIDs,
                                         int&                     NbNodes) const override;

  Standard_EXPORT const TColStd_PackedMapOfInteger& GetAllNodes() const override;

  Standard_EXPORT const TColStd_PackedMapOfInteger& GetAllElements() const override;

  Standard_EXPORT const NCollection_DataMap<int, gp_Vec>& GetVectors() const;

  Standard_EXPORT void SetVectors(const NCollection_DataMap<int, gp_Vec>& Map);

  Standard_EXPORT bool GetVector(const int ID, gp_Vec& Vect) const;

  Standard_EXPORT void SetVector(const int ID, const gp_Vec& Vect);

  Standard_EXPORT void SetNonDeformedDataSource(const occ::handle<MeshVS_DataSource>& theDS);

  Standard_EXPORT occ::handle<MeshVS_DataSource> GetNonDeformedDataSource() const;

  Standard_EXPORT void SetMagnify(const double theMagnify);

  Standard_EXPORT double GetMagnify() const;

  DEFINE_STANDARD_RTTIEXT(MeshVS_DeformedDataSource, MeshVS_DataSource)

private:
  occ::handle<MeshVS_DataSource>   myNonDeformedDataSource;
  TColStd_PackedMapOfInteger       myEmptyMap;
  NCollection_DataMap<int, gp_Vec> myVectors;
  double                           myMagnify;
};
