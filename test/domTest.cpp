#include <iostream>
#include <dae.h>

using namespace std;

bool loadFile() {
	DAE dae;
	return dae.load("/home/sthomas/models/cube.dae") == DAE_OK;
}

int main() {
	cout << (loadFile() ? "succeeded\n" : "failed\n");
	return 0;
}
