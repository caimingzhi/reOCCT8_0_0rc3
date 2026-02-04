#pragma once


#include <IMeshData_Shape.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>
#include <IMeshData_Types.hpp>

class TopoDS_Face;
class TopoDS_Edge;

//! Interface class representing discrete model of a shape.
class IMeshData_Model : public IMeshData_Shape
{
public:
  //! Destructor.
  ~IMeshData_Model() override = default;

  //! Returns maximum size of shape model.
  Standard_EXPORT virtual double GetMaxSize() const = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshData_Model, IMeshData_Shape)

public: //! @name discrete faces
  //! Returns number of faces in discrete model.
  Standard_EXPORT virtual int FacesNb() const = 0;

  //! Adds new face to shape model.
  Standard_EXPORT virtual const IMeshData::IFaceHandle& AddFace(const TopoDS_Face& theFace) = 0;

  //! Gets model's face with the given index.
  Standard_EXPORT virtual const IMeshData::IFaceHandle& GetFace(const int theIndex) const = 0;

public: //! @name discrete edges
  //! Returns number of edges in discrete model.
  Standard_EXPORT virtual int EdgesNb() const = 0;

  //! Adds new edge to shape model.
  Standard_EXPORT virtual const IMeshData::IEdgeHandle& AddEdge(const TopoDS_Edge& theEdge) = 0;

  //! Gets model's edge with the given index.
  Standard_EXPORT virtual const IMeshData::IEdgeHandle& GetEdge(const int theIndex) const = 0;

protected:
  //! Constructor.
  //! Initializes empty model.
  IMeshData_Model(const TopoDS_Shape& theShape)
      : IMeshData_Shape(theShape)
  {
  }
};

