#pragma once

#include <gp_Pnt.hpp>
#include <IVtk_Interface.hpp>
#include <IVtk_Types.hpp>
#include <NCollection_Vec3.hpp>

class IVtk_IShapeData : public IVtk_Interface
{
public:
  typedef occ::handle<IVtk_IShapeData> Handle;

  ~IVtk_IShapeData() override = default;

  DEFINE_STANDARD_RTTIEXT(IVtk_IShapeData, IVtk_Interface)

  virtual IVtk_PointId InsertPoint(const gp_Pnt&                  thePnt,
                                   const NCollection_Vec3<float>& theNorm) = 0;

  virtual void InsertVertex(const IVtk_IdType   theShapeID,
                            const IVtk_PointId  thePointId,
                            const IVtk_MeshType theMeshType = MT_Undefined) = 0;

  virtual void InsertLine(const IVtk_IdType   theShapeID,
                          const IVtk_PointId  thePointId1,
                          const IVtk_PointId  thePointId2,
                          const IVtk_MeshType theMeshType = MT_Undefined) = 0;

  virtual void InsertLine(const IVtk_IdType                     theShapeID,
                          const NCollection_List<IVtk_PointId>* thePointIds,
                          const IVtk_MeshType                   theMeshType = MT_Undefined) = 0;

  virtual void InsertTriangle(const IVtk_IdType   theShapeID,
                              const IVtk_PointId  thePointId1,
                              const IVtk_PointId  thePointId2,
                              const IVtk_PointId  thePointId3,
                              const IVtk_MeshType theMeshType = MT_Undefined) = 0;

public:
  virtual IVtk_PointId InsertCoordinate(double theX, double theY, double theZ)
  {
    return InsertCoordinate(gp_Pnt(theX, theY, theZ));
  }

  IVtk_PointId InsertCoordinate(const gp_Pnt& thePnt)
  {
    return InsertPoint(thePnt, NCollection_Vec3<float>(0.0f, 0.0f, 1.0f));
  }
};
