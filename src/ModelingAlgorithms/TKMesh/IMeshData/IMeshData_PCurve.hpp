#pragma once

#include <IMeshData_ParametersList.hpp>
#include <Standard_Type.hpp>
#include <IMeshData_Face.hpp>

class gp_Pnt2d;

//! Interface class representing pcurve of edge associated with discrete face.
//! Indexation of points starts from zero.
class IMeshData_PCurve : public IMeshData_ParametersList
{
public:
  //! Destructor.
  ~IMeshData_PCurve() override = default;

  //! Inserts new discretization point at the given position.
  Standard_EXPORT virtual void InsertPoint(const int       thePosition,
                                           const gp_Pnt2d& thePoint,
                                           const double    theParamOnPCurve) = 0;

  //! Adds new discretization point to pcurve.
  Standard_EXPORT virtual void AddPoint(const gp_Pnt2d& thePoint,
                                        const double    theParamOnPCurve) = 0;

  //! Returns discretization point with the given index.
  Standard_EXPORT virtual gp_Pnt2d& GetPoint(const int theIndex) = 0;

  //! Returns index in mesh corresponded to discretization point with the given index.
  Standard_EXPORT virtual int& GetIndex(const int theIndex) = 0;

  //! Removes point with the given index.
  Standard_EXPORT virtual void RemovePoint(const int theIndex) = 0;

  //! Returns forward flag of this pcurve.
  bool IsForward() const { return (myOrientation != TopAbs_REVERSED); }

  //! Returns internal flag of this pcurve.
  bool IsInternal() const { return (myOrientation == TopAbs_INTERNAL); }

  //! Returns orientation of the edge associated with current pcurve.
  TopAbs_Orientation GetOrientation() const { return myOrientation; }

  //! Returns discrete face pcurve is associated to.
  const IMeshData::IFacePtr& GetFace() const { return myDFace; }

  DEFINE_STANDARD_RTTIEXT(IMeshData_PCurve, IMeshData_ParametersList)

protected:
  //! Constructor.
  IMeshData_PCurve(const IMeshData::IFacePtr& theDFace, const TopAbs_Orientation theOrientation)
      : myDFace(theDFace),
        myOrientation(theOrientation)
  {
  }

private:
  IMeshData::IFacePtr myDFace;
  TopAbs_Orientation  myOrientation;
};
