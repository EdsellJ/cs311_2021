#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;
  
bool silent(string last5){
  int state = 0;
  /*
  states:
  0 = Silent
  1 = Confess
  */
  int charpos = 0;
  //finite automota implemented with switch
  while (last5[charpos] != '\0')
  {
    if (state == 0){
      switch (last5[charpos]){
        //confess or silent -> confess
        case 's':
        case 'c': state = 1; break;
        default: return false;
      }
    }
    if (state == 1){
      switch (last5[charpos]){
        //confess -> confess
        case 'c': state = 1; break;
        //silent -> silent
        case 's': state = 0; break;
        default: return false;
      }
    }
    charpos++;
  }
  //where did I end up?
  if (state == 0) 
    return true;
  else return false;
}

ifstream fin; //global stream for reading from the input file
ofstream fout;


void addToFile(string lastMove){
  char moveToAdd;
  string last5;
  fin >> last5;
  if (lastMove == "silent") moveToAdd = 's';
  else if (lastMove == "confess") moveToAdd = 'c';
  //else return;
  
  //add choice to string
  //cout << "before: " << last5 << endl;
  last5 += moveToAdd;
  //cout << "after: " << last5 << endl;
  //if is larger than size 5 remove first
  //if (last5.length() >= 6) last5.erase(0,1);

  //add new string to file
  fout << last5;
}

string choice(string l5){
  if(silent(l5)) return "silent";
  else return "confess";
}

int main(int argc, char** argv)
{
  fin.open("last5.txt");
  fout.open("last5.txt");

  if(strcmp(argv[1], "--last_opponent_move") == 0){

    //add their choice to my move history file
    addToFile(argv[2]);
    string last5;
    fin >> last5;
    cout << choice(last5);
  }
  //if first start with confess
  else cout << "confess";

  fin.close();
  fout.close();
  
    return 0;
}