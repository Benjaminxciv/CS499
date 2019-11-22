/*Name: gui.cpp
Purpose: Function definitions for SimulationApp class for the GUI
Last edit: 10-27-19
Last editor: AW
Note: This is based on a Direct2D tutorial from Microsoft: https://docs.microsoft.com/en-us/windows/win32/direct2d/direct2d-quickstart*/

#include "gui.h"
#include "clock.h"

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
            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<UINT>(ceil(1600.f * dpiX / 96.f)),
            static_cast<UINT>(ceil(1200.f * dpiY / 96.f)),
            NULL,
            NULL,
            HINST_THISCOMPONENT,
            this
        );

        HWND c_hWndx1 = CreateWindowExW(
            NULL,
            TEXT("BUTTON"),
            TEXT("Simulation speed x1"),
            WS_CHILD | WS_VISIBLE,
            1000,
            10,
            150,
            25,
            m_hwnd,
            (HMENU)IDM_SET_TICK_X1,
            (HINSTANCE)GetWindowLongPtrW(m_hwnd, GWLP_HINSTANCE),
            NULL
        );

        HWND c_hWndx10 = CreateWindowExW(
            NULL,
            TEXT("BUTTON"),
            TEXT("Simulation speed x10"),
            WS_CHILD | WS_VISIBLE,
            1000,
            35,
            150,
            25,
            m_hwnd,
            (HMENU)IDM_SET_TICK_X10,
            (HINSTANCE)GetWindowLongPtrW(m_hwnd, GWLP_HINSTANCE),
            NULL
        );

        HWND c_hWndx50 = CreateWindowExW(
            NULL,
            TEXT("BUTTON"),
            TEXT("Simulation speed x50"),
            WS_CHILD | WS_VISIBLE,
            1000,
            60,
            150,
            25,
            m_hwnd,
            (HMENU)IDM_SET_TICK_X50,
            (HINSTANCE)GetWindowLongPtrW(m_hwnd, GWLP_HINSTANCE),
            NULL
        );

        HWND c_hWndx100 = CreateWindowExW(
            NULL,
            TEXT("BUTTON"),
            TEXT("Simulation speed x100"),
            WS_CHILD | WS_VISIBLE,
            1000,
            85,
            150,
            25,
            m_hwnd,
            (HMENU)IDM_SET_TICK_X100,
            (HINSTANCE)GetWindowLongPtrW(m_hwnd, GWLP_HINSTANCE),
            NULL
        );

        HWND c_hWndStatusReport = CreateWindowExW(
            NULL,
            TEXT("BUTTON"),
            TEXT("Status Report"),
            WS_CHILD | WS_VISIBLE,
            1000,
            110,
            150,
            25,
            m_hwnd,
            (HMENU)IDM_STATUS_REPORT,
            (HINSTANCE)GetWindowLongPtrW(m_hwnd, GWLP_HINSTANCE),
            NULL
        );
        
        hr = m_hwnd ? S_OK : E_FAIL;
        if (SUCCEEDED(hr))
        {
            SetTimer(m_hwnd, SIM_TIMER_X1, 1000, NULL); 
            SetTimer(m_hwnd, SIM_TIMER_X10, 100, NULL); 
            SetTimer(m_hwnd, SIM_TIMER_X50, 20, NULL); 
            SetTimer(m_hwnd, SIM_TIMER_X100, 10, NULL); 
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
            switch (wParam)
            {
                case SIM_TIMER_X1:
                    int tick_speed = pSimulationApp->sim.get_tick_speed();
                    if(tick_speed == x1)
                    {
                        pSimulationApp->OnRender();
                        ValidateRect(hwnd, NULL);
                    }
                    break;
                case SIM_TIMER_X10:
                    if(tick_speed == x10)
                    {
                        pSimulationApp->OnRender();
                        ValidateRect(hwnd, NULL);
                    }
                    break;
                case SIM_TIMER_X50:
                    if(tick_speed == x50)
                    {
                        pSimulationApp->OnRender();
                        ValidateRect(hwnd, NULL);
                    }
                    break;
                case SIM_TIMER_X100:
                    if(tick_speed == x100)
                    {
                        pSimulationApp->OnRender();
                        ValidateRect(hwnd, NULL);
                    }
                    break;
            }
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
                case WM_COMMAND:
                    if(LOWORD(wParam) == IDM_SET_TICK_X1)
                    {
                        pSimulationApp->sim.set_tick_speed(x1);
                    }
                    if(LOWORD(wParam) == IDM_SET_TICK_X10)
                    {
                        pSimulationApp->sim.set_tick_speed(x10);
                    }
                    if(LOWORD(wParam) == IDM_SET_TICK_X50)
                    {
                        pSimulationApp->sim.set_tick_speed(x50);
                    }
                    if(LOWORD(wParam) == IDM_SET_TICK_X100)
                    {
                        pSimulationApp->sim.set_tick_speed(x100);
                    }
                    if(LOWORD(wParam) == IDM_STATUS_REPORT)
                    {
                        time_container curr_time = pSimulationApp->sim.get_simulation_time();

                        ofstream status_report_file;
                        std::string filename = "SimReport_";
                        std::string curr_time_hour = std::to_string(curr_time.time_hour);
                        if(curr_time_hour.size() < 2)
                        {
                            curr_time_hour = "0" + curr_time_hour;
                        }
                        std::string curr_time_min = std::to_string(curr_time.time_min);
                        if(curr_time_min.size() < 2)
                        {
                            curr_time_min = "0" + curr_time_min;
                        }
                        std::string curr_time_sec = std::to_string(curr_time.time_sec);
                        if(curr_time_sec.size() < 2)
                        {
                            curr_time_sec = "0" + curr_time_sec;
                        }
                        filename += curr_time_hour + "_";
                        filename += curr_time_min + "_";
                        filename += curr_time_sec + ".txt";
                        status_report_file.open(filename);
                        vector<environment_object*> cells = pSimulationApp->sim.iterate_cells(true);
                        vector<environment_object*> plants;
                        vector<environment_object*> grazers;
                        vector<environment_object*> predators;
                        for(int i = 0; i < cells.size(); i++)
                        {
                            if(cells[i]->get_type() == "plant")
                            {
                                plants.push_back(cells[i]);
                            }
                            else if(cells[i]->get_type() == "grazer")
                            {
                                grazers.push_back(cells[i]);
                            }
                            else if(cells[i]->get_type() == "predator")
                            {
                                predators.push_back(cells[i]);
                            }
                        }
                        status_report_file << "=========Plant info=========\n";
                        for(int i = 0; i < plants.size(); i++)
                        {
                            point p_loc = plants[i]->get_loc();
                            status_report_file << "Plant " + std::to_string(i+1) + ":\n";
                            status_report_file << "Location: " + std::to_string(p_loc.x_loc) + ", " + std::to_string(p_loc.y_loc) + "\n";
                            status_report_file << "\n";
                        }
                        status_report_file << "=========Grazer info=========\n";
                        for(int i = 0; i < grazers.size(); i++)
                        {
                            point g_loc = grazers[i]->get_loc();
                            grazer* grz = reinterpret_cast<grazer*>(grazers[i]);
                            int g_energy = grz->get_energy();
                            status_report_file << "Grazer " + std::to_string(i+1) + ":\n";
                            status_report_file << "Location: " + std::to_string(g_loc.x_loc) + ", " + std::to_string(g_loc.y_loc) + "\n";
                            status_report_file << "Energy: " + std::to_string(g_energy) + "\n";
                            status_report_file << "\n";
                        }
                        status_report_file << "=========Predator info=========\n";
                        for(int i = 0; i < predators.size(); i++)
                        {
                            point p_loc = predators[i]->get_loc();
                            predator* prd = reinterpret_cast<predator*>(predators[i]);
                            int p_energy = prd->get_energy();
                            status_report_file << "Predator " + std::to_string(i+1) + ":\n";
                            status_report_file << "Location: " + std::to_string(p_loc.x_loc) + ", " + std::to_string(p_loc.y_loc) + "\n";
                            status_report_file << "Energy: " + std::to_string(p_energy) + "\n";
                        }
                        status_report_file.close();
                    }
                    break;
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