#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <id3/tag.h>
#include <id3/misc_support.h>
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

void importSong()
{
	string mp3File;
	cout << "Enter the path of the song you would like to import: ";
	cin >> mp3File;
	cout << "\n";

	ID3_Tag songTag;
	try
	{
		songTag.Link(mp3File.c_str(), ID3TT_ID3V1 | ID3TT_LYRICS3V2 | ID3TT_MUSICMATCH);
	}
	catch (...)
	{
		throw new exception("Failed to load MP3 file");
	}

	if (songTag.GetFileSize() == 0)
	{
		throw new exception("Failed to load MP3 file");
	}

	ID3_Frame* titleFrame = songTag.Find(ID3FID_TITLE);
	if (NULL != titleFrame)
	{
		ID3_Field* titleField = titleFrame->GetField(ID3FN_TEXT);
		titleField->Get(aSong.title, 64);
		aSong.title[64 - 1] = '\0';
	}

	//ID3_Tag* songImport = &songTag;

	char* importTitle = ID3_GetTitle(&songTag);
	char* importArtist = ID3_GetArtist(&songTag);
	char* importAlbum = ID3_GetAlbum(&songTag);
	char* importTrack = ID3_GetTrack(&songTag);
	char* importReleaseYear = ID3_GetYear(&songTag);
	char* importGenre = ID3_GetGenre(&songTag);

	strcpy_s(aSong.title, importTitle);
	strcpy_s(aSong.artist, importArtist);
	strcpy_s(aSong.album, importAlbum);
	aSong.track = stoi(importTrack);
	aSong.releaseYear = stoi(importReleaseYear);

	string genreString;
	genreString = importGenre;
	transform(genreString.begin(), genreString.end(), genreString.begin(), ::tolower);

	aSong.genre = aSong.Unknown;

	if (genreString == "blues")
	{
		aSong.genre = aSong.Blues;
	}

	else if (genreString == "electronic")
	{
		aSong.genre = aSong.Electronic;
	}

	else if (genreString == "country")
	{
		aSong.genre = aSong.Country;
	}

	else if (genreString == "folk")
	{
		aSong.genre = aSong.Folk;
	}

	else if (genreString == "hip hop" || genreString == "hiphop")
	{
	aSong.genre = aSong.HipHop;
	}

	else if (genreString == "jazz")
	{
		aSong.genre = aSong.Jazz;
	}

	else if (genreString == "latin")
	{
		aSong.genre = aSong.Latin;
	}

	else if (genreString == "pop")
	{
		aSong.genre = aSong.Pop;
	}

	else if (genreString == "rock")
	{
		aSong.genre = aSong.Rock;
	}
	
	ID3_FreeString(importTitle);
	ID3_FreeString(importAlbum);
	ID3_FreeString(importArtist);
	ID3_FreeString(importTrack);
	ID3_FreeString(importReleaseYear);
	ID3_FreeString(importGenre);

	mySongs.push_back(aSong);

	cout << importTitle << " has been imported to the database.\n";
}
	
	
	/*ID3_Tag song_tag;
	try
	{
		song_tag.Link(mp3_file.c_str(), ID3TT_ID3V1 | ID3TT_LYRICS3V2 | ID3TT_MUSICMATCH);
	}
	catch (...)
	{
		throw new exception("Failed to load MP3 file");
	}

	if (song_tag.GetFileSize() == 0)
	{
		throw new exception("Failed to load MP3 file");
	}

	metadata::Song aSong;
	memset(&aSong, 0, sizeof(aSong));
	strncpy_s(aSong.title, UNKNOWN, 64);
	strncpy_s(aSong.artist, UNKNOWN, 32);
	strncpy_s(aSong.album, UNKNOWN, 64);

	auto title_tag_frame = song_tag.Find(ID3FID_TITLE);
	if (title_tag_frame != NULL)
	{
		auto title_tag_field = title_tag_frame->GetField(ID3FN_TEXT);
		title_tag_field->Get(aSong.title, 64);
		aSong.title[64 - 1] = '\0';
	}

	auto artist_tag_frame = song_tag.Find(ID3FID_ORIGARTIST);
	if (artist_tag_frame == NULL)
		artist_tag_frame = song_tag.Find(ID3FID_LEADARTIST);
	if (artist_tag_frame == NULL)
		artist_tag_frame = song_tag.Find(ID3FID_MIXARTIST);
	if (artist_tag_frame == NULL)
		artist_tag_frame = song_tag.Find(ID3FID_WWWARTIST);
	if (artist_tag_frame != NULL)
	{
		auto artist_tag_field = artist_tag_frame->GetField(ID3FN_TEXT);
		artist_tag_field->Get(aSong.artist, 32);
		aSong.artist[32 - 1] = '\0';
	}

	auto album_tag_frame = song_tag.Find(ID3FID_ALBUM);
	if (album_tag_frame != NULL)
	{
		auto album_tag_field = album_tag_frame->GetField(ID3FN_TEXT);
		album_tag_field->Get(aSong.album, 64);
		aSong.album[64 - 1] = '\0';
	}

	auto track_tag_frame = song_tag.Find(ID3FID_TRACKNUM);
	if (track_tag_frame != NULL)
	{
		char track_num[32];
		auto track_tag_field = track_tag_frame->GetField(ID3FN_TEXT);
		track_tag_field->Get(track_num, 32);
		aSong.track = ::strtoul(track_num, NULL, 10);
	}

	auto year_tag_frame = song_tag.Find(ID3FID_YEAR);
	if (year_tag_frame == NULL)
		year_tag_frame = song_tag.Find(ID3FID_ORIGYEAR);
	if (year_tag_frame != NULL)
	{
		char year[32];
		auto year_tag_field = year_tag_frame->GetField(ID3FN_TEXT);
		year_tag_field->Get(year, 32);
		aSong.releaseYear = ::strtoul(year, NULL, 10);
	}

	auto genre = ID3_GetGenreNum(&song_tag);

	string genreString = ID3_V1GENRE2DESCRIPTION(genre);
	transform(genreString.begin(), genreString.end(), genreString.begin(), ::tolower);

	aSong.genre = aSong.Unknown;

	if (genreString == "blues")
	{
		aSong.genre = aSong.Blues;
	}

	else if (genreString == "electronic")
	{
		aSong.genre = aSong.Electronic;
	}

	else if (genreString == "country")
	{
		aSong.genre = aSong.Country;
	}

	else if (genreString == "folk")
	{
		aSong.genre = aSong.Folk;
	}

	else if (genreString == "hip hop" || genreString == "hiphop")
	{
		aSong.genre = aSong.HipHop;
	}

	else if (genreString == "jazz")
	{
		aSong.genre = aSong.Jazz;
	}

	else if (genreString == "latin")
	{
		aSong.genre = aSong.Latin;
	}

	else if (genreString == "pop")
	{
		aSong.genre = aSong.Pop;
	}

	else if (genreString == "rock")
	{
		aSong.genre = aSong.Rock;
	}
}*/

	// add the song to the database