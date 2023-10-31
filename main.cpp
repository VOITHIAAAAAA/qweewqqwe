#include <wx-3.0/wx/wx.h>
#include "pomodoro.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        // Create an instance of the main frame
        MyFrame* frame = new MyFrame("Pomodoro");

        // Show the frame
        frame->Show(true);

        // Set the top window (main window)
        SetTopWindow(frame);

        return true;
    }
};

wxIMPLEMENT_APP(MyApp);