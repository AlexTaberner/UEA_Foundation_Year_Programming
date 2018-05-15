#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <bitset>
using namespace std;
vector<string> gameTypeStrings(int const & type);
string fillBinaryStringRand(int const & stringLength);
string userInput(int const & type);
string index2Code(int i);
string computerInput(int const & cows, int const & bulls, string const & lastGuess, vector<bool> & boolTable);
bool inputCheck01(char const & input);
int compareBulls(string const & a, string const & b);
int compareCows(string const & a, string const & b, int const & bulls);
int countZeros(string const & input);
void userInputProcess(string & output, string const & input, bool & loopCheck);
void codemasterPC();
void codemasterPlayer();
void gameCowsAndBulls(int const & mode);
void countZeros(string const & input, int & ones, int & zeros);
int main() {
	srand(time(NULL));
	while (true) {
		cout << "Please enter 1 for human codebreaking, 2 for computer codebreaking, anything else to exit: ";
		char input;
		cin >> input;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		if (input == 49) gameCowsAndBulls(0);
		else if(input == 50) gameCowsAndBulls(1);
		else break;
	}
	return 0;
}
string fillBinaryStringRand(int const & stringLength) {
	string output;
	for (int i = 0; i < stringLength; i++) {
		output.push_back((rand() % 2) + 48);
	}
	return output;
}
bool inputCheck01(char const & input) {
	bool output = false;
	if (input == 48 || input == 49) output = true;
	return output;
}
string userInput(string const & gameType) {
	string input, output;
	bool loopCheck = true;
	while (loopCheck) {
		cout << gameType;
		getline(cin, input);
		if (input.size() == 9) {
			userInputProcess(output, input, loopCheck);
		}
		else if (input.size() > 9) {
			cout << "your input was longer than 9 digits - using first 9 digits..." << endl;
			while (input.size() > 9) {
				input.pop_back();
			}
			userInputProcess(output, input, loopCheck);
		}
		else {
			cout << "INVALID INPUT" << endl;
		}
	}
	return output;
}
void userInputProcess(string & output, string const & input, bool & loopCheck) {
	for (size_t i = 0; i < input.size(); i++) {
		if (inputCheck01(input[i])) {
			output.push_back(input[i]);
			if (i == 8) {
				loopCheck = false;
			}
		}
		else {
			cout << "INVALID INPUT" << endl;
			output.clear();
			break;
		}
	}
}
vector<string> gameTypeStrings(int const & type) {
	vector<string> output;
	switch (type) {
	case 0:
		output = { "Please input your guess of |9| 1's and 0's on one line: ",
			"The computer has generated a string of numbers to guess.",
			"Your input: ",
			"you have guessed correctly!",
			"You have run out of tries!" };
		break;
	case 1:
		output = { "Please input a string of |9| 1's and 0's for the computer to guess on one line: ",
			"The computer Will now try to guess your string of numbers.",
			"Computers input: ",
			"The computer has guessed correctly!",
			"You have beaten the computer!" };
		break;
	};
	return output;
}
int compareBulls(string const & a, string const & b) {
	int output = 0;
	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] == b[i]) output++;
	}
	return output;
}
int compareCows(string const & a, string const & b, int const & bulls) {
	int aZero = 0, aOne = 0, bZero = 0, bOne = 0, output = 0;
	countZeros(a, aOne, aZero);
	countZeros(b, bOne, bZero);
	if (aZero > bZero) output += bZero;
	else output += aZero;
	if (aOne > bOne) output += bOne;
	else output += aOne;
	return output - bulls;
}
void countZeros(string const & input, int & ones, int & zeros) {
	for (size_t i = 0; i < input.size(); i++) {
		if (input[i] == 48) zeros++;
		else ones++;
	}
}
int countZeros(string const & input) {
	int zeros = 0;
	for (size_t i = 0; i < input.size(); i++) {
		if (input[i] == 48) zeros++;
	}
	return zeros;
}
void getBullsCows(int & cows, int & bulls, string const & playerInput, string const & codeMaster) {
	bulls = compareBulls(playerInput, codeMaster);
	cows = compareCows(playerInput, codeMaster, bulls);
}
void printGuessResult(int const & bulls, int const & cows, int const & loopCount, vector<string> const & gameType) {
	if (bulls == 9) {
		cout << gameType[3] << endl << endl;
	}
	else if (loopCount < 7) {
		cout << setw(7) << left << "Bulls: ";
		cout << bulls << endl;
		cout << setw(7) << left << "Cows: ";
		cout << cows << endl << endl;
	}
	else
	{
		cout << gameType[4] << endl << endl;
	}
}
void gameCowsAndBulls(int const & mode) {
	vector<bool> guesses;
	vector<string> strings = gameTypeStrings(mode);
	string codeMaster, playerInput = "";
	int cows = 0, bulls = 0;
	if (mode == 1) {
		codeMaster = userInput(strings[0]);
		guesses = vector<bool>(512, true);
	}
	else 
		codeMaster = fillBinaryStringRand(9);
	cout << strings[1] << endl;
	for (int i = 0; i < 7; i++) {
		cout << "Try " << (i + 1) << "/7. " << endl;
		if(mode == 1)
			playerInput = computerInput(cows, bulls, playerInput, guesses);
		else
			playerInput = userInput(strings[0]);
		cout << strings[2] << playerInput << endl;
		getBullsCows(cows, bulls, playerInput, codeMaster);
		printGuessResult(bulls, cows, i, strings);
		if (bulls == 9) break;
	}
}
string computerInput(int const & cows, int const & bulls, string const & lastGuess, vector<bool> & boolTable) {
	if (lastGuess.empty()) {
		return index2Code(318);
	}
	for (int i = 0; i < 512; i++) {
		string index = index2Code(i);
		if (index == lastGuess) boolTable[i] = false;
		else {
			int bullsTemp, cowsTemp;
			getBullsCows(cowsTemp, bullsTemp, index, lastGuess);
			if (bullsTemp != bulls || cowsTemp != cows)
				boolTable[i] = false;
		}
	}
	for (int i = 0; i < 512; i++) {
		if (boolTable[i] == true) return index2Code(i);
	}
}
string index2Code(int i) {
	return bitset<9>(i).to_string();
}