#include "cMain.h"
#include <sstream>
#include <fstream>

wxBEGIN_EVENT_TABLE(cMain,wxFrame)
	EVT_BUTTON(10001, OnDiificultySubmit)
	EVT_BUTTON(10002, OnNextQuestion)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr,wxID_ANY,"Game",wxPoint(100,100),wxSize(800,600), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	std::fstream myfile;
	myfile.open("HighScore.txt", std::ios::in);
	if (myfile.peek() != std::ifstream::traits_type::eof())
	{
		myfile >> highScore;
	}
	
	myfile.close();

	std::string HighScore = "HIGH SCORE : " + std::to_string(highScore);
	

	m_highScoreDisplay = new wxStaticText(this, wxID_ANY, HighScore, wxPoint(500, 5), wxSize(100, 20));
	m_highScoreDisplay->SetForegroundColour(wxColor(*wxWHITE));

	SetBackgroundColour(wxColor(*wxBLACK));

	m_label = new wxStaticText(this,wxID_ANY,"Difficulty Level",wxPoint(50,50),wxSize(100,20));
	m_label->SetForegroundColour(wxColor(*wxWHITE));

	m_label1 = new wxStaticText(this,wxID_ANY,":",wxPoint(200,50),wxSize(50,20));
	m_label1->SetForegroundColour(wxColor(*wxWHITE));

	m_difficultyInput = new wxTextCtrl(this,wxID_ANY,"1", wxPoint(350, 50), wxSize(50, 20));
	m_difficultyInput->SetBackgroundColour(wxColor(*wxBLACK));
	m_difficultyInput->SetForegroundColour(wxColor(*wxWHITE));

	m_difficultySubmit = new wxButton(this, 10001, "Submit", wxPoint(350, 150), wxSize(50, 20));
	m_difficultySubmit->SetBackgroundColour(wxColor(*wxBLACK));
	m_difficultySubmit->SetForegroundColour(wxColor(*wxWHITE));
	m_difficultySubmit->Bind(wxEVT_ENTER_WINDOW, &cMain::OnSubmitButtonHover, this);
	m_difficultySubmit->Bind(wxEVT_LEAVE_WINDOW, &cMain::OnSubmitButtonLeave, this);
	//-----------------------------------------------------------------

	m_question_text = new wxStaticText(this,wxID_ANY,"Question will be shown here",wxPoint(50,230),wxSize(150,20));
	m_question_text->SetForegroundColour(wxColor(*wxWHITE));
	
	m_questionFeild = new wxStaticText(this,wxID_ANY,"",wxPoint(50,250),wxSize(300,150),wxBORDER_RAISED);
	m_questionFeild->SetForegroundColour(wxColor(*wxWHITE));
	
	m_answer_text = new wxStaticText(this,wxID_ANY,"Answer will be taken here",wxPoint(450,230),wxSize(150,20));
	m_answer_text->SetForegroundColour(wxColor(*wxWHITE));

	m_answerFeild = new wxTextCtrl(this,wxID_ANY,"", wxPoint(450, 250), wxSize(300, 150), wxBORDER_RAISED);
	m_answerFeild->SetBackgroundColour(wxColor(*wxBLACK));
	m_answerFeild->SetForegroundColour(wxColor(*wxWHITE));

	m_nextQuestion = new wxButton(this, 10002, "Next", wxPoint(350, 450), wxSize(50, 20));
	m_nextQuestion->SetBackgroundColour(wxColor(*wxBLACK));
	m_nextQuestion->SetForegroundColour(wxColor(*wxWHITE));
	m_nextQuestion->Bind(wxEVT_ENTER_WINDOW, &cMain::OnNextButtonHover, this);
	m_nextQuestion->Bind(wxEVT_LEAVE_WINDOW, &cMain::OnNextButtonLeave, this);
}

cMain::~cMain()
{
}

void cMain::OnDiificultySubmit(wxCommandEvent& evt)
{
	if (!set)
	{
		//Set the difficulty
		std::string str(m_difficultyInput->GetValue().c_str());
		std::stringstream stream(str);
		stream >> difficulty;
		m_questionFeild->SetLabel(GenerateEquation());
		m_answerFeild->SetForegroundColour(wxColor(*wxWHITE));
		
		set = true;
		if(difficulty != 0)
			m_answerFeild->SetLabel("WAIT");
		else
			m_answerFeild->SetLabel("");
	}
	
}

void cMain::OnNextQuestion(wxCommandEvent& evt)
{
	if (set)
	{
		if (difficulty != 0)
		{
			difficulty--;
			//generate two numbers and one operator
			std::string equation = GenerateEquation();
			//Show it in the question section
			m_questionFeild->SetLabel(equation);
			if (difficulty == 0)
			{
				m_answerFeild->SetLabel("");
			}
		}
		else
		{
			//Check if the answer is correct
			wxString val = m_answerFeild->GetValue();
			std::string  str(val.c_str());
			std::stringstream stream(str);
			int ans = 0;
			stream >> ans;
			if (ans == vec[0])
			{
				//generate two numbers and one operator
				std::string equation = GenerateEquation();
				//Show it in the question section
				m_questionFeild->SetLabel(equation);
				m_answerFeild->SetLabel("");
				vec.erase(vec.begin(), vec.begin() + 1);
				score++;
			}
			else
			{
				//Wrong answer
				m_answerFeild->SetForegroundColour(wxColor(*wxRED));
				m_answerFeild->SetLabel("Wrong answer");
				set = false;
				vec.clear();

				if (highScore < score)
				{
					remove("HighScore.txt");
					std::fstream myfile1;
					myfile1.open("HighScore.txt", std::ios::out);
					myfile1 << score;
					myfile1.close();
					std::string HighScore = "HIGH SCORE : " + std::to_string(score);
					m_highScoreDisplay->SetLabel(HighScore);
				}
			}

		}
	}
	
}

void cMain::OnNextButtonHover(wxMouseEvent& event)
{
	m_nextQuestion->SetForegroundColour(wxColor(*wxBLACK));
}

void cMain::OnNextButtonLeave(wxMouseEvent& event)
{
	m_nextQuestion->SetForegroundColour(wxColor(*wxWHITE));
}
void cMain::OnSubmitButtonHover(wxMouseEvent& event)
{
	m_difficultySubmit->SetForegroundColour(wxColor(*wxBLACK));
}

void cMain::OnSubmitButtonLeave(wxMouseEvent& event)
{
	m_difficultySubmit->SetForegroundColour(wxColor(*wxWHITE));
}

std::string cMain::GenerateEquation()
{
	srand(time(0));
	int a = (rand() % 20) + 1;
	int b = (rand() % 20) + 1;
	int c = 1 + rand() % 4;
	std::string op;
	switch (c)
	{
	case 1: op = "+";
		vec.push_back(a + b);
		break;
	case 2: op = "-";
		vec.push_back(a - b);
		break;
	case 3: op = "*";
		vec.push_back(a * b);
		break;
	case 4: op = "/";
		vec.push_back(a / b);
		break;
	}
	
	return std::to_string(a) + op + std::to_string(b);
}
