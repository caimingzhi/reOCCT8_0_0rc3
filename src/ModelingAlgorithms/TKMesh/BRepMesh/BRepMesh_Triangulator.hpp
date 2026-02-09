#pragma once

#include <gp_Pln.hpp>
#include <Poly_Triangulation.hpp>
#include <IMeshData_Types.hpp>
#include <NCollection_Vector.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Shared.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepMesh_DataStructureOfDelaun.hpp>

class Message_Messenger;

class BRepMesh_Triangulator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Poly_Triangulation> ToPolyTriangulation(
    const NCollection_Array1<gp_Pnt>&      theNodes,
    const NCollection_List<Poly_Triangle>& thePolyTriangles);

public:
  Standard_EXPORT BRepMesh_Triangulator(const NCollection_Vector<gp_XYZ>&                  theXYZs,
                                        const NCollection_List<NCollection_Sequence<int>>& theWires,
                                        const gp_Dir&                                      theNorm);

  Standard_EXPORT bool Perform(NCollection_List<Poly_Triangle>& thePolyTriangles);

  void SetMessenger(const occ::handle<Message_Messenger>& theMess) { myMess = theMess; }

  BRepMesh_Triangulator& operator=(const BRepMesh_Triangulator& theOther);

private:
  void addTriange34(const NCollection_Sequence<int>& theW,
                    NCollection_List<Poly_Triangle>& thePolyTriangles);

  bool checkCondition(const int (&theNodes)[4], const NCollection_Sequence<int>& theWire);

  bool prepareMeshStructure();

  bool triangulate(NCollection_List<Poly_Triangle>& thePolyTriangles);

private:
  const NCollection_Vector<gp_XYZ>&                  myXYZs;
  const NCollection_List<NCollection_Sequence<int>>& myWires;
  gp_Pln                                             myPlane;
  occ::handle<Message_Messenger>                     myMess;

  occ::handle<BRepMesh_DataStructureOfDelaun> myMeshStructure;
  NCollection_DataMap<int, int>               myTmpMap;
  Handle(IMeshData::VectorOfInteger)          myIndices;
};
