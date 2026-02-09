#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <ShapeAnalysis_FreeBoundData.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
class ShapeAnalysis_FreeBoundData;
class TopoDS_Wire;

class ShapeAnalysis_FreeBoundsProperties
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeAnalysis_FreeBoundsProperties();

  Standard_EXPORT ShapeAnalysis_FreeBoundsProperties(const TopoDS_Shape& shape,
                                                     const double        tolerance,
                                                     const bool          splitclosed = false,
                                                     const bool          splitopen   = false);

  Standard_EXPORT ShapeAnalysis_FreeBoundsProperties(const TopoDS_Shape& shape,
                                                     const bool          splitclosed = false,
                                                     const bool          splitopen   = false);

  Standard_EXPORT void Init(const TopoDS_Shape& shape,
                            const double        tolerance,
                            const bool          splitclosed = false,
                            const bool          splitopen   = false);

  Standard_EXPORT void Init(const TopoDS_Shape& shape,
                            const bool          splitclosed = false,
                            const bool          splitopen   = false);

  Standard_EXPORT bool Perform();

  bool IsLoaded() const;

  TopoDS_Shape Shape() const;

  double Tolerance() const;

  int NbFreeBounds() const;

  int NbClosedFreeBounds() const;

  int NbOpenFreeBounds() const;

  occ::handle<NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>> ClosedFreeBounds()
    const;

  occ::handle<NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>> OpenFreeBounds()
    const;

  occ::handle<ShapeAnalysis_FreeBoundData> ClosedFreeBound(const int index) const;

  occ::handle<ShapeAnalysis_FreeBoundData> OpenFreeBound(const int index) const;

  Standard_EXPORT bool DispatchBounds();

  Standard_EXPORT bool CheckContours(const double prec = 0.0);

  Standard_EXPORT bool CheckNotches(const double prec = 0.0);

  Standard_EXPORT bool CheckNotches(occ::handle<ShapeAnalysis_FreeBoundData>& fbData,
                                    const double                              prec = 0.0);

  Standard_EXPORT bool CheckNotches(const TopoDS_Wire& freebound,
                                    const int          num,
                                    TopoDS_Wire&       notch,
                                    double&            distMax,
                                    const double       prec = 0.0);

  Standard_EXPORT bool FillProperties(occ::handle<ShapeAnalysis_FreeBoundData>& fbData,
                                      const double                              prec = 0.0);

private:
  TopoDS_Shape                                                                 myShape;
  double                                                                       myTolerance;
  bool                                                                         mySplitClosed;
  bool                                                                         mySplitOpen;
  occ::handle<NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>> myClosedFreeBounds;
  occ::handle<NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>> myOpenFreeBounds;
};

#include <ShapeAnalysis_FreeBoundData.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

inline TopoDS_Shape ShapeAnalysis_FreeBoundsProperties::Shape() const
{
  return myShape;
}

inline bool ShapeAnalysis_FreeBoundsProperties::IsLoaded() const
{
  return !(myShape.IsNull());
}

inline double ShapeAnalysis_FreeBoundsProperties::Tolerance() const
{
  return myTolerance;
}

inline int ShapeAnalysis_FreeBoundsProperties::NbFreeBounds() const
{
  return (myClosedFreeBounds->Length() + myOpenFreeBounds->Length());
}

inline int ShapeAnalysis_FreeBoundsProperties::NbClosedFreeBounds() const
{
  return myClosedFreeBounds->Length();
}

inline int ShapeAnalysis_FreeBoundsProperties::NbOpenFreeBounds() const
{
  return myOpenFreeBounds->Length();
}

inline occ::handle<NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>>
  ShapeAnalysis_FreeBoundsProperties::ClosedFreeBounds() const
{
  return myClosedFreeBounds;
}

inline occ::handle<NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>>
  ShapeAnalysis_FreeBoundsProperties::OpenFreeBounds() const
{
  return myOpenFreeBounds;
}

inline occ::handle<ShapeAnalysis_FreeBoundData> ShapeAnalysis_FreeBoundsProperties::ClosedFreeBound(
  const int index) const
{
  return myClosedFreeBounds->Value(index);
}

inline occ::handle<ShapeAnalysis_FreeBoundData> ShapeAnalysis_FreeBoundsProperties::OpenFreeBound(
  const int index) const
{
  return myOpenFreeBounds->Value(index);
}
