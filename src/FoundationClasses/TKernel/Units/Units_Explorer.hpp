#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Units_Quantity.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Units_Unit.hpp>
class Units_UnitsSystem;
class Units_UnitsDictionary;
class TCollection_AsciiString;

//! This class provides all the services to explore
//! UnitsSystem or UnitsDictionary.
class Units_Explorer
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor of the class.
  Standard_EXPORT Units_Explorer();

  //! Creates a new instance of the class, initialized with
  //! the UnitsSystem <aunitssystem>.
  Standard_EXPORT Units_Explorer(const occ::handle<Units_UnitsSystem>& aunitssystem);

  //! Creates a new instance of the class, initialized with
  //! the UnitsDictionary <aunitsdictionary>.
  Standard_EXPORT Units_Explorer(const occ::handle<Units_UnitsDictionary>& aunitsdictionary);

  //! Creates a new instance of the class, initialized with
  //! the UnitsSystem <aunitssystem> and positioned at the
  //! quantity <aquantity>.
  Standard_EXPORT Units_Explorer(const occ::handle<Units_UnitsSystem>& aunitssystem,
                                 const char*                           aquantity);

  //! Creates a new instance of the class, initialized with
  //! the UnitsDictionary <aunitsdictionary> and positioned
  //! at the quantity <aquantity>.
  Standard_EXPORT Units_Explorer(const occ::handle<Units_UnitsDictionary>& aunitsdictionary,
                                 const char*                               aquantity);

  //! Initializes the instance of the class with the
  //! UnitsSystem <aunitssystem>.
  Standard_EXPORT void Init(const occ::handle<Units_UnitsSystem>& aunitssystem);

  //! Initializes the instance of the class with the
  //! UnitsDictionary <aunitsdictionary>.
  Standard_EXPORT void Init(const occ::handle<Units_UnitsDictionary>& aunitsdictionary);

  //! Initializes the instance of the class with the
  //! UnitsSystem <aunitssystem> and positioned at the
  //! quantity <aquantity>.
  Standard_EXPORT void Init(const occ::handle<Units_UnitsSystem>& aunitssystem,
                            const char*                           aquantity);

  //! Initializes the instance of the class with the
  //! UnitsDictionary <aunitsdictionary> and positioned at
  //! the quantity <aquantity>.
  Standard_EXPORT void Init(const occ::handle<Units_UnitsDictionary>& aunitsdictionary,
                            const char*                               aquantity);

  //! Returns True if there is another Quantity to explore,
  //! False otherwise.
  Standard_EXPORT bool MoreQuantity() const;

  //! Sets the next Quantity current.
  Standard_EXPORT void NextQuantity();

  //! Returns the name of the current Quantity.
  Standard_EXPORT TCollection_AsciiString Quantity() const;

  //! Returns True if there is another Unit to explore,
  //! False otherwise.
  Standard_EXPORT bool MoreUnit() const;

  //! Sets the next Unit current.
  Standard_EXPORT void NextUnit();
  //! Returns the name of the current unit.
  Standard_EXPORT TCollection_AsciiString Unit() const;

  //! If the units system to explore is a user system,
  //! returns True if the current unit is active, False
  //! otherwise.
  //!
  //! If the units system to explore is the units
  //! dictionary, returns True if the current unit is the
  //! S.I. unit.
  Standard_EXPORT bool IsActive() const;

private:
  int                                                             thecurrentquantity{};
  occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>> thequantitiessequence;
  int                                                             thecurrentunit{};
  occ::handle<NCollection_HSequence<occ::handle<Units_Unit>>>     theunitssequence;
  occ::handle<NCollection_HSequence<int>>                         theactiveunitssequence;
};
