occ::handle<StepGeom_Vector>    Vect = new StepGeom_Vector;
occ::handle<StepGeom_Direction> aDirection;
double                          aMagnitude;

GeomToStep_MakeDirection MkDir(D);
aDirection                                 = MkDir.Value();
aMagnitude                                 = V.Magnitude();
occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
Vect->Init(name, aDirection, aMagnitude / lFactor);
theVector = Vect;
done      = true;
