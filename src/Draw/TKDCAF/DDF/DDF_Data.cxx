#include <DDF.hpp>
#include <DDF_Data.hpp>
#include <Draw_Display.hpp>
#include <Draw_Drawable3D.hpp>
#include <Standard_Type.hpp>
#include <TDF_AttributeIterator.hpp>
#include <TDF_Data.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DDF_Data, Draw_Drawable3D)

DDF_Data::DDF_Data(const occ::handle<TDF_Data>& aDF)
    : myDF(aDF)
{
}

void DDF_Data::DrawOn(Draw_Display&) const

{
  std::cout << "DDF_Data" << std::endl;
}

occ::handle<Draw_Drawable3D> DDF_Data::Copy() const
{
  return new DDF_Data(myDF);
}

void DDF_Data::Dump(Standard_OStream& S) const

{
  TDF_Tool::DeepDump(S, myDF);
}

occ::handle<TDF_Data> DDF_Data::DataFramework() const
{
  return myDF;
}

void DDF_Data::DataFramework(const occ::handle<TDF_Data>& aDF)

{
  myDF = aDF;
}

void DDF_Data::Whatis(Draw_Interpretor& I) const

{
  I << "Data Framework";
}
