#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(AdjMatrix* matrix)
{
	this->population = nullptr;
	this->parents = nullptr;
	this->children = nullptr;
	this->graph = matrix;
	this->populationSize = 10;		//Ten parametr bêdzie tak¿e liczb¹ rodziców
	this->tournamentParticipants = populationSize / 4;		//¯eby nie braæ wszystkich
	this->crossingFactor = 0.9;
	this->mutationFactor = 0.9;
	this->iterations = 1;
	this->bestPath = new BiList();
	//Wype³niam najlepsz¹ œcie¿kê zerami
	for (int i = 0; i < graph->getV() - 1; i++) {
		bestPath->addAtTheEnd(0);
	}
	this->bestWeight = INT_MAX;
	//Start randomizing
	srand(time(NULL));
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	delete this->bestPath;
}

void GeneticAlgorithm::calculate()
{
	//Wybór populacji pocz¹tkowej (rodziców)
	//Ocena przystosowania chromosomów
	generatePopulation();
	//Pêtla - sprawdzenie warunku zatrzymania
	for (int x = 0; x < iterations; x++) {
		//a. selekcja chromosomów do populacji macierzystej:
		chooseParents();
		//b. + d. krzy¿owanie chromosomów z populacji rodzicielskiej i ocena dzieci
		crossing();
		//c. + d. mutacja i ocena jeœli mutacja zasz³a

		//e. utworzenie nowej populacji: parents + children

	}
	showBestCycle();
}

void GeneticAlgorithm::showBestCycle()
{
	std::cout << "Najkrotsza sciezka:\n";
	std::cout << "[ 0 ";
	for (int i = 0; i < bestPath->getCount(); i++) {
		std::cout << bestPath->getElement(i)->key << " ";
	}
	std::cout << "0 ]\n";
	std::cout << "Cost: " << bestWeight << "\n";
}

void GeneticAlgorithm::setPopulationSize(int size)
{
	this->populationSize = size;
}

int GeneticAlgorithm::getPopulationSize()
{
	return this->populationSize;
}

void GeneticAlgorithm::setCrossingFactor(double factor)
{
	this->crossingFactor = factor;
}

double GeneticAlgorithm::getCrossingFactor()
{
	return this->crossingFactor;
}

void GeneticAlgorithm::setMutationFactor(double factor)
{
	this->mutationFactor = factor;
}

double GeneticAlgorithm::getMutationFactor()
{
	return this->mutationFactor;
}

void GeneticAlgorithm::setIterations(int iterations)
{
	this->iterations = iterations;
}

BiList* GeneticAlgorithm::getBestPath()
{
	return this->bestPath;
}

int GeneticAlgorithm::getBestWeight()
{
	return this->bestWeight;
}

void GeneticAlgorithm::chooseParents()
{
	if (parents != nullptr) {
		delete parents;
	}
	parents = new ListOfIndividuals();
	//Wybieram populationSize rodziców
	for (int i = 0; i < populationSize; i++) {
		//Zbiór indeksów osobników do wylosowania w turnieju
		BiList* set = new BiList();
		//Wype³niam ten zbiór
		for (int j = 0; j < population->getSize(); j++) {
			set->addAtTheEnd(j);
		}
		//Wybieram tournamentParticipants indeksów i zapamiêtujê ten najlepszy
		int bestIndex = 0;
		int bestCost = INT_MAX;
		for (int j = 0; j < tournamentParticipants; j++) {
			//Losujê pozycjê ze zbioru
			int setIndex = (std::rand() % set->getCount());
			//Wybór - indeks w populacji
			int index = set->getElement(setIndex)->key;
			//usuwam ze zbioru indeksów
			set->removeOnPosition(set->getElement(setIndex));
			//Sprawdzam czy aktualnie najlepszy:
			if (population->getElement(index)->individual->getCost() < bestCost) {
				bestIndex = index;
				bestCost = population->getElement(index)->individual->getCost();
			}
		}
		//W tym momencie mam zwyciêzcê turnieju, zatem dodajê go do populacji rodziców
		//Individual* ind = population->getElement(bestIndex)->individual;
		//ind->getPath()->showList();
		//std::cout << "Cost = " << ind->getCost() << "\n";
		//parents->addAtTheEnd(population->getElement(bestIndex)->individual);
		//parents->getTail()->individual->getPath()->showList();
		//std::cout << "Cost = " << parents->getTail()->individual->getCost() << "\n";
		
		Individual* ind = new Individual(graph->getV()-1);
		ind->setCost(population->getElement(bestIndex)->individual->getCost());
		for (int j = 0; j < ind->getSize(); j++) {
			ind->getPath()->getElement(j)->key = population->getElement(bestIndex)->individual->getPath()->getElement(j)->key;
		}
		parents->addAtTheEnd(ind);

		//I usuwam z populacji
		population->removeOnPosition(bestIndex);
	}
	showParents();
}

void GeneticAlgorithm::showPopulation()
{
	std::cout << "POPULATION:\n";
	for (int i = 0; i < population->getSize(); i++) {
		std::cout << "Size = " << population->getElement(i)->individual->getSize() << "\n";
		population->getElement(i)->individual->getPath()->showList();
		std::cout << "Cost = " << population->getElement(i)->individual->getCost() << "\n";
	}
}

void GeneticAlgorithm::showParents()
{
	std::cout << "PARENTS:\n";
	std::cout << parents->getSize() << " elements\n";
	for (int i = 0; i < parents->getSize(); i++) {
		std::cout << "Size = " << parents->getElement(i)->individual->getSize() << "\n";
		parents->getElement(i)->individual->getPath()->showList();
		std::cout << "Cost = " << parents->getElement(i)->individual->getCost() << "\n";
	}
}

void GeneticAlgorithm::crossing()
{
	if (children != nullptr) {
		delete children;
	}
	children = new ListOfIndividuals();
	//W tym miejscu uwzglêdniam tak¿e wspó³czynnik krzy¿owania
	//Krzy¿ujê s¹siednie osobniki
	for (int i = 0; i+1<=parents->getSize()-1; i+=2) {
		//Losujê parametr
		double parameter = drawFromTheRange01();
		//Jeœli mniejszy lub równy wspó³czynnikowi:
		if (parameter <= crossingFactor) {
			PMXCrossover(parents->getElement(i)->individual, parents->getElement(i+1)->individual);
		}
	}
	//Wyœwietl listê dzieci
	std::cout << "\nChildren:\n";
	for (int i = 0; i < children->getSize(); i++) {
		children->getElement(i)->individual->getPath()->showList();
		std::cout << "Cost = " << children->getElement(i)->individual->getCost() << "\n";
	}
}

void GeneticAlgorithm::PMXCrossover(Individual* parent1, Individual* parent2)
{
	int size = this->graph->getV() - 1;
	//Dzieci ze œcie¿kami wype³nionymi zerami
	Individual* child1 = new Individual(size);
	Individual* child2 = new Individual(size);

	//Listy mapuj¹ce
	BiList* map1 = new BiList();
	BiList* map2 = new BiList();
	for (int i = 0; i < graph->getV(); i++) {
		map1->addAtTheEnd(0);
		map2->addAtTheEnd(0);
	}

	int index1, index2;
	//Losujê indeksy:
	index1 = std::rand() % size;
	do {
		index2 = std::rand() % size;
	} while (index2 == index1);
	//Zamiana kolejnoœci¹ ¿eby pierwszy by³ zawsze mniejszy
	if (index2 < index1) {
		int bufor = index1;
		index1 = index2;
		index2 = bufor;
	}

	//Przepisujê wylosowane fragmenty do dzieci
	//I tworzê ci¹gi odwzorowañ
	for (int i = index1; i <= index2; i++) {
		child1->getPath()->getElement(i)->key = parent1->getPath()->getElement(i)->key;
		child2->getPath()->getElement(i)->key = parent2->getPath()->getElement(i)->key;
		map1->getElement(  parent1->getPath()->getElement(i)->key  )->key = parent2->getPath()->getElement(i)->key;
		map2->getElement(  parent2->getPath()->getElement(i)->key  )->key = parent1->getPath()->getElement(i)->key;
	}

	//Moment tworzenia dzieci
	//dziecko 1
	for (int i = 0; i < size; i++) {
		if (child1->getPath()->getElement(i)->key == 0) {
			/*int ind = parent1->getPath()->getElement(i)->key;
			//Elementy niezmapowane - przepisujê
			if (map1->getElement(ind)->key == 0 && map2->getElement(ind)->key == 0) {
				child1->getPath()->getElement(i)->key = parent1->getPath()->getElement(i)->key;
			}
			else {
				//Elementy zmapowane - odpowiednik z map2
				child1->getPath()->getElement(i)->key = map2->getElement(ind)->key;
			}*/
			
			if (!isInPath(parent2->getPath()->getElement(i)->key, index1, index2, child1)) {
				child1->getPath()->getElement(i)->key = parent2->getPath()->getElement(i)->key;
			}
			else {
				int temp = parent2->getPath()->getElement(i)->key;

				do {
					temp = map1->getElement(temp)->key;
				} while (isInPath(temp, index1, index2, child1));

				child1->getPath()->getElement(i)->key = temp;
			}
		}
	}

	//dziecko 2
	for (int i = 0; i < size; i++) {
		if (child2->getPath()->getElement(i)->key == 0) {
			/*int ind = parent2->getPath()->getElement(i)->key;
			//Elementy niezmapowane - przepisujê
			if (map1->getElement(ind)->key == 0 && map2->getElement(ind)->key == 0) {
				child2->getPath()->getElement(i)->key = parent2->getPath()->getElement(i)->key;
			}
			else {
				//Elementy zmapowane - odpowiednik z map1
				child2->getPath()->getElement(i)->key = map1->getElement(ind)->key;
			}*/

			if (!isInPath(parent1->getPath()->getElement(i)->key, index1, index2, child2)) {
				child2->getPath()->getElement(i)->key = parent1->getPath()->getElement(i)->key;
			}
			else {
				int temp = parent1->getPath()->getElement(i)->key;

				do {
					temp = map2->getElement(temp)->key;
				} while (isInPath(temp, index1, index2, child2));

				child2->getPath()->getElement(i)->key = temp;
			}
		}
	}
	//Obliczam koszt dzieci
	calculateCost(child1);
	calculateCost(child2);

	//Sprawdzam czy rozwi¹zanie nie jest najlepsze
	if (child1->getCost() < bestWeight) {
		updateBestPath(child1);
	}
	else if (child2->getCost() < bestWeight) {
		updateBestPath(child2);
	}

	//Dodajê narodzone dzieci do listy
	children->addAtTheEnd(child1);
	children->addAtTheEnd(child2);
}

bool GeneticAlgorithm::isInPath(int value, int beg, int end, Individual* ind)
{
	for (int i = beg; i <= end; i++) {
		if (value == ind->getPath()->getElement(i)->key) {
			return true;
		}
	}
	return false;
}

void GeneticAlgorithm::inversionMutation(Individual* individual)
{
	int size = individual->getSize();
	int index1, index2;
	//Losowanie pierwszego indeksu
	index1 = std::rand() % size;
	//Losowanie drugiego indeksu
	do {
		index2 = std::rand() % size;
	} while (index2 == index1);
	//Zamiana kolejnoœci¹ ¿eby pierwszy by³ zawsze mniejszy
	if (index2 > index1) {
		int bufor = index1;
		index1 = index2;
		index2 = bufor;
	}
	//Operacja inwersji:
	individual->getPath()->reverse(index1, index2);
}

void GeneticAlgorithm::exchangeMutation(Individual* individual)
{
	int size = individual->getSize();
	int index1, index2;
	//Losowanie pierwszego indeksu
	index1 = std::rand() % size;
	//Losowanie drugiego indeksu
	do {
		index2 = std::rand() % size;
	} while (index2 == index1);
	//Operacja zamiany:
	individual->getPath()->swap(index1, index2);
}

void GeneticAlgorithm::generatePopulation()
{
	this->population = new ListOfIndividuals();
	//Nowa pusta populacja
	for (int i = 0; i < populationSize*2; i++) {
		Individual* ind = new Individual(this->graph->getV() - 1);
		population->addAtTheEnd(ind);
	}
	//Losowanie wartoœci dla populacji:
	for (int i = 0; i < populationSize*2; i++) {
		//Wype³niam zbiór wierzcho³ków
		Array* set = new Array();
		for (int j = 1; j < graph->getV(); j++) {
			set->addAtTheEnd(j);
		}
		//Dla ka¿dego z nieu¿ytych wierzcho³ków:
		for (int j = 1; j < graph->getV(); j++) {
			//losowy indeks modulo rozmiar
			int index = (std::rand() % set->getSize());
			//Dodajê na koniec wybrany element
			population->getElement(i)->individual->getPath()->getElement(j - 1)->key = set->getTable()[index];
			//Usuwam ze zbioru wybrany element
			set->removeOnPosition(index);
		}
		delete set;
		calculateCost(population->getElement(i)->individual);
		//Aktualnie najlepsze rozwi¹zanie
		if (population->getElement(i)->individual->getCost() < bestWeight) {
			updateBestPath(population->getElement(i)->individual);
		}
		//population->getElement(i)->individual->getPath()->showList();
		//std::cout << " " << population->getElement(i)->individual->getCost() << " \n";
	}
	showPopulation();
	showBestCycle();
}

void GeneticAlgorithm::calculateCost(Individual* individual)
{
	int cost = 0;
	cost += graph->distance(0, individual->getPath()->getElement(0)->key);
	for (int i = 0; i < individual->getSize() - 1; i++) {
		cost += graph->distance(individual->getPath()->getElement(i)->key, individual->getPath()->getElement(i+1)->key);
	}
	cost += graph->distance(individual->getSize()-1, 0);
	//Ustawiam koszt w obiekcie
	individual->setCost(cost);
}

double GeneticAlgorithm::drawFromTheRange01()
{
	int number = std::rand() % 10000;
	double random = (double)number / 10000;
	return random;
}

void GeneticAlgorithm::updateBestPath(Individual* individual)
{
	bestWeight = individual->getCost();
	for (int i = 0; i < bestPath->getCount(); i++) {
		bestPath->getElement(i)->key = individual->getPath()->getElement(i)->key;
	}
}
