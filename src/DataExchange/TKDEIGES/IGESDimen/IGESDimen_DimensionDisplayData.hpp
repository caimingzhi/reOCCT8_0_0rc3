#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESDimen_DimensionDisplayData : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_DimensionDisplayData();

  Standard_EXPORT void Init(const int                                    numProps,
                            const int                                    aDimType,
                            const int                                    aLabelPos,
                            const int                                    aCharSet,
                            const occ::handle<TCollection_HAsciiString>& aString,
                            const int                                    aSymbol,
                            const double                                 anAng,
                            const int                                    anAlign,
                            const int                                    aLevel,
                            const int                                    aPlace,
                            const int                                    anOrient,
                            const double                                 initVal,
                            const occ::handle<NCollection_HArray1<int>>& notes,
                            const occ::handle<NCollection_HArray1<int>>& startInd,
                            const occ::handle<NCollection_HArray1<int>>& endInd);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int DimensionType() const;

  Standard_EXPORT int LabelPosition() const;

  Standard_EXPORT int CharacterSet() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> LString() const;

  Standard_EXPORT int DecimalSymbol() const;

  Standard_EXPORT double WitnessLineAngle() const;

  Standard_EXPORT int TextAlignment() const;

  Standard_EXPORT int TextLevel() const;

  Standard_EXPORT int TextPlacement() const;

  Standard_EXPORT int ArrowHeadOrientation() const;

  Standard_EXPORT double InitialValue() const;

  Standard_EXPORT int NbSupplementaryNotes() const;

  Standard_EXPORT int SupplementaryNote(const int Index) const;

  Standard_EXPORT int StartIndex(const int Index) const;

  Standard_EXPORT int EndIndex(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_DimensionDisplayData, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  int                                   theDimensionType;
  int                                   theLabelPosition;
  int                                   theCharacterSet;
  occ::handle<TCollection_HAsciiString> theLString;
  int                                   theDecimalSymbol;
  double                                theWitnessLineAngle;
  int                                   theTextAlignment;
  int                                   theTextLevel;
  int                                   theTextPlacement;
  int                                   theArrowHeadOrientation;
  double                                theInitialValue;
  occ::handle<NCollection_HArray1<int>> theSupplementaryNotes;
  occ::handle<NCollection_HArray1<int>> theStartIndex;
  occ::handle<NCollection_HArray1<int>> theEndIndex;
};
