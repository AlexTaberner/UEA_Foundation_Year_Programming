#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <bitset>
#include <stdlib.h>
#include <stdio.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

using namespace std;

//initialize functions
string fillBinaryStringRand(int const & stringLength);
string userInput(int const & type);
string gameTypeStrings(int const & type);
string index2Code(int i);
string computerInput(int const & cows, int const & bulls, string const & lastGuess, vector<bool> & boolTable, int countTry);

bool inputCheck01(char const & input);

int compareBulls(string const & a, string const & b);
int compareCows(string const & a, string const & b);
int countZeros(string const & input);

void userInputProcess(string & output, string const & input, bool & loopCheck);
void codemasterPC();
void codemasterPlayer();
void codemasterPlayerTest();
void fillBoolTable(vector<bool> & boolTable, int const & size);
void countZeros(string input, int & ones, int & zeros);
void *threadTest(void *threadarg);

//main
int main() {

	while (true) {
		cout << "Please enter 1 for human codebreaking, 2 for computer codebreaking, anything else to exit: ";
		char input;
		cin >> input;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		if (input == 49) codemasterPC();
		else if(input == 50) codemasterPlayerTest();
		else break;
	}

	return 0;
}

//takes int as input, creates a random string of 1's and 0's to input number of places
//outputs resultant string of 1's and 0's
string fillBinaryStringRand(int const & stringLength) {
	string output;

	srand(time(NULL));
	for (int i = 0; i < stringLength; i++) {
		output.push_back((rand() % 2) + 48);
	}

	return output;
}

//takes char as input, checks if input is char 0 or char 1, outputs true or false
bool inputCheck01(char const & input) {
	bool output = false;
	if (input == 48 || input == 49) output = true;
	return output;
}

string userInput(int const & type) {
	string input, output;
	string gameType = gameTypeStrings(type);
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

string gameTypeStrings(int const & type) {
	string output;
	switch (type) {
	case 0:
		output = "Please input your guess of |9| 1's and 0's on one line: ";
		break;
	case 1:
		output = "please input a string of |9| 1's and 0's for the computer to guess on one line: ";
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

int compareCows(string const & a, string const & b) {
	int aZero = 0, aOne = 0, bZero = 0, bOne = 0, output = 0;

	countZeros(a, aOne, aZero);
	countZeros(b, bOne, bZero);

	if (aZero > bZero) output += bZero;
	else output += aZero;
	
	if (aOne > bOne) output += bOne;
	else output += aOne;

	return output;
}

void countZeros(string input, int & ones, int & zeros) {
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

void codemasterPC() {

	string codeMaster = fillBinaryStringRand(9);
	bool loopCheck = true;

	cout << "The computer has generated a string of numbers |9| digits long for you to guess." << endl << endl;
	for (int i = 0; i < 7; i++) {
		int cows, bulls;

		cout << "Try " << (i + 1) << "/7. ";
		string playerInput = userInput(0);
		bulls = compareBulls(playerInput, codeMaster);
		cows = compareCows(playerInput, codeMaster) - bulls;

		if (bulls == 9) {
			cout << "You have guessed correctly!" << endl << endl;
			break;
		}
		else if(i < 7){
			cout << setw(7) << left << "Bulls: ";
			cout << bulls << endl;
			cout << setw(7) << left << "Cows: ";
			cout << cows << endl << endl;
		}
		else
		{
			cout << "You have run out of tries, please try again!" << endl << endl;
		}
	}
}

/*
void codemasterPlayer() {
	string codeMaster = userInput(1);
	vector<bool> guesses;

	cout << "The computer Will now try to guess your string of numbers." << endl;
	int cows = 0, bulls = 0;
	string playerInput = "";

	for (int i = 0; i < 7; i++) {

		cout << "Try " << (i + 1) << "/7. ";
		playerInput = computerInput(cows, bulls, playerInput, guesses);
		bulls = compareBulls(playerInput, codeMaster);
		cows = compareCows(playerInput, codeMaster) - bulls;

		cout << "Computers input: " << playerInput << endl;

		if (bulls == 9) {
			cout << "The computer has guessed correctly!" << endl << endl;
			break;
		}
		else if (i < 7) {
			cout << setw(7) << left << "Bulls: ";
			cout << bulls << endl;
			cout << setw(7) << left << "Cows: ";
			cout << cows << endl << endl;
			if(i == 6) cout << "You have beaten the computer, this shouldn't be possible!" << endl << endl;
		}
	}


}*/

void codemasterPlayerTest() {
	vector<pthread_t> threads;
	void *status;
	volatile int h;
	for (h = 0; h < 512; h++) {
		//cout << "thread: " << h << endl;
		pthread_t tempthread;
		pthread_create(&tempthread, NULL, threadTest, (void *) &h);
		threads.push_back(tempthread);
		_sleep(100);
	}

	for (int h = 0; h < 512; h++) {
		pthread_join(threads[h], &status);
	}
	
}

void *threadTest(void *threadarg) {
	int counter = 512;
	int permutation = *((int *) threadarg);
	//cout << permutation << endl;
	for (int j = 0; j < 512; j++) {
		string codeMaster = index2Code(j);
		vector<bool> guesses;

		//cout << "The computer will now try to guess your string of numbers." << endl;
		int cows = 0, bulls = 0;
		string playerInput = "";

		for (int i = 0; i < 7; i++) {

			//cout << "Try " << (i + 1) << "/7. ";
			playerInput = computerInput(cows, bulls, playerInput, guesses, permutation);
			bulls = compareBulls(playerInput, codeMaster);
			cows = compareCows(playerInput, codeMaster) - bulls;

			//cout << "Computers input: " << playerInput << endl;

			if (bulls == 9) {
				//cout << "The computer has guessed correctly!" << endl << endl;
				break;
			}
			else {
				//cout << setw(7) << left << "Bulls: ";
				//cout << bulls << endl;
				//cout << setw(7) << left << "Cows: ";
				//cout << cows << endl << endl;
				if (i == 6) {
					//cout << "You have beaten the computer!" << endl << endl;
					counter--;
				}
			}
		}
	}
	if (counter == 512) {
		cout << "Perfect match on permutation: " << permutation << endl;
	}
	return NULL;
}

//inputs results of last guess, outputs string of next guess to try.
string computerInput(int const & cows, int const & bulls, string const & lastGuess, vector<bool> & boolTable, int countTry) {

	if (lastGuess.empty()) {
		fillBoolTable(boolTable, 512);
		return index2Code(countTry);
	}

	for (int i = 0; i < 512; i++) {
		if (index2Code(i) == lastGuess) boolTable[i] = false;
		else {
			int bullsTemp = compareBulls(index2Code(i), lastGuess);
			int cowsTemp = compareCows(index2Code(i), lastGuess) - bullsTemp;
			if (bullsTemp != bulls || cowsTemp != cows)
				boolTable[i] = false;
		}
	}

	for (int i = 0; i < 512; i++) {
		if (boolTable[i] == true) return index2Code(i);
	}
}

void fillBoolTable(vector<bool> & boolTable, int const & size) {
	for (int i = 0; i < size; i++) {
		boolTable.push_back(true);
	}
}

string index2Code(int i) {
	return bitset<9>(i).to_string();
}