#pragma once

#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>

namespace GeomGridEval
{

  struct CurveD1
  {
    gp_Pnt Point;
    gp_Vec D1;
  };

  struct CurveD2
  {
    gp_Pnt Point;
    gp_Vec D1;
    gp_Vec D2;
  };

  struct CurveD3
  {
    gp_Pnt Point;
    gp_Vec D1;
    gp_Vec D2;
    gp_Vec D3;
  };

  struct SurfD1
  {
    gp_Pnt Point;
    gp_Vec D1U;
    gp_Vec D1V;
  };

  struct SurfD2
  {
    gp_Pnt Point;
    gp_Vec D1U;
    gp_Vec D1V;
    gp_Vec D2U;
    gp_Vec D2V;
    gp_Vec D2UV;
  };

  struct SurfD3
  {
    gp_Pnt Point;
    gp_Vec D1U;
    gp_Vec D1V;
    gp_Vec D2U;
    gp_Vec D2V;
    gp_Vec D2UV;
    gp_Vec D3U;
    gp_Vec D3V;
    gp_Vec D3UUV;
    gp_Vec D3UVV;
  };

  struct UVPoint
  {
    double U;
    double V;
    int    OutputIdx;
  };

  struct UVPointWithSpan
  {
    double U;
    double V;
    double LocalU;
    double LocalV;
    int    USpanIdx;
    int    VSpanIdx;
    int    OutputIdx;
  };

  template <typename Evaluator>
  NCollection_Array2<gp_Pnt> EvaluateGridHelper(const NCollection_Array1<double>& theUParams,
                                                const NCollection_Array1<double>& theVParams,
                                                Evaluator                         theEval)
  {
    const int aNbU = theUParams.Size();
    const int aNbV = theVParams.Size();
    if (aNbU == 0 || aNbV == 0)
    {
      return NCollection_Array2<gp_Pnt>();
    }

    NCollection_Array2<gp_Pnt> aResult(1, aNbU, 1, aNbV);
    for (int iU = 1; iU <= aNbU; ++iU)
    {
      const double aU = theUParams.Value(theUParams.Lower() + iU - 1);
      for (int iV = 1; iV <= aNbV; ++iV)
      {
        const double aV = theVParams.Value(theVParams.Lower() + iV - 1);
        aResult.SetValue(iU, iV, theEval(aU, aV));
      }
    }
    return aResult;
  }

  template <typename Evaluator>
  NCollection_Array2<SurfD1> EvaluateGridD1Helper(const NCollection_Array1<double>& theUParams,
                                                  const NCollection_Array1<double>& theVParams,
                                                  Evaluator                         theEval)
  {
    const int aNbU = theUParams.Size();
    const int aNbV = theVParams.Size();
    if (aNbU == 0 || aNbV == 0)
    {
      return NCollection_Array2<SurfD1>();
    }

    NCollection_Array2<SurfD1> aResult(1, aNbU, 1, aNbV);
    for (int iU = 1; iU <= aNbU; ++iU)
    {
      const double aU = theUParams.Value(theUParams.Lower() + iU - 1);
      for (int iV = 1; iV <= aNbV; ++iV)
      {
        const double aV             = theVParams.Value(theVParams.Lower() + iV - 1);
        aResult.ChangeValue(iU, iV) = theEval(aU, aV);
      }
    }
    return aResult;
  }

  template <typename Evaluator>
  NCollection_Array2<SurfD2> EvaluateGridD2Helper(const NCollection_Array1<double>& theUParams,
                                                  const NCollection_Array1<double>& theVParams,
                                                  Evaluator                         theEval)
  {
    const int aNbU = theUParams.Size();
    const int aNbV = theVParams.Size();
    if (aNbU == 0 || aNbV == 0)
    {
      return NCollection_Array2<SurfD2>();
    }

    NCollection_Array2<SurfD2> aResult(1, aNbU, 1, aNbV);
    for (int iU = 1; iU <= aNbU; ++iU)
    {
      const double aU = theUParams.Value(theUParams.Lower() + iU - 1);
      for (int iV = 1; iV <= aNbV; ++iV)
      {
        const double aV             = theVParams.Value(theVParams.Lower() + iV - 1);
        aResult.ChangeValue(iU, iV) = theEval(aU, aV);
      }
    }
    return aResult;
  }

  template <typename Evaluator>
  NCollection_Array2<SurfD3> EvaluateGridD3Helper(const NCollection_Array1<double>& theUParams,
                                                  const NCollection_Array1<double>& theVParams,
                                                  Evaluator                         theEval)
  {
    const int aNbU = theUParams.Size();
    const int aNbV = theVParams.Size();
    if (aNbU == 0 || aNbV == 0)
    {
      return NCollection_Array2<SurfD3>();
    }

    NCollection_Array2<SurfD3> aResult(1, aNbU, 1, aNbV);
    for (int iU = 1; iU <= aNbU; ++iU)
    {
      const double aU = theUParams.Value(theUParams.Lower() + iU - 1);
      for (int iV = 1; iV <= aNbV; ++iV)
      {
        const double aV             = theVParams.Value(theVParams.Lower() + iV - 1);
        aResult.ChangeValue(iU, iV) = theEval(aU, aV);
      }
    }
    return aResult;
  }

  template <typename Evaluator>
  NCollection_Array2<gp_Vec> EvaluateGridDNHelper(const NCollection_Array1<double>& theUParams,
                                                  const NCollection_Array1<double>& theVParams,
                                                  Evaluator                         theEval)
  {
    const int aNbU = theUParams.Size();
    const int aNbV = theVParams.Size();
    if (aNbU == 0 || aNbV == 0)
    {
      return NCollection_Array2<gp_Vec>();
    }

    NCollection_Array2<gp_Vec> aResult(1, aNbU, 1, aNbV);
    for (int iU = 1; iU <= aNbU; ++iU)
    {
      const double aU = theUParams.Value(theUParams.Lower() + iU - 1);
      for (int iV = 1; iV <= aNbV; ++iV)
      {
        const double aV = theVParams.Value(theVParams.Lower() + iV - 1);
        aResult.SetValue(iU, iV, theEval(aU, aV));
      }
    }
    return aResult;
  }

  template <typename Evaluator>
  NCollection_Array1<gp_Pnt> EvaluatePointsHelper(const NCollection_Array1<gp_Pnt2d>& theUVPairs,
                                                  Evaluator                           theEval)
  {
    const int aNbPts = theUVPairs.Size();
    if (aNbPts == 0)
    {
      return NCollection_Array1<gp_Pnt>();
    }

    NCollection_Array1<gp_Pnt> aResult(1, aNbPts);
    for (int i = 1; i <= aNbPts; ++i)
    {
      const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i - 1);
      aResult.SetValue(i, theEval(aUV.X(), aUV.Y()));
    }
    return aResult;
  }

  template <typename Evaluator>
  NCollection_Array1<SurfD1> EvaluatePointsD1Helper(const NCollection_Array1<gp_Pnt2d>& theUVPairs,
                                                    Evaluator                           theEval)
  {
    const int aNbPts = theUVPairs.Size();
    if (aNbPts == 0)
    {
      return NCollection_Array1<SurfD1>();
    }

    NCollection_Array1<SurfD1> aResult(1, aNbPts);
    for (int i = 1; i <= aNbPts; ++i)
    {
      const gp_Pnt2d& aUV    = theUVPairs.Value(theUVPairs.Lower() + i - 1);
      aResult.ChangeValue(i) = theEval(aUV.X(), aUV.Y());
    }
    return aResult;
  }

  template <typename Evaluator>
  NCollection_Array1<SurfD2> EvaluatePointsD2Helper(const NCollection_Array1<gp_Pnt2d>& theUVPairs,
                                                    Evaluator                           theEval)
  {
    const int aNbPts = theUVPairs.Size();
    if (aNbPts == 0)
    {
      return NCollection_Array1<SurfD2>();
    }

    NCollection_Array1<SurfD2> aResult(1, aNbPts);
    for (int i = 1; i <= aNbPts; ++i)
    {
      const gp_Pnt2d& aUV    = theUVPairs.Value(theUVPairs.Lower() + i - 1);
      aResult.ChangeValue(i) = theEval(aUV.X(), aUV.Y());
    }
    return aResult;
  }

  template <typename Evaluator>
  NCollection_Array1<SurfD3> EvaluatePointsD3Helper(const NCollection_Array1<gp_Pnt2d>& theUVPairs,
                                                    Evaluator                           theEval)
  {
    const int aNbPts = theUVPairs.Size();
    if (aNbPts == 0)
    {
      return NCollection_Array1<SurfD3>();
    }

    NCollection_Array1<SurfD3> aResult(1, aNbPts);
    for (int i = 1; i <= aNbPts; ++i)
    {
      const gp_Pnt2d& aUV    = theUVPairs.Value(theUVPairs.Lower() + i - 1);
      aResult.ChangeValue(i) = theEval(aUV.X(), aUV.Y());
    }
    return aResult;
  }

  template <typename Evaluator>
  NCollection_Array1<gp_Vec> EvaluatePointsDNHelper(const NCollection_Array1<gp_Pnt2d>& theUVPairs,
                                                    Evaluator                           theEval)
  {
    const int aNbPts = theUVPairs.Size();
    if (aNbPts == 0)
    {
      return NCollection_Array1<gp_Vec>();
    }

    NCollection_Array1<gp_Vec> aResult(1, aNbPts);
    for (int i = 1; i <= aNbPts; ++i)
    {
      const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i - 1);
      aResult.SetValue(i, theEval(aUV.X(), aUV.Y()));
    }
    return aResult;
  }

} // namespace GeomGridEval
