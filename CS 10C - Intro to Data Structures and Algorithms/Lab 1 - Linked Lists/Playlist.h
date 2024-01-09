#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
using namespace std;

class PlaylistNode {
public:
    PlaylistNode();
    PlaylistNode(string ID, string sName, string aName, int sLength);
    
    void InsertAfter(PlaylistNode* node);
    void SetNext(PlaylistNode* node);
    string GetID();
    string GetSongName();
    string GetArtistName();
    int GetSongLength();
    PlaylistNode* GetNext();
    void PrintPlaylistNode();
    
private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
};

#endif
