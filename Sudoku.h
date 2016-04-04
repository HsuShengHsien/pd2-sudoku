#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Sudoku{
public:
	Sudoku();
	void printOut();
	void giveQuestion();
    void readInstr();
	void readIn();
	void solve();
	void changeNum(int a, int b);
    void changeRow(int a, int b);
	void changeCol(int a, int b);
	void rotate(int n);
	void flip(int n);
	void transform();
	bool isCorrect();
	int backtrace();
	int getNextZeroIndex(int index);
	int push(int index);
	int pop();
	static const int sudokuSize=81;

private:
    int map[sudokuSize];
	int ans[sudokuSize];
	void change();
	bool checkUnity(int arr[]);
};	
