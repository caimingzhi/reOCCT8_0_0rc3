#include <BRepGProp_Domain.hpp>
#include <TopoDS_Edge.hpp>

void BRepGProp_Domain::Next()
{

  myExplorer.Next();
  while (myExplorer.More())
  {
    TopAbs_Orientation Or = myExplorer.Current().Orientation();
    if ((Or == TopAbs_FORWARD) || (Or == TopAbs_REVERSED))
      return;
    myExplorer.Next();
  }
}
