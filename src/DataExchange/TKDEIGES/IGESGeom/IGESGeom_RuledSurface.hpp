#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

//! defines IGESRuledSurface, Type <118> Form <0-1>
//! in package IGESGeom
//! A ruled surface is formed by moving a line connecting points
//! of equal relative arc length or equal relative parametric
//! value on two parametric curves from a start point to a
//! terminate point on the curves. The parametric curves may be
//! points, lines, circles, conics, rational B-splines,
//! parametric splines or any parametric curve defined in
//! the IGES specification.
class IGESGeom_RuledSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_RuledSurface();

  //! This method is used to set the fields of the class
  //! RuledSurface
  //! - aCurve       : First parametric curve
  //! - anotherCurve : Second parametric curve
  //! - aDirFlag     : Direction Flag
  //! 0 = Join first to first, last to last
  //! 1 = Join first to last, last to first
  //! - aDevFlag     : Developable Surface Flag
  //! 1 = Developable
  //! 0 = Possibly not
  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>& aCurve,
                            const occ::handle<IGESData_IGESEntity>& anotherCurve,
                            const int                               aDirFlag,
                            const int                               aDevFlag);

  //! Sets <me> to be Ruled by Parameter (Form 1) if <mode> is
  //! True, or Ruled by Length (Form 0) else
  Standard_EXPORT void SetRuledByParameter(const bool mode);

  //! Returns True if Form is 1
  Standard_EXPORT bool IsRuledByParameter() const;

  //! returns the first curve
  Standard_EXPORT occ::handle<IGESData_IGESEntity> FirstCurve() const;

  //! returns the second curve
  Standard_EXPORT occ::handle<IGESData_IGESEntity> SecondCurve() const;

  //! return the sense of direction
  //! 0 = Join first to first, last to last
  //! 1 = Join first to last, last to first
  Standard_EXPORT int DirectionFlag() const;

  //! returns True if developable else False
  Standard_EXPORT bool IsDevelopable() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_RuledSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity> theCurve1;
  occ::handle<IGESData_IGESEntity> theCurve2;
  int                              theDirFlag;
  int                              theDevFlag;
};

