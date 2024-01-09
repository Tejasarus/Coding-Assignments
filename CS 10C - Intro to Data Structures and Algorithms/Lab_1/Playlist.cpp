#include "Playlist.h"
#ifndef PLAYLIST
#define PLAYLIST
#include <iostream>
using namespace std;

PlaylistNode::PlaylistNode()
{
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    next = 0;
}
PlaylistNode::PlaylistNode(string ID, string s, string a, int l)
{
    uniqueID = ID;
    songName = s;
    artistName = a;
    songLength = l;
    next = 0;
}
void PlaylistNode::InsertAfter(PlaylistNode* song)
{
    PlaylistNode* temp = next; //make a temp "song" of the new song
    next = song; //set the new song to the old song
    next->next = temp; //add the new song AFTER the old song
}
void PlaylistNode::SetNext(PlaylistNode* song)
{
    next = song; //next IS the tail
}
void PlaylistNode::PrintPlaylistNode()
{
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song name: " << songName << endl;
    cout << "Artist name: " << artistName << endl;
    cout << "Song Length (seconds): " << songLength << endl;
}
#endif