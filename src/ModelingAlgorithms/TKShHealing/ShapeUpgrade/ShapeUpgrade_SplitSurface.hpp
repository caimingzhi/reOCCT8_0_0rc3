#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <ShapeExtend_Status.hpp>
class Geom_Surface;
class ShapeExtend_CompositeSurface;

#ifdef Status
  #undef Status
#endif

class ShapeUpgrade_SplitSurface : public Standard_Transient
{

public:
  Standard_EXPORT ShapeUpgrade_SplitSurface();

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& S);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& S,
                            const double                     UFirst,
                            const double                     ULast,
                            const double                     VFirst,
                            const double                     VLast,
                            const double                     theArea = 0.);

  Standard_EXPORT void SetUSplitValues(const occ::handle<NCollection_HSequence<double>>& UValues);

  Standard_EXPORT void SetVSplitValues(const occ::handle<NCollection_HSequence<double>>& VValues);

  Standard_EXPORT virtual void Build(const bool Segment);

  Standard_EXPORT virtual void Compute(const bool Segment = true);

  Standard_EXPORT void Perform(const bool Segment = true);

  Standard_EXPORT const occ::handle<NCollection_HSequence<double>>& USplitValues() const;

  Standard_EXPORT const occ::handle<NCollection_HSequence<double>>& VSplitValues() const;

  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  Standard_EXPORT const occ::handle<ShapeExtend_CompositeSurface>& ResSurfaces() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitSurface, Standard_Transient)

protected:
  occ::handle<NCollection_HSequence<double>> myUSplitValues;
  occ::handle<NCollection_HSequence<double>> myVSplitValues;
  int                                        myNbResultingRow;
  int                                        myNbResultingCol;
  occ::handle<Geom_Surface>                  mySurface;
  int                                        myStatus;
  occ::handle<ShapeExtend_CompositeSurface>  myResSurfaces;
  double                                     myArea;
  double                                     myUsize;
  double                                     myVsize;
};
