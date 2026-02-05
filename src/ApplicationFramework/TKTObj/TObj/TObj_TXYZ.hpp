#pragma once

#include <gp_XYZ.hpp>
#include <TDF_Attribute.hpp>

class Standard_GUID;
class TDF_Label;

/*
 * Attribute for storing gp_XYZ
 */

class TObj_TXYZ : public TDF_Attribute
{
public:
  //! Standard methods of OCAF attribute

  //! Empty constructor
  Standard_EXPORT TObj_TXYZ();

  //! This method is used in implementation of ID()
  static Standard_EXPORT const Standard_GUID& GetID();

  //! Returns the ID of TObj_TXYZ attribute.
  Standard_EXPORT const Standard_GUID& ID() const override;

public:
  //! Method for create TObj_TXYZ object

  //! Creates attribute and sets the XYZ
  static Standard_EXPORT occ::handle<TObj_TXYZ> Set(const TDF_Label& theLabel,
                                                    const gp_XYZ&    theXYZ);

public:
  //! Methods for setting and obtaining XYZ

  //! Sets the XYZ
  Standard_EXPORT void Set(const gp_XYZ& theXYZ);

  //! Returns the XYZ
  Standard_EXPORT gp_XYZ Get() const;

public:
  //! Redefined OCAF abstract methods

  //! Returns an new empty TObj_TXYZ attribute. It is used by the
  //! copy algorithm.
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  //! Restores the backuped contents from <theWith> into this one. It is used
  //! when aborting a transaction.
  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  //! This method is used when copying an attribute from a source structure
  //! into a target structure.
  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

  //! This method dumps the attribute value into the stream
  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& theOS) const override;

private:
  //! Fields
  gp_XYZ myXYZ; //!< The object interface stored by the attribute

public:
  //! CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(TObj_TXYZ, TDF_Attribute)
};

//! Define handle class for TObj_TXYZ

#ifdef _MSC_VER
  #pragma once
#endif
