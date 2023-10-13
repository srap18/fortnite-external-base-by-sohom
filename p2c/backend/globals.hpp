#pragma once
#ifndef GLOBALS
#define GLOBALS

//namespace globals
//{
//	uintptr_t imagebase;
//	int width, height;
//
//	int refreshrate = 10;
//
//	bool visibilitycheck = true;
//
//	bool developermode = true;
//
//	namespace aimbot
//	{
//		bool enable = true;
//
//		int key;
//
//		bool fov = true;
//		bool filledfov = true;
//		float fovsize = 50;
//		float smoothing = 12;
//	}
//
//	namespace visuals
//	{
//		bool enable = true;
//
//		bool regular = true;
//		bool filled = true;
//		bool skeleton = true;
//
//		bool playerdetails = true;
//		bool distance = true;
//		bool platform = true;
//		bool weapon = true;
//		bool username = true;
//	}
//
//	namespace colours
//	{
//		float fov[4] = { 255, 0 , 0 , 255 };
//		float regularbox[4] = { 255, 0 , 0 , 255 };
//		float skeleton[4] = { 255, 0 , 0 , 255 };
//		float visible[4] = { 255, 0 , 0 , 255 };
//		float invisible[4] = { 255, 0 , 0 , 255 };
//	}
//}

namespace globalsdef
{
	class main
	{
	public:
		uintptr_t imagebase;
		int width, height;

		bool visibilitycheck = true;
		bool developermode = true;
	};

	class aimbot
	{
	public:
		bool enable = true;

		int key;

		bool fov = true;
		bool filledfov = true;
		float fovsize = 50;
		float smoothing = 12;
	};

	class visual
	{
	public:
		bool enable = true;

		bool regular = true;
		bool filled = true;
		bool skeleton = true;

		bool playerdetails = true;
		bool distance = true;
		bool platform = true;
		bool weapon = true;
		bool username = true;
	};

	class colours
	{
	public:
		float fov[4] = { 255, 0 , 0 , 255 };
		float regularbox[4] = { 255, 0 , 0 , 255 };
		float skeleton[4] = { 255, 0 , 0 , 255 };
		float visible[4] = { 255, 0 , 0 , 255 };
		float invisible[4] = { 255, 0 , 0 , 255 };
	};

	class exploits
	{
	public:
		bool fovslider = true;
	};

	class misc
	{
	public:
		bool crosshair = true;
		bool watermark = true;
	};
};

static globalsdef::main* globals = new globalsdef::main();
static globalsdef::aimbot* aimbot = new globalsdef::aimbot();
static globalsdef::visual* visuals = new globalsdef::visual();
static globalsdef::colours* colours = new globalsdef::colours();
static globalsdef::exploits* exploits = new globalsdef::exploits();
static globalsdef::misc* misc = new globalsdef::misc();

#endif

