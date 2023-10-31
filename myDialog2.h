/* class gia alagi sto break 
duration me slider kai ok button*/

#include <wx-3.0/wx/wx.h>

wxDECLARE_EVENT(EVT_BREAK_DURATION_UPDATED, wxCommandEvent);

class myDialog2 : public wxDialog
{
    
    private:
            
        wxSlider * slider;
        wxPanel * panel; 
        int sliderValue; 
        
        void OnOK(wxCommandEvent& event)
    {
        
            sliderValue = slider->GetValue();
            
            wxCommandEvent evt(EVT_BREAK_DURATION_UPDATED, GetId());
            evt.SetInt(sliderValue);
            
            wxPostEvent(GetParent(), evt);

            EndModal(wxID_OK);
            
    }

    public: 

        myDialog2(wxWindow* parent ,const wxString& title,int Breakduration) : wxDialog(parent,wxID_ANY,title),sliderValue(Breakduration)
        {
            
            
            SetMinSize(wxSize(410,100));
            SetMaxSize(wxSize(410,100));


            panel = new wxPanel(this, wxID_ANY);
            
            slider = new wxSlider(panel,wxID_ANY,sliderValue,0,60,wxDefaultPosition,wxSize(400,-1),wxSL_VALUE_LABEL);

            wxButton* okButton = new wxButton(panel, wxID_OK, "OK",wxPoint(310,50));
            okButton->Bind(wxEVT_BUTTON, &myDialog2::OnOK, this);

        } 

        int GetSliderValue() { return sliderValue; }
};