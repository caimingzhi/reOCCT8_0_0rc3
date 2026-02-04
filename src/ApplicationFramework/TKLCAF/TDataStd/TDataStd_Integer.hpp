#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TDF_RelocationTable;

//! The basis to define an integer attribute.
class TDataStd_Integer : public TDF_Attribute
{

public:
  //! class methods
  //! =============
  //! Returns the GUID for integers.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Finds, or creates, an Integer attribute and sets <value>
  //! the Integer attribute is returned.
  Standard_EXPORT static occ::handle<TDataStd_Integer> Set(const TDF_Label& label, const int value);

  //! Finds, or creates, an Integer attribute with explicit user defined <guid> and sets <value>.
  //! The Integer attribute is returned.
  Standard_EXPORT static occ::handle<TDataStd_Integer> Set(const TDF_Label&     label,
                                                           const Standard_GUID& guid,
                                                           const int            value);

  //! Integer methods
  //! ===============
  Standard_EXPORT void Set(const int V);

  //! Sets the explicit GUID (user defined) for the attribute.
  Standard_EXPORT void SetID(const Standard_GUID& guid) override;

  //! Sets default GUID for the attribute.
  Standard_EXPORT void SetID() override;

  //! Returns the integer value contained in the attribute.
  Standard_EXPORT int Get() const;

  //! Returns True if there is a reference on the same label
  Standard_EXPORT bool IsCaptured() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT TDataStd_Integer();

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_Integer, TDF_Attribute)

private:
  int           myValue;
  Standard_GUID myID;
};

