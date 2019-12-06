/*Name: gui.cpp
Purpose: Function definitions for SimulationApp class for the GUI
Last edit: 12-3-19
Last editor: AW
Note: This is based on a Direct2D tutorial from Microsoft: https://docs.microsoft.com/en-us/windows/win32/direct2d/direct2d-quickstart*/

#include "gui.h"
#include "clock.h"
#include <chrono>

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

        HWND c_hWndx0 = CreateWindowExW(
            NULL,
            TEXT("BUTTON"),
            TEXT("Pause Simulation"),
            WS_CHILD | WS_VISIBLE,
            1050,
            10,
            170,
            25,
            m_hwnd,
            (HMENU)IDM_SET_TICK_X0,
            (HINSTANCE)GetWindowLongPtrW(m_hwnd, GWLP_HINSTANCE),
            NULL
        );

        HWND c_hWndx1 = CreateWindowExW(
            NULL,
            TEXT("BUTTON"),
            TEXT("Simulation speed x1"),
            WS_CHILD | WS_VISIBLE,
            1050,
            35,
            170,
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
            1050,
            60,
            170,
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
            1050,
            85,
            170,
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
            1050,
            110,
            170,
            25,
            m_hwnd,
            (HMENU)IDM_SET_TICK_X100,
            (HINSTANCE)GetWindowLongPtrW(m_hwnd, GWLP_HINSTANCE),
            NULL
        );

        HWND c_hWndx1000 = CreateWindowExW(
            NULL,
            TEXT("BUTTON"),
            TEXT("Simulation speed x1000"),
            WS_CHILD | WS_VISIBLE,
            1050,
            135,
            170,
            25,
            m_hwnd,
            (HMENU)IDM_SET_TICK_X1000,
            (HINSTANCE)GetWindowLongPtrW(m_hwnd, GWLP_HINSTANCE),
            NULL
        );

        HWND c_hWndStatusReport = CreateWindowExW(
            NULL,
            TEXT("BUTTON"),
            TEXT("Status Report"),
            WS_CHILD | WS_VISIBLE,
            1050,
            160,
            170,
            25,
            m_hwnd,
            (HMENU)IDM_STATUS_REPORT,
            (HINSTANCE)GetWindowLongPtrW(m_hwnd, GWLP_HINSTANCE),
            NULL
        );

        HWND c_hWndDebugging = CreateWindowExW(
            NULL,
            TEXT("BUTTON"),
            TEXT("Toggle debugging"),
            WS_CHILD | WS_VISIBLE,
            1050,
            185,
            170,
            25,
            m_hwnd,
            (HMENU)IDM_DEBUGGING,
            (HINSTANCE)GetWindowLongPtrW(m_hwnd, GWLP_HINSTANCE),
            NULL
        );
        
        hr = m_hwnd ? S_OK : E_FAIL;
        if (SUCCEEDED(hr))
        {
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
    else if(message == WM_PAINT)
    {
        PAINTSTRUCT ps;
        HDC h_device_context = BeginPaint(hwnd, &ps);
        SimulationApp *pSimulationApp = reinterpret_cast<SimulationApp*>(static_cast<LONG_PTR>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
                )));
        int tick_speed = pSimulationApp->sim.get_tick_speed();
        chrono::high_resolution_clock::time_point timer_comp = chrono::high_resolution_clock::now();
        auto time_span = chrono::duration_cast<chrono::milliseconds>(timer_comp - timer_base);
        if(tick_speed == 0)
        {
            InvalidateRect(hwnd, NULL, false);
            EndPaint(hwnd, &ps);
            return result;
        }
        if(time_span.count() >= (double)(1000/tick_speed))
        {
            pSimulationApp->OnRender();
            timer_base = chrono::high_resolution_clock::now();
        }
        InvalidateRect(hwnd, NULL, false);
        EndPaint(hwnd, &ps);
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
                    if(LOWORD(wParam) == IDM_SET_TICK_X0)
                    {
                        pSimulationApp->sim.set_tick_speed(x0);
                    }
                    else if(LOWORD(wParam) == IDM_SET_TICK_X1)
                    {
                        pSimulationApp->sim.set_tick_speed(x1);
                    }
                    else if(LOWORD(wParam) == IDM_SET_TICK_X10)
                    {
                        pSimulationApp->sim.set_tick_speed(x10);
                    }
                    else if(LOWORD(wParam) == IDM_SET_TICK_X50)
                    {
                        pSimulationApp->sim.set_tick_speed(x50);
                    }
                    else if(LOWORD(wParam) == IDM_SET_TICK_X100)
                    {
                        pSimulationApp->sim.set_tick_speed(x100);
                    }
                    else if(LOWORD(wParam) == IDM_SET_TICK_X1000)
                    {
                        pSimulationApp->sim.set_tick_speed(x1000);
                    }
                    else if(LOWORD(wParam) == IDM_DEBUGGING)
                    {
                        debugging_enabled = !debugging_enabled;
                    }
                    else if(LOWORD(wParam) == IDM_STATUS_REPORT)
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
                        vector<environment_object*> cells = pSimulationApp->sim.get_created_objects();
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
                        status_report_file << "Total number of plants: " << plants.size() << "\n";
                        for(int i = 0; i < plants.size(); i++)
                        {
                            point p_loc = plants[i]->get_loc();
                            plant* plt = reinterpret_cast<plant*>(plants[i]);
                            status_report_file << "Plant " << i+1 << ":\n";
                            status_report_file << "Max size: " << plt->get_max_size() << "\n";
                            status_report_file << "Current size: " << plt->get_current_size() << "\n";
                            status_report_file << "Location: " << p_loc.x_loc << ", " << p_loc.y_loc << "\n";
                            status_report_file << "\n";
                        }
                        status_report_file << "=========Grazer info=========\n";
                        status_report_file << "Total number of grazers: " << grazers.size() << "\n";
                        for(int i = 0; i < grazers.size(); i++)
                        {
                            point g_loc = grazers[i]->get_loc();
                            grazer* grz = reinterpret_cast<grazer*>(grazers[i]);
                            int g_energy = grz->get_energy();
                            status_report_file << "Grazer "<< i+1 << ":\n";
                            status_report_file << "Energy level required for reproduction: " << grz->get_energy_reproduce_min() << "\n";
                            status_report_file << "Location: " << g_loc.x_loc << ", " << g_loc.y_loc << "\n";
                            status_report_file << "Energy: " << g_energy << "\n";
                            status_report_file << "\n";
                        }
                        status_report_file << "=========Predator info=========\n";
                        status_report_file << "Total number of predators: " << predators.size() << "\n";
                        for(int i = 0; i < predators.size(); i++)
                        {
                            point p_loc = predators[i]->get_loc();
                            predator* prd = reinterpret_cast<predator*>(predators[i]);
                            int p_energy = prd->get_energy();
                            status_report_file << "Predator " << i+1 << ":\n";
                            status_report_file << "Energy level required for reproduction: " << prd->get_energy_reproduce_min() << "\n";
                            status_report_file << "Location: " << p_loc.x_loc << ", " << p_loc.y_loc << "\n";
                            status_report_file << "Energy: " << p_energy << "\n";
                            status_report_file << "\n";
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

void SimulationApp::DrawVisionCone(mammal* target, ID2D1SolidColorBrush* brush)
{
    vector<point> vision_cone = target->get_vision_points();
    ID2D1PathGeometry* cone;
    HRESULT hr = m_pDirect2dFactory->CreatePathGeometry(&cone);
    
    if(SUCCEEDED(hr))
    {
        ID2D1GeometrySink *pSink = NULL;

        hr = cone->Open(&pSink);
        if (SUCCEEDED(hr))
        {
            pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

            pSink->BeginFigure(
                D2D1::Point2F(vision_cone[0].x_loc, sim.get_world_height() - vision_cone[0].y_loc),
                D2D1_FIGURE_BEGIN_FILLED
                );
            D2D1_POINT_2F points[] = {
                D2D1::Point2F(vision_cone[1].x_loc, sim.get_world_height() - vision_cone[1].y_loc),
                D2D1::Point2F(vision_cone[2].x_loc, sim.get_world_height() - vision_cone[2].y_loc),
                };
            pSink->AddLines(points, ARRAYSIZE(points));
            pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
        }
        hr = pSink->Close();

        SafeRelease(&pSink);
        m_pRenderTarget->DrawGeometry(cone, brush, 2.f);
    }
}

void SimulationApp::DrawObject(environment_object* target)
{
    HRESULT hr = S_OK;

    int world_width = sim.get_world_width();
    int world_height = sim.get_world_height();
    point target_loc = target->get_loc();
    //Offset location by 5 because the grid & objects go off-screen otherwise
    D2D1_RECT_F e_obj_rect = D2D1::RectF(
        (target_loc.x_loc+5)-4.5f,
        (world_height - target_loc.y_loc+5)-4.5f,
        (target_loc.x_loc+5)+4.5f,
        (world_height - target_loc.y_loc+5)+4.5f
    );
    D2D1_RECT_F e_obj_outline_rect = D2D1::RectF(
        (target_loc.x_loc+5)-5.0f,
        (world_height - target_loc.y_loc+5)-5.0f,
        (target_loc.x_loc+5)+5.0f,
        (world_height - target_loc.y_loc+5)+5.0f
    );

    // Draw the outline of a rectangle.
    ID2D1SolidColorBrush* brush;
    std::string target_type = target->get_type();
    if(target_type == "plant" || target_type == "leaf")
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
        if(debugging_enabled)
        {
            DrawVisionCone(p_target, m_pRedBrush);
        }
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
        if(debugging_enabled)
        {
            DrawVisionCone(g_target, m_pNavyBrush);
        }
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
        if(g_target->found_food())
        {
            m_pRenderTarget->DrawRectangle(&e_obj_outline_rect, m_pGreenBrush, 2.0);
        }
        if(g_target->found_danger())
        {
            m_pRenderTarget->DrawRectangle(&e_obj_outline_rect, m_pRedBrush, 2.0);
        }
    }

    m_pRenderTarget->FillRectangle(&e_obj_rect, brush);
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
                D2D1::Point2F(static_cast<FLOAT>(x+5), 5.0f),
                D2D1::Point2F(static_cast<FLOAT>(x+5), world_height+5),
                m_pBlackBrush,
                0.5f
            );
        }

        for (int y = 0; y <= world_height; y+=10)
        {
            m_pRenderTarget->DrawLine(
                D2D1::Point2F(5.0f, static_cast<FLOAT>(y+5)),
                D2D1::Point2F(world_width+5, static_cast<FLOAT>(y+5)),
                m_pBlackBrush,
                0.5f
            );
        }
        auto start = std::chrono::high_resolution_clock::now();
        sim.iterate_cells();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        start = std::chrono::high_resolution_clock::now();
        vector<environment_object*> cells = sim.get_created_objects();
        vector<environment_object*>::iterator cell;
        for(cell = cells.begin(); cell != cells.end(); cell++)
        {
            DrawObject(*cell);
        }
        stop = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        ofstream timings;
        timings.open("timings.txt", std::ios_base::app);
        timings << "Iterate cells: ";
        timings << duration1.count();
        timings << "ms\n";
        timings << "Draw cells: ";
        timings << duration2.count();
        timings << "ms\n\n";
        timings.close();

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