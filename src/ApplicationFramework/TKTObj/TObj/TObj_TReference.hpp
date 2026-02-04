#pragma once


#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>

class TObj_Object;
class Standard_GUID;

/**
 * Attribute for storing references to the objects which implement
 * TObj_Object interface in the OCAF tree.
 * Its persistency mechanism provides transparent method for storing
 * cross-model references.
 * Each reference, when created, registers itself in the referred object,
 * to support back references
 */

class TObj_TReference : public TDF_Attribute
{
public:
  //! Standard methods of OCAF attribute

  //! Empty constructor
  Standard_EXPORT TObj_TReference();

  //! This method is used in implementation of ID()
  static Standard_EXPORT const Standard_GUID& GetID();

  //! Returns the ID of TObj_TReference attribute.
  Standard_EXPORT const Standard_GUID& ID() const override;

public:
  //! Method for create TObj_TReference object

  //! Creates reference on TDF_Label <theLabel> to the object <theObject> and
  //! creates backreference from the object <theObject> to <theMaster> one.
  static Standard_EXPORT occ::handle<TObj_TReference> Set(
    const TDF_Label&                theLabel,
    const occ::handle<TObj_Object>& theObject,
    const occ::handle<TObj_Object>& theMaster);

public:
  //! Methods for setting and obtaining referenced object

  //! Sets the reference to the theObject
  Standard_EXPORT void Set(const occ::handle<TObj_Object>& theObject,
                           const TDF_Label&                theMasterLabel);

  //! Sets the reference to the theObject at indicated Label.
  //! It is method for persistent only. Don`t use anywhere else.
  Standard_EXPORT void Set(const TDF_Label& theLabel, const TDF_Label& theMasterLabel);

  //! Returns the referenced theObject
  Standard_EXPORT occ::handle<TObj_Object> Get() const;

  //! Returns the Label of master object.
  TDF_Label GetMasterLabel() const { return myMasterLabel; }

  //! Returns the referred label.
  TDF_Label GetLabel() const { return myLabel; }

public:
  //! Redefined OCAF abstract methods

  //! Returns an new empty TObj_TReference attribute. It is used by the
  //! copy algorithm.
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  //! Restores the backuped contents from <theWith> into this one. It is used
  //! when aborting a transaction.
  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  //! This method is used when copying an attribute from a source structure
  //! into a target structure.
  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

  //! Remove back references of it reference if it is in other document.
  Standard_EXPORT void BeforeForget() override;

  //! It is necessary for tranzaction mechanism (Undo/Redo).
  Standard_EXPORT bool BeforeUndo(const occ::handle<TDF_AttributeDelta>& theDelta,
                                  const bool                             isForced = false) override;

  //! It is necessary for tranzaction mechanism (Undo/Redo).
  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& theDelta,
                                 const bool                             isForced = false) override;

  //! Check if back reference exists for reference.
  Standard_EXPORT void AfterResume() override;

  //! Called after retrieval reference from file.
  Standard_EXPORT bool AfterRetrieval(const bool forceIt = false) override;

private:
  //! Fields
  TDF_Label myLabel;       //!< Label that indicate referenced object
  TDF_Label myMasterLabel; //!< Label of object that have this reference.

public:
  //! CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(TObj_TReference, TDF_Attribute)
};

//! Define handle class for TObj_TReference

#ifdef _MSC_VER
#pragma once
#endif
