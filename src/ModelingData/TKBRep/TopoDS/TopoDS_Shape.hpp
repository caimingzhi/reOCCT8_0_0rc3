#pragma once

#include <Standard_Handle.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_TShape.hpp>
#include <Standard_HashUtils.hpp>

#ifdef Convex
  #undef Convex
#endif

class TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

  TopoDS_Shape()
      : myOrient(TopAbs_EXTERNAL)
  {
  }

  template <class T2>
  TopoDS_Shape(
    T2&& theOther,
    typename std::enable_if<opencascade::std::is_base_of<TopoDS_Shape, T2>::value>::type* = nullptr)
      : myTShape(std::forward<T2>(theOther).myTShape),
        myLocation(std::forward<T2>(theOther).myLocation),
        myOrient(std::forward<T2>(theOther).myOrient)
  {
  }

  template <class T2>
  typename std::enable_if<opencascade::std::is_base_of<TopoDS_Shape, T2>::value,
                          TopoDS_Shape>::type&
    operator=(T2&& theOther)
  {
    myTShape   = std::forward<T2>(theOther).myTShape;
    myLocation = std::forward<T2>(theOther).myLocation;
    myOrient   = std::forward<T2>(theOther).myOrient;
    return *this;
  }

  bool IsNull() const { return myTShape.IsNull(); }

  void Nullify()
  {
    myTShape.Nullify();
    myLocation.Clear();
    myOrient = TopAbs_EXTERNAL;
  }

  const TopLoc_Location& Location() const { return myLocation; }

  void Location(const TopLoc_Location& theLoc, const bool theRaiseExc = false)
  {
    const gp_Trsf& aTrsf = theLoc.Transformation();
    if (theRaiseExc)
    {
      validateTransformation(aTrsf);
    }
    myLocation = theLoc;
  }

  TopoDS_Shape Located(const TopLoc_Location& theLoc, const bool theRaiseExc = false) const
  {
    TopoDS_Shape aShape(*this);
    aShape.Location(theLoc, theRaiseExc);
    return aShape;
  }

  TopAbs_Orientation Orientation() const { return myOrient; }

  void Orientation(TopAbs_Orientation theOrient) { myOrient = theOrient; }

  TopoDS_Shape Oriented(TopAbs_Orientation theOrient) const
  {
    TopoDS_Shape aShape(*this);
    aShape.Orientation(theOrient);
    return aShape;
  }

  const occ::handle<TopoDS_TShape>& TShape() const { return myTShape; }

  TopAbs_ShapeEnum ShapeType() const { return myTShape->ShapeType(); }

  bool Free() const { return myTShape->Free(); }

  void Free(bool theIsFree) { myTShape->Free(theIsFree); }

  bool Locked() const { return myTShape->Locked(); }

  void Locked(bool theIsLocked) { myTShape->Locked(theIsLocked); }

  bool Modified() const { return myTShape->Modified(); }

  void Modified(bool theIsModified) { myTShape->Modified(theIsModified); }

  bool Checked() const { return myTShape->Checked(); }

  void Checked(bool theIsChecked) { myTShape->Checked(theIsChecked); }

  bool Orientable() const { return myTShape->Orientable(); }

  void Orientable(const bool theIsOrientable) { myTShape->Orientable(theIsOrientable); }

  bool Closed() const { return myTShape->Closed(); }

  void Closed(bool theIsClosed) { myTShape->Closed(theIsClosed); }

  bool Infinite() const { return myTShape->Infinite(); }

  void Infinite(bool theIsInfinite) { myTShape->Infinite(theIsInfinite); }

  bool Convex() const { return myTShape->Convex(); }

  void Convex(bool theIsConvex) { myTShape->Convex(theIsConvex); }

  void Move(const TopLoc_Location& thePosition, const bool theRaiseExc = false)
  {
    const gp_Trsf& aTrsf = thePosition.Transformation();
    if (theRaiseExc)
    {
      validateTransformation(aTrsf);
    }
    myLocation = thePosition * myLocation;
  }

  TopoDS_Shape Moved(const TopLoc_Location& thePosition, const bool theRaiseExc = false) const
  {
    TopoDS_Shape aShape(*this);
    aShape.Move(thePosition, theRaiseExc);
    return aShape;
  }

  void Reverse() { myOrient = TopAbs::Reverse(myOrient); }

  TopoDS_Shape Reversed() const
  {
    TopoDS_Shape aShape(*this);
    aShape.Reverse();
    return aShape;
  }

  void Complement() { myOrient = TopAbs::Complement(myOrient); }

  TopoDS_Shape Complemented() const
  {
    TopoDS_Shape aShape(*this);
    aShape.Complement();
    return aShape;
  }

  void Compose(TopAbs_Orientation theOrient) { myOrient = TopAbs::Compose(myOrient, theOrient); }

  TopoDS_Shape Composed(TopAbs_Orientation theOrient) const
  {
    TopoDS_Shape aShape(*this);
    aShape.Compose(theOrient);
    return aShape;
  }

  int NbChildren() const { return myTShape.IsNull() ? 0 : myTShape->NbChildren(); }

  bool IsPartner(const TopoDS_Shape& theOther) const { return (myTShape == theOther.myTShape); }

  bool IsSame(const TopoDS_Shape& theOther) const
  {
    return myTShape == theOther.myTShape && myLocation == theOther.myLocation;
  }

  bool IsEqual(const TopoDS_Shape& theOther) const
  {
    return myTShape == theOther.myTShape && myLocation == theOther.myLocation
           && myOrient == theOther.myOrient;
  }

  bool operator==(const TopoDS_Shape& theOther) const { return IsEqual(theOther); }

  bool IsNotEqual(const TopoDS_Shape& theOther) const { return !IsEqual(theOther); }

  bool operator!=(const TopoDS_Shape& theOther) const { return IsNotEqual(theOther); }

  void EmptyCopy() { myTShape = myTShape->EmptyCopy(); }

  TopoDS_Shape EmptyCopied() const
  {
    TopoDS_Shape aShape(*this);
    aShape.EmptyCopy();
    return aShape;
  }

  void TShape(const occ::handle<TopoDS_TShape>& theTShape) { myTShape = theTShape; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  void validateTransformation(const gp_Trsf& theTrsf) const
  {
    if (std::abs(std::abs(theTrsf.ScaleFactor()) - 1.) > TopLoc_Location::ScalePrec()
        || theTrsf.IsNegative())
    {

      throw Standard_DomainError("Transformation with scaling transformation is forbidden");
    }
  }

private:
  occ::handle<TopoDS_TShape> myTShape;
  TopLoc_Location            myLocation;
  TopAbs_Orientation         myOrient;
};

namespace std
{
  template <>
  struct hash<TopoDS_Shape>
  {
    size_t operator()(const TopoDS_Shape& theShape) const noexcept
    {
      const size_t aHL = std::hash<TopLoc_Location>{}(theShape.Location());
      return aHL == 0
               ? opencascade::hash(theShape.TShape().get())
               : opencascade::MurmurHash::hash_combine(theShape.TShape().get(), sizeof(void*), aHL);
    }
  };
} // namespace std
