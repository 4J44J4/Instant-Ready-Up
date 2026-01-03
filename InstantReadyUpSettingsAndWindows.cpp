#include "pch.h"
#include "InstantReadyUp.h"

void InstantReadyUp::RenderSettings()
{
	ImGui::TextUnformatted("Button below turns plugin on and off (plugin is on by default).");
	if (pluginOn() == true)
	{
		if (ImGui::Button("ON"))
		{
			cvarManager->executeCommand("InstantReadyUp::on_off");
		}
	}
	else
	{
		if (ImGui::Button("OFF"))
		{
			cvarManager->executeCommand("InstantReadyUp::on_off");
		}
	}
}