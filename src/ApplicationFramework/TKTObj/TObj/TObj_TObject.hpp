#pragma once

#include <TObj_Object.hpp>

#include <TDF_Attribute.hpp>

class Standard_GUID;
class TDF_Label;

/**
 * Purpose: OCAF Attribute to storing objects (interfaces) of OCAF-based
 * modelers in the OCAF tree.
 * The persistency mechanism of the TObj_TObject allows to save
 * and restore objects of various subtypes without recompilation of the schema
 */

class TObj_TObject : public TDF_Attribute
{
public:
  //! Standard methods of OCAF attribute

  //! Empty constructor
  Standard_EXPORT TObj_TObject();

  //! This method is used in implementation of ID()
  static Standard_EXPORT const Standard_GUID& GetID();

  //! Returns the ID of TObj_TObject attribute.
  Standard_EXPORT const Standard_GUID& ID() const override;

public:
  //! Method for create TObj_TObject object

  //! Creates TObj_TObject attribute on given label
  static Standard_EXPORT occ::handle<TObj_TObject> Set(const TDF_Label&                theLabel,
                                                       const occ::handle<TObj_Object>& theElem);

public:
  //! Methods for setting and obtaining TObj_Object

  //! Sets the TObj_Object object
  Standard_EXPORT void Set(const occ::handle<TObj_Object>& theElem);

  //! Returns the TObj_Object object
  Standard_EXPORT occ::handle<TObj_Object> Get() const;

public:
  //! Redefined OCAF abstract methods

  //! Returns an new empty TObj_TObject attribute. It is used by the
  //! copy algorithm.
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  //! Restores the backuped contents from <theWith> into this one. It is used
  //! when aborting a transaction.
  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  //! This method is used when copying an attribute from a source structure
  //! into a target structure.
  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

  //! Tell TObj_Object to die,
  //! i.e. (myElem->IsAlive() == false) after that
  Standard_EXPORT void BeforeForget() override;

  //! Tell TObj_Object to rise from the dead,
  //! i.e. (myElem->IsAlive() == true) after that
  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                 const bool                             forceIt) override;

private:
  //! Fields
  occ::handle<TObj_Object> myElem; //!< The object interface stored by the attribute

public:
  //! CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(TObj_TObject, TDF_Attribute)
};

//! Define handle class for TObj_TObject

#ifdef _MSC_VER
  #pragma once
#endif
