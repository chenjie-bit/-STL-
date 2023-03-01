#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
using namespace std;

class SpeechManager {
public:
	SpeechManager();
	void show_menu();
	void exit_system();
	void init_speech();
	void create_speaker();
	void start_speech();
	void speech_draw();
	void speech_contest();
	void show_score();
	void save_record();
	void load_record();
	void show_record();
	void clear_record();
	~SpeechManager();
public:
	vector<int> v1;
	vector<int> v2;
	vector<int> vVictory;
	map<int, Speaker> m_speaker;
	int m_index;
	bool fileIsempty;
	map<int, vector<string>> m_record;
};