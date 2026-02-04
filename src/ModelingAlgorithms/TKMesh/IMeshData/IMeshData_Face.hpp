#pragma once


#include <IMeshData_TessellatedShape.hpp>
#include <IMeshData_StatusOwner.hpp>
#include <Standard_Type.hpp>
#include <TopoDS.hpp>
#include <IMeshData_Status.hpp>
#include <IMeshData_Types.hpp>
#include <BRepAdaptor_Surface.hpp>

class TopoDS_Wire;

//! Interface class representing discrete model of a face.
//! Face model contains one or several wires.
//! First wire is always outer one.
class IMeshData_Face : public IMeshData_TessellatedShape, public IMeshData_StatusOwner
{
public:
  //! Destructor.
  ~IMeshData_Face() override = default;

  //! Returns number of wires.
  Standard_EXPORT virtual int WiresNb() const = 0;

  //! Adds wire to discrete model of face.
  Standard_EXPORT virtual const IMeshData::IWireHandle& AddWire(const TopoDS_Wire& theWire,
                                                                const int theEdgeNb = 0) = 0;

  //! Returns discrete edge with the given index.
  Standard_EXPORT virtual const IMeshData::IWireHandle& GetWire(const int theIndex) const = 0;

  //! Returns face's surface.
  const occ::handle<BRepAdaptor_Surface>& GetSurface() const { return mySurface; }

  //! Returns TopoDS_Face attached to model.
  const TopoDS_Face& GetFace() const { return TopoDS::Face(GetShape()); }

  //! Returns whether the face discrete model is valid.
  bool IsValid() const
  {
    return (IsEqual(IMeshData_NoError) || IsEqual(IMeshData_ReMesh)
            || IsEqual(IMeshData_UnorientedWire));
  }

  DEFINE_STANDARD_RTTIEXT(IMeshData_Face, IMeshData_TessellatedShape)

protected:
  //! Constructor.
  //! Initializes empty model.
  IMeshData_Face(const TopoDS_Face& theFace)
      : IMeshData_TessellatedShape(theFace)
  {
    BRepAdaptor_Surface aSurfAdaptor(GetFace(), false);
    mySurface = new BRepAdaptor_Surface(aSurfAdaptor);
  }

private:
  mutable occ::handle<BRepAdaptor_Surface> mySurface;
};

