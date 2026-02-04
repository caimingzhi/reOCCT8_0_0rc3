occ::handle<StepGeom_Axis1Placement> Axe = new StepGeom_Axis1Placement;
occ::handle<StepGeom_CartesianPoint> P;
occ::handle<StepGeom_Direction>      D;

GeomToStep_MakeCartesianPoint MkPoint(A.Location(), theLocalFactors.LengthFactor());
GeomToStep_MakeDirection      MkDir(A.Direction());

P = MkPoint.Value();
D = MkDir.Value();
Axe->SetLocation(P);
Axe->SetAxis(D);
occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
Axe->SetName(name);
theAxis1Placement = Axe;
done              = true;
