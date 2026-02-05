#include <IGESGraph_DrawingSize.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_DrawingSize, IGESData_IGESEntity)

IGESGraph_DrawingSize::IGESGraph_DrawingSize() = default;

void IGESGraph_DrawingSize::Init(const int nbProps, const double aXSize, const double aYSize)
{
  theNbPropertyValues = nbProps;
  theXSize            = aXSize;
  theYSize            = aYSize;
  InitTypeAndForm(406, 16);
}

int IGESGraph_DrawingSize::NbPropertyValues() const
{
  return theNbPropertyValues;
}

double IGESGraph_DrawingSize::XSize() const
{
  return theXSize;
}

double IGESGraph_DrawingSize::YSize() const
{
  return theYSize;
}
