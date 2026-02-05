#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_HAsciiString.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines LevelToPWBLayerMap, Type <406> Form <24>
//! in package IGESAppli
//! Used to correlate an exchange file level number with
//! its corresponding native level identifier, physical PWB
//! layer number and predefined functional level
//! identification
class IGESAppli_LevelToPWBLayerMap : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_LevelToPWBLayerMap();

  //! This method is used to set the fields of the class
  //! LevelToPWBLayerMap
  //! - nbPropVal       : Number of property values
  //! - allExchLevels   : Exchange File Level Numbers
  //! - allNativeLevels : Native Level Identifications
  //! - allPhysLevels   : Physical Layer Numbers
  //! - allExchIdents   : Exchange File Level Identifications
  //! raises exception if allExchLevels, allNativeLevels, allPhysLevels
  //! and all ExchIdents are not of same dimensions
  Standard_EXPORT void Init(
    const int                                                                      nbPropVal,
    const occ::handle<NCollection_HArray1<int>>&                                   allExchLevels,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& allNativeLevels,
    const occ::handle<NCollection_HArray1<int>>&                                   allPhysLevels,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& allExchIdents);

  //! returns number of property values
  Standard_EXPORT int NbPropertyValues() const;

  //! returns number of level to layer definitions
  Standard_EXPORT int NbLevelToLayerDefs() const;

  //! returns Exchange File Level Number
  //! raises exception if Index <= 0 or Index > NbLevelToLayerDefs
  Standard_EXPORT int ExchangeFileLevelNumber(const int Index) const;

  //! returns Native Level Identification
  //! raises exception if Index <= 0 or Index > NbLevelToLayerDefs
  Standard_EXPORT occ::handle<TCollection_HAsciiString> NativeLevel(const int Index) const;

  //! returns Physical Layer Number
  //! raises exception if Index <= 0 or Index > NbLevelToLayerDefs
  Standard_EXPORT int PhysicalLayerNumber(const int Index) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ExchangeFileLevelIdent(
    const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_LevelToPWBLayerMap, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<NCollection_HArray1<int>> theExchangeFileLevelNumber;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theNativeLevel;
  occ::handle<NCollection_HArray1<int>>                                   thePhysicalLayerNumber;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theExchangeFileLevelIdent;
};
