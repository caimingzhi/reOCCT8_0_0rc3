#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Intf_SectionPoint.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Boolean.hpp>
class Intf_SectionPoint;

//! Describe a polyline of intersection between two
//! polyhedra as a sequence of points of intersection.
class Intf_SectionLine
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns number of points in this SectionLine.
  int NumberOfPoints() const;

  //! Gives the point of intersection of address <Index> in the
  //! SectionLine.
  Standard_EXPORT const Intf_SectionPoint& GetPoint(const int Index) const;

  //! Returns True if the SectionLine is closed.
  Standard_EXPORT bool IsClosed() const;

  //! Returns True if ThePI is in the SectionLine <me>.
  Standard_EXPORT bool Contains(const Intf_SectionPoint& ThePI) const;

  //! Checks if <ThePI> is an end of the SectionLine. Returns 1
  //! for the beginning, 2 for the end, otherwise 0.
  Standard_EXPORT int IsEnd(const Intf_SectionPoint& ThePI) const;

  //! Compares two SectionLines.
  Standard_EXPORT bool IsEqual(const Intf_SectionLine& Other) const;

  bool operator==(const Intf_SectionLine& Other) const { return IsEqual(Other); }

  //! Constructs an empty SectionLine.
  Standard_EXPORT Intf_SectionLine();

  //! Copies a SectionLine.
  Standard_EXPORT Intf_SectionLine(const Intf_SectionLine& Other);

  //! Assignment
  Intf_SectionLine& operator=(const Intf_SectionLine& theOther)
  {
    // closed = theOther.closed; // not copied as in copy constructor
    myPoints = theOther.myPoints;
    return *this;
  }

  //! Adds a point at the end of the SectionLine.
  Standard_EXPORT void Append(const Intf_SectionPoint& Pi);

  //! Concatenates the SectionLine <LS> at the end of the
  //! SectionLine <me>.
  Standard_EXPORT void Append(Intf_SectionLine& LS);

  //! Adds a point to the beginning of the SectionLine <me>.
  Standard_EXPORT void Prepend(const Intf_SectionPoint& Pi);

  //! Concatenates a SectionLine <LS> at the beginning of the
  //! SectionLine <me>.
  Standard_EXPORT void Prepend(Intf_SectionLine& LS);

  //! Reverses the order of the elements of the SectionLine.
  Standard_EXPORT void Reverse();

  //! Closes the SectionLine.
  Standard_EXPORT void Close();

  Standard_EXPORT void Dump(const int Indent) const;

private:
  NCollection_Sequence<Intf_SectionPoint> myPoints;
  bool                                    closed;
};

#include <Intf_SectionPoint.hpp>
#include <NCollection_Sequence.hpp>

//=================================================================================================

inline int Intf_SectionLine::NumberOfPoints() const
{
  return myPoints.Length();
}
