occ::handle<StepGeom_Line>           Lin = new StepGeom_Line;
occ::handle<StepGeom_CartesianPoint> aPnt;
occ::handle<StepGeom_Vector>         aDir;

GeomToStep_MakeCartesianPoint MkPoint(L.Location(), theLocalFactors.LengthFactor());
GeomToStep_MakeVector         MkVector(Vec_gen(L.Direction()), theLocalFactors);
aPnt                                       = MkPoint.Value();
aDir                                       = MkVector.Value();
occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
Lin->Init(name, aPnt, aDir);
theLine = Lin;
done    = true;
