#define MAX_PARKPOINT 300

enum    E_PARK
{
	// loaded from db
	Float: parkX,
	Float: parkY,
	Float: parkZ,
	Float: parkA,
	parkInt,
	parkWorld,
	// temp
	parkActor,
	Text3D: parkLabel,
	parkMap,
    Float: spawn[4]
}

new GarkotData[MAX_PARKPOINT][E_PARK],
	Iterator:Parks<MAX_PARKPOINT>;
