#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Elips.hpp>
#include <gce_Root.hpp>
class gp_Ax2;
class gp_Pnt;

//! This class implements the following algorithms used to
//! create an ellipse from gp.
//!
//! * Create an ellipse from its center, and two points:
//! one on the ciconference giving the major radius, the
//! other giving the value of the small radius.
class gce_MakeElips : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! The major radius of the ellipse is on the "XAxis" and the
  //! minor radius is on the "YAxis" of the ellipse. The "XAxis"
  //! is defined with the "XDirection" of A2 and the "YAxis" is
  //! defined with the "YDirection" of A2.
  //! Warnings :
  //! It is not forbidden to create an ellipse with
  //! MajorRadius = MinorRadius.
  Standard_EXPORT gce_MakeElips(const gp_Ax2& A2,
                                const double  MajorRadius,
                                const double  MinorRadius);

  //! Make an ellipse with its center and two points.
  //! Warning
  //! The MakeElips class does not prevent the
  //! construction of an ellipse where the MajorRadius is
  //! equal to the MinorRadius.
  //! If an error occurs (that is, when IsDone returns
  //! false), the Status function returns:
  //! -   gce_InvertRadius if MajorRadius is less than MinorRadius;
  //! -   gce_NegativeRadius if MinorRadius is less than 0.0;
  //! -   gce_NullAxis if the points S1 and Center are coincident; or
  //! -   gce_InvertAxis if:
  //! -   the major radius computed with Center and S1
  //! is less than the minor radius computed with Center, S1 and S2, or
  //! -   Center, S1 and S2 are collinear.
  Standard_EXPORT gce_MakeElips(const gp_Pnt& S1, const gp_Pnt& S2, const gp_Pnt& Center);

  //! Returns the constructed ellipse.
  //! Exceptions StdFail_NotDone if no ellipse is constructed.
  Standard_EXPORT const gp_Elips& Value() const;

  Standard_EXPORT const gp_Elips& Operator() const;
  Standard_EXPORT                 operator gp_Elips() const;

private:
  gp_Elips TheElips;
};

