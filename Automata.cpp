#include <iostream> 
#include <fstream> 
#include <vector> 
#include <unordered_map> 
#include <string> 
#include <set> 
/* 
ʳ������ �������: 
�����: {0, 1, 2, 3} 
���������� ����: 0 
Գ������� ����: {3} 
��������: 
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

// ������� ����� �������� 
	file >> automaton.size; 

// ������� ���������� ���� 
	file >> automaton.startState; 

// ������� ������� ����� 
	int numOfFinalStates; 
	file >> numOfFinalStates; 
	for (int i = 0; i < numOfFinalStates; ++i) { 
		int finalState; 
		file >> finalState; 
		automaton.finalStates.insert(finalState); 
	} 

// ������� �������� 
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
		// ����������, �� ���� ������� 
		if (automaton.transitions.at(currentState).find(ch) == 
			automaton.transitions.at(currentState).end()) { 
		return false; 
} 
	currentState = 
automaton.transitions.at(currentState).at(ch); 
} 

	// ����������, �� �������� ������� ���� � ��������� 

	return automaton.finalStates.find(currentState) != automaton.finalStates.end(); 
} 
bool checkForWords(const Automaton& automaton, const std::string& w1, const std::string& w2) {

	// ��������� ��� w0, ������� ���� �� �������� 10 ������� 
	for (int len = 1; len <= 10; ++len) {
		for (int i = 0; i < (1 << len); ++i) {
			std::string w0;
			for (int j = 0; j < len; ++j) {
				if (i & (1 << j)) w0 += 'b'; // ����� �� 'b' 
				else w0 += 'a'; // ����� �� 'a' 
			}

			// ����������, �� ������ ������� w1 + w0 + w2 
			if (isWordAccepted(automaton, w1 + w0 + w2))
				return true;
		}
	}
	return false;
}

/* 
������ �������� 
��������: 
w1 = "a", w2 = "a" 
�������: ���� ����� �abba�, �� w0 = �bb�. 

w1 = "a", w2 = "b" 
�������: ���� ����� "aab", �� w0 = "a". 

��������: 
w1 = "b", w2 = "a" 
�������: �� ���� ���, �� ����������� � "b" � ����������� �� "a" 

w1 = "bb", w2 = "aa" 
�������: �� ���� ���, �� ����������� � "bb" � ����������� �� "aa" 
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