#pragma once
#include <wx/wx.h>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	std::string GenerateEquation();
public:
	void OnDiificultySubmit(wxCommandEvent& evt);
	void OnNextQuestion(wxCommandEvent& evt);
	void OnSubmitButtonHover(wxMouseEvent& event);
	void OnNextButtonHover(wxMouseEvent& event);
	void OnSubmitButtonLeave(wxMouseEvent& event);
	void OnNextButtonLeave(wxMouseEvent& event);
public:
	int difficulty = 0,score = 0,highScore = 0;
	std::vector<int> vec;
	bool set = false;
private:
	wxStaticText* m_label = nullptr,* m_label1 = nullptr,*m_questionFeild = nullptr,*m_question_text = nullptr,*m_answer_text = nullptr,*m_highScoreDisplay = nullptr;
	wxTextCtrl* m_difficultyInput = nullptr,* m_answerFeild = nullptr;
	wxButton* m_difficultySubmit = nullptr,*m_nextQuestion = nullptr;
	wxDECLARE_EVENT_TABLE();
};