#include "Combinations.h"

Combinations::Combinations()
{
	this->lib = new Additional();
	this->n = 0;
	this->k = 0;
	this->Tab = nullptr;
	this->solution = nullptr;
	this->repetitions = 0;
	this->index = 0;
}

Combinations::Combinations(int n, int k)
{
	this->lib = new Additional();
	this->n = n;
	this->k = k;
	this->Tab = new int[n];
	for (int i = 1; i <= n; i++) {
		Tab[i-1] = i;
	}
	this->solution = new int[k];
	for (int i = 0; i < k; i++) {
		solution[i] = i + 1;
	}
	this->repetitions = (int)lib->Newton(n, k);
	this->index = k - 1;
}

Combinations::~Combinations()
{
	delete this->solution;
	delete this->Tab;
}

bool Combinations::hasNext() {
	if (this->repetitions > 0) {
		this->repetitions--;
		return true;
	}
	else {
		return false;
	}
}

void Combinations::update()
{
	if (solution[index] == n) {
		do {
			index--;
		} while (solution[index]+1 == solution[index+1]);
		solution[index]++;
		int bufor = solution[index];
		this->index++;
		for (int i=1, j = this->index; j < k; j++, i++) {
			solution[j] = bufor+i;
		}
		this->index = this->k - 1;
	}
	else {
		solution[this->index]++;
	}
}

int Combinations::searchKey(int key)
{
	for (int i = 0; i < this->k; i++) {
		if (this->solution[i] == key) {
			return i;
		}
	}
	return -1;
}

int* Combinations::getTab()
{
	return this->Tab;
}

int* Combinations::getSolution()
{
	return this->solution;
}

void Combinations::print() {
	while (this->hasNext()) {
		for (int i = 0; i < this->k; i++) {
			std::cout << " " << solution[i] << " ";
		}
		std::cout << "\n";
		update();
	}
}
