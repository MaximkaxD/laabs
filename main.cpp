#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define MAX_DOGS 10

class Dog { // класс "собака"
private:
	static int count; 
	string breed; 
	unsigned int age; 
	float height, weight;
public:
	Dog(const char* breed = NULL,
		unsigned int age = 0,
		float height = 0.0f,
		float weight = 0.0); 
	Dog(Dog& object);
	~Dog(); 
	void print(void); 
	friend void changeBreed(Dog& object, const char* str); 
	static int getCount(void) { return count; } 
};

int Dog::count;

Dog::Dog(const char* breed, unsigned int age, float height, float weight) {
	this->breed = breed;
	this->age = age;
	this->height = height;
	this->weight = weight;
	++count;
}

Dog::Dog(Dog& object) {
	this->breed = object.breed;
	this->age = object.age;
	this->height = object.height;
	this->weight = object.weight;
	++count;
}

Dog::~Dog() {
	--count;
}

void Dog::print(void) {
	cout << "Breed: " << breed << "\n" <<
		"Age: " << age << "\n" <<
		"Height: " << height << "\n" <<
		"Weight: " << weight << "\n";
}

void changeBreed(Dog& object, const char* str) {
	object.breed = str;
}

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
}