#pragma once

#include <IMeshData_Types.hpp>
#include <NCollection_Handle.hpp>

#include <memory>

class gp_Pnt2d;
class CSLib_Class2d;

class BRepMesh_Classifier : public Standard_Transient
{
public:
  Standard_EXPORT BRepMesh_Classifier();

  Standard_EXPORT ~BRepMesh_Classifier() override;

  Standard_EXPORT TopAbs_State Perform(const gp_Pnt2d& thePoint) const;

  Standard_EXPORT void RegisterWire(const NCollection_Sequence<const gp_Pnt2d*>& theWire,
                                    const std::pair<double, double>&             theTolUV,
                                    const std::pair<double, double>&             theRangeU,
                                    const std::pair<double, double>&             theRangeV);

  DEFINE_STANDARD_RTTIEXT(BRepMesh_Classifier, Standard_Transient)

private:
  NCollection_Vector<NCollection_Handle<CSLib_Class2d>> myTabClass;
  IMeshData::VectorOfBoolean                            myTabOrient;
};
