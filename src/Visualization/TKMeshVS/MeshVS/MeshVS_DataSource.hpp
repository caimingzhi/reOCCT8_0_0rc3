#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <MeshVS_EntityType.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <gp_Pnt2d.hpp>
class Bnd_Box;
class MeshVS_Mesh;
class TColStd_HPackedMapOfInteger;
class Bnd_Box2d;

class MeshVS_DataSource : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool GetGeom(const int                   ID,
                                       const bool                  IsElement,
                                       NCollection_Array1<double>& Coords,
                                       int&                        NbNodes,
                                       MeshVS_EntityType&          Type) const = 0;

  Standard_EXPORT virtual bool GetGeomType(const int          ID,
                                           const bool         IsElement,
                                           MeshVS_EntityType& Type) const = 0;

  Standard_EXPORT virtual bool Get3DGeom(
    const int                                                    ID,
    int&                                                         NbNodes,
    occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>& Data) const;

  Standard_EXPORT virtual void* GetAddr(const int ID, const bool IsElement) const = 0;

  Standard_EXPORT virtual bool GetNodesByElement(const int                ID,
                                                 NCollection_Array1<int>& NodeIDs,
                                                 int&                     NbNodes) const = 0;

  Standard_EXPORT virtual const TColStd_PackedMapOfInteger& GetAllNodes() const = 0;

  Standard_EXPORT virtual const TColStd_PackedMapOfInteger& GetAllElements() const = 0;

  Standard_EXPORT virtual bool GetNormal(const int Id,
                                         const int Max,
                                         double&   nx,
                                         double&   ny,
                                         double&   nz) const;

  Standard_EXPORT virtual bool GetNodeNormal(const int ranknode,
                                             const int ElementId,
                                             double&   nx,
                                             double&   ny,
                                             double&   nz) const;

  Standard_EXPORT virtual bool GetNormalsByElement(
    const int                                 Id,
    const bool                                IsNodal,
    const int                                 MaxNodes,
    occ::handle<NCollection_HArray1<double>>& Normals) const;

  Standard_EXPORT virtual void GetAllGroups(TColStd_PackedMapOfInteger& Ids) const;

  Standard_EXPORT virtual bool GetGroup(const int                   Id,
                                        MeshVS_EntityType&          Type,
                                        TColStd_PackedMapOfInteger& Ids) const;

  Standard_EXPORT virtual void* GetGroupAddr(const int ID) const;

  Standard_EXPORT virtual bool IsAdvancedSelectionEnabled() const;

  Standard_EXPORT virtual Bnd_Box GetBoundingBox() const;

  Standard_EXPORT virtual bool GetDetectedEntities(
    const occ::handle<MeshVS_Mesh>&           Prs,
    const double                              X,
    const double                              Y,
    const double                              aTol,
    occ::handle<TColStd_HPackedMapOfInteger>& Nodes,
    occ::handle<TColStd_HPackedMapOfInteger>& Elements,
    double&                                   DMin);

  Standard_EXPORT virtual bool GetDetectedEntities(
    const occ::handle<MeshVS_Mesh>&           Prs,
    const double                              XMin,
    const double                              YMin,
    const double                              XMax,
    const double                              YMax,
    const double                              aTol,
    occ::handle<TColStd_HPackedMapOfInteger>& Nodes,
    occ::handle<TColStd_HPackedMapOfInteger>& Elements);

  Standard_EXPORT virtual bool GetDetectedEntities(
    const occ::handle<MeshVS_Mesh>&           Prs,
    const NCollection_Array1<gp_Pnt2d>&       Polyline,
    const Bnd_Box2d&                          aBox,
    const double                              aTol,
    occ::handle<TColStd_HPackedMapOfInteger>& Nodes,
    occ::handle<TColStd_HPackedMapOfInteger>& Elements);

  Standard_EXPORT virtual bool GetDetectedEntities(
    const occ::handle<MeshVS_Mesh>&           Prs,
    occ::handle<TColStd_HPackedMapOfInteger>& Nodes,
    occ::handle<TColStd_HPackedMapOfInteger>& Elements);

  DEFINE_STANDARD_RTTIEXT(MeshVS_DataSource, Standard_Transient)
};
