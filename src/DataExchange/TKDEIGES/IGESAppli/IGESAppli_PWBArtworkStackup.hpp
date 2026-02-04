#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines PWBArtworkStackup, Type <406> Form <25>
//! in package IGESAppli
//! Used to communicate which exchange file levels are to
//! be combined in order to create the artwork for a
//! printed wire board (PWB). This property should be
//! attached to the entity defining the printed wire
//! assembly (PWA) or if no such entity exists, then the
//! property should stand alone in the file.
class IGESAppli_PWBArtworkStackup : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_PWBArtworkStackup();

  //! This method is used to set the fields of the class
  //! PWBArtworkStackup
  //! - nbPropVal    : number of property values
  //! - anArtIdent   : Artwork Stackup Identification
  //! - allLevelNums : Level Numbers
  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const occ::handle<TCollection_HAsciiString>& anArtIdent,
                            const occ::handle<NCollection_HArray1<int>>& allLevelNums);

  //! returns number of property values
  Standard_EXPORT int NbPropertyValues() const;

  //! returns Artwork Stackup Identification
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Identification() const;

  //! returns total number of Level Numbers
  Standard_EXPORT int NbLevelNumbers() const;

  //! returns Level Number
  //! raises exception if Index <= 0 or Index > NbLevelNumbers
  Standard_EXPORT int LevelNumber(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_PWBArtworkStackup, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<TCollection_HAsciiString> theArtworkStackupIdent;
  occ::handle<NCollection_HArray1<int>> theLevelNumbers;
};

