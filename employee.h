#pragma once

#include<iostream>
#include<string>
using namespace std;
#include"worker.h"

class employee :public worker
{
public:

	employee(int id, string name, int did);

	virtual void showinfo();
	virtual string getdeptname();
};