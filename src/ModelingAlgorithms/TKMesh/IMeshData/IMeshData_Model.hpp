#pragma once

#include <IMeshData_Shape.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>
#include <IMeshData_Types.hpp>

class TopoDS_Face;
class TopoDS_Edge;

class IMeshData_Model : public IMeshData_Shape
{
public:
  ~IMeshData_Model() override = default;

  Standard_EXPORT virtual double GetMaxSize() const = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshData_Model, IMeshData_Shape)

public:
  Standard_EXPORT virtual int FacesNb() const = 0;

  Standard_EXPORT virtual const IMeshData::IFaceHandle& AddFace(const TopoDS_Face& theFace) = 0;

  Standard_EXPORT virtual const IMeshData::IFaceHandle& GetFace(const int theIndex) const = 0;

public:
  Standard_EXPORT virtual int EdgesNb() const = 0;

  Standard_EXPORT virtual const IMeshData::IEdgeHandle& AddEdge(const TopoDS_Edge& theEdge) = 0;

  Standard_EXPORT virtual const IMeshData::IEdgeHandle& GetEdge(const int theIndex) const = 0;

protected:
  IMeshData_Model(const TopoDS_Shape& theShape)
      : IMeshData_Shape(theShape)
  {
  }
};
