#include "Board.h"

Board::Board()
{
	// Determine the following amounts of objects:
	// Ants - 5
	// Dragons - 2
	// Food - 7 (units)

	numOfAnts = 5;
	numOfDragons = 4;
	numOfFood = 7;

	this->ClearMap();

	for (int i = 0; i < numOfAnts; i++)
		Ants.push_back(Ant(rand() % WIDTH, rand() % LENGTH));

	for (int i = 0; i < numOfDragons; i++)
		Dragons.push_back(Dragon(rand() % WIDTH, rand() % LENGTH));

	for (int i = 0; i < numOfFood; i++)
		Food.push_back({ rand() % WIDTH, rand() % LENGTH });

}

void Board::ClearMap()
{
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			Map[i][j] = ' ';
		}
	}

}


void Board::Update()
{
	for (unsigned int i = 0; i < Food.size(); i++)
	{
		Map[std::get<1>(Food[i])][std::get<0>(Food[i])] = 'F';
	}

	for (unsigned int i = 0; i < Ants.size(); i++)
	{
		Ants[i].Move();
		Map[Ants[i].GetY()][Ants[i].GetX()] = 'A';
	}

	for (unsigned int i = 0; i < Dragons.size(); i++)
	{
		Dragons[i].Move();
		Map[Dragons[i].GetY()][Dragons[i].GetX()] = 'D';
	}

	auto it = Ants.begin();    // An iterator for the "Ants" vector

	while (it != Ants.end())
	{
		it->InformOthers(Map);
		if (it->GetNutritionLevel() <= 0)
		{
			it = Ants.erase(it);
			--numOfAnts;
		}
		else it++;
	}

	auto ite = Dragons.begin(); // An iterator for the "Dragons" vector

	while (ite != Dragons.end())
	{
		ite->InformOthers(Map);
		if (ite->GetNutritionLevel() <= 0)
		{
			ite = Dragons.erase(ite);
			--numOfDragons;
		}
		else ite++;
	}

	// Check whether an ant has eaten food or it has been eaten

	for (unsigned int i = 0; i < Ants.size(); i++)
	{
		for (unsigned int j = 0; j < Food.size(); j++)
		{
			if (Ants[i].GetX() == std::get<0>(Food[j]) && Ants[i].GetY() == std::get<1>(Food[j]))
			{
				Ants[i].Eat(0);
				Food.erase(Food.begin() + j);
				AddFood();
				break;
			}
		}
	}

	it = Ants.begin();
	bool is_eaten = false;

	while (it != Ants.end()) {

		is_eaten = false;

		for (unsigned int j = 0; j < Dragons.size(); j++)
		{
			if (it->GetX() == Dragons[j].GetX() && it->GetY() == Dragons[j].GetY())
			{
				Dragons[j].Eat(it->GetNutritionLevel());
				it = Ants.erase(it);
				--numOfAnts;
				is_eaten = true;
				break;
			}
		}
		if (!is_eaten) it++;
	}

	this->ClearMap();

	for (unsigned int i = 0; i < Food.size(); i++)
	{
		Map[std::get<1>(Food[i])][std::get<0>(Food[i])] = 'F';
	}

	for (unsigned int i = 0; i < Ants.size(); i++)
	{
		Map[Ants[i].GetY()][Ants[i].GetX()] = 'A';
	}

	for (unsigned int i = 0; i < Dragons.size(); i++)
	{
		Map[Dragons[i].GetY()][Dragons[i].GetX()] = 'D';
	}
}

void Board::Print()
{
	for (int i = 0; i < WIDTH + 2; i++)
	{
		std::cout << "X";
	}
	std::cout << "\n";

	for (int i = 0; i < LENGTH; i++)
	{
		std::cout << "X";
		for (int j = 0; j < WIDTH; j++)
		{
			std::cout << Map[i][j];         // [row][column]
		}
		std::cout << "X\n";
	}

	for (int i = 0; i < WIDTH + 2; i++)
	{
		std::cout << "X";
	}

	std::cout << "\n";
}

void Board::PrintLog()
{
	std::cout << "[LOG]\n";
	std::cout << "Notifications of the ants:\n";
	Ant::PrintNotifications(10);
	std::cout << "Notifications of the dragons:\n";
	Dragon::PrintNotifications(10);
}

void Board::AddFood()
{
	Food.push_back({ rand() % WIDTH, rand() % LENGTH });
}

bool Board::NoAnts()
{
	return (numOfAnts == 0);
}

bool Board::NoDragons()
{
	return (numOfDragons == 0);
}

bool Board::IsFinished()
{
	return (numOfAnts == 0 || numOfDragons == 0);
}

