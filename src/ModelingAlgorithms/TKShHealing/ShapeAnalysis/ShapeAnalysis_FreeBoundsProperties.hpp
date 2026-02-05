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

//! This class is intended to calculate shape free bounds
//! properties.
//! This class provides the following functionalities:
//! - calculates area of the contour,
//! - calculates perimeter of the contour,
//! - calculates ratio of average length to average width of the
//! contour,
//! - estimates average width of contour,
//! - finds the notches (narrow 'V'-like sub-contour) on the
//! contour.
//!
//! For getting free bounds this class uses
//! ShapeAnalysis_FreeBounds class.
//!
//! For description of parameters used for initializing this
//! class refer to CDL of ShapeAnalysis_FreeBounds.
//!
//! Properties of each contour are stored in the data structure
//! ShapeAnalysis_FreeBoundData.
class ShapeAnalysis_FreeBoundsProperties
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT ShapeAnalysis_FreeBoundsProperties();

  //! Creates the object and calls corresponding Init.
  //! <shape> should be a compound of faces.
  Standard_EXPORT ShapeAnalysis_FreeBoundsProperties(const TopoDS_Shape& shape,
                                                     const double        tolerance,
                                                     const bool          splitclosed = false,
                                                     const bool          splitopen   = false);

  //! Creates the object and calls corresponding Init.
  //! <shape> should be a compound of shells.
  Standard_EXPORT ShapeAnalysis_FreeBoundsProperties(const TopoDS_Shape& shape,
                                                     const bool          splitclosed = false,
                                                     const bool          splitopen   = false);

  //! Initializes the object with given parameters.
  //! <shape> should be a compound of faces.
  Standard_EXPORT void Init(const TopoDS_Shape& shape,
                            const double        tolerance,
                            const bool          splitclosed = false,
                            const bool          splitopen   = false);

  //! Initializes the object with given parameters.
  //! <shape> should be a compound of shells.
  Standard_EXPORT void Init(const TopoDS_Shape& shape,
                            const bool          splitclosed = false,
                            const bool          splitopen   = false);

  //! Builds and analyzes free bounds of the shape.
  //! First calls ShapeAnalysis_FreeBounds for building free
  //! bounds.
  //! Then on each free bound computes its properties:
  //! - area of the contour,
  //! - perimeter of the contour,
  //! - ratio of average length to average width of the contour,
  //! - average width of contour,
  //! - notches on the contour and for each notch
  //! - maximum width of the notch.
  Standard_EXPORT bool Perform();

  //! Returns True if shape is loaded
  bool IsLoaded() const;

  //! Returns shape
  TopoDS_Shape Shape() const;

  //! Returns tolerance
  double Tolerance() const;

  //! Returns number of free bounds
  int NbFreeBounds() const;

  //! Returns number of closed free bounds
  int NbClosedFreeBounds() const;

  //! Returns number of open free bounds
  int NbOpenFreeBounds() const;

  //! Returns all closed free bounds
  occ::handle<NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>> ClosedFreeBounds()
    const;

  //! Returns all open free bounds
  occ::handle<NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>> OpenFreeBounds()
    const;

  //! Returns properties of closed free bound specified by its rank
  //! number
  occ::handle<ShapeAnalysis_FreeBoundData> ClosedFreeBound(const int index) const;

  //! Returns properties of open free bound specified by its rank
  //! number
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

//=================================================================================================

inline TopoDS_Shape ShapeAnalysis_FreeBoundsProperties::Shape() const
{
  return myShape;
}

//=======================================================================
// function : IsLoaded
// purpose  : Returns True if shape is loaded
//=======================================================================

inline bool ShapeAnalysis_FreeBoundsProperties::IsLoaded() const
{
  return !(myShape.IsNull());
}

//=================================================================================================

inline double ShapeAnalysis_FreeBoundsProperties::Tolerance() const
{
  return myTolerance;
}

//=======================================================================
// function : NbFreeBounds
// purpose  : Returns number of free bounds
//=======================================================================

inline int ShapeAnalysis_FreeBoundsProperties::NbFreeBounds() const
{
  return (myClosedFreeBounds->Length() + myOpenFreeBounds->Length());
}

//=======================================================================
// function : NbClosedFreeBounds
// purpose  : Returns number of closed free bounds
//=======================================================================

inline int ShapeAnalysis_FreeBoundsProperties::NbClosedFreeBounds() const
{
  return myClosedFreeBounds->Length();
}

//=======================================================================
// function : NbOpenFreeBounds
// purpose  : Returns number of open free bounds
//=======================================================================

inline int ShapeAnalysis_FreeBoundsProperties::NbOpenFreeBounds() const
{
  return myOpenFreeBounds->Length();
}

//=======================================================================
// function : ClosedFreeBounds
// purpose  : Returns all closed free bounds
//=======================================================================

inline occ::handle<NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>>
  ShapeAnalysis_FreeBoundsProperties::ClosedFreeBounds() const
{
  return myClosedFreeBounds;
}

//=======================================================================
// function : OpenFreeBounds
// purpose  : Returns all open free bounds
//=======================================================================

inline occ::handle<NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>>
  ShapeAnalysis_FreeBoundsProperties::OpenFreeBounds() const
{
  return myOpenFreeBounds;
}

//=======================================================================
// function : ClosedFreeBound
// purpose  : Returns properties of closed free bound specified by its rank
//           number
//=======================================================================

inline occ::handle<ShapeAnalysis_FreeBoundData> ShapeAnalysis_FreeBoundsProperties::ClosedFreeBound(
  const int index) const
{
  return myClosedFreeBounds->Value(index);
}

//=======================================================================
// function : OpenFreeBound
// purpose  : Returns properties of open free bound specified by its rank
//           number
//=======================================================================

inline occ::handle<ShapeAnalysis_FreeBoundData> ShapeAnalysis_FreeBoundsProperties::OpenFreeBound(
  const int index) const
{
  return myOpenFreeBounds->Value(index);
}
