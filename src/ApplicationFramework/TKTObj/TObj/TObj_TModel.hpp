#pragma once

#include <TDF_Attribute.hpp>

class TObj_Model;

/**
 * Attribute to store OCAF-based models in OCAF tree
 * The persistency mechanism of the TObj_TModel allows to save
 * and restore various types of models without recompilation of the schema
 */

class TObj_TModel : public TDF_Attribute
{
public:
  /**
   * Standard methods of attribute
   */

  //! Empty constructor
  Standard_EXPORT TObj_TModel();

  //! This method is used in implementation of ID()
  static Standard_EXPORT const Standard_GUID& GetID();

  //! Returns the ID of TObj_TModel attribute.
  Standard_EXPORT const Standard_GUID& ID() const override;

public:
  //! Methods for setting and obtaining the Model object

  //! Sets the Model object
  Standard_EXPORT void Set(const occ::handle<TObj_Model>& theModel);

  //! Returns the Model object
  Standard_EXPORT occ::handle<TObj_Model> Model() const;

public:
  //! Redefined OCAF abstract methods

  //! Returns an new empty TObj_TModel attribute. It is used by the
  //! copy algorithm.
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  //! Restores the backuped contents from <theWith> into this one. It is used
  //! when aborting a transaction.
  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  //! This method is used when copying an attribute from a source structure
  //! into a target structure.
  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

private:
  //! Fields
  occ::handle<TObj_Model> myModel; //!< The Model object stored by the attribute

public:
  //! CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(TObj_TModel, TDF_Attribute)
};

//! Define handle class for TObj_TModel

#ifdef _MSC_VER
  #pragma once
#endif
