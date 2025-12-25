/*
This programme is made because i keep needing to type in 
"xrandr --output HDMI-A-1 --brightness 0.5"
to change my monitor's brightness

im new to linux, arch linux btw and xfce. i want a way to change my 
monitor's brightness without using the terminal so that
1) its easier for me
2) its easier if my family member wants to use the pc

I made this programme on 24 & 25 Dec 2025

~ Mikhail s/o Mahamood
*/


#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Hor_Value_Slider.H>
#include <FL/Fl_Valuator.H>

// constants
const int MIN_VALUE{20};
const int MAX_VALUE{100};
const int STEP_SIZE{5};
const int WINDOW_WIDTH{300};
const int WINDOW_HEIGHT{60};
std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();	

std::string outputName = "HDMI-A-1"; // my pc usual output name
std::string toWrite = "xrandr --output ";


void getValue(Fl_Widget* widget)
{
	// this is the callback function of the GUI slider
	// get time because otherwise, programme will lag if callbacked too much
	std::chrono::duration<double> duration = std::chrono::steady_clock::now() - start;

	if (duration < std::chrono::duration<double>(0.01)) return;
	start = std::chrono::steady_clock::now();	

	Fl_Valuator* valuator = static_cast<Fl_Valuator*>(widget);
	double value = valuator->value() / 100;
	
	std::string temp = toWrite + std::to_string(value);
	system(temp.c_str());
}

int main(int argc, char* argv[])
{
	// get screen dimensions to spawn window at bottom left
	int x, y, SCREEN_WIDTH, SCREEN_HEIGHT;
	Fl::screen_work_area(x, y, SCREEN_WIDTH, SCREEN_HEIGHT);

	// get output name of monitor no matter which hdmi port is used
	FILE* pipe = popen("xrandr --current" , "r");
	if (pipe == NULL) std::cout << "cant popen" << '\n';
	std::string stringLine = "";
	char line[64];
	while (fgets(line, sizeof(line), pipe))
	{
		stringLine = line;
		if (stringLine.find(" connected") != std::string::npos)
		{
			outputName = stringLine.substr(0, stringLine.find(' '));
			toWrite += outputName + " --brightness "; 
		}
	}

	// if change brightness using terminal
	if (argc > 1)
	{
		std::string brightness = argv[1];
		toWrite += brightness;
		system(toWrite.c_str());
		return 0;
	}
	// else start-up FLTK

	Fl_Window* window = new Fl_Window(	SCREEN_WIDTH - WINDOW_WIDTH, 
										SCREEN_HEIGHT - WINDOW_HEIGHT, 
										WINDOW_WIDTH, 
										WINDOW_HEIGHT, 
										"change brightness");
	
	Fl_Hor_Value_Slider* slider = new Fl_Hor_Value_Slider(10, 10, WINDOW_WIDTH - 20, WINDOW_HEIGHT / 2 + 10);
	// slider->when(FL_WHEN_RELEASE);
	slider->bounds(MIN_VALUE, MAX_VALUE);
	slider->value(42);
	slider->callback(getValue);
	slider->step(STEP_SIZE);

	window->end();
	window->show();

	return Fl::run();
}
