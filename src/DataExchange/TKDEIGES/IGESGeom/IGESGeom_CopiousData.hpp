#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class gp_Vec;

class IGESGeom_CopiousData : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_CopiousData();

  Standard_EXPORT void Init(const int                                       aDataType,
                            const double                                    aZPlane,
                            const occ::handle<NCollection_HArray1<double>>& allData);

  Standard_EXPORT void SetPolyline(const bool mode);

  Standard_EXPORT void SetClosedPath2D();

  Standard_EXPORT bool IsPointSet() const;

  Standard_EXPORT bool IsPolyline() const;

  Standard_EXPORT bool IsClosedPath2D() const;

  Standard_EXPORT int DataType() const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT double Data(const int NumPoint, const int NumData) const;

  Standard_EXPORT double ZPlane() const;

  Standard_EXPORT gp_Pnt Point(const int anIndex) const;

  Standard_EXPORT gp_Pnt TransformedPoint(const int anIndex) const;

  Standard_EXPORT gp_Vec Vector(const int anIndex) const;

  Standard_EXPORT gp_Vec TransformedVector(const int anIndex) const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_CopiousData, IGESData_IGESEntity)

private:
  int                                      theDataType;
  double                                   theZPlane;
  occ::handle<NCollection_HArray1<double>> theData;
};
