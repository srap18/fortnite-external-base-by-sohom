#pragma once
#ifndef MOUSE
#define MOUSE

#include "../../framework/imgui/imgui.h"
#include "../../globals.hpp"
#include "movement/mouse.hpp"

static auto aimfunction(float x, float y) -> void
{
	float CenterX = (ImGui::GetIO().DisplaySize.x / 2);
	float CenterY = (ImGui::GetIO().DisplaySize.y / 2);

	float Smoothness = aimbot->smoothing;

	float TargetX = 0.f;
	float TargetY = 0.f;

	if (x != 0.f)
	{
		if (x > CenterX)
		{
			TargetX = -(CenterX - x);
			TargetX /= Smoothness;
			if (TargetX + CenterX > CenterX * 2.f) TargetX = 0.f;
		}

		if (x < CenterX)
		{
			TargetX = x - CenterX;
			TargetX /= Smoothness;
			if (TargetX + CenterX < 0.f) TargetX = 0.f;
		}
	}

	if (y != 0.f)
	{
		if (y > CenterY)
		{
			TargetY = -(CenterY - y);
			TargetY /= Smoothness;
			if (TargetY + CenterY > CenterY * 2.f) TargetY = 0.f;
		}

		if (y < CenterY)
		{
			TargetY = y - CenterY;
			TargetY /= Smoothness;
			if (TargetY + CenterY < 0.f) TargetY = 0.f;
		}
	}

	Mouse::NtInjectMouse((int)TargetX, (int)(TargetY));

}

#endif 
