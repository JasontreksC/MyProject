#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <assert.h>
#include <iomanip>


using namespace std;

#define ENTER 13
#define ESC 27	
#define LEFT 75	
#define RIGHT 77
#define UP 72	
#define DOWN 80	

/*******************/
/****JasontreksC****/
/*******************/

/*
���� ������Ʈ ��¥: 22-07-19
�ڵ� ���� ����
- ����Ʈ�� ������ ���ø� Ŭ�������� ����� ���Ǹ� ����
- ���ͷ����� Ŭ�������� ����Լ� find() �߰�
- Ŭ���� ������ find() �Լ��� �̿��� �����Լ������� ���ͷ����͸� ã�� �Լ��� ������(�ڵ� ����ȭ)
- ���ͷ����͸� ã�� �� ���� ������ page * 10 + index �� ��ó���� define ����(�ڵ� ����ȭ)
*/