#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <LocOpe_Gluer.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <LocOpe_Operation.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;
class TopoDS_Face;
class TopoDS_Edge;

class BRepFeat_Gluer : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  BRepFeat_Gluer();

  BRepFeat_Gluer(const TopoDS_Shape& Snew, const TopoDS_Shape& Sbase);

  void Init(const TopoDS_Shape& Snew, const TopoDS_Shape& Sbase);

  void Bind(const TopoDS_Face& Fnew, const TopoDS_Face& Fbase);

  void Bind(const TopoDS_Edge& Enew, const TopoDS_Edge& Ebase);

  LocOpe_Operation OpeType() const;

  const TopoDS_Shape& BasisShape() const;

  const TopoDS_Shape& GluedShape() const;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& F) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& F) override;

private:
  LocOpe_Gluer myGluer;
};

inline BRepFeat_Gluer::BRepFeat_Gluer() = default;

inline BRepFeat_Gluer::BRepFeat_Gluer(const TopoDS_Shape& Snew, const TopoDS_Shape& Sbase)
    : myGluer(Sbase, Snew)
{
}

inline void BRepFeat_Gluer::Init(const TopoDS_Shape& Snew, const TopoDS_Shape& Sbase)
{
  myGluer.Init(Sbase, Snew);
}

inline void BRepFeat_Gluer::Bind(const TopoDS_Face& Fnew, const TopoDS_Face& Fbase)
{
  myGluer.Bind(Fnew, Fbase);
}

inline void BRepFeat_Gluer::Bind(const TopoDS_Edge& Enew, const TopoDS_Edge& Ebase)
{
  myGluer.Bind(Enew, Ebase);
}

inline LocOpe_Operation BRepFeat_Gluer::OpeType() const
{
  return myGluer.OpeType();
}

inline const TopoDS_Shape& BRepFeat_Gluer::BasisShape() const
{
  return myGluer.BasisShape();
}

inline const TopoDS_Shape& BRepFeat_Gluer::GluedShape() const
{
  return myGluer.GluedShape();
}
