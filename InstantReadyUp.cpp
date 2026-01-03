#include "pch.h"
#include "InstantReadyUp.h"


BAKKESMOD_PLUGIN(InstantReadyUp, "write a plugin description here", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

int tracker1 = 0;
int tracker2 = 0;
bool pluginActive = true;
bool readyUpHasHappened = false;

void InstantReadyUp::onLoad()
{
	_globalCvarManager = cvarManager;

	cvarManager->registerNotifier("InstantReadyUp::on_off", [this](std::vector<std::string> args) {
		if (pluginActive)
			pluginActive = false;
		else
			pluginActive = true;
		}, "", PERMISSION_ALL);

	this->loadHooks();
}

bool InstantReadyUp::pluginOn()
{
	if (pluginActive)
		return true;
	else
		return false;
}

void InstantReadyUp::readyUp()
{
	cvarManager->executeCommand("unreal_command ReadyUp");
}

void InstantReadyUp::loadHooks()
{
	gameWrapper->HookEvent("Function TAGame.GFxData_Chat_TA.HandleGameEnded",
		[this](std::string eventName) {
			if (pluginActive)
				tracker1 = 1;
		});

	gameWrapper->HookEvent("Function TAGame.PRI_TA.IsSpectator",
		[this](std::string eventName) {
			if (pluginActive)
				if (tracker1 >= 1)
				{
					tracker2++;
					if (tracker2%100 == 0)
						readyUp();
				}
		});

	gameWrapper->HookEvent("Function ProjectX.GRI_X.EventGameStarted",
		[this](std::string eventName) {
			tracker1 = 0;
			tracker2 = 0;
		});
}