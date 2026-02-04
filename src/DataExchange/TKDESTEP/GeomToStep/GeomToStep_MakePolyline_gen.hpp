int                                                                    N, i;
occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> aPoints;
occ::handle<StepGeom_CartesianPoint>                                   P2;

N       = P.Length();
aPoints = new NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>(1, N);
for (i = P.Lower(); i <= P.Upper(); i++)
{
  P1 = P.Value(i);
  GeomToStep_MakeCartesianPoint MkPoint(P1, theLocalFactors.LengthFactor());
  P2 = MkPoint.Value();
  aPoints->SetValue(i, P2);
}
thePolyline                                = new StepGeom_Polyline;
occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
thePolyline->Init(name, aPoints);
done = true;
