//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------
USEFORM("SDIMain.cpp", MainForm);
USEFORM("About.cpp", AboutBox);
USERES("goaledit.res");
USEUNIT("Scenario.cpp");
USEFORM("GoalView.cpp", GoalForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application->Initialize();
	Application->Title = "Sir Henry's 1602 Scenario Goal Editor";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TGoalForm), &GoalForm);
                 Application->Run();

	return 0;
}
//---------------------------------------------------------------------
