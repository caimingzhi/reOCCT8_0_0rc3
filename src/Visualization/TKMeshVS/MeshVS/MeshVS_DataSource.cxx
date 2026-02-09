#include <Bnd_Box2d.hpp>
#include <gp.hpp>
#include <gp_Vec.hpp>
#include <MeshVS_Buffer.hpp>
#include <MeshVS_DataSource.hpp>
#include <MeshVS_Mesh.hpp>
#include <MeshVS_Tool.hpp>
#include <Standard_Type.hpp>
#include <TColStd_HPackedMapOfInteger.hpp>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MeshVS_DataSource, Standard_Transient)

bool MeshVS_DataSource::Get3DGeom(
  const int,
  int&,
  occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>&) const
{
  return false;
}

bool MeshVS_DataSource::GetNormal(const int Id,
                                  const int Max,
                                  double&   nx,
                                  double&   ny,
                                  double&   nz) const
{
  if (Max <= 0)
    return false;

  MeshVS_Buffer              aCoordsBuf(3 * Max * sizeof(double));
  NCollection_Array1<double> Coords(aCoordsBuf, 1, 3 * Max);
  int                        nbNodes;
  MeshVS_EntityType          Type;

  bool res = false;

  if (!GetGeom(Id, true, Coords, nbNodes, Type))
    return res;

  if (Type == MeshVS_ET_Face && nbNodes >= 3)
  {
    double x1 = Coords(1);
    double y1 = Coords(2);
    double z1 = Coords(3);
    double x2 = Coords(4);
    double y2 = Coords(5);
    double z2 = Coords(6);
    double x3 = Coords((nbNodes - 1) * 3 + 1);
    double y3 = Coords((nbNodes - 1) * 3 + 2);
    double z3 = Coords((nbNodes - 1) * 3 + 3);
    double p1 = x2 - x1, p2 = y2 - y1, p3 = z2 - z1, q1 = x3 - x1, q2 = y3 - y1, q3 = z3 - z1;
    nx         = p2 * q3 - p3 * q2;
    ny         = p3 * q1 - p1 * q3;
    nz         = p1 * q2 - p2 * q1;
    double len = sqrt(nx * nx + ny * ny + nz * nz);
    if (len <= gp::Resolution())
    {
      nx = ny = nz = 0;
      return res;
    }
    nx /= len;
    ny /= len;
    nz /= len;
    res = true;
  }
  return res;
}

bool MeshVS_DataSource::GetNodeNormal(const int, const int, double&, double&, double&) const
{
  return false;
}

bool MeshVS_DataSource::GetNormalsByElement(const int                                 Id,
                                            const bool                                IsNodal,
                                            const int                                 MaxNodes,
                                            occ::handle<NCollection_HArray1<double>>& Normals) const
{
  MeshVS_Buffer              aCoordsBuf(3 * MaxNodes * sizeof(double));
  NCollection_Array1<double> Coords(aCoordsBuf, 1, 3 * MaxNodes);
  int                        NbNodes;
  MeshVS_EntityType          Type;

  bool res = false;
  if (MaxNodes <= 0)
    return res;

  if (!GetGeom(Id, true, Coords, NbNodes, Type))
    return res;

  int aNbNormals = NbNodes;

  occ::handle<NCollection_HArray1<NCollection_Sequence<int>>> aTopo;
  if (Type == MeshVS_ET_Volume)
  {
    if (!Get3DGeom(Id, NbNodes, aTopo))
      return res;

    aNbNormals = aTopo->Upper() - aTopo->Lower() + 1;
  }

  occ::handle<NCollection_HArray1<double>> aNormals =
    new NCollection_HArray1<double>(1, 3 * aNbNormals);

  bool allNormals = (Type == MeshVS_ET_Face && IsNodal);

  for (int k = 1; k <= NbNodes && allNormals; k++)
    allNormals = GetNodeNormal(k,
                               Id,
                               aNormals->ChangeValue(3 * k - 2),
                               aNormals->ChangeValue(3 * k - 1),
                               aNormals->ChangeValue(3 * k));

  if (!allNormals)
  {
    switch (Type)
    {

      case MeshVS_ET_Face:
        res = GetNormal(Id,
                        MaxNodes,
                        aNormals->ChangeValue(1),
                        aNormals->ChangeValue(2),
                        aNormals->ChangeValue(3));
        if (res)
        {
          for (int k = 2; k <= NbNodes; k++)
          {
            aNormals->ChangeValue(3 * k - 2) = aNormals->Value(1);
            aNormals->ChangeValue(3 * k - 1) = aNormals->Value(2);
            aNormals->ChangeValue(3 * k)     = aNormals->Value(3);
          }
        }
        break;

      case MeshVS_ET_Volume:
      {
        gp_Vec norm;
        int    low = Coords.Lower();
        for (int k = aTopo->Lower(), last = aTopo->Upper(), i = 1; k <= last; k++, i++)
        {
          const NCollection_Sequence<int>& aSeq = aTopo->Value(k);
          int                              m    = aSeq.Length(), ind;

          norm.SetCoord(0, 0, 0);
          MeshVS_Buffer              PolyNodesBuf(3 * m * sizeof(double));
          NCollection_Array1<double> PolyNodes(PolyNodesBuf, 0, 3 * m);
          PolyNodes.SetValue(0, m);
          for (int j = 1; j <= m; j++)
          {
            ind = aSeq.Value(j);
            PolyNodes.SetValue(3 * j - 2, Coords(low + 3 * ind));
            PolyNodes.SetValue(3 * j - 1, Coords(low + 3 * ind + 1));
            PolyNodes.SetValue(3 * j, Coords(low + 3 * ind + 2));
          }

          MeshVS_Tool::GetAverageNormal(PolyNodes, norm);

          aNormals->ChangeValue(i * 3 - 2) = norm.X();
          aNormals->ChangeValue(i * 3 - 1) = norm.Y();
          aNormals->ChangeValue(i * 3)     = norm.Z();
        }
        res = true;
      }
      break;

      default:
        return res;
    }
  }

  if (res || allNormals)
    Normals = aNormals;

  return (res || allNormals);
}

void MeshVS_DataSource::GetAllGroups(TColStd_PackedMapOfInteger&) const {}

bool MeshVS_DataSource::GetGroup(const int,
                                 MeshVS_EntityType& Type,
                                 TColStd_PackedMapOfInteger&) const
{
  Type = MeshVS_ET_NONE;
  return false;
}

void* MeshVS_DataSource::GetGroupAddr(const int) const
{
  return nullptr;
}

bool MeshVS_DataSource::IsAdvancedSelectionEnabled() const
{
  return false;
}

bool MeshVS_DataSource::GetDetectedEntities(const occ::handle<MeshVS_Mesh>&,
                                            const double,
                                            const double,
                                            const double,
                                            occ::handle<TColStd_HPackedMapOfInteger>&,
                                            occ::handle<TColStd_HPackedMapOfInteger>&,
                                            double&)
{
  return false;
}

bool MeshVS_DataSource::GetDetectedEntities(const occ::handle<MeshVS_Mesh>&,
                                            const double,
                                            const double,
                                            const double,
                                            const double,
                                            const double,
                                            occ::handle<TColStd_HPackedMapOfInteger>&,
                                            occ::handle<TColStd_HPackedMapOfInteger>&)
{
  return false;
}

bool MeshVS_DataSource::GetDetectedEntities(const occ::handle<MeshVS_Mesh>&,
                                            const NCollection_Array1<gp_Pnt2d>&,
                                            const Bnd_Box2d&,
                                            const double,
                                            occ::handle<TColStd_HPackedMapOfInteger>&,
                                            occ::handle<TColStd_HPackedMapOfInteger>&)
{
  return false;
}

bool MeshVS_DataSource::GetDetectedEntities(const occ::handle<MeshVS_Mesh>&,
                                            occ::handle<TColStd_HPackedMapOfInteger>&,
                                            occ::handle<TColStd_HPackedMapOfInteger>&)
{
  return false;
}

Bnd_Box MeshVS_DataSource::GetBoundingBox() const
{

  Bnd_Box                           aBox;
  const TColStd_PackedMapOfInteger& aNodes = GetAllNodes();
  if (aNodes.Extent())
  {
    double                                  aCoordsBuf[3];
    NCollection_Array1<double>              aCoords(*aCoordsBuf, 1, 3);
    int                                     nbNodes;
    MeshVS_EntityType                       aType;
    TColStd_MapIteratorOfPackedMapOfInteger anIter(aNodes);
    for (; anIter.More(); anIter.Next())
    {
      int aKey = anIter.Key();
      if (!GetGeom(aKey, false, aCoords, nbNodes, aType))
        continue;
      aBox.Add(gp_Pnt(aCoordsBuf[0], aCoordsBuf[1], aCoordsBuf[2]));
    }
  }
  return aBox;
}
