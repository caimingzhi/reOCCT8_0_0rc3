

#include <Vrml_Separator.hpp>

Vrml_Separator::Vrml_Separator(const Vrml_SeparatorRenderCulling aRenderCulling)
{
  myRenderCulling = aRenderCulling;
  myFlagPrint     = false;
}

Vrml_Separator::Vrml_Separator()
{
  myRenderCulling = Vrml_AUTO;
  myFlagPrint     = false;
}

void Vrml_Separator::SetRenderCulling(const Vrml_SeparatorRenderCulling aRenderCulling)
{
  myRenderCulling = aRenderCulling;
}

Vrml_SeparatorRenderCulling Vrml_Separator::RenderCulling() const
{
  return myRenderCulling;
}

Standard_OStream& Vrml_Separator::Print(Standard_OStream& anOStream)
{
  if (myFlagPrint == 0)
  {
    anOStream << "Separator {\n";
    if (myRenderCulling != Vrml_AUTO)
    {
      if (myRenderCulling == Vrml_ON)
        anOStream << "    renderCulling\tON\n";
      else
        anOStream << "    renderCulling\tOFF\n";
    }
    myFlagPrint = true;
  }
  else
  {
    anOStream << "}\n";
    myFlagPrint = false;
  }
  return anOStream;
}
