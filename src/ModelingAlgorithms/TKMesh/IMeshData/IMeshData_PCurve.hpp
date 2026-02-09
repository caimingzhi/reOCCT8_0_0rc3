#pragma once

#include <IMeshData_ParametersList.hpp>
#include <Standard_Type.hpp>
#include <IMeshData_Face.hpp>

class gp_Pnt2d;

class IMeshData_PCurve : public IMeshData_ParametersList
{
public:
  ~IMeshData_PCurve() override = default;

  Standard_EXPORT virtual void InsertPoint(const int       thePosition,
                                           const gp_Pnt2d& thePoint,
                                           const double    theParamOnPCurve) = 0;

  Standard_EXPORT virtual void AddPoint(const gp_Pnt2d& thePoint,
                                        const double    theParamOnPCurve) = 0;

  Standard_EXPORT virtual gp_Pnt2d& GetPoint(const int theIndex) = 0;

  Standard_EXPORT virtual int& GetIndex(const int theIndex) = 0;

  Standard_EXPORT virtual void RemovePoint(const int theIndex) = 0;

  bool IsForward() const { return (myOrientation != TopAbs_REVERSED); }

  bool IsInternal() const { return (myOrientation == TopAbs_INTERNAL); }

  TopAbs_Orientation GetOrientation() const { return myOrientation; }

  const IMeshData::IFacePtr& GetFace() const { return myDFace; }

  DEFINE_STANDARD_RTTIEXT(IMeshData_PCurve, IMeshData_ParametersList)

protected:
  IMeshData_PCurve(const IMeshData::IFacePtr& theDFace, const TopAbs_Orientation theOrientation)
      : myDFace(theDFace),
        myOrientation(theOrientation)
  {
  }

private:
  IMeshData::IFacePtr myDFace;
  TopAbs_Orientation  myOrientation;
};
