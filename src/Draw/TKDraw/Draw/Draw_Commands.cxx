#include <Draw.hpp>
#include <Draw_Drawable3D.hpp>

void Draw::Commands(Draw_Interpretor& theCommands)
{
  Draw::BasicCommands(theCommands);
  Draw::MessageCommands(theCommands);
  Draw::VariableCommands(theCommands);
  Draw::GraphicCommands(theCommands);
  Draw::PloadCommands(theCommands);
  Draw::UnitCommands(theCommands);
}
