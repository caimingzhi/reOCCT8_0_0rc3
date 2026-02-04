#pragma once


#include <Standard.hpp>

#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class Standard_GUID;
class TDF_RelocationTable;

//! Transient attribute which register modified labels.
//! This attribute is attached to root label.
class TDocStd_Modified : public TDF_Attribute
{

public:
  //! API class methods
  //! =================
  Standard_EXPORT static bool IsEmpty(const TDF_Label& access);

  Standard_EXPORT static bool Add(const TDF_Label& alabel);

  Standard_EXPORT static bool Remove(const TDF_Label& alabel);

  Standard_EXPORT static bool Contains(const TDF_Label& alabel);

  //! if <IsEmpty> raise an exception.
  Standard_EXPORT static const NCollection_Map<TDF_Label>& Get(const TDF_Label& access);

  //! remove all modified labels. becomes empty
  Standard_EXPORT static void Clear(const TDF_Label& access);

  //! Modified methods
  //! ================
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDocStd_Modified();

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT void Clear();

  //! add <L> as modified
  Standard_EXPORT bool AddLabel(const TDF_Label& L);

  //! remove <L> as modified
  Standard_EXPORT bool RemoveLabel(const TDF_Label& L);

  //! returns modified label map
  Standard_EXPORT const NCollection_Map<TDF_Label>& Get() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_STANDARD_RTTIEXT(TDocStd_Modified, TDF_Attribute)

private:
  NCollection_Map<TDF_Label> myModified;
};

