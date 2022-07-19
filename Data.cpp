#include "Data.h"

Data::Data()
	: name()
	, major()
	, grade(0)
	, idnum(0)
	, sbcnt(0)
{
}

Data::Data(const char* _name, const char* _major, const short& _grade, const int& _idnum)
	: name()
	, major()
	, grade(_grade)
	, idnum(_idnum)
	, sbcnt(0)
	, subjects{ 0, }
	, scores{ 0, }
{
	strcpy(name, _name);
	strcpy(major, _major);

	while (1)
	{

		cout << "+++과목/점수 추가하기+++\n";
		cout << "과목 : "; cin >> subjects[sbcnt];
		cout << "점수 : "; cin >> scores[sbcnt];
		sbcnt++;
		cout << "과목 더 추가하기 : ENTER\n저장하기 : ESC\n";
	loop:
		int k = _getch();
		if (k == ENTER)
			continue;
		else if (k == ESC)
			break;
		else
			goto loop;
	}
}

Data::~Data()
{
}

void Data::SaveFile(int _i)
{
	FILE* fpT = fopen(/*"D:\\Jasontreks\\Clang\\MyProject\\files\\*/"filelist.txt", "a");
	
	time_t timer = time(NULL);
	struct tm* t;
	t = localtime(&timer);
	char buff[256];
	strftime(buff, 256, /*"D:\\Jasontreks\\Clang\\MyProject\\files\\*/"%y%m%d%H%M%S", t);

	char istr[4];
	sprintf(istr, "%d", _i);
	strcat(buff, istr);
	strcat(buff, ".dat");

	fputs(buff, fpT);
	fputc('\n', fpT);

	fclose(fpT);

	FILE* fpB = fopen(buff, "wb");
	fwrite(this, 1, sizeof(Data), fpB);
	fclose(fpB);
}

float Data::getAverage()
{
	float average = 0;

	for (int i = 0; i < sbcnt; i++)
		average += scores[i];

	average /= sbcnt;

	return average;
}



