#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GCE2d_Root.hpp>
#include <Geom2d_Line.hpp>

class gp_Ax2d;
class gp_Lin2d;
class gp_Pnt2d;
class gp_Dir2d;

//! This class implements the following algorithms used
//! to create a Line from Geom2d.
//! * Create a Line parallel to another and passing
//! through a point.
//! * Create a Line passing through 2 points.
class GCE2d_MakeLine : public GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a line located in 2D space with the axis placement A.
  //! The Location of A is the origin of the line.
  Standard_EXPORT GCE2d_MakeLine(const gp_Ax2d& A);

  //! Creates a line from a non persistent line from package gp.
  Standard_EXPORT GCE2d_MakeLine(const gp_Lin2d& L);

  //! P is the origin and V is the direction of the line.
  Standard_EXPORT GCE2d_MakeLine(const gp_Pnt2d& P, const gp_Dir2d& V);

  //! Make a Line from Geom2d <TheLin> parallel to another
  //! Lin <Lin> and passing through a Pnt <Point>.
  Standard_EXPORT GCE2d_MakeLine(const gp_Lin2d& Lin, const gp_Pnt2d& Point);

  //! Make a Line from Geom2d <TheLin> parallel to another
  //! Lin <Lin> at a distance <Dist>.
  Standard_EXPORT GCE2d_MakeLine(const gp_Lin2d& Lin, const double Dist);

  //! Make a Line from Geom2d <TheLin> passing through 2
  //! Pnt <P1>,<P2>.
  //! It returns false if <p1> and <P2> are confused.
  //! Warning
  //! If points P1 and P2 coincident (that is, when IsDone
  //! returns false), the Status function returns gce_ConfusedPoints.
  Standard_EXPORT GCE2d_MakeLine(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  //! Returns the constructed line.
  //! Exceptions StdFail_NotDone if no line is constructed.
  Standard_EXPORT const occ::handle<Geom2d_Line>& Value() const;

  operator const occ::handle<Geom2d_Line>&() const { return Value(); }

private:
  occ::handle<Geom2d_Line> TheLine;
};
