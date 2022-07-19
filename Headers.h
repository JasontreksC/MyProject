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
최종 업데이트 날짜: 22-07-19
코드 수정 내역
- 리스트가 구현된 템플릿 클래스에서 선언과 정의를 분할
- 이터레이터 클래스에서 멤버함수 find() 추가
- 클래스 내부의 find() 함수를 이용해 메인함수에서의 이터레이터를 찾는 함수를 지웠음(코드 간결화)
- 이터레이터를 찾을 떄 쓰는 수식인 page * 10 + index 를 전처리로 define 했음(코드 간결화)
*/