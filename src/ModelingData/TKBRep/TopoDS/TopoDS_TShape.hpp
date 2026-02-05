#pragma once

#include <TopAbs.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;

// resolve name collisions with X11 headers
#ifdef Convex
  #undef Convex
#endif

//! A TShape is a topological structure describing a
//! set of points in a 2D or 3D space.
//!
//! A topological shape is a structure made from other
//! shapes. This is a deferred class used to support
//! topological objects.
//!
//! TShapes are defined by their optional domain
//! (geometry) and their components (other TShapes
//! with Locations and Orientations). The components
//! are stored in a List of Shapes.
//!
//! A TShape contains the following boolean flags:
//!
//! - Free       : Free or Frozen.
//! - Modified   : Has been modified.
//! - Checked    : Has been checked.
//! - Orientable : Can be oriented.
//! - Closed     : Is closed (note that only Wires and Shells may be closed).
//! - Infinite   : Is infinite.
//! - Convex     : Is convex.
//!
//! Users have no direct access to the classes derived
//! from TShape. They handle them with the classes
//! derived from Shape.
class TopoDS_TShape : public Standard_Transient
{

public:
  //! Returns the free flag.
  bool Free() const { return ((myFlags & TopoDS_TShape_Flags_Free) != 0); }

  //! Sets the free flag.
  void Free(bool theIsFree) { setFlag(TopoDS_TShape_Flags_Free, theIsFree); }

  //! Returns the locked flag.
  bool Locked() const { return ((myFlags & TopoDS_TShape_Flags_Locked) != 0); }

  //! Sets the locked flag.
  void Locked(bool theIsLocked) { setFlag(TopoDS_TShape_Flags_Locked, theIsLocked); }

  //! Returns the modification flag.
  bool Modified() const { return ((myFlags & TopoDS_TShape_Flags_Modified) != 0); }

  //! Sets the modification flag.
  void Modified(bool theIsModified)
  {
    setFlag(TopoDS_TShape_Flags_Modified, theIsModified);
    if (theIsModified)
    {
      // clang-format off
      setFlag (TopoDS_TShape_Flags_Checked, false); // when a TShape is modified it is also unchecked
      // clang-format on
    }
  }

  //! Returns the checked flag.
  bool Checked() const { return ((myFlags & TopoDS_TShape_Flags_Checked) != 0); }

  //! Sets the checked flag.
  void Checked(bool theIsChecked) { setFlag(TopoDS_TShape_Flags_Checked, theIsChecked); }

  //! Returns the orientability flag.
  bool Orientable() const { return ((myFlags & TopoDS_TShape_Flags_Orientable) != 0); }

  //! Sets the orientability flag.
  void Orientable(bool theIsOrientable)
  {
    setFlag(TopoDS_TShape_Flags_Orientable, theIsOrientable);
  }

  //! Returns the closedness flag.
  bool Closed() const { return ((myFlags & TopoDS_TShape_Flags_Closed) != 0); }

  //! Sets the closedness flag.
  void Closed(bool theIsClosed) { setFlag(TopoDS_TShape_Flags_Closed, theIsClosed); }

  //! Returns the infinity flag.
  bool Infinite() const { return ((myFlags & TopoDS_TShape_Flags_Infinite) != 0); }

  //! Sets the infinity flag.
  void Infinite(bool theIsInfinite) { setFlag(TopoDS_TShape_Flags_Infinite, theIsInfinite); }

  //! Returns the convexness flag.
  bool Convex() const { return ((myFlags & TopoDS_TShape_Flags_Convex) != 0); }

  //! Sets the convexness flag.
  void Convex(bool theIsConvex) { setFlag(TopoDS_TShape_Flags_Convex, theIsConvex); }

  //! Returns the type as a term of the ShapeEnum enum :
  //! VERTEX, EDGE, WIRE, FACE, ....
  Standard_EXPORT virtual TopAbs_ShapeEnum ShapeType() const = 0;

  //! Returns a copy of the TShape with no sub-shapes.
  Standard_EXPORT virtual occ::handle<TopoDS_TShape> EmptyCopy() const = 0;

  //! Returns the number of direct sub-shapes (children).
  //! @sa TopoDS_Iterator for accessing sub-shapes
  int NbChildren() const { return myShapes.Size(); }

  //! Dumps the content of me into the stream
  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  friend class TopoDS_Iterator;
  friend class TopoDS_Builder;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TShape, Standard_Transient)

protected:
  //! Constructs an empty TShape.
  //! Free       : True
  //! Modified   : True
  //! Checked    : False
  //! Orientable : True
  //! Closed     : False
  //! Infinite   : False
  //! Convex     : False
  TopoDS_TShape()
      : myFlags(TopoDS_TShape_Flags_Free | TopoDS_TShape_Flags_Modified
                | TopoDS_TShape_Flags_Orientable)
  {
  }

private:
  // Defined mask values
  enum TopoDS_TShape_Flags
  {
    TopoDS_TShape_Flags_Free       = 0x001,
    TopoDS_TShape_Flags_Modified   = 0x002,
    TopoDS_TShape_Flags_Checked    = 0x004,
    TopoDS_TShape_Flags_Orientable = 0x008,
    TopoDS_TShape_Flags_Closed     = 0x010,
    TopoDS_TShape_Flags_Infinite   = 0x020,
    TopoDS_TShape_Flags_Convex     = 0x040,
    TopoDS_TShape_Flags_Locked     = 0x080
  };

  //! Set bit flag.
  void setFlag(TopoDS_TShape_Flags theFlag, bool theIsOn)
  {
    if (theIsOn)
      myFlags |= (int)theFlag;
    else
      myFlags &= ~(int)theFlag;
  }

private:
  NCollection_List<TopoDS_Shape> myShapes;
  int                            myFlags;
};
