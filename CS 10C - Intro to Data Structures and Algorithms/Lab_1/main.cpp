#include "Playlist.h"
#include <iostream>
#include <string>
using namespace std;

void PrintMenu(string);

int main()
{
  string title;
  

  cout << "Enter the playlist's title:" << endl;
  cin >> title;
  PrintMenu(title);
  
  return 0;
}

void PrintMenu(string t)
{
    char option = ' ';
    PlaylistNode* head = nullptr;
    PlaylistNode* tail = nullptr; //making the actual playlist here becuase I dont know where else to do it
    
  
  while(option != 'q')
  {
    cout << t << "PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl << endl;
  cout << "Choose an option:" << endl;
  cin >> option;
    cout << endl;
    if(option == 'a')
    {
      string ID, name, artist;
      int length;
      cout << "ADD SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      cin >> ID;
      cout << endl << "Enter song's name:" << endl;
      getline(cin, name);
      cout << endl << "Enter artist's name:" << endl;
      getline(cin, artist);
      cout << endl << "Enter song's length (in seconds):" << endl;
      cin >> length;

      PlaylistNode* song = new PlaylistNode(ID,name,artist,length); //creates the song so we can add it to the playlist linked list
      
      if(head == nullptr)
      {
          //make head and tail the song bc there isn't anything in the playlist
          head = song;
          tail = song;
      }
      else
      {
          //do the temp tail switch thing
          PlaylistNode* temp = tail;
          tail = song;
          temp->SetNext(song); //since we dont have the ability to call the struct with "next"
      }
    }
    else if(option == 'd')
    {
      string ID;
      cout << "REMOVE SONG" << endl << "Enter song's unique ID:" << endl;
      cin >> ID;
      
      PlaylistNode* temp = head; //to locate the song w/o affecting the list head
      
      if(temp->GetID() == ID) //if the head is the pointer
      {
          
      }
      
    }
    else if(option == 'c')
    {
      
    }
    else if(option == 's')
    {
      
    }
    else if(option == 't')
    {
     
    }
    else if(option == 'o')
    {
      
    }
    else if(option == 'q')
    {
      break;
    }
  }

}