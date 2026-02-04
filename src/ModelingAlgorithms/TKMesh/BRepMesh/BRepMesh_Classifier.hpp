#pragma once


#include <IMeshData_Types.hpp>
#include <NCollection_Handle.hpp>

#include <memory>

class gp_Pnt2d;
class CSLib_Class2d;

//! Auxiliary class intended for classification of points
//! regarding internals of discrete face.
class BRepMesh_Classifier : public Standard_Transient
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_Classifier();

  //! Destructor.
  Standard_EXPORT ~BRepMesh_Classifier() override;

  //! Performs classification of the given point regarding to face internals.
  //! @param thePoint Point in parametric space to be classified.
  //! @return TopAbs_IN if point lies within face boundaries and TopAbs_OUT elsewhere.
  Standard_EXPORT TopAbs_State Perform(const gp_Pnt2d& thePoint) const;

  //! Registers wire specified by sequence of points for
  //! further classification of points.
  //! @param theWire Wire to be registered. Specified by sequence of points.
  //! @param theTolUV Tolerance to be used for calculations in parametric space.
  //! @param theUmin Lower U boundary of the face in parametric space.
  //! @param theUmax Upper U boundary of the face in parametric space.
  //! @param theVmin Lower V boundary of the face in parametric space.
  //! @param theVmax Upper V boundary of the face in parametric space.
  Standard_EXPORT void RegisterWire(const NCollection_Sequence<const gp_Pnt2d*>& theWire,
                                    const std::pair<double, double>&             theTolUV,
                                    const std::pair<double, double>&             theRangeU,
                                    const std::pair<double, double>&             theRangeV);

  DEFINE_STANDARD_RTTIEXT(BRepMesh_Classifier, Standard_Transient)

private:
  NCollection_Vector<NCollection_Handle<CSLib_Class2d>> myTabClass;
  IMeshData::VectorOfBoolean                            myTabOrient;
};

