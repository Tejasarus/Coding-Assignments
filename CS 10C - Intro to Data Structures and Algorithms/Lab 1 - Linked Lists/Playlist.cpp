#include "Playlist.h"
#ifndef PLAYLIST_CPP
#define PLAYLIST_CPP

PlaylistNode::PlaylistNode() {
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}

PlaylistNode::PlaylistNode(string ID, string sName, string aName, int sLength) {
    uniqueID = ID;
    songName = sName;
    artistName = aName;
    songLength = sLength;
    nextNodePtr = nullptr;
}

string PlaylistNode::GetID() {
    return uniqueID;
}

string PlaylistNode::GetSongName() {
    return songName;
}

string PlaylistNode::GetArtistName() {
    return artistName;
}

int PlaylistNode::GetSongLength() {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() {
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() {
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

void PlaylistNode::SetNext(PlaylistNode* node) {
    nextNodePtr = node;
}

void PlaylistNode::InsertAfter(PlaylistNode* node) {
    PlaylistNode* temp = nextNodePtr; //make a temp "song" of the new song
    nextNodePtr = node; //set the new song to the old song
    nextNodePtr->nextNodePtr = temp;
}

#endif
