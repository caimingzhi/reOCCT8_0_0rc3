

#include <IntImp_ComputeTangence.hpp>
#include <IntImp_ConstIsoparametric.hpp>
#include <Standard_OutOfRange.hpp>

static const IntImp_ConstIsoparametric staticChoixRef[4] = {
  IntImp_UIsoparametricOnCaro1,
  IntImp_VIsoparametricOnCaro1,
  IntImp_UIsoparametricOnCaro2,
  IntImp_VIsoparametricOnCaro2,
};

IntImp_ConstIsoparametric ChoixRef(int theIndex)
{
  Standard_OutOfRange_Raise_if(theIndex < 0 || theIndex > 3,
                               "ChoixRef() in " __FILE__) return staticChoixRef[theIndex];
}

bool IntImp_ComputeTangence(const gp_Vec              DPuv[],
                            const double              EpsUV[],
                            double                    Tgduv[],
                            IntImp_ConstIsoparametric TabIso[])

{
  double NormDuv[4], aM2, aTol2;
  int    i;

  aTol2 = 1.e-32;

  for (i = 0; i < 4; ++i)
  {
    NormDuv[i] = DPuv[i].SquareMagnitude();
    if (NormDuv[i] <= aTol2)
    {
      return true;
    }
  }

  gp_Vec N1 = DPuv[0];
  N1.Cross(DPuv[1]);

  aM2 = N1.SquareMagnitude();
  if (aM2 < aTol2)
  {
    return true;
  }

  N1.Normalize();

  gp_Vec N2 = DPuv[2];
  N2.Cross(DPuv[3]);

  aM2 = N2.SquareMagnitude();
  if (aM2 < aTol2)
  {
    return true;
  }

  N2.Normalize();

  for (i = 0; i < 4; ++i)
  {
    NormDuv[i] = sqrt(NormDuv[i]);
  }

  Tgduv[0] = -DPuv[1].Dot(N2);
  Tgduv[1] = DPuv[0].Dot(N2);
  Tgduv[2] = DPuv[3].Dot(N1);
  Tgduv[3] = -DPuv[2].Dot(N1);

  bool tangent =
    (std::abs(Tgduv[0]) <= EpsUV[0] * NormDuv[1] && std::abs(Tgduv[1]) <= EpsUV[1] * NormDuv[0]
     && std::abs(Tgduv[2]) <= EpsUV[2] * NormDuv[3] && std::abs(Tgduv[3]) <= EpsUV[3] * NormDuv[2]);
  if (!tangent)
  {
    double t = N1.Dot(N2);
    if (t < 0.0)
      t = -t;
    if (t > 0.999999999)
    {
      tangent = true;
    }
  }

  if (!tangent)
  {
    NormDuv[0] = std::abs(Tgduv[1]) / NormDuv[0];
    NormDuv[1] = std::abs(Tgduv[0]) / NormDuv[1];
    NormDuv[2] = std::abs(Tgduv[3]) / NormDuv[2];
    NormDuv[3] = std::abs(Tgduv[2]) / NormDuv[3];

    bool                      triOk = false;
    double                    t;
    IntImp_ConstIsoparametric ti;
    for (i = 0; i <= 3; i++)
    {
      TabIso[i] = staticChoixRef[i];
    }
    do
    {
      triOk = true;
      for (i = 1; i <= 3; i++)
      {
        if (NormDuv[i - 1] > NormDuv[i])
        {
          triOk          = false;
          t              = NormDuv[i];
          NormDuv[i]     = NormDuv[i - 1];
          NormDuv[i - 1] = t;

          ti            = TabIso[i];
          TabIso[i]     = TabIso[i - 1];
          TabIso[i - 1] = ti;
        }
      }
    } while (!triOk);
  }
  return tangent;
}
