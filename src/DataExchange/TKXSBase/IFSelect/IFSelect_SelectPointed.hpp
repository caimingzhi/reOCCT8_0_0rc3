#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectBase.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_CopyControl;
class IFSelect_Transformer;
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

class IFSelect_SelectPointed : public IFSelect_SelectBase
{

public:
  Standard_EXPORT IFSelect_SelectPointed();

  Standard_EXPORT void Clear();

  Standard_EXPORT bool IsSet() const;

  Standard_EXPORT void SetEntity(const occ::handle<Standard_Transient>& item);

  Standard_EXPORT void SetList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  Standard_EXPORT bool Add(const occ::handle<Standard_Transient>& item);

  Standard_EXPORT bool Remove(const occ::handle<Standard_Transient>& item);

  Standard_EXPORT bool Toggle(const occ::handle<Standard_Transient>& item);

  Standard_EXPORT bool AddList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  Standard_EXPORT bool RemoveList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  Standard_EXPORT bool ToggleList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  Standard_EXPORT int Rank(const occ::handle<Standard_Transient>& item) const;

  Standard_EXPORT int NbItems() const;

  Standard_EXPORT occ::handle<Standard_Transient> Item(const int num) const;

  Standard_EXPORT void Update(const occ::handle<Interface_CopyControl>& control);

  Standard_EXPORT void Update(const occ::handle<IFSelect_Transformer>& trf);

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectPointed, IFSelect_SelectBase)

private:
  bool                                                  theset;
  NCollection_Sequence<occ::handle<Standard_Transient>> theitems;
};
