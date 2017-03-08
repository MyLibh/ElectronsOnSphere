#pragma once

#include "Graphics\Graphics.hpp"
#include "Physics\Physics.hpp"

class App final : public NoncopyableFull
{
private:
	Graphics graphics_;
	physics::Physics  physics_;

public:
	App(HINSTANCE);
	~App() { DBG("Closing app"); }

	VOID update(FLOAT);
	INT run(); 
	BOOL init() { return graphics_.init(); };
};