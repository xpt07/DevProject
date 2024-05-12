#pragma once

// entry point
#include "include/independent/core/entrypoint.h"
#include "engine.h"

class engineApp : public Newton::Application
{
public:
	engineApp();
	~engineApp() override;
};
