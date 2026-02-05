#pragma once

#include <IMeshData_TessellatedShape.hpp>
#include <IMeshData_StatusOwner.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS.hpp>
#include <IMeshData_Types.hpp>

//! Interface class representing discrete model of a wire.
//! Wire should represent an ordered set of edges.
class IMeshData_Wire : public IMeshData_TessellatedShape, public IMeshData_StatusOwner
{
public:
  //! Destructor.
  ~IMeshData_Wire() override = default;

  //! Returns TopoDS_Face attached to model.
  const TopoDS_Wire& GetWire() const { return TopoDS::Wire(GetShape()); }

  //! Returns number of edges.
  Standard_EXPORT virtual int EdgesNb() const = 0;

  //! Adds new discrete edge with specified orientation to wire chain.
  //! @return index of added edge in wire chain.
  Standard_EXPORT virtual int AddEdge(const IMeshData::IEdgePtr& theDEdge,
                                      const TopAbs_Orientation   theOrientation) = 0;

  //! Returns discrete edge with the given index.
  Standard_EXPORT virtual const IMeshData::IEdgePtr& GetEdge(const int theIndex) const = 0;

  //! Returns True if orientation of discrete edge with the given index is forward.
  Standard_EXPORT virtual TopAbs_Orientation GetEdgeOrientation(const int theIndex) const = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshData_Wire, IMeshData_TessellatedShape)

protected:
  //! Constructor.
  //! Initializes empty model.
  IMeshData_Wire(const TopoDS_Wire& theWire)
      : IMeshData_TessellatedShape(theWire)
  {
  }
};
