#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_XYZ.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <gp_Trsf.hpp>
#include <Standard_Integer.hpp>
class gp_XY;
class gp_XYZ;
class IGESGeom_CopiousData;
class gp_Ax3;
class gp_Ax2;
class gp_Ax1;
class IGESGeom_TransformationMatrix;

class IGESConvGeom_GeomBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESConvGeom_GeomBuilder();

  Standard_EXPORT void Clear();

  Standard_EXPORT void AddXY(const gp_XY& val);

  Standard_EXPORT void AddXYZ(const gp_XYZ& val);

  Standard_EXPORT void AddVec(const gp_XYZ& val);

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT gp_XYZ Point(const int num) const;

  Standard_EXPORT occ::handle<IGESGeom_CopiousData> MakeCopiousData(
    const int  datatype,
    const bool polyline = false) const;

  Standard_EXPORT gp_Trsf Position() const;

  Standard_EXPORT void SetPosition(const gp_Trsf& pos);

  Standard_EXPORT void SetPosition(const gp_Ax3& pos);

  Standard_EXPORT void SetPosition(const gp_Ax2& pos);

  Standard_EXPORT void SetPosition(const gp_Ax1& pos);

  Standard_EXPORT bool IsIdentity() const;

  Standard_EXPORT bool IsTranslation() const;

  Standard_EXPORT bool IsZOnly() const;

  Standard_EXPORT void EvalXYZ(const gp_XYZ& val, double& X, double& Y, double& Z) const;

  Standard_EXPORT occ::handle<IGESGeom_TransformationMatrix> MakeTransformation(
    const double unit = 1) const;

private:
  occ::handle<NCollection_HSequence<gp_XYZ>> theXYZ;
  occ::handle<NCollection_HSequence<gp_XYZ>> theVec;
  gp_Trsf                                    thepos;
};
