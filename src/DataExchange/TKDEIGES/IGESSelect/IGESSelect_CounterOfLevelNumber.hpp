#pragma once

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IFSelect_SignCounter.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

class Interface_InterfaceModel;
class TCollection_HAsciiString;

class IGESSelect_CounterOfLevelNumber : public IFSelect_SignCounter
{

public:
  Standard_EXPORT IGESSelect_CounterOfLevelNumber(const bool withmap  = true,
                                                  const bool withlist = false);

  Standard_EXPORT void Clear() override;

  Standard_EXPORT void AddSign(const occ::handle<Standard_Transient>&       ent,
                               const occ::handle<Interface_InterfaceModel>& model) override;

  Standard_EXPORT void AddLevel(const occ::handle<Standard_Transient>& ent, const int level);

  Standard_EXPORT int HighestLevel() const;

  Standard_EXPORT int NbTimesLevel(const int level) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<int>> Levels() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Sign(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT void PrintCount(Standard_OStream& S) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_CounterOfLevelNumber, IFSelect_SignCounter)

private:
  int                                   thehigh;
  int                                   thenblists;
  occ::handle<NCollection_HArray1<int>> thelevels;
};
