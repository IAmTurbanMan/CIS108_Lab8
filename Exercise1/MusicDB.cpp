#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <id3/tag.h>
#include "MusicDB.h"
#include "Song.h"

using namespace std;

//intializing Song data type as aSong and vector as mySongs
metadata::Song aSong;

vector <metadata::Song> mySongs;


//function to load .txt file into database
void programLoad(string fileName)
{
	metadata::Song aSong;
	ifstream musicDatabase;
	mySongs.clear();
	char ch;
	
	musicDatabase.open(fileName, ios::in | ios::binary);
	while (musicDatabase.is_open() && musicDatabase.peek() != EOF)
	{
		musicDatabase.read((char*)& aSong, sizeof(aSong));
		mySongs.push_back(aSong);
	}
	musicDatabase.close();
}

//function to add a song to the database
void addSong()
{
	cout << "\n" << "Enter song title: ";
	cin.getline (aSong.title, 64);						//input into the title of the aSong struct
	cout << "Enter artist: ";
	cin.getline (aSong.artist, 64);						//input into artist
	cout << "Enter album: ";
	cin.getline (aSong.album, 64);						//input into album
	cout << "Enter track number: ";
	cin >> aSong.track;									//input into track
	cout << "Enter release year: ";
	cin >> aSong.releaseYear;							//input into  release year
	cout << " Blues\n" << " Country\n" << " Electronic\n" << " Folk\n" << " Hip Hop\n" << " Jazz\n" << " Latin\n" << " Pop\n" << " Rock\n";
	cout << "Choose a genre: ";							//list genres, then ask for input

	string genreString;
	
	while (true)										
	{
		getline (cin, genreString);						//read a whole line of input
		transform(genreString.begin(), genreString.end(), genreString.begin(), ::tolower); //convert the string genreString to lowercase


		//a series of if statements to read a string and input the string into the genre field of the struct.
		
		
		if (genreString == "blues")
		{
			aSong.genre = aSong.Blues;
			break;
		}

		else if (genreString == "electronic")
		{
			aSong.genre = aSong.Electronic;
			break;
		}

		else if (genreString == "country")
		{
			aSong.genre = aSong.Country;
			break;
		}

		else if (genreString == "folk")
		{
			aSong.genre = aSong.Folk;
			break;
		}

		else if (genreString == "hip hop" || genreString == "hiphop")
		{
			aSong.genre = aSong.HipHop;
			break;
		}

		else if (genreString == "jazz")
		{
			aSong.genre = aSong.Jazz;
			break;
		}

		else if (genreString == "latin")
		{
			aSong.genre = aSong.Latin;
			break;
		}

		else if (genreString == "pop")
		{
			aSong.genre = aSong.Pop;
			break;
		}

		else if (genreString == "rock")
		{
			aSong.genre = aSong.Rock;
			break;
		}
	}

  	mySongs.push_back (aSong);
}

// function to save the songs to a .txt file in binary mode, credit to Wesley A.
// I used part of his code and changed it to make sense for me.
void saveSong(metadata::Song& aSong, string fileName)									
{

	ofstream musicDatabase;
	musicDatabase.open(fileName, ios::out | ios::binary);
	auto vectorCount = mySongs.begin();
	while (vectorCount != mySongs.end())
	{
		metadata::Song aSong = *vectorCount;
		musicDatabase.write((char*)&aSong, sizeof(aSong));
		vectorCount++;
	}
}

// function to list the songs out
void listSong()
{
	int vectorCount = 0;
	vector <metadata::Song>::iterator songCount;
	metadata::Song aSong;

	for (songCount = mySongs.begin(); songCount < mySongs.end(); songCount++)
	{
		aSong = *songCount;
		cout << "#" << vectorCount + 1 << "\n";
		cout << "Title : " << aSong.title << "\n";
		cout << "Artist: " << aSong.artist << "\n";
		cout << "Album : " << aSong.album << "\n";
		cout << "Track : " << aSong.track << "\n";
		cout << "Year  : " << aSong.releaseYear << "\n";
		if (aSong.genre == 0)
			cout << "Genre : Blues\n";
		if (aSong.genre == 1)
			cout << "Genre : Country\n";
		if (aSong.genre == 2)
			cout << "Genre : Electronic\n";
		if (aSong.genre == 3)
			cout << "Genre : Folk\n";
		if (aSong.genre == 4)
			cout << "Genre : Hip Hop\n";
		if (aSong.genre == 5)
			cout << "Genre : Jazz\n";
		if (aSong.genre == 6)
			cout << "Genre : Latin\n";
		if (aSong.genre == 7)
			cout << "Genre : Pop\n";
		if (aSong.genre == 8)
			cout << "Genre : Rock\n";
		cout << "\n";
		vectorCount++;
	}
}

//function to clear the music database
void clearSong(string fileName)			
{
	mySongs.clear();											// clear the vector
	fstream musicDatabase;										// clear the txt file
	musicDatabase.open(fileName, ios::out | ios::trunc);		// code taken from https://stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c
	musicDatabase.close();
}

void menu()
{
	cout << "add   : add a song to the database\n";
	cout << "list  : list the songs in the database\n";
	cout << "save  : save the songs to the database\n";
	cout << "sort  : sort database by title/artist/year\n";
	cout << "clear : clear the song database\n";
	cout << "find  : search for a song in the database\n";
	cout << "import: import metadata from .mp3 file\n";
	cout << "help  : display this menu\n";
	cout << "x     : exit the program\n";
}

bool sortByYear(metadata::Song left, metadata::Song right)
{
	return (left.releaseYear < right.releaseYear);
}

void sortYear()
{
	sort(mySongs.begin(), mySongs.end(), sortByYear);
}

//credit to Curtis for helping me with the sort function
bool sortByArtist(metadata::Song left, metadata::Song right)
{
	char* l = left.artist;
	char* r = right.artist;
	return strcmp(l, r) < 0;
}

void sortArtist()
{
	sort(mySongs.begin(), mySongs.end(), sortByArtist);
}

bool sortByTitle(metadata::Song left, metadata::Song right)
{
	char* l = left.title;
	char* r = right.title;
	return strcmp(l, r) < 0;
}

void sortTitle()
{
	sort(mySongs.begin(), mySongs.end(), sortByTitle);
}

//bool songSearch(metadata::Song search, string searchByTitle)
//{
//
//}
//
//void findSong()
//{
//	find_if(mySongs.begin(), mySongs.end(), );
//}


void importSong(string songName)
{
	
	ID3_Tag song(string songName + ".mp3");

}
