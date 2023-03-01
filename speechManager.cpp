#include "speechManager.h"

SpeechManager::SpeechManager() {
	this->init_speech();
	this->create_speaker();
	this->load_record();
}

void SpeechManager::show_menu() {
	cout << "*******************************" << endl;
	cout << "******* 欢迎参加演讲比赛 ******" << endl;
	cout << "******* 1、开始演讲比赛  ******" << endl;
	cout << "******* 2、查看往届记录  ******" << endl;
	cout << "******* 3、清空比赛记录  ******" << endl;
	cout << "******* 0、退出比赛程序  ******" << endl;
	cout << "*******************************" << endl;
	cout << endl;
}

void SpeechManager::init_speech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();
	this->m_index = 1;
	this->m_record.clear();
}

void SpeechManager::create_speaker() {
	string nameSeed = "ABCDEFGHIJKL";	
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "speaker_";
		name += nameSeed[i];
		Speaker sp;
		sp.Name = name;
		sp.Score[0] = 0;
		sp.Score[1] = 0;

		this->v1.push_back(i + 10001);
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeechManager::exit_system() {
	cout << "退出系统中......" << endl;
	Sleep(500);
	cout << "已退出系统" << endl;
	cout << "欢迎下次使用!" << endl;
	exit(0);
}

void SpeechManager::start_speech() {
	this->speech_draw();
	this->speech_contest();
	this->show_score();
	this->m_index++;
	this->speech_draw();
	this->speech_contest();
	this->show_score();
	this->save_record();
	cout << "本届比赛已结束！" << endl;
	//重置比赛 获取记录
	this->init_speech();
	this->create_speaker();
	this->load_record();
	system("pause");
	system("cls");
}

void SpeechManager::speech_draw() {
	cout << "-----------第<<" << this->m_index << ">>轮比赛正在抽签中-------" << endl;
	if (this->m_index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}	
	system("pause");
}

void SpeechManager::speech_contest() {
	cout << "---------第<<" << this->m_index << ">>轮比赛正在进行-----------" << endl;
	vector<int> v_Src;
	if (this->m_index == 1) v_Src = v1;
	else v_Src = v2;

	multimap<double, int, greater<double>> groupScore;
	int num = 0;

	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		deque<double> dscore;
		for (int i = 0; i < 5; i++) {			
			double score = (rand() % 401 + 600) / 10.f;
			dscore.push_back(score);
		}
		sort(dscore.begin(), dscore.end(), greater<double>());
		dscore.pop_back(); dscore.pop_front();
		double sum = accumulate(dscore.begin(), dscore.end(), 0.0f); double avg = sum / dscore.size();
		this->m_speaker[*it].Score[this->m_index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "编号：" << it->second << " 姓名：" << this->m_speaker[it->second].Name << " 分数："
					 << this->m_speaker[it->second].Score[this->m_index - 1] << endl;
			}
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++) {
				if (this->m_index == 1) v2.push_back((*it).second);
				else vVictory.push_back((*it).second);
			}

			groupScore.clear();
			cout << endl;
		}
	}
	cout << "-----------第" << this->m_index << "轮比赛已完毕！-------------" << endl;
	system("pause");
}

void SpeechManager::show_score() {
	cout << "-------------第" << this->m_index << "轮比赛信息如下-----------" << endl;
	vector<int> v;
	if (this->m_index == 1) v = v2;
	else v = vVictory;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "编号：" << *it << " 姓名：" << this->m_speaker[*it].Name << " 成绩："
			<< this->m_speaker[*it].Score[this->m_index - 1] << endl;
	}
	cout << endl;
	system("pause"); system("cls");
}

void SpeechManager::save_record() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_speaker[*it].Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已保存！" << endl;
	this->fileIsempty = false;
}

void SpeechManager::load_record() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsempty = true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->fileIsempty = true;
		//cout << "文件为空！" << endl;
		ifs.close();
		return;
	}
	this->fileIsempty = false;
	ifs.putback(ch);
	string data; int index = 0;
	while (ifs >> data) {
		int pos = -1; int start = 0; vector<string> v;
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				//查不到
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			//cout << tmp << endl;
			start = pos + 1;
		}	
		m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	
	/*for (map<int, vector<string>>::iterator it = this->m_record.begin(); it != this->m_record.end(); it++) {
		cout << "第" << it->first + 1 << "届冠军编号：" << it->second[0] << " 分数：" << it->second[1] << endl;
	}*/
}

void SpeechManager::show_record() {
	if (this->fileIsempty) {
		cout << "文件不存在或文件为空！" << endl;
	}
	else {
		for (int i = 0; i < this->m_record.size(); i++) {
			if (i == 0) cout << "------------------------------" << endl;
			cout << "第" << i + 1 << "届比赛记录如下：" << endl;
			cout << "冠军编号：" << this->m_record[i][0] << " 得分：" << this->m_record[i][1] << endl;
			cout << "亚军编号：" << this->m_record[i][2] << " 得分：" << this->m_record[i][3] << endl;
			cout << "季军编号：" << this->m_record[i][4] << " 得分：" << this->m_record[i][5] << endl;
			cout << "------------------------------" << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void SpeechManager::clear_record() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		this->init_speech();
		this->create_speaker();
		this->load_record();
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager() {

}