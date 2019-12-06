/*Name: gui.h
Purpose: Definition of SimulationApp class for the GUI
Last edit: 12-3-19
Last editor: AW
Note: This is based on a Direct2D tutorial from Microsoft: https://docs.microsoft.com/en-us/windows/win32/direct2d/direct2d-quickstart*/

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <fstream>
#include <chrono>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include "Resources.h"
#include "simulation.h"
#include "predator.h"
#include "grazer.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "d2d1.lib")

template<class Interface>
inline void SafeRelease(
    Interface** ppInterfaceToRelease
    )
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = NULL;
    }
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class SimulationApp
{
    public:
        SimulationApp();
        ~SimulationApp();

        // Register the window class and call methods for instantiating drawing resources
        HRESULT Initialize();

        // Process and dispatch messages
        void RunMessageLoop();

    private:
        // Initialize device-independent resources.
        HRESULT CreateDeviceIndependentResources();

        // Initialize device-dependent resources.
        HRESULT CreateDeviceResources();

        // Release device-dependent resource.
        void DiscardDeviceResources();

        // Draw content.
        HRESULT OnRender();

        void DrawObject(environment_object*);

        // Resize the render target.
        void OnResize(
            UINT width,
            UINT height
            );

        // The windows procedure.
        static LRESULT CALLBACK WndProc(
            HWND hWnd,
            UINT message,
            WPARAM wParam,
            LPARAM lParam
            );

        void DrawVisionCone(mammal* target, ID2D1SolidColorBrush*);

        HWND m_hwnd;
        ID2D1Factory* m_pDirect2dFactory;
        ID2D1HwndRenderTarget* m_pRenderTarget;
        //Black brush for gridlines
        ID2D1SolidColorBrush* m_pBlackBrush;
        //Grey brush for obstacles
        ID2D1SolidColorBrush* m_pGreyBrush;
        //Green brush for plants
        ID2D1SolidColorBrush* m_pGreenBrush;
        //Yellow brush for seeds
        ID2D1SolidColorBrush* m_pYellowBrush;
        //Cyan, teal, and navy brushes for grazers
        ID2D1SolidColorBrush* m_pCyanBrush;
        ID2D1SolidColorBrush* m_pTealBrush;
        ID2D1SolidColorBrush* m_pNavyBrush;
        //Red, orange, and maroon brushes for predators
        ID2D1SolidColorBrush* m_pRedBrush;
        ID2D1SolidColorBrush* m_pOrangeBrush;
        ID2D1SolidColorBrush* m_pMaroonBrush;
        static bool debugging_enabled;
        
        simulation sim;

        static chrono::high_resolution_clock::time_point timer_base;
};

bool SimulationApp::debugging_enabled = false;
chrono::high_resolution_clock::time_point SimulationApp::timer_base = chrono::high_resolution_clock::now();