#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataXtd_ConstraintEnum.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
#include <Standard_OStream.hpp>

class TDataStd_Real;
class Standard_GUID;
class TDF_Label;
class TNaming_NamedShape;
class TDF_RelocationTable;
class TDF_DataSet;

class TDataXtd_Constraint : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataXtd_Constraint> Set(const TDF_Label& label);

  Standard_EXPORT TDataXtd_Constraint();

  Standard_EXPORT void Set(const TDataXtd_ConstraintEnum          type,
                           const occ::handle<TNaming_NamedShape>& G1);

  Standard_EXPORT void Set(const TDataXtd_ConstraintEnum          type,
                           const occ::handle<TNaming_NamedShape>& G1,
                           const occ::handle<TNaming_NamedShape>& G2);

  Standard_EXPORT void Set(const TDataXtd_ConstraintEnum          type,
                           const occ::handle<TNaming_NamedShape>& G1,
                           const occ::handle<TNaming_NamedShape>& G2,
                           const occ::handle<TNaming_NamedShape>& G3);

  Standard_EXPORT void Set(const TDataXtd_ConstraintEnum          type,
                           const occ::handle<TNaming_NamedShape>& G1,
                           const occ::handle<TNaming_NamedShape>& G2,
                           const occ::handle<TNaming_NamedShape>& G3,
                           const occ::handle<TNaming_NamedShape>& G4);

  Standard_EXPORT bool Verified() const;

  Standard_EXPORT TDataXtd_ConstraintEnum GetType() const;

  Standard_EXPORT bool IsPlanar() const;

  Standard_EXPORT const occ::handle<TNaming_NamedShape>& GetPlane() const;

  Standard_EXPORT bool IsDimension() const;

  Standard_EXPORT const occ::handle<TDataStd_Real>& GetValue() const;

  Standard_EXPORT int NbGeometries() const;

  Standard_EXPORT occ::handle<TNaming_NamedShape> GetGeometry(const int Index) const;

  Standard_EXPORT void ClearGeometries();

  Standard_EXPORT void SetType(const TDataXtd_ConstraintEnum CTR);

  Standard_EXPORT void SetPlane(const occ::handle<TNaming_NamedShape>& plane);

  Standard_EXPORT void SetValue(const occ::handle<TDataStd_Real>& V);

  Standard_EXPORT void SetGeometry(const int Index, const occ::handle<TNaming_NamedShape>& G);

  Standard_EXPORT void Verified(const bool status);

  Standard_EXPORT void Inverted(const bool status);

  Standard_EXPORT bool Inverted() const;

  Standard_EXPORT void Reversed(const bool status);

  Standard_EXPORT bool Reversed() const;

  Standard_EXPORT static void CollectChildConstraints(const TDF_Label&             aLabel,
                                                      NCollection_List<TDF_Label>& TheList);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& DS) const override;

  DEFINE_STANDARD_RTTIEXT(TDataXtd_Constraint, TDF_Attribute)

private:
  TDataXtd_ConstraintEnum         myType;
  occ::handle<TDataStd_Real>      myValue;
  occ::handle<TDF_Attribute>      myGeometries[4];
  occ::handle<TNaming_NamedShape> myPlane;
  bool                            myIsReversed;
  bool                            myIsInverted;
  bool                            myIsVerified;
};
