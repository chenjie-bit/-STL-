#include <iostream>
using namespace std;
#include "speechManager.h"
#include <ctime>

int main() {
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	int choice = 0;
	while (true) {
		sm.show_menu();
		cout << "ÇëÊäÈëÄúµÄÑ¡Ôñ£º" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.start_speech();
			break;
		case 2:
			//sm.load_record();
			sm.show_record();
			break;
		case 3:
			sm.clear_record();
			break;
		case 0:
			sm.exit_system();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	return 0;
}