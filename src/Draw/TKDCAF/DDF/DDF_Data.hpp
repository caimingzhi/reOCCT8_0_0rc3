#pragma once

#include <Standard.hpp>

#include <Draw_Drawable3D.hpp>
#include <Standard_OStream.hpp>
#include <Draw_Interpretor.hpp>
class TDF_Data;
class Draw_Display;

//! Encapsulates a data framework from TDF in a drawable object
class DDF_Data : public Draw_Drawable3D
{

public:
  Standard_EXPORT DDF_Data(const occ::handle<TDF_Data>& aDF);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void DataFramework(const occ::handle<TDF_Data>& aDF);

  Standard_EXPORT occ::handle<TDF_Data> DataFramework() const;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

  DEFINE_STANDARD_RTTIEXT(DDF_Data, Draw_Drawable3D)

private:
  occ::handle<TDF_Data> myDF;
};
