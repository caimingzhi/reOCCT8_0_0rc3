#pragma once

#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <IVtk_IShapeData.hpp>

#include <Standard_WarningsDisable.hpp>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkIdTypeArray.h>
#include <Standard_WarningsRestore.hpp>

class vtkIdTypeArray;
class vtkFloatArray;

class IVtkVTK_ShapeData : public IVtk_IShapeData
{
public:
  static const char* ARRNAME_SUBSHAPE_IDS() { return "SUBSHAPE_IDS"; }

  static const char* ARRNAME_MESH_TYPES() { return "MESH_TYPES"; }

  typedef occ::handle<IVtkVTK_ShapeData> Handle;

  Standard_EXPORT IVtkVTK_ShapeData();

  Standard_EXPORT ~IVtkVTK_ShapeData() override;

  DEFINE_STANDARD_RTTIEXT(IVtkVTK_ShapeData, IVtk_IShapeData)

  Standard_EXPORT IVtk_PointId InsertPoint(const gp_Pnt&                  thePnt,
                                           const NCollection_Vec3<float>& theNorm) override;

  Standard_EXPORT void InsertVertex(const IVtk_IdType   theShapeID,
                                    const IVtk_PointId  thePointId,
                                    const IVtk_MeshType theMeshType) override;

  Standard_EXPORT void InsertLine(const IVtk_IdType   theShapeID,
                                  const IVtk_PointId  thePointId1,
                                  const IVtk_PointId  thePointId2,
                                  const IVtk_MeshType theMeshType) override;

  Standard_EXPORT void InsertLine(const IVtk_IdType                     theShapeID,
                                  const NCollection_List<IVtk_PointId>* thePointIds,
                                  const IVtk_MeshType                   theMeshType) override;

  Standard_EXPORT void InsertTriangle(const IVtk_IdType   theShapeID,
                                      const IVtk_PointId  thePointId1,
                                      const IVtk_PointId  thePointId2,
                                      const IVtk_PointId  thePointId3,
                                      const IVtk_MeshType theMeshType) override;

public:
  vtkPolyData* getVtkPolyData() const { return myPolyData; }

private:
  void insertNextSubShapeId(IVtk_IdType theShapeID, IVtk_MeshType theMeshType)
  {
    const vtkIdType aShapeIDVTK = theShapeID;
    const vtkIdType aType       = theMeshType;
#if (VTK_MAJOR_VERSION > 7) || (VTK_MAJOR_VERSION == 7 && VTK_MINOR_VERSION >= 1)
    mySubShapeIDs->InsertNextTypedTuple(&aShapeIDVTK);
    myMeshTypes->InsertNextTypedTuple(&aType);
#else
    mySubShapeIDs->InsertNextTupleValue(&aShapeIDVTK);
    myMeshTypes->InsertNextTupleValue(&aType);
#endif
  }

private:
  vtkSmartPointer<vtkPolyData>    myPolyData;
  vtkSmartPointer<vtkFloatArray>  myNormals;
  vtkSmartPointer<vtkIdTypeArray> mySubShapeIDs;
  vtkSmartPointer<vtkIdTypeArray> myMeshTypes;
};
