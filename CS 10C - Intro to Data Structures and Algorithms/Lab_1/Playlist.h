#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>
using namespace std;

class PlaylistNode
{ 
  public:
  PlaylistNode();
  PlaylistNode(string ID, string s, string a, int l);

  void InsertAfter(PlaylistNode*); //inserts after a specific song 
  void SetNext(PlaylistNode*); //inserts a song at the end of the (play)list
  string GetID() {return uniqueID;}; //returns ID
  string GetSongName() {return songName;}; //returns song name
  string GetArtistName() {return artistName;}; //returns artist name
  PlaylistNode* GetNext() {return next;}; //returns the next song in the playlist (so if I do song1.GetNext it should return song2)
  void PrintPlaylistNode(); //prints the entire playlist like in the instructions

  private:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* next;
};
#endif