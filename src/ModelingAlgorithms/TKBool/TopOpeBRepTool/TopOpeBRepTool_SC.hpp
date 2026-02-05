#pragma once

#include <TopOpeBRepTool_ShapeClassifier.hpp>

Standard_EXPORT TopOpeBRepTool_ShapeClassifier& FSC_GetPSC();
Standard_EXPORT TopOpeBRepTool_ShapeClassifier& FSC_GetPSC(const TopoDS_Shape& S);
// ----------------------------------------------------------------------
//  state point <P> on/in shapes (edge <E>,face <F>)
// ----------------------------------------------------------------------
Standard_EXPORT TopAbs_State FSC_StatePonFace(const gp_Pnt&                   P,
                                              const TopoDS_Shape&             F,
                                              TopOpeBRepTool_ShapeClassifier& PSC);
Standard_EXPORT TopAbs_State FSC_StateEonFace(const TopoDS_Shape&             E,
                                              const double                    t,
                                              const TopoDS_Shape&             F,
                                              TopOpeBRepTool_ShapeClassifier& PSC);
