#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class Standard_GUID;
class TFunction_Logbook;
class TDF_RelocationTable;

class TFunction_Logbook : public TDF_Attribute
{
public:
  Standard_EXPORT static occ::handle<TFunction_Logbook> Set(const TDF_Label& Access);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TFunction_Logbook();

  Standard_EXPORT void Clear();
  Standard_EXPORT bool IsEmpty() const;

  void SetTouched(const TDF_Label& L);

  Standard_EXPORT void SetImpacted(const TDF_Label& L, const bool WithChildren = false);

  Standard_EXPORT void SetValid(const TDF_Label& L, const bool WithChildren = false);
  Standard_EXPORT void SetValid(const NCollection_Map<TDF_Label>& Ls);

  Standard_EXPORT bool IsModified(const TDF_Label& L, const bool WithChildren = false) const;

  const NCollection_Map<TDF_Label>& GetTouched() const;

  const NCollection_Map<TDF_Label>& GetImpacted() const;

  const NCollection_Map<TDF_Label>& GetValid() const;
  Standard_EXPORT void              GetValid(NCollection_Map<TDF_Label>& Ls) const;

  void Done(const bool status);

  bool IsDone() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_STANDARD_RTTIEXT(TFunction_Logbook, TDF_Attribute)

private:
  NCollection_Map<TDF_Label> myTouched;
  NCollection_Map<TDF_Label> myImpacted;
  NCollection_Map<TDF_Label> myValid;
  bool                       isDone;
};

inline void TFunction_Logbook::SetTouched(const TDF_Label& L)
{
  if (!myTouched.Contains(L))
  {
    Backup();
    myTouched.Add(L);
  }
}

inline const NCollection_Map<TDF_Label>& TFunction_Logbook::GetTouched() const
{
  return myTouched;
}

inline const NCollection_Map<TDF_Label>& TFunction_Logbook::GetImpacted() const
{
  return myImpacted;
}

inline const NCollection_Map<TDF_Label>& TFunction_Logbook::GetValid() const
{
  return myValid;
}

inline void TFunction_Logbook::Done(const bool status)
{
  if (isDone != status)
  {
    Backup();
    isDone = status;
  }
}

inline bool TFunction_Logbook::IsDone() const
{
  return isDone;
}
