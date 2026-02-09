#pragma once

#include <TopAbs.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;

#ifdef Convex
  #undef Convex
#endif

class TopoDS_TShape : public Standard_Transient
{

public:
  bool Free() const { return ((myFlags & TopoDS_TShape_Flags_Free) != 0); }

  void Free(bool theIsFree) { setFlag(TopoDS_TShape_Flags_Free, theIsFree); }

  bool Locked() const { return ((myFlags & TopoDS_TShape_Flags_Locked) != 0); }

  void Locked(bool theIsLocked) { setFlag(TopoDS_TShape_Flags_Locked, theIsLocked); }

  bool Modified() const { return ((myFlags & TopoDS_TShape_Flags_Modified) != 0); }

  void Modified(bool theIsModified)
  {
    setFlag(TopoDS_TShape_Flags_Modified, theIsModified);
    if (theIsModified)
    {

      setFlag(TopoDS_TShape_Flags_Checked, false);
    }
  }

  bool Checked() const { return ((myFlags & TopoDS_TShape_Flags_Checked) != 0); }

  void Checked(bool theIsChecked) { setFlag(TopoDS_TShape_Flags_Checked, theIsChecked); }

  bool Orientable() const { return ((myFlags & TopoDS_TShape_Flags_Orientable) != 0); }

  void Orientable(bool theIsOrientable)
  {
    setFlag(TopoDS_TShape_Flags_Orientable, theIsOrientable);
  }

  bool Closed() const { return ((myFlags & TopoDS_TShape_Flags_Closed) != 0); }

  void Closed(bool theIsClosed) { setFlag(TopoDS_TShape_Flags_Closed, theIsClosed); }

  bool Infinite() const { return ((myFlags & TopoDS_TShape_Flags_Infinite) != 0); }

  void Infinite(bool theIsInfinite) { setFlag(TopoDS_TShape_Flags_Infinite, theIsInfinite); }

  bool Convex() const { return ((myFlags & TopoDS_TShape_Flags_Convex) != 0); }

  void Convex(bool theIsConvex) { setFlag(TopoDS_TShape_Flags_Convex, theIsConvex); }

  Standard_EXPORT virtual TopAbs_ShapeEnum ShapeType() const = 0;

  Standard_EXPORT virtual occ::handle<TopoDS_TShape> EmptyCopy() const = 0;

  int NbChildren() const { return myShapes.Size(); }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  friend class TopoDS_Iterator;
  friend class TopoDS_Builder;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TShape, Standard_Transient)

protected:
  TopoDS_TShape()
      : myFlags(TopoDS_TShape_Flags_Free | TopoDS_TShape_Flags_Modified
                | TopoDS_TShape_Flags_Orientable)
  {
  }

private:
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
