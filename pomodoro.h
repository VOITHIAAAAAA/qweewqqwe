#include <wx-3.0/wx/wx.h>
#include <wx-3.0/wx/timer.h>
#include <wx-3.0/wx/panel.h>
#include <wx-3.0/wx/sizer.h>
#include <wx-3.0/wx/stattext.h>
#include "myDialog1.h"
#include "myDialog2.h"
wxDEFINE_EVENT(EVT_WORK_DURATION_UPDATED, wxCommandEvent);
wxDEFINE_EVENT(EVT_BREAK_DURATION_UPDATED, wxCommandEvent);
class MyFrame : public wxFrame
{    
    private:
  
        wxStaticText* timerText;
        wxTimer* timer;
        int countdown;

    //WORK DURATION   

        void WorkDurationUpdated(wxCommandEvent& event){
            int newWorkDuration = event.GetInt();
            workduration = newWorkDuration;
            
            timerText->SetLabel(wxString::Format("%02d:00", workduration));
            ResetTimer();
            //UpdateTimerDisplay();
        }

    //END WORK DURATION

    //BREAK DURATION
        void BreakDuration(wxCommandEvent& event)
        {
            myDialog2* dialog = new myDialog2(this, "Set Break Duration",breakduration);

        
            dialog->ShowModal();
            breakduration = dialog->GetSliderValue();
            dialog->Destroy();
        }

        void BreakDurationUpdated(wxCommandEvent& event){
            int newBreakDuration = event.GetInt();
            breakduration = newBreakDuration;
        }

    //END BREAK DURATION

    //TIMER
       
        void UpdateTimerDisplay(){
            int minutes = countdown / 60;
            int seconds = countdown % 60;
            timerText->SetLabel(wxString::Format("%02d:%02d", minutes, seconds));
        }
        void OnTimer(wxTimerEvent& event)
        {
            countdown--;
            UpdateTimerDisplay();

            if (countdown == 0)
            {
                timer->Stop();
                wxMessageBox("Sesion completed!");
                ResetTimer();
            }
        }
        void OnStart(wxCommandEvent& event)
        {
            countdown = workduration*60;
            timer->Start(1000);
        }

        void OnStop(wxCommandEvent& event)
        {
            timer->Stop();
            countdown = workduration*60;
            ResetTimer();
        }

        void OnPause(wxCommandEvent& event)
        {
            timer->Stop();
        }
    public:


        void WorkDuration(wxCommandEvent& event)
        {
            myDialog1* dialog = new myDialog1(this, "Set Work Duration",workduration);
            dialog->ShowModal();
            workduration = dialog->GetSliderValue();
            dialog->Destroy();
        }
        int workduration=25;
        int breakduration=5;
        static const int TimerID = 1001;
        void ResetTimer(){
            int countdown = workduration*60;
            UpdateTimerDisplay();
        }

        MyFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title)
    {

        SetMinSize(wxSize(300,200));
        SetMaxSize(wxSize(300,200));
        
        //menu
        wxMenuBar* menuBar = new wxMenuBar();
        
        wxMenu* fileMenu = new wxMenu();
        //work duration menu
        wxMenuItem * wd = fileMenu->Append(wxID_ANY, "&set Work Duration(Minutes)");
        Bind(wxEVT_MENU, &MyFrame::WorkDuration, this, wd->GetId());
        
        //break duration menu
        wxMenuItem * bd = fileMenu->Append(wxID_ANY, "&set Break Duration");
        Bind(wxEVT_MENU, &MyFrame::BreakDuration, this, bd->GetId());

        //total work time menu
        wxMenuItem * tt = fileMenu->Append(wxID_ANY, "&View Total Work Time");
        

        menuBar->Append(fileMenu, "&Settings");

        SetMenuBar(menuBar);

        //buttons

        wxButton* Button1 = new wxButton(this,wxID_ANY,"START",wxPoint(1,1));
        Button1->Bind(wxEVT_BUTTON, &MyFrame::OnStart, this);
        
        wxButton* Button2 = new wxButton(this,wxID_ANY,"PAUSE",wxPoint(1,50));
        Button2->Bind(wxEVT_BUTTON, &MyFrame::OnPause, this);
                
        wxButton* Button3 = new wxButton(this,wxID_ANY,"STOP",wxPoint(1,100));
        Button3->Bind(wxEVT_BUTTON, &MyFrame::OnStop, this);

        //TIMER 
        countdown = workduration*60;
        
        timerText = new wxStaticText(this, wxID_ANY, wxString::Format("%02d:00", workduration), wxPoint(150, 50));
        timer = new wxTimer(this, TimerID);
        Bind(wxEVT_TIMER, &MyFrame::OnTimer, this, TimerID);
        UpdateTimerDisplay();
        //END OF TIMER
 
    }
};
