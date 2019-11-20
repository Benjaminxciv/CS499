/*Name: gui.cpp
Purpose: Function definitions for SimulationApp class for the GUI
Last edit: 10-27-19
Last editor: AW
Note: This is based on a Direct2D tutorial from Microsoft: https://docs.microsoft.com/en-us/windows/win32/direct2d/direct2d-quickstart*/

#include "gui.h"

SimulationApp::SimulationApp() :
        m_hwnd(NULL),
        m_pDirect2dFactory(NULL),
        m_pRenderTarget(NULL),
        m_pBlackBrush(NULL),
        m_pGreyBrush(NULL),
        m_pGreenBrush(NULL),
        m_pYellowBrush(NULL),
        m_pCyanBrush(NULL),
        m_pTealBrush(NULL),
        m_pNavyBrush(NULL),
        m_pOrangeBrush(NULL),
        m_pRedBrush(NULL),
        m_pMaroonBrush(NULL),
        sim()
{

}

    
SimulationApp::~SimulationApp()
{
    SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pGreyBrush);
    SafeRelease(&m_pGreenBrush);
    SafeRelease(&m_pYellowBrush);
    SafeRelease(&m_pCyanBrush);
    SafeRelease(&m_pTealBrush);
    SafeRelease(&m_pNavyBrush);
    SafeRelease(&m_pOrangeBrush);
    SafeRelease(&m_pRedBrush);
    SafeRelease(&m_pMaroonBrush);
}

void SimulationApp::RunMessageLoop()
{
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HRESULT SimulationApp::Initialize()
{
    HRESULT hr;

    this->sim.init_sim();

    // Initialize device-indpendent resources, such
    // as the Direct2D factory.
    hr = CreateDeviceIndependentResources();

    if (SUCCEEDED(hr))
    {
        // Register the window class.
        WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
        wcex.style         = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc   = SimulationApp::WndProc;
        wcex.cbClsExtra    = 0;
        wcex.cbWndExtra    = sizeof(LONG_PTR);
        wcex.hInstance     = HINST_THISCOMPONENT;
        wcex.hbrBackground = NULL;
        wcex.lpszMenuName  = NULL;
        wcex.hCursor       = LoadCursor(NULL, IDI_APPLICATION);
        wcex.lpszClassName = L"D2DSimulationApp";

        RegisterClassEx(&wcex);


        // Because the CreateWindow function takes its size in pixels,
        // obtain the system DPI and use it to scale the window size.
        FLOAT dpiX, dpiY;

        // The factory returns the current system DPI. This is also the value it will use
        // to create its own windows.
        m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);


        // Create the window.
        m_hwnd = CreateWindow(
            L"D2DSimulationApp",
            L"Direct2D Simulation App",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<UINT>(ceil(1600.f * dpiX / 96.f)),
            static_cast<UINT>(ceil(1200.f * dpiY / 96.f)),
            NULL,
            NULL,
            HINST_THISCOMPONENT,
            this
            );
        hr = m_hwnd ? S_OK : E_FAIL;
        if (SUCCEEDED(hr))
        {
            int tick_speed = sim.get_tick_speed();
            SetTimer(m_hwnd, 1, tick_speed, NULL); 
            ShowWindow(m_hwnd, SW_SHOWNORMAL);
            UpdateWindow(m_hwnd);
        }
    }

    return hr;
}

int WINAPI WinMain(
        HINSTANCE /* hInstance */,
        HINSTANCE /* hPrevInstance */,
        LPSTR /* lpCmdLine */,
        int /* nCmdShow */
        )
{
    // Use HeapSetInformation to specify that the process should
    // terminate if the heap manager detects an error in any heap used
    // by the process.
    // The return value is ignored, because we want to continue running in the
    // unlikely event that HeapSetInformation fails.
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    if (SUCCEEDED(CoInitialize(NULL)))
    {
        {
            SimulationApp app;

            if (SUCCEEDED(app.Initialize()))
            {
                app.RunMessageLoop();
            }
        }
        CoUninitialize();
    }

    return 0;
}

HRESULT SimulationApp::CreateDeviceIndependentResources()
{
    HRESULT hr = S_OK;

    // Create a Direct2D factory.
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

    return hr;
}

HRESULT SimulationApp::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    if (!m_pRenderTarget)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(
            rc.right - rc.left,
            rc.bottom - rc.top
            );

        // Create a Direct2D render target.
        hr = m_pDirect2dFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &m_pRenderTarget
            );

        if (SUCCEEDED(hr))
        {
            m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(0,0,0,1),
                &m_pBlackBrush
            );
            m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(0.5,0.5,0.5,1),
                &m_pGreyBrush
            );
            m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(0,1,0,1),
                &m_pGreenBrush
            );
            m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(1,1,0,1),
                &m_pYellowBrush
            );
            m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(0,1,1,1),
                &m_pCyanBrush
            );
            m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(0,0.5,1,1),
                &m_pTealBrush
            );
            m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(0,0,1,1),
                &m_pNavyBrush
            );
            m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(1,0.5,0,1),
                &m_pOrangeBrush
            );
            m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(1,0,0,1),
                &m_pRedBrush
            );
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(0.5,0,0,1),
                &m_pMaroonBrush
            );
        }
    }

    return hr;
}

void SimulationApp::DiscardDeviceResources()
{
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pGreyBrush);
    SafeRelease(&m_pGreenBrush);
    SafeRelease(&m_pYellowBrush);
    SafeRelease(&m_pCyanBrush);
    SafeRelease(&m_pTealBrush);
    SafeRelease(&m_pNavyBrush);
    SafeRelease(&m_pOrangeBrush);
    SafeRelease(&m_pRedBrush);
    SafeRelease(&m_pMaroonBrush);
}

LRESULT CALLBACK SimulationApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        SimulationApp *pSimulationApp = (SimulationApp*)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            PtrToUlong(pSimulationApp)
            );

        result = 1;
    }
    else if (message == WM_TIMER)
    {
        SimulationApp *pSimulationApp = reinterpret_cast<SimulationApp*>(static_cast<LONG_PTR>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
                )));

        if (pSimulationApp)
        {
            pSimulationApp->OnRender();
        }
    }
    else
    {
        SimulationApp *pSimulationApp = reinterpret_cast<SimulationApp*>(static_cast<LONG_PTR>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
                )));

        bool wasHandled = false;

        if (pSimulationApp)
        {
            switch (message)
            {
            case WM_SIZE:
                {
                    UINT width = LOWORD(lParam);
                    UINT height = HIWORD(lParam);
                    pSimulationApp->OnResize(width, height);
                }
                result = 0;
                wasHandled = true;
                break;

            case WM_DISPLAYCHANGE:
                {
                    InvalidateRect(hwnd, NULL, FALSE);
                }
                result = 0;
                wasHandled = true;
                break;

            case WM_PAINT:
                {
                    pSimulationApp->OnRender();
                    ValidateRect(hwnd, NULL);
                }
                result = 0;
                wasHandled = true;
                break;

            case WM_DESTROY:
                {
                    PostQuitMessage(0);
                }
                result = 1;
                wasHandled = true;
                break;
            }
        }

        if (!wasHandled)
        {
            result = DefWindowProc(hwnd, message, wParam, lParam);
        }
    }

    return result;
}

void SimulationApp::DrawObject(environment_object* target)
{
    HRESULT hr = S_OK;
    point target_loc = target->get_loc();
    D2D1_RECT_F rectangle2 = D2D1::RectF(
        target_loc.x_loc-5.0f,
        target_loc.y_loc-5.0f,
        target_loc.x_loc+5.0f,
        target_loc.y_loc+5.0f
    );

    // Draw the outline of a rectangle.
    ID2D1SolidColorBrush* brush;
    std::string target_type = target->get_type();
    if(target_type == "plant")
    {
        brush = m_pGreenBrush;
    }
    else if(target_type == "seed")
    {
        brush = m_pYellowBrush;
    }
    //How do I explain this...
    //Seeds take 2 ticks to grow into a plant
    //This no longer happens, but leaving just in case
    else if(target_type == "")
    {
        brush = m_pBlackBrush;
    }
    else if(target_type == "boulder")
    {
        brush = m_pGreyBrush;
    }
    else if(target_type == "predator")
    {
        predator* p_target = reinterpret_cast<predator*>(target);
        if(p_target->ready_to_reproduce())
        {
            brush = m_pRedBrush;
        }
        else if(p_target->get_energy() <= 25)
        {
            brush = m_pMaroonBrush;
        }
        else
        {
            brush = m_pOrangeBrush;
        }
    }
    else if(target_type == "grazer")
    {
        grazer* g_target = reinterpret_cast<grazer*>(target);
        if(g_target->ready_to_reproduce())
        {
            brush = m_pCyanBrush;
        }
        else if(g_target->get_energy() <= 25)
        {
            brush = m_pNavyBrush;
        }
        else
        {
            brush = m_pTealBrush;
        }
    }
    m_pRenderTarget->FillRectangle(&rectangle2, brush);
}

HRESULT SimulationApp::OnRender()
{
    HRESULT hr = S_OK;

    hr = CreateDeviceResources();
    if (SUCCEEDED(hr))
    {
        m_pRenderTarget->BeginDraw();

        m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

        //D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

        // Draw a grid background.
        //int width = static_cast<int>(rtSize.width);
        //int height = static_cast<int>(rtSize.height);

        int world_width = sim.get_world_width();
        int world_height = sim.get_world_height();
        for (int x = 0; x <= world_width; x+=10)
        {
            m_pRenderTarget->DrawLine(
                D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
                //D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
                D2D1::Point2F(static_cast<FLOAT>(x), world_height),
                m_pBlackBrush,
                0.5f
            );
        }

        for (int y = 0; y <= world_height; y+=10)
        {
            m_pRenderTarget->DrawLine(
                D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
                D2D1::Point2F(world_width, static_cast<FLOAT>(y)),
                m_pBlackBrush,
                0.5f
            );
        }
        std::vector<environment_object*> cells = sim.iterate_cells();
        for(int i = 0; i < cells.size(); i++)
        {
            DrawObject(cells[i]);
        }

        hr = m_pRenderTarget->EndDraw();
    }
    if (hr == D2DERR_RECREATE_TARGET)
    {
        hr = S_OK;
        DiscardDeviceResources();
    }
    
    return hr;
}

void SimulationApp::OnResize(UINT width, UINT height)
{
    if (m_pRenderTarget)
    {
        // Note: This method can fail, but it's okay to ignore the
        // error here, because the error will be returned again
        // the next time EndDraw is called.
        m_pRenderTarget->Resize(D2D1::SizeU(width, height));
    }
}