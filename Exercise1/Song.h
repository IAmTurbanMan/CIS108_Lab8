#pragma once
#include <iostream>
#include <string>


namespace metadata
{

	struct Song
	{
		char title [64];
		char artist [64];
		char album [64];
		int track;
		int releaseYear;
		enum genre
		{
			Blues = 0,
			Country,
			Electronic,
			Folk,
			HipHop,
			Jazz,
			Latin,
			Pop,
			Rock
		} genre;
	};
}