#pragma once

#include <Standard.hpp>

#include <TDF_Label.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>
class TDF_Attribute;
class Standard_GUID;

class TDF_AttributeDelta : public Standard_Transient
{

public:
  Standard_EXPORT virtual void Apply() = 0;

  Standard_EXPORT TDF_Label Label() const;

  Standard_EXPORT occ::handle<TDF_Attribute> Attribute() const;

  Standard_EXPORT Standard_GUID ID() const;

  Standard_EXPORT virtual Standard_OStream& Dump(Standard_OStream& OS) const;

  Standard_OStream& operator<<(Standard_OStream& OS) const { return Dump(OS); }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(TDF_AttributeDelta, Standard_Transient)

protected:
  Standard_EXPORT TDF_AttributeDelta(const occ::handle<TDF_Attribute>& anAttribute);

private:
  occ::handle<TDF_Attribute> myAttribute;
  TDF_Label                  myLabel;
};
