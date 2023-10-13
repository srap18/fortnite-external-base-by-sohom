#pragma once
#ifndef OVERLAY
#define OVERLAY

//#include "../../../../includes.hpp"
//#include "../../framework/imgui/imgui_impl_win32.cpp"
#include "../entity.hpp"

#include <dxgi.h>
#include <d3d11.h>

ID3D11Device* g_pd3dDevice;
ID3D11DeviceContext* g_pd3dDeviceContext;
IDXGISwapChain* g_pSwapChain;
ID3D11RenderTargetView* g_mainRenderTargetView;

HWND window;

namespace DirectX
{
	class DirectX11
	{
	public:

		__forceinline auto hijack() -> bool
		{
			return false;
		}

		LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
				return true;

			switch (msg)
			{
			case WM_SIZE:
				if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
				{
					cleanrender();
					g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
					createrender();
				}
				return 0;
			case WM_SYSCOMMAND:
				if ((wParam & 0xfff0) == SC_KEYMENU)
					return 0;
				break;
			case WM_DESTROY:
				::PostQuitMessage(0);
				return 0;
			}
			return ::DefWindowProc(hWnd, msg, wParam, lParam);
		}

		__forceinline void createrender()
		{
			ID3D11Texture2D* pBackBuffer;
			g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
			g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
			pBackBuffer->Release();
		}

		__forceinline void cleanrender()
		{
			if (g_mainRenderTargetView)
			{
				g_mainRenderTargetView->Release();
				g_mainRenderTargetView = NULL;
			}
		}

		void cleand3d()
		{
			cleanrender();
			if (g_pSwapChain)
			{
				g_pSwapChain->Release(); g_pSwapChain = NULL;
			}
			if (g_pd3dDeviceContext)
			{
				g_pd3dDeviceContext->Release();
				g_pd3dDeviceContext = NULL;
			}
			if (g_pd3dDevice)
			{
				g_pd3dDevice->Release();
				g_pd3dDevice = NULL;
			}
		}

		__forceinline auto initiate() -> bool
		{
			DXGI_SWAP_CHAIN_DESC SwapChainDesc;
			ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
			SwapChainDesc.Windowed = TRUE;
			SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
			SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
			SwapChainDesc.BufferDesc.Height = 0;
			SwapChainDesc.BufferDesc.Width = 0;
			SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			SwapChainDesc.BufferCount = 1;
			SwapChainDesc.OutputWindow = window;
			SwapChainDesc.SampleDesc.Count = 8;
			SwapChainDesc.SampleDesc.Quality = 0;

			UINT createDeviceFlags = 0;
			D3D_FEATURE_LEVEL featureLevel;
			const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
			if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &SwapChainDesc, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
			{
				return false;
			}

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			ImGui::SetNextWindowSize(io.DisplaySize);
			io.IniFilename = NULL;

			ImGuiStyle& style = ImGui::GetStyle();
			auto color = style.Colors;

			color[ImGuiCol_WindowBg] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_ChildBg] = ImColor(35, 35, 35, 255);
			color[ImGuiCol_Border] = ImColor(25, 25, 25, 255);
			color[ImGuiCol_BorderShadow] = ImColor(50, 50, 50, 255);
			color[ImGuiCol_Button] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_ButtonActive] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_ButtonHovered] = ImColor(25, 25, 25, 255);
			color[ImGuiCol_ScrollbarBg] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_ScrollbarGrab] = ImColor(95, 75, 113, 255);
			color[ImGuiCol_ScrollbarGrabActive] = ImColor(95, 75, 113, 255);
			color[ImGuiCol_ScrollbarGrabHovered] = ImColor(95, 75, 113, 255);
			color[ImGuiCol_CheckMark] = ImColor(130, 60, 180, 255);
			color[ImGuiCol_FrameBg] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_SliderGrab] = ImColor(95, 75, 113, 255);
			color[ImGuiCol_SliderGrabActive] = ImColor(95, 75, 113, 255);
			color[ImGuiCol_PlotLines] = ImColor(130, 60, 180, 255);
			color[ImGuiCol_PlotLinesHovered] = ImColor(130, 60, 180, 255);
			color[ImGuiCol_PlotHistogram] = ImColor(130, 60, 180, 255);
			color[ImGuiCol_PlotHistogramHovered] = ImColor(130, 60, 180, 255);
			color[ImGuiCol_TabActive] = ImColor(130, 60, 180, 255);
			color[ImGuiCol_TabUnfocusedActive] = ImColor(130, 60, 180, 255);
			color[ImGuiCol_Header] = ImColor(95, 75, 113, 255);
			color[ImGuiCol_HeaderActive] = ImColor(95, 75, 113, 255);
			color[ImGuiCol_HeaderHovered] = ImColor(95, 75, 113, 255);
			color[ImGuiCol_TitleBg] = ImColor(130, 60, 180, 255);
			color[ImGuiCol_FrameBgActive] = ImColor(130, 60, 180, 255);
			color[ImGuiCol_TitleBgActive] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_TitleBgCollapsed] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_PopupBg] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_TextSelectedBg] = ImColor(130, 60, 180, 255);
			color[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
			color[ImGuiCol_TextDisabled] = ImColor(255, 255, 255, 255);
			color[ImGuiCol_NavHighlight] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_NavWindowingHighlight] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_NavWindowingDimBg] = ImColor(40, 40, 40, 255);
			color[ImGuiCol_ModalWindowDimBg] = ImColor(40, 40, 40, 255);

			style.WindowTitleAlign = ImVec2(0.5, 0.5);
			style.WindowBorderSize = 1.0;

			style.ChildRounding = 0;
			style.FrameRounding = 0;
			style.ScrollbarRounding = 0;
			style.GrabRounding = 0;
			style.PopupRounding = 0;
			style.WindowRounding = 0;

			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

			ID3D11Texture2D* pBackBuffer;

			g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

			g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);

			ImGui_ImplWin32_Init(window);

			ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

			pBackBuffer->Release();

			//SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}

		__forceinline auto init() -> void
		{
			LPDIRECT3D9              g_pD3D = NULL;
			LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;
			D3DPRESENT_PARAMETERS    g_d3dpp = {};
			auto& io = ImGui::GetIO();
			auto& style = ImGui::GetStyle();

			io.MouseDrawCursor = false;

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			entity->loop();

			menu();

			ImGui::Render();
			ImVec4 clear_color = ImVec4(0., 0., 0., 0.);
			g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
			g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
			g_d3dpp.FullScreen_RefreshRateInHz = true;

			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			g_pSwapChain->Present(1, 0);
		}

		__forceinline auto draw() -> bool
		{
			static RECT old_rc;
			MSG Message = { NULL };
			ZeroMemory(&Message, sizeof(MSG));
			while (Message.message != WM_QUIT)
			{
				if (PeekMessage(&Message, window, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				ImGuiIO& io = ImGui::GetIO(); (void)io;
				POINT p;
				POINT xy;
				GetCursorPos(&p);
				io.MousePos.x = p.x;
				io.MousePos.y = p.y;
				if (GetAsyncKeyState(VK_LBUTTON)) {
					io.MouseDown[0] = true;
					io.MouseClicked[0] = true;
					io.MouseClickedPos[0].x = io.MousePos.x;
					io.MouseClickedPos[0].x = io.MousePos.y;
				}
				else
					io.MouseDown[0] = false;

				init();
			}

			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();
			cleand3d();
			DestroyWindow(window);
			return Message.wParam;
		}

		__forceinline auto menu() -> void
		{
			ImGui::Begin("##LEFT", nullptr, ImGuiWindowFlags_NoDecoration);
			{
				ImGui::BeginChild("##LEFTinside", ImVec2(400, 400), ImGuiWindowFlags_NoDecoration);
				{
				}
			}
			ImGui::End();
			ImGui::PopStyleVar();
		}
	};
}
static DirectX::DirectX11* render = new DirectX::DirectX11();

#endif