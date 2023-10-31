/* class gia alagi sto work duration me slider kai ok button*/

#include <wx-3.0/wx/wx.h>

wxDECLARE_EVENT(EVT_WORK_DURATION_UPDATED, wxCommandEvent);


class myDialog1 : public wxDialog
{
    
    private:
            
        wxSlider * slider;
        wxPanel * panel; 
        int sliderValue; 
        MyFrame * myframe;

        void OnOK(wxCommandEvent& event)
        {
        
            sliderValue = slider->GetValue();
            
            wxCommandEvent evt(EVT_WORK_DURATION_UPDATED, GetId());
            evt.SetInt(sliderValue);
            
            wxPostEvent(GetParent(), evt);
            myframe->ResetTimer();
            EndModal(wxID_OK);
           
        }

    public: 
        
        
        myDialog1(wxWindow* parent ,const wxString& title,int workduration) : wxDialog(parent,wxID_ANY,title),sliderValue(workduration)
        {
            
            
            SetMinSize(wxSize(410,100));
            SetMaxSize(wxSize(410,100));


            panel = new wxPanel(this, wxID_ANY);
            
            slider = new wxSlider(panel,wxID_ANY,sliderValue,0,60,wxDefaultPosition,wxSize(400,-1),wxSL_VALUE_LABEL);

            wxButton* okButton = new wxButton(panel, wxID_OK, "OK",wxPoint(310,50));
            okButton->Bind(wxEVT_BUTTON, &myDialog1::OnOK, this);

        } 

        int GetSliderValue() { return sliderValue; }
};