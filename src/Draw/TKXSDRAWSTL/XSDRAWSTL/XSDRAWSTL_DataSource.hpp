#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <MeshVS_DataSource.hpp>
#include <NCollection_Array1.hpp>
#include <MeshVS_EntityType.hpp>
#include <Poly_Triangulation.hpp>

class XSDRAWSTL_DataSource : public MeshVS_DataSource
{

public:
  Standard_EXPORT XSDRAWSTL_DataSource(const occ::handle<Poly_Triangulation>& aMesh);

  Standard_EXPORT bool GetGeom(const int                   ID,
                               const bool                  IsElement,
                               NCollection_Array1<double>& Coords,
                               int&                        NbNodes,
                               MeshVS_EntityType&          Type) const override;

  Standard_EXPORT bool GetGeomType(const int          ID,
                                   const bool         IsElement,
                                   MeshVS_EntityType& Type) const override;

  Standard_EXPORT void* GetAddr(const int ID, const bool IsElement) const override;

  Standard_EXPORT bool GetNodesByElement(const int                ID,
                                         NCollection_Array1<int>& NodeIDs,
                                         int&                     NbNodes) const override;

  Standard_EXPORT const TColStd_PackedMapOfInteger& GetAllNodes() const override;

  Standard_EXPORT const TColStd_PackedMapOfInteger& GetAllElements() const override;

  Standard_EXPORT bool GetNormal(const int Id,
                                 const int Max,
                                 double&   nx,
                                 double&   ny,
                                 double&   nz) const override;

  DEFINE_STANDARD_RTTIEXT(XSDRAWSTL_DataSource, MeshVS_DataSource)

private:
  occ::handle<Poly_Triangulation>          myMesh;
  TColStd_PackedMapOfInteger               myNodes;
  TColStd_PackedMapOfInteger               myElements;
  occ::handle<NCollection_HArray2<int>>    myElemNodes;
  occ::handle<NCollection_HArray2<double>> myNodeCoords;
  occ::handle<NCollection_HArray2<double>> myElemNormals;
};
