#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <TDF_Attribute.hpp>
class Standard_GUID;
class TDF_Label;
class TDF_RelocationTable;

//! This attribute manage a tag provider to create
//! child labels of a given one.
class TDF_TagSource : public TDF_Attribute
{

public:
  //! class methods
  //! =============
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Find, or create, a TagSource attribute. the TagSource
  //! attribute is returned.
  Standard_EXPORT static occ::handle<TDF_TagSource> Set(const TDF_Label& label);

  //! Find (or create) a tagSource attribute located at <L>
  //! and make a new child label.
  //! TagSource methods
  //! =================
  Standard_EXPORT static TDF_Label NewChild(const TDF_Label& L);

  Standard_EXPORT TDF_TagSource();

  Standard_EXPORT int NewTag();

  Standard_EXPORT TDF_Label NewChild();

  Standard_EXPORT int Get() const;

  //! TDF_Attribute methods
  //! =====================
  Standard_EXPORT void Set(const int T);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDF_TagSource, TDF_Attribute)

private:
  int myTag;
};
