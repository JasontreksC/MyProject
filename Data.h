#pragma once
#include "Headers.h"

class Data
{
public:
	char name[20];
	char major[20];
	short grade;
	int idnum;
	short sbcnt;
	char subjects[15][10];
	short scores[10];

	Data();
	Data(const char* _name, const char* _major, const short& _grade, const int& _idnum);
	~Data();

	void SaveFile(int _i);
	float getAverage();
};

