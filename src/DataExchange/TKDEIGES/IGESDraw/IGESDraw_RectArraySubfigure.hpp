#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

class IGESDraw_RectArraySubfigure : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDraw_RectArraySubfigure();

  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>&      aBase,
                            const double                                 aScale,
                            const gp_XYZ&                                aCorner,
                            const int                                    nbCols,
                            const int                                    nbRows,
                            const double                                 hDisp,
                            const double                                 vtDisp,
                            const double                                 rotationAngle,
                            const int                                    doDont,
                            const occ::handle<NCollection_HArray1<int>>& allNumPos);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> BaseEntity() const;

  Standard_EXPORT double ScaleFactor() const;

  Standard_EXPORT gp_Pnt LowerLeftCorner() const;

  Standard_EXPORT gp_Pnt TransformedLowerLeftCorner() const;

  Standard_EXPORT int NbColumns() const;

  Standard_EXPORT int NbRows() const;

  Standard_EXPORT double ColumnSeparation() const;

  Standard_EXPORT double RowSeparation() const;

  Standard_EXPORT double RotationAngle() const;

  Standard_EXPORT bool DisplayFlag() const;

  Standard_EXPORT int ListCount() const;

  Standard_EXPORT bool DoDontFlag() const;

  Standard_EXPORT bool PositionNum(const int Index) const;

  Standard_EXPORT int ListPosition(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_RectArraySubfigure, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity>      theBaseEntity;
  double                                theScaleFactor;
  gp_XYZ                                theLowerLeftCorner;
  int                                   theNbColumns;
  int                                   theNbRows;
  double                                theColumnSeparation;
  double                                theRowSeparation;
  double                                theRotationAngle;
  bool                                  theDoDontFlag;
  occ::handle<NCollection_HArray1<int>> thePositions;
};
