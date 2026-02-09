#include <MeshVS_Buffer.hpp>
#include <MeshVS_DeformedDataSource.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MeshVS_DeformedDataSource, MeshVS_DataSource)

MeshVS_DeformedDataSource::MeshVS_DeformedDataSource(
  const occ::handle<MeshVS_DataSource>& theNonDeformDS,
  const double                          theMagnify)
{
  myNonDeformedDataSource = theNonDeformDS;
  SetMagnify(theMagnify);
}

static inline void shiftCoord(NCollection_Array1<double>& Coords, int i, const gp_Vec& aVec)
{
  Coords(3 * i - 2) = Coords(3 * i - 2) + aVec.X();
  Coords(3 * i - 1) = Coords(3 * i - 1) + aVec.Y();
  Coords(3 * i)     = Coords(3 * i) + aVec.Z();
}

bool MeshVS_DeformedDataSource::GetGeom(const int                   ID,
                                        const bool                  IsElement,
                                        NCollection_Array1<double>& Coords,
                                        int&                        NbNodes,
                                        MeshVS_EntityType&          Type) const
{
  if (myNonDeformedDataSource.IsNull()
      || !myNonDeformedDataSource->GetGeom(ID, IsElement, Coords, NbNodes, Type))
    return false;

  if (Type == MeshVS_ET_Node)
  {
    gp_Vec Vect;
    if (!GetVector(ID, Vect))
      return false;
    shiftCoord(Coords, 1, myMagnify * Vect);
  }
  else
  {
    MeshVS_Buffer           aNodesBuf(NbNodes * sizeof(int));
    NCollection_Array1<int> aNodes(aNodesBuf, 1, NbNodes);
    if (!myNonDeformedDataSource->GetNodesByElement(ID, aNodes, NbNodes))
      return false;
    for (int i = 1; i <= NbNodes; i++)
    {
      gp_Vec Vect;
      if (!GetVector(aNodes(i), Vect))
        return false;
      shiftCoord(Coords, i, myMagnify * Vect);
    }
  }
  return true;
}

bool MeshVS_DeformedDataSource::GetGeomType(const int          ID,
                                            const bool         IsElement,
                                            MeshVS_EntityType& Type) const
{
  if (myNonDeformedDataSource.IsNull())
    return false;
  else
    return myNonDeformedDataSource->GetGeomType(ID, IsElement, Type);
}

bool MeshVS_DeformedDataSource::Get3DGeom(
  const int                                                    ID,
  int&                                                         NbNodes,
  occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>& Data) const
{
  if (myNonDeformedDataSource.IsNull())
    return false;
  else
    return myNonDeformedDataSource->Get3DGeom(ID, NbNodes, Data);
}

void* MeshVS_DeformedDataSource::GetAddr(const int ID, const bool IsElement) const
{
  if (myNonDeformedDataSource.IsNull())
    return nullptr;
  else
    return myNonDeformedDataSource->GetAddr(ID, IsElement);
}

bool MeshVS_DeformedDataSource::GetNodesByElement(const int                ID,
                                                  NCollection_Array1<int>& NodeIDs,
                                                  int&                     NbNodes) const
{
  if (myNonDeformedDataSource.IsNull())
    return false;
  else
    return myNonDeformedDataSource->GetNodesByElement(ID, NodeIDs, NbNodes);
}

const TColStd_PackedMapOfInteger& MeshVS_DeformedDataSource::GetAllNodes() const
{
  if (myNonDeformedDataSource.IsNull())
    return myEmptyMap;
  else
    return myNonDeformedDataSource->GetAllNodes();
}

const TColStd_PackedMapOfInteger& MeshVS_DeformedDataSource::GetAllElements() const
{
  if (myNonDeformedDataSource.IsNull())
    return myEmptyMap;
  else
    return myNonDeformedDataSource->GetAllElements();
}

const NCollection_DataMap<int, gp_Vec>& MeshVS_DeformedDataSource::GetVectors() const
{
  return myVectors;
}

void MeshVS_DeformedDataSource::SetVectors(const NCollection_DataMap<int, gp_Vec>& Map)
{
  myVectors = Map;
}

bool MeshVS_DeformedDataSource::GetVector(const int ID, gp_Vec& Vect) const
{
  bool aRes = myVectors.IsBound(ID);
  if (aRes)
    Vect = myVectors.Find(ID);
  return aRes;
}

void MeshVS_DeformedDataSource::SetVector(const int ID, const gp_Vec& Vect)
{
  bool aRes = myVectors.IsBound(ID);
  if (aRes)
    myVectors.ChangeFind(ID) = Vect;
  else
    myVectors.Bind(ID, Vect);
}

void MeshVS_DeformedDataSource::SetNonDeformedDataSource(
  const occ::handle<MeshVS_DataSource>& theDS)
{
  myNonDeformedDataSource = theDS;
}

occ::handle<MeshVS_DataSource> MeshVS_DeformedDataSource::GetNonDeformedDataSource() const
{
  return myNonDeformedDataSource;
}

void MeshVS_DeformedDataSource::SetMagnify(const double theMagnify)
{
  if (theMagnify <= 0)
    myMagnify = 1.0;
  else
    myMagnify = theMagnify;
}

double MeshVS_DeformedDataSource::GetMagnify() const
{
  return myMagnify;
}
