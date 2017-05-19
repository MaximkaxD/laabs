#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

using namespace std;
#define MAX_CATS 3
#define MAX_DOGS 3


class Animals 
{
protected: 
	string breed; 
	float height; 
	float weight; 
	unsigned int age; 
virtual ~Animals()
{
	int aaa;
	aaa = 5;
};
public: 
	virtual const char* animal_kind() = 0; 	
	void print(void); 	
	virtual int getCount(const char* Kind)	{ return 0; }; 
};

void Animals::print(void) {
	class Local 
    {
	public: 
        void Breed(){	std::cout << "Порода: ";	}
		void Age(){	std::cout << "Возраст: ";	}
		void Height(){	std::cout << "Рост: ";	}
		void Weight(){	std::cout << "Вес: ";	}
    };

	Local local; 
	
	local.Breed();	cout << breed << "\n";
	local.Age();	cout << age << "\n";
	local.Height();	cout << height << "\n";
	local.Weight();	cout << weight << "\n\n";	
}

class Cat : public virtual Animals
{
private:
	class Nested {
		public:
			static int count; 
	};

public: 
	Cat(){}; 
   ~Cat(){}; 
	static int getCount(void) { return Nested::count; } 
	const char* getKindName() {	return "Вид животного - Кот"; };
	Cat& operator++(){	++Nested::count;	return *this;	};
	Cat& operator--(){	--Nested::count;	return *this;	}; 
	Cat operator+(float Weight) { Cat* TempObject;	TempObject = this;	TempObject->weight += Weight;	
																
return *TempObject; }; 
};


class Dog : public virtual Animals 
{
private: 
	class Nested {
		public:
			static int count; 
	};

public: 
	Dog(){}; 
   ~Dog(){};
    static int getCount(void) { return Nested::count; } 
	const char* getKindName() {	return "Вид животного - Собака"; };
	Dog& operator++(){	++Nested::count; 	return *this;	}; 
	Dog& operator--(){	--Nested::count;	return *this;	}; 
	Dog operator+(float Weight) { Dog* TempObject;	TempObject = this;	TempObject->weight += Weight;	
return *TempObject; }; 
};

int Cat::Nested::count = 0;
int Dog::Nested::count = 0;


class Pets : public Cat, public Dog 
{
private: 
	string kind; 

public: 
	Pets(const char* Kind = NULL, const char* Breed = NULL, unsigned int Age = 0, float Height = 0.0f, float Weight = 0.0f);  	
	Pets(const Pets& source);  
   ~Pets();
	friend void changeBreed(Pets& object, const char* str); 
	virtual const char* animal_kind(); 	
	virtual int getCount(const char* Kind); 
};

int Pets::getCount(const char* Kind)
{
	if ( kind == "Собака" ) return Dog::getCount();
		else	if ( kind == "Кот" ) return Cat::getCount();

	return 0;
}

Pets::Pets(const char* Kind, const char* Breed, unsigned int Age, float Height, float Weight)
{	
	this->kind = Kind; 
	this->breed = Breed; 
	this->age = Age; 
	this->height = Height; 
	this->weight = Weight; 	

	if ( kind == "Собака" ) Dog::operator++();
		else	if ( kind == "Кот" ) Cat::operator++();
}

Pets::Pets(const Pets& source)
{
	this->kind = source.kind; 
	this->breed = source.breed; 
	this->age = source.age; 
	this->height = source.height; 
	this->weight = source.weight; 

	if ( kind == "Собака" ) Dog::operator++();
		else	if ( kind == "Кот" ) Cat::operator++();
}

Pets::~Pets()
{
	if ( kind == "Собака" ) Dog::operator--();
		else	if ( kind == "Кот" ) Cat::operator--();		
}

const char* Pets::animal_kind()
{	
	if ( kind == "Собака" )	return	Dog::getKindName();
	if ( kind == "Кот" )	return	Cat::getKindName();
	return "";
}

void changeBreed(Pets& object, const char* str) {
	object.breed = str;   
}



int main(void)
{
	
	vector<Animals*> arrayOfAnnimals;
	unsigned int i=0;
	char breedsCat[][20] = { "Египетская", "Сиамская", "Канадский сфинкс"};
	char breedsDog[][20] = { "Далматин", "Доберман", "Лабрадор"};

	setlocale(LC_ALL, "Russian"); 

	for (i = 0; i < MAX_CATS; i++)
		arrayOfAnnimals.push_back(new Pets("Кот", breedsCat[i], i, i + 16.23f, i + 1.331f));

	for (i = 0; i < MAX_DOGS; i++)
		arrayOfAnnimals.push_back(new Pets("Собака", breedsDog[i], i, i + 52.23f, i + 15.331f));

	cout << "Количество собак - " << arrayOfAnnimals[0]->getCount("Собака") << "\n";
	cout << "Количество kотов - " << arrayOfAnnimals[0]->getCount("Кот") << "\n\n";

	for (unsigned int i = 0; i < arrayOfAnnimals.size(); ++i) {
		cout << arrayOfAnnimals[i]->animal_kind() << "\n";	
		arrayOfAnnimals[i]->print();		
	}

	/*
	delete arrayOfAnnimals;
	arrayOfAnnimals.pop_back();

	cout << "Количество собак - " << arrayOfAnnimals[0]->getCount("Собака") << "\n";
	cout << "Количество котов - " << arrayOfAnnimals[0]->getCount("Кот") << "\n\n";
	*/
	system("pause"); 

	return 0;
}





/*

//virtual ~Base();            



*/

/*
int main(void) {
	char breeds[][20] = { "Dolmatine", "Pudel", "Taksa", "German Ovcharka", "Mops", "Beegle", "Bulldog", "Haskee", "Chau-Chau", "Pincher" };
	vector<Dog*> arrayOfDogs;
	for (unsigned int i = 0; i < MAX_DOGS; ++i) {
		arrayOfDogs.push_back(new Dog(breeds[i], i, i + 16.23f, i + 19.331f));
		cout << Dog::getCount() << "\n";
	}
	changeBreed(*(arrayOfDogs[0]), "NONDOLMATINE");
	//
	cout << "\n";
	for (unsigned int i = 0; i < arrayOfDogs.size(); ++i) {
		arrayOfDogs[i]->print();
		delete arrayOfDogs[i];
		cout << "\n\n" << Dog::getCount() << "\n\n";
	}
	system("pause");
	return 0;
