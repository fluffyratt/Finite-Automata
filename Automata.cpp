#include <iostream> 
#include <fstream> 
#include <vector> 
#include <unordered_map> 
#include <string> 
#include <set> 
/* 
Кінцевий автомат: 
Стани: {0, 1, 2, 3} 
Початковий стан: 0 
Фінальний стан: {3} 
Переходи: 
0 --a--> 1 
1 --a--> 2 
1 --b--> 3 
2 --a--> 3 
2 --b--> 2 
3 --a--> 3 
3 --b--> 3 
*/ 
struct Automaton { 
	int size; 
	int startState; 
	std::set<int> finalStates; 
	std::unordered_map<int, std::unordered_map<char, int>> transitions; 
	}; 

Automaton readAutomatonFromFile(const std::string& filename) { Automaton automaton; 
	std::ifstream file(filename); 
	if (!file) { 
	std::cerr << "Failed to open file." << std::endl; 
	exit(1); 
	} 

// Зчитуємо розмір автомата 
	file >> automaton.size; 

// Зчитуємо початковий стан 
	file >> automaton.startState; 

// Зчитуємо фінальні стани 
	int numOfFinalStates; 
	file >> numOfFinalStates; 
	for (int i = 0; i < numOfFinalStates; ++i) { 
		int finalState; 
		file >> finalState; 
		automaton.finalStates.insert(finalState); 
	} 

// Зчитуємо переходи 
	int from, to; 
	char transitionChar; 
	while (file >> from >> transitionChar >> to) { 
		automaton.transitions[from][transitionChar] = to; 
	} 

	file.close(); 
	return automaton; 
} 

bool isWordAccepted(const Automaton& automaton, const std::string& word) 
	{ 
   int currentState = automaton.startState; 
	for (char ch : word) { 
		// Перевіряємо, чи існує перехід 
		if (automaton.transitions.at(currentState).find(ch) == 
			automaton.transitions.at(currentState).end()) { 
		return false; 
} 
	currentState = 
automaton.transitions.at(currentState).at(ch); 
} 

	// Перевіряємо, чи перебуває останній стан у фінальних 

	return automaton.finalStates.find(currentState) != automaton.finalStates.end(); 
} 
bool checkForWords(const Automaton& automaton, const std::string& w1, const std::string& w2) {

	// Генерація слів w0, довжина яких не перевищує 10 символів 
	for (int len = 1; len <= 10; ++len) {
		for (int i = 0; i < (1 << len); ++i) {
			std::string w0;
			for (int j = 0; j < len; ++j) {
				if (i & (1 << j)) w0 += 'b'; // Заміна на 'b' 
				else w0 += 'a'; // Заміна на 'a' 
			}

			// Перевіряємо, чи приймає автомат w1 + w0 + w2 
			if (isWordAccepted(automaton, w1 + w0 + w2))
				return true;
		}
	}
	return false;
}

/* 
Кейсові ситуації 
Позитивні: 
w1 = "a", w2 = "a" 
Причина: існує слово «abba», де w0 = «bb». 

w1 = "a", w2 = "b" 
Причина: існує слово "aab", де w0 = "a". 

Негативні: 
w1 = "b", w2 = "a" 
Причина: не існує слів, які починаються з "b" і закінчуються на "a" 

w1 = "bb", w2 = "aa" 
Причина: не існує слів, які починаються з "bb" і закінчуються на "aa" 
*/ 


int main() {

	Automaton automaton = readAutomatonFromFile("automation.txt");
	std::string w1, w2;
	std::cout << "Enter w1: ";
	std::cin >> w1;
	std::cout << "Enter w2: ";
	std::cin >> w2;

	if (checkForWords(automaton, w1, w2)) {
		std::cout << "The automaton admits words of the form w = w1 w0 w2." << std::endl;
	}
	else {
		std::cout << "The automaton does not admit words of the form w = w1 w0 w2." << std::endl;
	}

	return 0;

}