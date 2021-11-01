#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;
  
//this is my logic function which makes the decisions
bool silent(string last5){
  int state = 0;
  /*
  states:
  0 = Silent
  1 = Confess
  */
  int charpos = 0;
  //finite state automota implemented with switch
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
    else if (state == 1){
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
  if (state == 0){
    return true;
  }
  else return false;
}

fstream fs; //global stream for reading from the input file

void addToFile(string lastMove){
  char moveToAdd;
  string last5;
  fs >> last5;

  //add last opponent move to text file
  if (lastMove == "silent") last5 += 's';
  else if (lastMove == "confess") last5 = 'c';
  
  //if is larger than size 5 remove first
  if (last5.length() >= 6) last5.erase(0,1);

  //add new string to file
  fs.close();
  fs.open("last5.txt", ios::in | ios::out | ios::trunc); //delete old content
  fs << last5;
}

string choice(string l5){
  if(silent(l5) == true) return "silent";
  else return "confess";
}

int main(int argc, char** argv)
{
  //if not the first turn
  if(strcmp(argv[1], "--last_opponent_move") == 0){
    //open file
    fs.open("last5.txt");

    //add their choice to my move history file
    addToFile(argv[2]);

    //reset file input
    fs.close();
    fs.open("last5.txt");

    //make choice
    string last5;
    fs >> last5;
    cout << choice(last5);
  }

  //if first start with confess
  else if (strcmp(argv[2], "true") == 0){
    fs.open("last5.txt", ios::in | ios::out | ios::trunc);
    cout << "confess";
  }
  fs.close();
  
  return 0;
}