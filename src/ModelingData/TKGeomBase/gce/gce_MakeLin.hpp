#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Lin.hpp>
#include <gce_Root.hpp>
class gp_Ax1;
class gp_Pnt;
class gp_Dir;

//! This class implements the following algorithms used
//! to create a Lin from gp.
//! * Create a Lin parallel to another and passing
//! through a point.
//! * Create a Lin passing through 2 points.
//! * Create a lin from its axis (Ax1 from gp).
//! * Create a lin from a point and a direction.
class gce_MakeLin : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a line located along the axis A1.
  Standard_EXPORT gce_MakeLin(const gp_Ax1& A1);

  //! <P> is the location point (origin) of the line and
  //! <V> is the direction of the line.
  Standard_EXPORT gce_MakeLin(const gp_Pnt& P, const gp_Dir& V);

  //! Make a Lin from gp <TheLin> parallel to another
  //! Lin <Lin> and passing through a Pnt <Point>.
  Standard_EXPORT gce_MakeLin(const gp_Lin& Lin, const gp_Pnt& Point);

  //! Make a Lin from gp <TheLin> passing through 2
  //! Pnt <P1>,<P2>.
  //! It returns false if <p1> and <P2> are confused.
  Standard_EXPORT gce_MakeLin(const gp_Pnt& P1, const gp_Pnt& P2);

  //! Returns the constructed line.
  //! Exceptions StdFail_NotDone is raised if no line is constructed.
  Standard_EXPORT const gp_Lin& Value() const;

  Standard_EXPORT const gp_Lin& Operator() const;
  Standard_EXPORT               operator gp_Lin() const;

private:
  gp_Lin TheLin;
};

