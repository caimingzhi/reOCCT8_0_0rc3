#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Ax3.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_Shape.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Boolean.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_List.hpp>

#include <NCollection_HArray1.hpp>
class gp_Ax1;
class gp_Pnt;
class TopoDS_Wire;
class TopoDS_Edge;

//! Implementation of building helix wire
//! Values of Error Status returned by algo:
//! 0 - OK
//! 1 - object is just initialized, it means that no input parameters were set
//! 2 - approximation fails
//!
//! 10 - R < tolerance - starting point is too close to axis
//! 11 - step (Pitch) < tolerance
//! 12 - Height < tolerance
//! 13 - TaperAngle < 0 or TaperAngle > Pi/2 - TolAng
//! Warning Status:
//! 0 - OK
//! 1 - tolerance reached by approximation > requested tolerance.
class HelixBRep_BuilderHelix
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT HelixBRep_BuilderHelix();
  Standard_EXPORT virtual ~HelixBRep_BuilderHelix();

  //! Sets parameters of general composite helix
  Standard_EXPORT void SetParameters(const gp_Ax3&                     theAxis,
                                     const NCollection_Array1<double>& theDiams,
                                     const NCollection_Array1<double>& theHeights,
                                     const NCollection_Array1<double>& thePitches,
                                     const NCollection_Array1<bool>&   theIsPitches);

  //! Sets parameters of pure helix
  Standard_EXPORT void SetParameters(const gp_Ax3&                     theAxis,
                                     const double                      theDiam,
                                     const NCollection_Array1<double>& theHeights,
                                     const NCollection_Array1<double>& thePitches,
                                     const NCollection_Array1<bool>&   theIsPitches);

  //! Sets parameters of pure spiral
  Standard_EXPORT void SetParameters(const gp_Ax3&                     theAxis,
                                     const double                      theDiam1,
                                     const double                      theDiam2,
                                     const NCollection_Array1<double>& theHeights,
                                     const NCollection_Array1<double>& thePitches,
                                     const NCollection_Array1<bool>&   theIsPitches);

  //! Sets parameters of general composite helix
  Standard_EXPORT void SetParameters(const gp_Ax3&                     theAxis,
                                     const NCollection_Array1<double>& theDiams,
                                     const NCollection_Array1<double>& thePitches,
                                     const NCollection_Array1<double>& theNbTurns);

  //! Sets parameters of pure helix
  Standard_EXPORT void SetParameters(const gp_Ax3&                     theAxis,
                                     const double                      theDiam,
                                     const NCollection_Array1<double>& thePitches,
                                     const NCollection_Array1<double>& theNbTurns);

  //! Sets parameters of pure spiral
  Standard_EXPORT void SetParameters(const gp_Ax3&                     theAxis,
                                     const double                      theDiam1,
                                     const double                      theDiam2,
                                     const NCollection_Array1<double>& thePitches,
                                     const NCollection_Array1<double>& theNbTurns);

  //! Sets parameters for approximation
  Standard_EXPORT void SetApproxParameters(const double        theTolerance,
                                           const int           theMaxDegree,
                                           const GeomAbs_Shape theContinuity);

  //! Performs calculations
  Standard_EXPORT void Perform();

  //! Gets tolerance reached by approximation
  Standard_EXPORT double ToleranceReached() const;

  //! Returns error status of algorithm
  Standard_EXPORT int ErrorStatus() const;

  //! Returns warning status of algorithm
  Standard_EXPORT int WarningStatus() const;

  //! Gets result of algorithm
  Standard_EXPORT const TopoDS_Shape& Shape() const;

protected:
  gp_Ax3                                   myAxis3;
  occ::handle<NCollection_HArray1<double>> myDiams;
  occ::handle<NCollection_HArray1<double>> myHeights;
  occ::handle<NCollection_HArray1<double>> myPitches;
  occ::handle<NCollection_HArray1<bool>>   myIsPitches;
  double                                   myTolerance;
  double                                   myTolReached;
  GeomAbs_Shape                            myContinuity;
  int                                      myMaxDegree;
  int                                      myMaxSegments;
  int                                      myErrorStatus;
  int                                      myWarningStatus;
  TopoDS_Shape                             myShape;

private:
  Standard_EXPORT void BuildPart(const gp_Ax1& theAxis,
                                 const gp_Pnt& thePStart,
                                 const double  theHeight,
                                 const double  thePitch,
                                 const double  theTaperAngle,
                                 const bool    theIsClockwise,
                                 TopoDS_Wire&  thePart);

  Standard_EXPORT void Smoothing(NCollection_List<TopoDS_Shape>& theParts);

  Standard_EXPORT void SmoothingEdges(TopoDS_Edge& thePrev, TopoDS_Edge& theNext);

  int myNParts;
};

