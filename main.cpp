#include "Data.h"
#include "LinkedList.h"
enum Selects { quit, enter, push, find, fix, del, sort, gomain, up, down, nxtpage, prvpage };

int page = 0;
int index = 0;
#define ITERIDX page * 10 + index

void Sort(LinkedList<Data>& _LinkedList);

void add_new(LinkedList<Data>& _LinkedList);

void add_new(LinkedList<Data>& _LinkedList, LinkedList<Data>::iterator& _iter);

void search(LinkedList<Data>& _LinkedList, LinkedList<Data>& _Result);

void revise(LinkedList<Data>& _LinkedList);

void revise(LinkedList<Data>& _LinkedList, LinkedList<Data>::iterator& _iter);

void del_index(LinkedList<Data>& _LinkedList);

void Sort(LinkedList<Data>& _LinkedList);

void show_detail(LinkedList<Data>& _LinkedList);

void print_chart(LinkedList<Data>& _LinkedList, int _page, int _index);

int print_mainmenu(LinkedList<Data>& _LinkedList, int& _page, int& _index);

void InitLinkedListFromFile(LinkedList<Data>& _LinkedList);

void ReSaveLinkedListToFile(LinkedList<Data>& _LinkedList);

int main()
{
    system("mode con lines=30 cols=130");

    LinkedList<Data> StLinkedList;
    InitLinkedListFromFile(StLinkedList);

    while (1)
    {
    Main:
        LinkedList<Data> ResultLinkedList;
    Result:
        system("cls");

        if (ResultLinkedList.GetCount() == 0)
            print_chart(StLinkedList, page, index);

        else
            print_chart(ResultLinkedList, page, index);

        int select = print_mainmenu(StLinkedList, page, index);

        if (select == Selects::quit)
            break;

        else if (select == Selects::enter)
        {
            if (ResultLinkedList.GetCount() == 0)
                show_detail(StLinkedList);
            else
                show_detail(ResultLinkedList);
        }

        else if (select == Selects::push)
        {
            if (ResultLinkedList.GetCount() == 0)
                add_new(StLinkedList);
            else
            {
                LinkedList<Data>::iterator rsiter = ResultLinkedList.find(ITERIDX);
                LinkedList<Data>::iterator stiter = StLinkedList.begin();

                while (stiter != StLinkedList.end())
                {
                    Data rsDat = *rsiter;
                    Data stDat = *stiter;
                    if (strcmp(rsDat.name, stDat.name) == 0 && rsDat.idnum == stDat.idnum)
                    {
                        break;
                    }
                    ++stiter;
                }
                add_new(StLinkedList, stiter);
            }
            goto Main;
            
        }

        else if (select == Selects::find)
        {
            search(StLinkedList, ResultLinkedList);
            goto Result;
        }

        else if (select == Selects::fix)
        {
            if (ResultLinkedList.GetCount() == 0)
                revise(StLinkedList);
            else
            {
                LinkedList<Data>::iterator rsiter = ResultLinkedList.find(ITERIDX);
                LinkedList<Data>::iterator stiter = StLinkedList.begin();

                while (stiter != StLinkedList.end())
                {
                    Data rsDat = *rsiter;
                    Data stDat = *stiter;
                    if (strcmp(rsDat.name, stDat.name) == 0 && rsDat.idnum == stDat.idnum)
                    {
                        break;
                    }
                    ++stiter;
                }
                revise(StLinkedList, stiter);
            }
            goto Main;
        }

        else if (select == Selects::del)
        {
            if (ResultLinkedList.GetCount() == 0)
                del_index(StLinkedList);
            else
            {
                LinkedList<Data>::iterator rsiter = ResultLinkedList.find(ITERIDX);
                LinkedList<Data>::iterator stiter = StLinkedList.begin();

                while (stiter != StLinkedList.end())
                {
                    Data rsDat = *rsiter;
                    Data stDat = *stiter;
                    if (strcmp(rsDat.name, stDat.name) == 0 && rsDat.idnum == stDat.idnum)
                    {
                        break;
                    }
                    ++stiter;
                }
                StLinkedList.erase(stiter);                
            }
            goto Main;
        }
        
        else if (select == Selects::sort)
        {
            Sort(StLinkedList);
        }

        else if (select == Selects::gomain)
        {
            goto Main;
        }

        goto Result;
            
    }
    ReSaveLinkedListToFile(StLinkedList);
    return 0;
}

///////////////////////////////FUNCTONS////////////////////////////////

void add_new(LinkedList<Data>& _LinkedList)
{
    char name[20], major[20];
    short grade;
    int idnum;

    cout << "이름: "; cin >> name;
    cout << "학년: "; cin >> grade;
    cout << "학번: "; cin >> idnum;
    cout << "전공: "; cin >> major;

    Data newData(name, major, grade, idnum);
    newData.SaveFile(0);
    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n";
    cout << "[1] 상단에 추가\t[2] 하단에 추가\n[3] 지정한 인덱스의 전위 추가\n[4] 지정한 인덱스의 후위 추가\n";
loop:
    int k = _getch();
    switch (k)
    {
    case '1': _LinkedList.PushFront(newData); break;
    case '2': _LinkedList.PushBack(newData); break;
    case '3':
    {
        LinkedList<Data>::iterator iter = _LinkedList.find(ITERIDX);
        _LinkedList.insert_front(iter, newData);
        break;
    }
    case '4':
    {
        LinkedList<Data>::iterator iter = _LinkedList.find(ITERIDX);
        _LinkedList.insert_back(iter, newData);
        break;
    }
    default: goto loop;
    }

}

void add_new(LinkedList<Data>& _LinkedList, LinkedList<Data>::iterator& _iter)
{
    char name[20], major[20];
    short grade;
    int idnum;

    cout << "이름: "; cin >> name;
    cout << "학년: "; cin >> grade;
    cout << "학번: "; cin >> idnum;
    cout << "전공: "; cin >> major;

    Data newData(name, major, grade, idnum);
    newData.SaveFile(0);
    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n";
    cout << "[1] 상단에 추가\t[2] 하단에 추가\n[3] 지정한 인덱스의 전위 추가\n[4] 지정한 인덱스의 후위 추가\n";
loop:
    int k = _getch();
    switch (k)
    {
    case '1': _LinkedList.PushFront(newData); break;
    case '2': _LinkedList.PushBack(newData); break;
    case '3':
    {
        _LinkedList.insert_front(_iter, newData);
        break;
    }
    case '4':
    {
        _LinkedList.insert_back(_iter, newData);
        break;
    }
    default: goto loop;
    }
}

void search(LinkedList<Data>& _LinkedList, LinkedList<Data>& _Result)
{
    char buffer[20];
    cout << "이름>>"; cin >> buffer;

    LinkedList<Data>::iterator iter = _LinkedList.begin();

    for (int i = 0; i < _LinkedList.GetCount(); i++)
    {
        Data stDat = *iter;
        if (strcmp(stDat.name, buffer) == 0)
            _Result.PushBack(*iter);

        ++iter;
    }

}

void revise(LinkedList<Data>& _LinkedList)
{
    LinkedList<Data>::iterator iter = _LinkedList.find(ITERIDX);
    Data newDat = *iter;
    char strbuff[20];
    int  numbuff;

    while (1)
    {
        int k;
        cout << "============인적사항 수정============\n";
        cout << "수정할 부분 : [0]종료 [1]이름 [2]학년 [3]학번 [4]전공 [5]성적\n";
        k = _getch();
        switch (k)
        {
        case '0': 
            _LinkedList.insert_back(iter, newDat);
            _LinkedList.erase(iter); 
            return;
        case '1': cout << "이름 : "; cin >> strbuff; strcpy(newDat.name, strbuff); break;
        case '2': cout << "학년 : "; cin >> numbuff; newDat.grade = numbuff; break;
        case '3': cout << "학번 : "; cin >> numbuff; newDat.idnum = numbuff; break;
        case '4': cout << "전공 : "; cin >> strbuff; strcpy(newDat.major, strbuff); break;
        case '5':
        {
            cout << "======성적정보 수정======\n수정할 과목\n";
            for (int i = 0; i < newDat.sbcnt; i++)
                cout << "[" << i + 1 << "]" << newDat.subjects[i] << " : " << newDat.scores[i] << endl;
            k = _getch() - 48;

            cout << "과목 : "; cin >> strbuff;
            strcpy(newDat.subjects[k], strbuff);

            cout << "성적 : "; cin >> numbuff;
            newDat.scores[k] = numbuff;
            continue;
        }
        }
    }
}

void revise(LinkedList<Data>& _LinkedList, LinkedList<Data>::iterator& _iter)
{
    Data newDat = *_iter;
    char strbuff[20];
    int  numbuff;

    while (1)
    {
        int k;
        cout << "============인적사항 수정============\n";
        cout << "수정할 부분 : [0]종료 [1]이름 [2]학년 [3]학번 [4]전공 [5]성적\n";
        k = _getch();
        switch (k)
        {
        case '0': 
            _LinkedList.insert_back(_iter, newDat);
            _LinkedList.erase(_iter); 
            return;
        case '1': cout << "이름 : "; cin >> strbuff; strcpy(newDat.name, strbuff); break;
        case '2': cout << "학년 : "; cin >> numbuff; newDat.grade = numbuff; break;
        case '3': cout << "학번 : "; cin >> numbuff; newDat.idnum = numbuff; break;
        case '4': cout << "전공 : "; cin >> strbuff; strcpy(newDat.major, strbuff); break;
        case '5':
        {
            cout << "======성적정보 수정======\n수정할 과목\n";
            for (int i = 0; i < newDat.sbcnt; i++)
                cout << "[" << i + 1 << "]" << newDat.subjects[i] << " : " << newDat.scores[i] << endl;
            k = _getch() - 48;

            cout << "과목 : "; cin >> strbuff;
            strcpy(newDat.subjects[k], strbuff);

            cout << "성적 : "; cin >> numbuff;
            newDat.scores[k] = numbuff;
            continue;
        }
        }
    }
}

void del_index(LinkedList<Data>& _LinkedList)
{
    LinkedList<Data>::iterator iter = _LinkedList.find(ITERIDX);
    _LinkedList.erase(iter);
}

void Sort(LinkedList<Data>& _LinkedList)
{
    cout << "======정렬 선택======\n";
loop:
    cout << "[1]이름순 [2]평균순\n";
    int k = _getch();

    if (k == '1')
    {
        while (_LinkedList.GetCount() >= 2)
        {
            LinkedList<Data>::iterator iter = _LinkedList.begin();
            int swap = 0;

            while (1)
            {
                if (strcmp((*iter).name, (*(iter + 1)).name) > 0)
                {
                    Data temp = *iter;
                    *iter = *(iter + 1);
                    *(iter + 1) = temp;
                    swap = 1;
                }
                ++iter;

                if (iter + 1 == _LinkedList.end())
                    break;
            }
            if (!swap)
                break;
        }
    }
    else if (k == '2')
    {
        while (_LinkedList.GetCount() >= 2)
        {
            LinkedList<Data>::iterator iter = _LinkedList.begin();
            int swap = 0;

            while (1)
            {
                if ((*iter).getAverage() < (*(iter + 1)).getAverage())
                {
                    Data temp = *iter;
                    *iter = *(iter + 1);
                    *(iter + 1) = temp;
                    swap = 1;
                }
                ++iter;
                if (iter + 1 == _LinkedList.end())
                    break;
            }
            if (!swap)
                break;
        }
    }
    else
        goto loop;
}

void show_detail(LinkedList<Data>& _LinkedList)
{
    LinkedList<Data>::iterator iter = _LinkedList.find(ITERIDX);
    Data newDat = *iter;
    cout << "======성적 정보======\n";
    for (int i = 0; i < newDat.sbcnt; i++)
    {
        cout << newDat.subjects[i] << " : " << newDat.scores[i] << endl;
    }
    cout << "ENTER를 누르십시오.\n";
keyloop:
    if (_getch() == ENTER)
        return;
    else
        goto keyloop;
}

void print_chart(LinkedList<Data>& _LinkedList, int _page, int _index)
{
    for (int i = 0; i < 30; i++)
        cout << "■";
    cout << endl;

    cout.width(10); cout << left << "순번";
    cout.width(10); cout << left << "이름";
    cout.width(10); cout << left << "학년";
    cout.width(10); cout << left << "학번";
    cout.width(10); cout << left << "전공";
    cout.width(10); cout << left << "평균" << endl;


    LinkedList<Data>::iterator iter = _LinkedList.begin();

    for (int i = 0; i < _page * 10; i++)
    {
        if (iter != _LinkedList.end())
            ++iter;
    }

    iter = _LinkedList.begin();
    for (int i = _page * 10; i < _page * 10 + 10; i++)
    {
        if (i == _index + (_page * 10))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        else
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        Data newDat;
        if (iter != _LinkedList.end())
            newDat = *iter;

        if (i < _LinkedList.GetCount())
        {
            printf("[%2d]\t  ", i + 1);
            cout.width(10); cout << newDat.name;
            cout.width(10); cout << newDat.grade;
            cout.width(10); cout << newDat.idnum;
            cout.width(10); cout << newDat.major;
            cout.width(10); cout.fixed; cout << newDat.getAverage() << endl;
        }
        else
            printf("[%2d]\n", i + 1);

        if (iter != _LinkedList.end())
            ++iter;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    for (int i = 0; i < 30; i++)
        cout << "■";
    cout << endl;
}

int print_mainmenu(LinkedList<Data>& _LinkedList, int& _page, int& _index)
{
    cout << "ESC  종료\t";
    cout << "ENTER 성적보기\t";
    cout << "P  추가하기\t";
    cout << "S  검색하기\n";
    cout << "R  수정하기\t";
    cout << "D  삭제하기\t";
    cout << "F  정렬하기\t";
    cout << "M 메인으로\t";
    cout << "↑ 상향이동\n";
    cout << "↓ 하향이동\t";
    cout << "→ 다음 페이지\t";
    cout << "← 이전 페이지\n";
menuloop:
    int k = _getch();

    if (k == ESC)
    {
        return Selects::quit;
    }
    else if (k == 224) // 방향키 조건문
    {
        k = _getch();
        switch (k)
        {
        case DOWN:
        {
            if (_index < 9)
                _index++;
            return 100;
        }
        case  UP:
        {
            if (_index > 0)
                _index--;
            return 100;
        }
        case RIGHT:
        {
            _page++;
            return 100;
        }
        case  LEFT:
            if (_page > 0)
                _page--;
            return 100;
        }
    }
    else if (k == ENTER)
    {
        return Selects::enter;
    }
    else if (k == 'P' || k == 'p')
    {
        return Selects::push;
    }
    else if (k == 'S' || k == 's')
    {
        return Selects::find;
    }
    else if (k == 'R' || k == 'r')
    {
        return Selects::fix;
    }
    else if (k == 'D' || k == 'd')
    {
        return Selects::del;
    }
    else if (k == 'F' || k == 'f')
    {
        return Selects::sort;
    }
    else if (k == 'M' || k == 'm')
    {
        return Selects::gomain;
    }
    else
        goto menuloop;
}

void InitLinkedListFromFile(LinkedList<Data>& _LinkedList)
{
    FILE* fpT = fopen(/*"D:\\Jasontreks\\Clang\\MyProject\\files\\*/"filelist.txt", "r");
    if (fpT == NULL)
        return;

    char buff[256];

    while (fgets(buff, 256, fpT) != NULL)
    {
        for (int i = 0; i < 256; i++)
        {
            if (buff[i] == '\n')
            {
                buff[i] = 0;
                break;
            }
        }
        FILE* fpB = fopen(buff, "rb");
        Data newData;
        fread(&newData, sizeof(Data), 1, fpB);
        fclose(fpB);
        _LinkedList.PushBack(newData);
    }
    fclose(fpT);
}

void ReSaveLinkedListToFile(LinkedList<Data>& _LinkedList)
{
    cout << "저장중...강제로 종료하지 마십시오.\n";

    FILE* fpT = fopen(/*"D:\\Jasontreks\\Clang\\MyProject\\files\\*/"filelist.txt", "r");
    if (fpT == NULL)
        return;

    char buff[256];
    int file_i = 0;

    while (!feof(fpT))
    {
        fgets(buff, 256, fpT);
        for (int i = 0; i < 256; i++)
        {
            if (buff[i] == '\n')
            {
                buff[i] = 0;
                break;
            }
        }
        remove(buff);
    }
    fclose(fpT);
    remove(/*"D:\\Jasontreks\\Clang\\MyProject\\files\\*/"filelist.txt");

    LinkedList<Data>::iterator iter = _LinkedList.begin();

    while (iter != _LinkedList.end())
    {
        Data newDat = *iter;
        newDat.SaveFile(file_i++);
        ++iter;
    }
    cout << "저장 완료.\n";
}