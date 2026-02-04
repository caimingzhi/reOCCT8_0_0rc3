#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>
#include <gp_XYZ.hpp>
#include <gp_XY.hpp>

//! to Update OutLines.
class HLRAlgo_PolyInternalNode : public Standard_Transient
{
public:
  struct NodeIndices
  {
    int NdSg, Flag, Edg1, Edg2;
  };

  struct NodeData
  {
    NodeData()
        : PCu1(0.0),
          PCu2(0.0),
          Scal(0.0)
    {
    }

    gp_XYZ Point, Normal;
    gp_XY  UV;
    double PCu1, PCu2, Scal;
  };

  HLRAlgo_PolyInternalNode()
  {
    myIndices.NdSg = 0;
    myIndices.Flag = 0;
    myIndices.Edg1 = 0;
    myIndices.Edg2 = 0;
  }

  NodeIndices& Indices() { return myIndices; }

  NodeData& Data() { return myData; }

  DEFINE_STANDARD_RTTIEXT(HLRAlgo_PolyInternalNode, Standard_Transient)

private:
  NodeIndices myIndices;
  NodeData    myData;
};

