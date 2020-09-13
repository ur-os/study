#include <string>
using namespace std;

typedef struct egg{
  char* cristmass;
} Eggo;

typedef struct s{
	char* left_s;
	char main_s[5];
	char* right_s;
  char mex[3] = {'y','e','p'};
  Eggo egg;
  int xem[3] = {1, 2, 3};
  } S;

class Class {
	int classInt;
	void foo(){};
};

int ololo(){
	S** chicken = new S*[2];
	chicken[0] = new S[1];
	chicken[1] = new S[1];



	chicken[0][0].left_s = new char[5];
	chicken[0][0].right_s = new char[5];
	chicken[0][0].main_s[0] = 'o';
	chicken[0][0].main_s[0] = 'l';
	chicken[0][0].main_s[0] = 'o';
	chicken[0][0].main_s[0] = 'l';
	return 0;
}

int main(void){
	int x;
	int y = 1;
	S lock;
	S* lel;
	Class my_class;
	int arrayInt[] = {1, 2, 3};
	char arrayChar[] = {'a','b','c'};
	string str;
  char yes;
  char* starchar;
  char* starcraft[1][1];
  char*** two_d;
  two_d = new char**[4];
  for(int i = 0; i < 4; i++) {
    two_d[i] = new char*[6];
    for(int j = 0; j < 6; j++) {
        two_d[i][j] = new char[8];
    }
  }
  yes = 'Y';

  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 6; j++)
        starcraft[i][j] = new char[6];
  int size = 50;
  starchar = new char[50];
  delete(starchar);
  starchar = new char[size];
  starcraft[0][0] = starchar;
	arrayInt[0] = 0;
	arrayChar[2] = 'a';
	str = "lololo";
	lel = new S[3];
	ololo();
	x = 0;
	x += 100;
	return 0;
}
