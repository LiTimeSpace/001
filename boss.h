#pragma once

#include<iostream>
#include<string>
using namespace std;
#include"worker.h"

class boss:public worker
{
public:

	boss(int id, string name, int did);

	virtual void showinfo();
	virtual string getdeptname();
};