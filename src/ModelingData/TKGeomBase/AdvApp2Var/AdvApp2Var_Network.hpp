#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AdvApp2Var_Patch.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Boolean.hpp>
class AdvApp2Var_Patch;

class AdvApp2Var_Network
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AdvApp2Var_Network();

  Standard_EXPORT AdvApp2Var_Network(const NCollection_Sequence<occ::handle<AdvApp2Var_Patch>>& Net,
                                     const NCollection_Sequence<double>& TheU,
                                     const NCollection_Sequence<double>& TheV);

  Standard_EXPORT bool FirstNotApprox(int& Index) const;

  AdvApp2Var_Patch& ChangePatch(const int Index) { return *myNet.Value(Index); }

  AdvApp2Var_Patch& operator()(const int Index) { return ChangePatch(Index); }

  Standard_EXPORT void UpdateInU(const double CuttingValue);

  Standard_EXPORT void UpdateInV(const double CuttingValue);

  Standard_EXPORT void SameDegree(const int iu, const int iv, int& ncfu, int& ncfv);

  Standard_EXPORT int NbPatch() const;

  Standard_EXPORT int NbPatchInU() const;

  Standard_EXPORT int NbPatchInV() const;

  Standard_EXPORT double UParameter(const int Index) const;

  Standard_EXPORT double VParameter(const int Index) const;

  const AdvApp2Var_Patch& Patch(const int UIndex, const int VIndex) const
  {
    return *myNet.Value((VIndex - 1) * (myUParameters.Length() - 1) + UIndex);
  }

  const AdvApp2Var_Patch& operator()(const int UIndex, const int VIndex) const
  {
    return Patch(UIndex, VIndex);
  }

private:
  NCollection_Sequence<occ::handle<AdvApp2Var_Patch>> myNet;
  NCollection_Sequence<double>                        myUParameters;
  NCollection_Sequence<double>                        myVParameters;
};
