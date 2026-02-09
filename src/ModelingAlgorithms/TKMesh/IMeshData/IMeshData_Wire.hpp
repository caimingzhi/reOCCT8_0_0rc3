#pragma once

#include <IMeshData_TessellatedShape.hpp>
#include <IMeshData_StatusOwner.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS.hpp>
#include <IMeshData_Types.hpp>

class IMeshData_Wire : public IMeshData_TessellatedShape, public IMeshData_StatusOwner
{
public:
  ~IMeshData_Wire() override = default;

  const TopoDS_Wire& GetWire() const { return TopoDS::Wire(GetShape()); }

  Standard_EXPORT virtual int EdgesNb() const = 0;

  Standard_EXPORT virtual int AddEdge(const IMeshData::IEdgePtr& theDEdge,
                                      const TopAbs_Orientation   theOrientation) = 0;

  Standard_EXPORT virtual const IMeshData::IEdgePtr& GetEdge(const int theIndex) const = 0;

  Standard_EXPORT virtual TopAbs_Orientation GetEdgeOrientation(const int theIndex) const = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshData_Wire, IMeshData_TessellatedShape)

protected:
  IMeshData_Wire(const TopoDS_Wire& theWire)
      : IMeshData_TessellatedShape(theWire)
  {
  }
};
