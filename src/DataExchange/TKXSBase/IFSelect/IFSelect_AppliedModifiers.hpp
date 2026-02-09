#pragma once

#include <Standard.hpp>

#include <IFSelect_GeneralModifier.hpp>
#include <NCollection_Sequence.hpp>
#include <Interface_IntList.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_HSequence.hpp>
class IFSelect_GeneralModifier;

class IFSelect_AppliedModifiers : public Standard_Transient
{
public:
  Standard_EXPORT IFSelect_AppliedModifiers(const int nbmax, const int nbent);

  Standard_EXPORT bool AddModif(const occ::handle<IFSelect_GeneralModifier>& modif);

  Standard_EXPORT bool AddNum(const int nument);

  Standard_EXPORT int Count() const;

  Standard_EXPORT bool Item(const int                              num,
                            occ::handle<IFSelect_GeneralModifier>& modif,
                            int&                                   entcount);

  Standard_EXPORT int ItemNum(const int nument) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<int>> ItemList() const;

  Standard_EXPORT bool IsForAll() const;

  DEFINE_STANDARD_RTTIEXT(IFSelect_AppliedModifiers, Standard_Transient)

private:
  NCollection_Sequence<occ::handle<IFSelect_GeneralModifier>> themodifs;
  Interface_IntList                                           thelists;
  int                                                         thenbent;
  int                                                         theentcnt;
};
