#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <TopOpeBRepDS_Config.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_State.hpp>
#include <Standard_OStream.hpp>

class TopOpeBRepBuild_GTopo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_GTopo();

  Standard_EXPORT TopOpeBRepBuild_GTopo(const bool                II,
                                        const bool                IN,
                                        const bool                IO,
                                        const bool                NI,
                                        const bool                NN,
                                        const bool                NO,
                                        const bool                OI,
                                        const bool                ON,
                                        const bool                OO,
                                        const TopAbs_ShapeEnum    t1,
                                        const TopAbs_ShapeEnum    t2,
                                        const TopOpeBRepDS_Config C1,
                                        const TopOpeBRepDS_Config C2);

  Standard_EXPORT void Reset();

  Standard_EXPORT void Set(const bool II,
                           const bool IN,
                           const bool IO,
                           const bool NI,
                           const bool NN,
                           const bool NO,
                           const bool OI,
                           const bool ON,
                           const bool OO);

  Standard_EXPORT void Type(TopAbs_ShapeEnum& t1, TopAbs_ShapeEnum& t2) const;

  Standard_EXPORT void ChangeType(const TopAbs_ShapeEnum t1, const TopAbs_ShapeEnum t2);

  Standard_EXPORT TopOpeBRepDS_Config Config1() const;

  Standard_EXPORT TopOpeBRepDS_Config Config2() const;

  Standard_EXPORT void ChangeConfig(const TopOpeBRepDS_Config C1, const TopOpeBRepDS_Config C2);

  Standard_EXPORT bool Value(const TopAbs_State s1, const TopAbs_State s2) const;

  Standard_EXPORT bool Value(const int I1, const int I2) const;

  Standard_EXPORT bool Value(const int II) const;

  Standard_EXPORT void ChangeValue(const int i1, const int i2, const bool b);

  Standard_EXPORT void ChangeValue(const TopAbs_State s1, const TopAbs_State s2, const bool b);

  Standard_EXPORT int GIndex(const TopAbs_State S) const;

  Standard_EXPORT TopAbs_State GState(const int I) const;

  Standard_EXPORT void Index(const int II, int& i1, int& i2) const;

  Standard_EXPORT void DumpVal(Standard_OStream&  OS,
                               const TopAbs_State s1,
                               const TopAbs_State s2) const;

  Standard_EXPORT void DumpType(Standard_OStream& OS) const;

  Standard_EXPORT static void DumpSSB(Standard_OStream&  OS,
                                      const TopAbs_State s1,
                                      const TopAbs_State s2,
                                      const bool         b);

  Standard_EXPORT virtual void Dump(Standard_OStream& OS, void* const s = nullptr) const;

  Standard_EXPORT void StatesON(TopAbs_State& s1, TopAbs_State& s2) const;

  Standard_EXPORT bool IsToReverse1() const;

  Standard_EXPORT bool IsToReverse2() const;

  Standard_EXPORT void SetReverse(const bool rev);

  Standard_EXPORT bool Reverse() const;

  Standard_EXPORT TopOpeBRepBuild_GTopo CopyPermuted() const;

private:
  bool                mycases[3][3];
  TopAbs_ShapeEnum    myt1;
  TopAbs_ShapeEnum    myt2;
  TopOpeBRepDS_Config myConfig1;
  TopOpeBRepDS_Config myConfig2;
  bool                myReverseForce;
  bool                myReverseValue;
};
