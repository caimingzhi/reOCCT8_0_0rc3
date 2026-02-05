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

//! The class provides default class which helps to represent node displacements by deformed mesh
//! This class has an internal handle to canonical non-deformed mesh data source and
//! map of displacement vectors. The displacement can be magnified to useful size.
//! All methods is implemented with calling the corresponding methods of non-deformed data source.
class MeshVS_DeformedDataSource : public MeshVS_DataSource
{

public:
  //! Constructor
  //! theNonDeformDS is canonical non-deformed data source, by which we are able to calculate
  //! deformed mesh geometry
  //! theMagnify is coefficient of displacement magnify
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

  //! This method returns map of nodal displacement vectors
  Standard_EXPORT const NCollection_DataMap<int, gp_Vec>& GetVectors() const;

  //! This method sets map of nodal displacement vectors (Map).
  Standard_EXPORT void SetVectors(const NCollection_DataMap<int, gp_Vec>& Map);

  //! This method returns vector ( Vect ) assigned to node number ID.
  Standard_EXPORT bool GetVector(const int ID, gp_Vec& Vect) const;

  //! This method sets vector ( Vect ) assigned to node number ID.
  Standard_EXPORT void SetVector(const int ID, const gp_Vec& Vect);

  Standard_EXPORT void SetNonDeformedDataSource(const occ::handle<MeshVS_DataSource>& theDS);

  //! With this methods you can read and change internal canonical data source
  Standard_EXPORT occ::handle<MeshVS_DataSource> GetNonDeformedDataSource() const;

  Standard_EXPORT void SetMagnify(const double theMagnify);

  //! With this methods you can read and change magnify coefficient of nodal displacements
  Standard_EXPORT double GetMagnify() const;

  DEFINE_STANDARD_RTTIEXT(MeshVS_DeformedDataSource, MeshVS_DataSource)

private:
  occ::handle<MeshVS_DataSource>   myNonDeformedDataSource;
  TColStd_PackedMapOfInteger       myEmptyMap;
  NCollection_DataMap<int, gp_Vec> myVectors;
  double                           myMagnify;
};
