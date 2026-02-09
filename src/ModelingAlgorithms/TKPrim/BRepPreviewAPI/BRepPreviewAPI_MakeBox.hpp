#pragma once

#include <BRepPrimAPI_MakeBox.hpp>

class BRepPreviewAPI_MakeBox : public BRepPrimAPI_MakeBox
{
public:
  BRepPreviewAPI_MakeBox() = default;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

private:
  void makeVertex(const gp_Pnt& thePoint);

  void makeEdge(const gp_Pnt& thePoint1, const gp_Pnt& thePoint2);

  void makeRectangle(const gp_Pnt& thePnt1,
                     const gp_Pnt& thePnt2,
                     const gp_Pnt& thePnt3,
                     const gp_Pnt& thePnt4);
};
