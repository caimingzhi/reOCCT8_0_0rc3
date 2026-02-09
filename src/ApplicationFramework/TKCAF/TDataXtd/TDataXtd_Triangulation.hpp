#pragma once

#include <Standard.hpp>

#include <Poly_Triangulation.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_Label;
class TDF_RelocationTable;

class TDataXtd_Triangulation : public TDF_Attribute
{
public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataXtd_Triangulation> Set(const TDF_Label& theLabel);

  Standard_EXPORT static occ::handle<TDataXtd_Triangulation> Set(
    const TDF_Label&                       theLabel,
    const occ::handle<Poly_Triangulation>& theTriangulation);

  Standard_EXPORT TDataXtd_Triangulation();

  Standard_EXPORT void Set(const occ::handle<Poly_Triangulation>& theTriangulation);

  Standard_EXPORT const occ::handle<Poly_Triangulation>& Get() const;

  Standard_EXPORT double Deflection() const;

  Standard_EXPORT void Deflection(const double theDeflection);

  Standard_EXPORT void RemoveUVNodes();

  Standard_EXPORT int NbNodes() const;

  Standard_EXPORT int NbTriangles() const;

  Standard_EXPORT bool HasUVNodes() const;

  Standard_EXPORT gp_Pnt Node(const int theIndex) const;

  Standard_EXPORT void SetNode(const int theIndex, const gp_Pnt& theNode);

  Standard_EXPORT gp_Pnt2d UVNode(const int theIndex) const;

  Standard_EXPORT void SetUVNode(const int theIndex, const gp_Pnt2d& theUVNode);

  Standard_EXPORT Poly_Triangle Triangle(const int theIndex) const;

  Standard_EXPORT void SetTriangle(const int theIndex, const Poly_Triangle& theTriangle);

  Standard_EXPORT void SetNormal(const int theIndex, const gp_Dir& theNormal);

  Standard_EXPORT bool HasNormals() const;

  Standard_EXPORT gp_Dir Normal(const int theIndex) const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theAttribute) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_STANDARD_RTTI_INLINE(TDataXtd_Triangulation, TDF_Attribute)

private:
  occ::handle<Poly_Triangulation> myTriangulation;
};
