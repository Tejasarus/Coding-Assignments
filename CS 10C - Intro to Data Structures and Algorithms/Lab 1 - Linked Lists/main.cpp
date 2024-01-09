#include "Playlist.h"
#include <iostream>
#include <string>
using namespace std;

void PrintMenu(string);

int main()
{
    string title;
    
    cout << "Enter playlist's title:" << endl;
    getline(cin,title);
    cout << endl;
    PrintMenu(title);
    return 0;
}

void PrintMenu(string t)
{
    char option = 'z'; //doesnt equal any of the other things
    PlaylistNode* head = nullptr;
    PlaylistNode* tail = nullptr; //making the actual playlist here becuase I dont know where else to do it
    
    
    while(option != 'q')
    {
        cout << t << " PLAYLIST MENU" << endl;
        cout << "a - Add song" << endl;
        cout << "d - Remove song" << endl;
        cout << "c - Change position of song" << endl;
        cout << "s - Output songs by specific artist" << endl;
        cout << "t - Output total time of playlist (in seconds)" << endl;
        cout << "o - Output full playlist" << endl;
        cout << "q - Quit" << endl << endl;
        cout << "Choose an option:";
        cin >> option;
        cout << endl;
        
        if(option == 'a') {
        string ID, name, artist;
        int length;
        cout << "ADD SONG" << endl;
        cout << "Enter song's unique ID:";
        cin >> ID;
        cin.ignore(); //needed otherwise it skips over the song getline
        cout << endl << "Enter song's name:";
        getline(cin, name);
        cout << endl << "Enter artist's name:";
        getline(cin, artist);
        cout << endl << "Enter song's length (in seconds):";
        cin >> length;
        cout << endl; //zybooks whitespace (what a pain) =(
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
        cout << endl; //whitespace sadness =(
    }
        
        else if(option == 'd') {
             string ID;
      cout << "REMOVE SONG" << endl << "Enter song's unique ID:"<< endl;
      cin >> ID;
     
      ///*
      PlaylistNode* t = head;
      if(ID == t->GetID())//if the head is the song
        {
          //delete the head;
          string sn;
          sn = head->GetSongName(); //for the confirmation message that the song was deleted;
          PlaylistNode* temp = head->GetNext();
          delete head;
          head = temp;
          cout << "\"" << sn <<"\"" << " removed." << endl;
          
        }
      else
      {
        for(PlaylistNode* i = head; i != nullptr; i = i->GetNext()) //cycle through each song in the playlist to find the song to remove
      {
        if(i->GetNext()->GetID()==ID)
        {
          PlaylistNode* temp = i->GetNext();
          i->SetNext(i->GetNext()->GetNext()); //point the song before the delete song to the song after delete song
          string sn;
          sn = temp->GetSongName(); //for the confirmation message that the song was deleted;
          delete temp;
          cout << "\"" << sn <<"\"" << " removed." << endl;
          break;
        }

      }
      }  
            /*
        string ID;
        PlaylistNode* temp;
        cout << "REMOVE SONG" << endl << "Enter song's unique ID:" << endl;
        cin >> ID;
        cout << endl;
        
        if(head->GetID() == ID) {
            temp = head;
            head = head->GetNext();
        }
        else {
            PlaylistNode* currNode = head->GetNext();
            PlaylistNode* previous = head;
            
            while(currNode) {
                if(currNode->GetID() == ID) {
                    temp = currNode;
                    
                    if(currNode == tail) {
                        tail = previous;
                    }
                    
                    previous->SetNext(currNode->GetNext());
                    delete currNode;
                    break;
                }
                
                currNode = currNode->GetNext();
                previous = previous->GetNext();
            }
        }
        */
       cout << endl; //whitespace sadness =(
    }
        
        else if(option == 'c') {
            int listnum, newlistnum, maxnum = 0; //the ints that the user will input
            //PlaylistNode* currNode = head->GetNext();
           // PlaylistNode* previous = head;
           // PlaylistNode* temp = nullptr;
            
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" ;
            cin >> listnum;
            cout << endl << "Enter new position for song:" <<endl;
            cin >> newlistnum;
           // cout << endl; //so the confirmation message and the int the user puts in arent on the same line
            
            //Loop to get the total number of nodes. This is required to form a contingency when user inputs a newlistnum out of bounds.
            for(PlaylistNode* t = head; t != nullptr; t = t->GetNext())
            {
                ++maxnum;
            }
           
            //find the song and copy it
            PlaylistNode* temp = head;
            //if the song is the head
            if(listnum == 1) 
            {
                temp = head;
                head = head->GetNext(); //set the song head to the next song bc we are moving the current head
            }
            else if(listnum == maxnum)//if the song is the tail
            {
                temp = tail;
                for(PlaylistNode* i = head; i != nullptr; i = i->GetNext())
                {
                    if(i->GetNext() == tail)
                    {
                        tail = i; //sets the tail to the previous song
                        i->SetNext(nullptr);
                        break;
                    }
                }
            }
            else //find that song
            {
                int n = 1;
                for(PlaylistNode* i = head; i != nullptr; i = i->GetNext())
                {
                    if(n == listnum - 1)//gets the previous song so we can point it to the next new song
                    {
                        temp = i->GetNext();
                        i->SetNext(i->GetNext()->GetNext()); //points the previous song to the new playlist song two songs down
                    }
                    ++n;
                }
            }
            
            //now we move the song to its new position
            if(newlistnum == 1) //if it needs to be moved to the head
            {
                PlaylistNode* temp2 = head;
                head = temp; //set the head to the new song
                head->SetNext(temp2); //point the song to the old head
            }
            else
            {
                int numc = 1;
                PlaylistNode* song;
                PlaylistNode* nexts;
                for(PlaylistNode* i = head; i != nullptr; i = i->GetNext())
                {
                    if(numc == newlistnum - 1)//gets the previous song so we can point it to the next new song
                    {
                        nexts = i->GetNext();
                        song = i;
                    }
                    ++numc;
                }
                temp->SetNext(nexts);
                song->SetNext(temp);

                



               /*
                
                PlaylistNode* temp4 = head;
                for(int i = 0; i < newlistnum; ++i)
                {
                    PlaylistNode* temp3 = temp4->GetNext();
                    temp3->PrintPlaylistNode();
                    cout << endl << "---------------------";
                    temp4->SetNext(temp); //point the new previous song to the moved song
                    temp->SetNext(temp3); //point the newly moved song to the new next song
                    temp4= temp4->GetNext();
                    
                }
                */
            }
            cout << "\"" << temp->GetSongName() << "\" moved to position " << newlistnum << endl;
            
           cout << endl; //for zybooks whitespace
        }
        else if(option == 's') {
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl << "Enter artist's name:" << endl;
        string aname;
        cin.ignore();
        getline(cin,aname);
        cout << endl; //for zybooks whitespace =)
        if(head == nullptr) //if the playlist is empty
        {
            cout << "Playlist is empty" << endl;
        }
        else
        {
            PlaylistNode* temp = head;
            int i = 1; //counter that "numberizes" the songs
            while(temp != nullptr)
            {
                if(temp->GetArtistName() == aname)
                {
                    cout << i << "." << endl;
                    temp->PrintPlaylistNode();
                    cout << endl;
                }
                ++i;
                temp = temp->GetNext();
            }
                
            
        }
        
    }
        
        else if(option == 't') {
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
        PlaylistNode* temp = head;
        int time = 0;
        while(temp != nullptr)//cycle through each song, get its time, and add it to time
        {
            time = temp->GetSongLength() + time;
            temp = temp->GetNext();
        }
        cout << "Total time: " << time << " seconds" << endl;
        cout << endl; //whitespace sadness =(
    }
        
        else if(option == 'o') {
        cout << t << " - OUTPUT FULL PLAYLIST" << endl;
        if(head == nullptr) //if the playlist is empty
        {
            cout << "Playlist is empty" << endl;
        }
        else
        {
            int i = 1;
            PlaylistNode* temp = head;
            while(temp != nullptr)
            {
                if(temp->GetNext() == nullptr) //this pointless if statement is here for the sole purpose of satisfying the zybooks whitespace. It is so ridiculous.
                {
                    cout << i << "." << endl; //song # in the playlist
                    temp->PrintPlaylistNode(); //print the details of the song
                    temp = temp->GetNext(); //get the next node (same as temp->next)
                    ++i; //to incriment the counter of the songs
                }
                else
                {
                    cout << i << "." << endl; //song # in the playlist
                    temp->PrintPlaylistNode(); //print the details of the song
                    temp = temp->GetNext(); //get the next node (same as temp->next)
                    cout << endl; //newline space between the songs
                    ++i; //to increment the counter of the songs
                }
                
            }
        }
        cout << endl; //whitespace sadness =(
    }
    }
    
}
