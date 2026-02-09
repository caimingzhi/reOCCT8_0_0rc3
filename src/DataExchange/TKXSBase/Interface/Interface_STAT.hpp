#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;

class Interface_STAT
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_STAT(const char* title = "");

  Standard_EXPORT Interface_STAT(const Interface_STAT& other);

  Interface_STAT& operator=(const Interface_STAT& theOther)
  {
    theOther.Internals(thetitle, thetotal, thephnam, thephw, thephdeb, thephfin, thestw);
    return *this;
  }

  Standard_EXPORT void Internals(occ::handle<TCollection_HAsciiString>&                       tit,
                                 double&                                                      total,
                                 occ::handle<NCollection_HSequence<TCollection_AsciiString>>& phn,
                                 occ::handle<NCollection_HSequence<double>>&                  phw,
                                 occ::handle<NCollection_HSequence<int>>&                     phdeb,
                                 occ::handle<NCollection_HSequence<int>>&                     phfin,
                                 occ::handle<NCollection_HSequence<double>>& stw) const;

  Standard_EXPORT void AddPhase(const double weight, const char* name = "");

  Standard_EXPORT void AddStep(const double weight = 1);

  Standard_EXPORT void Description(int& nbphases, double& total, const char*& title) const;

  Standard_EXPORT void Phase(const int    num,
                             int&         n0step,
                             int&         nbstep,
                             double&      weight,
                             const char*& name) const;

  Standard_EXPORT double Step(const int num) const;

  Standard_EXPORT void Start(const int items, const int cycles = 1) const;

  Standard_EXPORT static void StartCount(const int items, const char* title = "");

  Standard_EXPORT static void NextPhase(const int items, const int cycles = 1);

  Standard_EXPORT static void SetPhase(const int items, const int cycles = 1);

  Standard_EXPORT static void NextCycle(const int items);

  Standard_EXPORT static void NextStep();

  Standard_EXPORT static void NextItem(const int nbitems = 1);

  Standard_EXPORT static void End();

  Standard_EXPORT static const char* Where(const bool phase = true);

  Standard_EXPORT static int Percent(const bool phase = false);

private:
  occ::handle<TCollection_HAsciiString>                       thetitle;
  double                                                      thetotal;
  occ::handle<NCollection_HSequence<TCollection_AsciiString>> thephnam;
  occ::handle<NCollection_HSequence<double>>                  thephw;
  occ::handle<NCollection_HSequence<int>>                     thephdeb;
  occ::handle<NCollection_HSequence<int>>                     thephfin;
  occ::handle<NCollection_HSequence<double>>                  thestw;
};
