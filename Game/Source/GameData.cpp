#include "GameData.h"

namespace GameData
{
	const std::vector<VectorTwo>shipPoints
	{
		{ 5, 0 }, 
		{ -5, -5 }, 
		{ -5, 5 },
		{ 5, 0 }
	};

	const std::vector<VectorTwo>powerPoints
	{
		{1, 7},
		{7, 1},
		{-7, 1},
		{-1, 7},
		{-7, -7},
		{-1, -1},
		{1, 7}
	};
}