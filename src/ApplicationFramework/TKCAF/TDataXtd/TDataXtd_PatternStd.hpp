#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <TDataXtd_Pattern.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_OStream.hpp>
class TNaming_NamedShape;
class TDataStd_Real;
class TDataStd_Integer;
class Standard_GUID;
class TDF_Label;
class TDF_Attribute;
class TDF_RelocationTable;
class TDF_DataSet;

class TDataXtd_PatternStd : public TDataXtd_Pattern
{

public:
  Standard_EXPORT static const Standard_GUID& GetPatternID();

  Standard_EXPORT static occ::handle<TDataXtd_PatternStd> Set(const TDF_Label& label);

  Standard_EXPORT TDataXtd_PatternStd();

  Standard_EXPORT void Signature(const int signature);

  Standard_EXPORT void Axis1(const occ::handle<TNaming_NamedShape>& Axis1);

  Standard_EXPORT void Axis2(const occ::handle<TNaming_NamedShape>& Axis2);

  Standard_EXPORT void Axis1Reversed(const bool Axis1Reversed);

  Standard_EXPORT void Axis2Reversed(const bool Axis2Reversed);

  Standard_EXPORT void Value1(const occ::handle<TDataStd_Real>& value);

  Standard_EXPORT void Value2(const occ::handle<TDataStd_Real>& value);

  Standard_EXPORT void NbInstances1(const occ::handle<TDataStd_Integer>& NbInstances1);

  Standard_EXPORT void NbInstances2(const occ::handle<TDataStd_Integer>& NbInstances2);

  Standard_EXPORT void Mirror(const occ::handle<TNaming_NamedShape>& plane);

  int Signature() const;

  occ::handle<TNaming_NamedShape> Axis1() const;

  occ::handle<TNaming_NamedShape> Axis2() const;

  bool Axis1Reversed() const;

  bool Axis2Reversed() const;

  occ::handle<TDataStd_Real> Value1() const;

  occ::handle<TDataStd_Real> Value2() const;

  occ::handle<TDataStd_Integer> NbInstances1() const;

  occ::handle<TDataStd_Integer> NbInstances2() const;

  occ::handle<TNaming_NamedShape> Mirror() const;

  Standard_EXPORT int NbTrsfs() const override;

  Standard_EXPORT void ComputeTrsfs(NCollection_Array1<gp_Trsf>& Trsfs) const override;

  Standard_EXPORT const Standard_GUID& PatternID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& aDataSet) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_STANDARD_RTTIEXT(TDataXtd_PatternStd, TDataXtd_Pattern)

private:
  int                             mySignature;
  bool                            myAxis1Reversed;
  bool                            myAxis2Reversed;
  occ::handle<TNaming_NamedShape> myAxis1;
  occ::handle<TNaming_NamedShape> myAxis2;
  occ::handle<TDataStd_Real>      myValue1;
  occ::handle<TDataStd_Real>      myValue2;
  occ::handle<TDataStd_Integer>   myNb1;
  occ::handle<TDataStd_Integer>   myNb2;
  occ::handle<TNaming_NamedShape> myMirror;
};

inline int TDataXtd_PatternStd::Signature() const
{
  return mySignature;
}

inline occ::handle<TNaming_NamedShape> TDataXtd_PatternStd::Axis1() const
{
  return myAxis1;
}

inline occ::handle<TNaming_NamedShape> TDataXtd_PatternStd::Axis2() const
{
  return myAxis2;
}

inline bool TDataXtd_PatternStd::Axis1Reversed() const
{
  return myAxis1Reversed;
}

inline bool TDataXtd_PatternStd::Axis2Reversed() const
{
  return myAxis2Reversed;
}

inline occ::handle<TDataStd_Real> TDataXtd_PatternStd::Value1() const
{
  return myValue1;
}

inline occ::handle<TDataStd_Real> TDataXtd_PatternStd::Value2() const
{
  return myValue2;
}

inline occ::handle<TDataStd_Integer> TDataXtd_PatternStd::NbInstances1() const
{
  return myNb1;
}

inline occ::handle<TDataStd_Integer> TDataXtd_PatternStd::NbInstances2() const
{
  return myNb2;
}

inline occ::handle<TNaming_NamedShape> TDataXtd_PatternStd::Mirror() const
{
  return myMirror;
}
