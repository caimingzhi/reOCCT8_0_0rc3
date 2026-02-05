#include <Aspect_Background.hpp>
#include <Quantity_Color.hpp>
#include <Standard_Dump.hpp>

//-Aliases
//-Global data definitions
//	-- la couleur associee au fond d'ecran
//	MyColor	:	Color;
//-Constructors
//-Destructors
//-Methods, in order
Aspect_Background::Aspect_Background()
{

  Quantity_Color MatraGray(Quantity_NOC_MATRAGRAY);

  MyColor = MatraGray;
}

Aspect_Background::Aspect_Background(const Quantity_Color& AColor)
{

  MyColor = AColor;
}

void Aspect_Background::SetColor(const Quantity_Color& AColor)
{

  MyColor = AColor;
}

Quantity_Color Aspect_Background::Color() const
{

  return (MyColor);
}

//=================================================================================================

void Aspect_Background::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, Aspect_Background)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &MyColor)
}
