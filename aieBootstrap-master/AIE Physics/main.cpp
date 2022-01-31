#include "AIE_PhysicsApp.h"

int main() {
	
	// allocation
	auto app = new AIE_PhysicsApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}