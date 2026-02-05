#pragma once

#include <Standard.hpp>

#include <TDF_Label.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>
class TDF_Attribute;
class Standard_GUID;

//! This class describes the services we need to
//! implement Delta and Undo/Redo services.
//!
//! AttributeDeltas are applied in an unpredictable
//! order. But by the redefinition of the method
//! IsNowApplicable, a condition can be verified
//! before application. If the AttributeDelta is not
//! yet applicable, it is put at the end of the
//! AttributeDelta list, to be treated later. If a
//! dead lock if found on the list, the
//! AttributeDeltas are forced to be applied in an
//! unpredictable order.
class TDF_AttributeDelta : public Standard_Transient
{

public:
  //! Applies the delta to the attribute.
  Standard_EXPORT virtual void Apply() = 0;

  //! Returns the label concerned by <me>.
  Standard_EXPORT TDF_Label Label() const;

  //! Returns the reference attribute.
  Standard_EXPORT occ::handle<TDF_Attribute> Attribute() const;

  //! Returns the ID of the attribute concerned by <me>.
  Standard_EXPORT Standard_GUID ID() const;

  //! Dumps the contents.
  Standard_EXPORT virtual Standard_OStream& Dump(Standard_OStream& OS) const;

  Standard_OStream& operator<<(Standard_OStream& OS) const { return Dump(OS); }

  //! Dumps the content of me into the stream
  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(TDF_AttributeDelta, Standard_Transient)

protected:
  Standard_EXPORT TDF_AttributeDelta(const occ::handle<TDF_Attribute>& anAttribute);

private:
  occ::handle<TDF_Attribute> myAttribute;
  TDF_Label                  myLabel;
};
