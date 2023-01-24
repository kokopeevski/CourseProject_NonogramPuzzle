/**
*
* Solution to course project # 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kaloyan Kirilov Peevski
* @idnumber 2MI0600170
* @compiler VC
*
* main file with all functions
*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

const size_t MAX_LEN_OF_NAME_OF_FILE = 105;
const size_t MAX_LEN_LOGIN_INFO = 100;
size_t countOfPossibleMistakesAccordingToTheCurrentLevel = 3; // by default 3 for the first level
const size_t MAX_POSSIBLE_LEVEL_OF_THE_GAME = 3;
const size_t MIN_POSSIBLE_LEVEL_OF_THE_GAME = 1;

int LengthOfCharArr(const char* arr)
{
	int len = 0;
	while (arr[len] != '\0')
	{
		len++;
	}
	return len;
}

void AddTxtExtension(int lenOfUsername, char* fileName)
{
	for (int i = lenOfUsername; i < lenOfUsername + 4; i++)
	{
		if (i == lenOfUsername) {
			fileName[i] = '.';
		}
		else if (i == lenOfUsername + 1) {
			fileName[i] = 't';
		}
		else if (i == lenOfUsername + 2) {
			fileName[i] = 'x';
		}
		else if (i == lenOfUsername + 3) {
			fileName[i] = 't';
		}
	}
}

// when a person creating new account
void CreateNewAccount(const char* username, const char* password)
{
	char fileName[MAX_LEN_OF_NAME_OF_FILE];
	int lenOfUsername = LengthOfCharArr(username);
	AddTxtExtension(lenOfUsername, fileName);
	ofstream output(username);
	output << password << endl;
	output.close();
	cout << "You have successfully created your account. Now you can already start playing from the first level!";
}

// when a person already has got existing account
void AlreadyExistingAccount(const char* username, const char* password)
{
	char fileName[MAX_LEN_OF_NAME_OF_FILE];
	int lenOfUsername = LengthOfCharArr(username);
	AddTxtExtension(lenOfUsername, fileName);
	ifstream input;
	input.open(username);
	//char* passwordOfUser[MAX_LEN_LOGIN_INFO];
	string passwordOfUser = "";
	getline(input, passwordOfUser);
	if ((passwordOfUser != password) || (input.is_open() == false))
	{
		cout << "Wrong password! Try again!";
		return;
	}
	cout << "You heve succesfully loggedin in your account! Now you can start playing!";
	input.close();
}

//Check wheter the person has got an account
void HasAPersonAlreadyAccountOrWillCreateANewOne()
{
	cout << "Welcome to the Nonogram game! I appreciate you playing my game and now you can start the game after you login!" << endl;
	cout << "Do you have already an account? (write \"1\" in case you have OR \"0\" in case you don't have, please: ";
	const size_t MAX_LEN_OF_ANSWER = 3;
	//char answer[MAX_LEN_OF_ANSWER];
	bool answer;
	//cin.getline(answer, MAX_LEN_OF_ANSWER);
	cin >> answer;
	char username[MAX_LEN_LOGIN_INFO];
	char password[MAX_LEN_LOGIN_INFO];
	if (answer)
	{
		cout << "So, enter your username, please: ";
		cin >> username;
		cout << "Enter your password, please: ";
		cin >> password;
		AlreadyExistingAccount(username, password);
	}
	else if (!answer)
	{
		cout << "No problem, just create one in a few seconds!" << endl;
		cout << "Enter your username, please: ";
		cin >> username;
		cout << "Enter your password, please: ";
		cin >> password;
		CreateNewAccount(username, password);
	}
	else
	{
		cout << "Invalid input! Please, try again!";
		return;
	}
}

//Create start matrix of nonogram puzzle
char** CreateMatrix(int countOfRowsAndCols)
{
	char** matrix = new char* [countOfRowsAndCols];
	for (int i = 0; i < countOfRowsAndCols; i++)
	{
		matrix[i] = new char[countOfRowsAndCols];
	}
	return matrix;
}

// Redefining the method for creating non-square matrices
int** CreateMatrix(size_t rows, size_t cols)
{
	int** matrix = new int* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		matrix[i] = new int[cols];
	}
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			matrix[i][j] = NULL; //default initialization
		}
	}
	return matrix;
}

//Deleting using memory in the stack
void FreeMatrix(char** matrix, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

// Choosing a level
void UsersChoiceOfLevel(size_t& level)
{
	cout << "Please, choose the level you  want to play(between 1 and 3): ";
	cin >> level;
	while (level < MIN_POSSIBLE_LEVEL_OF_THE_GAME || level > MAX_POSSIBLE_LEVEL_OF_THE_GAME)
	{
		cout << "Inccorect choice! Please, try again, you can choose between 1 and 3!";
		cin >> level;
	}
}

// Loading level
void SelectAndLoadLevel(size_t level, string& matrix, size_t sizeOfMatrix)
{
	ifstream currentFileOfUsersChoice;
	//srand(time(0));
	double randomOptionSelector = rand() % 1 + 0;
	switch (level)
	{
	case 1:
		if (randomOptionSelector == 0)
		{
			currentFileOfUsersChoice.open("level_1_v1.txt");
		}
		else
		{
			currentFileOfUsersChoice.open("level_1_v2.txt");
		}
		countOfPossibleMistakesAccordingToTheCurrentLevel = 3;
		break;
	case 2:
		if (randomOptionSelector == 0)
		{
			currentFileOfUsersChoice.open("level_2_v1.txt");
		}
		else
		{
			currentFileOfUsersChoice.open("level_2_v2.txt");
		}
		countOfPossibleMistakesAccordingToTheCurrentLevel = 4;
		break;
	case 3:
		if (randomOptionSelector == 0)
		{
			currentFileOfUsersChoice.open("level_3_v1.txt");
		}
		else
		{
			currentFileOfUsersChoice.open("level_3_v2.txt");
		}
		countOfPossibleMistakesAccordingToTheCurrentLevel = 5;
		break;
	default:
		cout << "The game supports only 3 levels!";
		break;
	}
	// check for error when reading the file
	if (currentFileOfUsersChoice.is_open() == false)
	{
		cout << "Sorry, there was a problem with reading the file, please try again!";
		return;
	}
	//read the data for the filled fields of the matrix form the selected file
	getline(currentFileOfUsersChoice, matrix);
}

// visualising the arrays with the count of consecutively occupied fields in the columns
void VisualizeTheMatrixCorrespondingToTheOccupiedFieldsOfTheCols(int** matrixAbovePuzzle, size_t maxRows, size_t cols, size_t maxCols)
{
	for (size_t i = 0; i < maxRows; i++)
	{
		for (size_t j = 0; j < maxCols; j++)
		{
			cout << "  ";
		}
		for (size_t k = 0; k < cols; k++)
		{
			if (matrixAbovePuzzle[i][k] == 0)
			{
				cout << "    ";
			}
			else
			{
				cout << " " << matrixAbovePuzzle[i][k] << "  ";
			}
		}
		cout << endl;
	}
}

void CountOfConsecutivelyOccupiedFieldsInRows(char** puzzle, int sizeOfPuzzle, int** matrixToTheLeftOfThePuzzle, int& rows, int& maxCols)
{
	int cols = 0;
	size_t counter = 0;
	for (int i = 0; i < sizeOfPuzzle; i++)
	{
		for (int j = 0; j < sizeOfPuzzle; j++)
		{
			if (puzzle[i][j] == '0')
			{
				if (counter != 0)
				{
					matrixToTheLeftOfThePuzzle[i][cols] = counter;
					cols++;
					counter = 0;
				}
			}
			if (puzzle[i][j] == '1')
			{
				counter++;
			}
			if (j == sizeOfPuzzle - 1 && counter != 0)
			{
				matrixToTheLeftOfThePuzzle[i][cols] = counter;
				cols++;
			}
		}
		if (maxCols < cols) maxCols = cols;
		cols = 0;
		counter = 0;
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < maxCols; j++)
		{
			if (matrixToTheLeftOfThePuzzle[i][j] < 0 || matrixToTheLeftOfThePuzzle[i][j] > sizeOfPuzzle)
				matrixToTheLeftOfThePuzzle[i][j] = 0;
		}
	}
}

void CountOfConsecutivelyOccupiedFieldsInColumns(char** puzzle, int sizeOfPuzzle, int& maxCols,
	int**& matrixAbovePuzzle, int& rows, int& cols, int& maxRows)
{
	size_t countOfOccupiedFields = 0;
	for (int i = 0; i < sizeOfPuzzle; i++)
	{
		for (int j = 0; j < sizeOfPuzzle; j++)
		{
			if (puzzle[j][i] == '0')
			{
				if (countOfOccupiedFields != 0)
				{
					matrixAbovePuzzle[rows][cols] = countOfOccupiedFields;
					rows++;
					countOfOccupiedFields = 0;
				}
			}
			if (puzzle[j][i] == '1')
			{
				countOfOccupiedFields++;
			}
			if (j == sizeOfPuzzle - 1 && countOfOccupiedFields != 0)
			{
				matrixAbovePuzzle[rows][cols] = countOfOccupiedFields;
				rows++;
			}
		}
		if (maxRows < rows) maxRows = rows;
		cols++;
		rows = 0;
		countOfOccupiedFields = 0;
	}
	for (int i = 0; i < maxRows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (matrixAbovePuzzle[i][j] < 0 || matrixAbovePuzzle[i][j] > sizeOfPuzzle)
				matrixAbovePuzzle[i][j] = 0;
		}
	}
}

// Visualizing the entire nonogram puzzle with the filled fields read from the selected file
void VisualizeTheEntireNonogramPuzzle(char** puzzle, size_t sizeOfPuzzle, int** matrixToTheLeftOfThePuzzle,
	int** matrixAbovePuzzle, int rows, int maxCols, int maxRows, int cols)
{
	VisualizeTheMatrixCorrespondingToTheOccupiedFieldsOfTheCols(matrixAbovePuzzle, maxRows, cols, maxCols);
	for (size_t i = 0; i < sizeOfPuzzle; i++)
	{
		for (int j = 0; j < maxCols; j++)
		{
			if (matrixToTheLeftOfThePuzzle[i][j] == 0)
			{
				cout << "  ";
			}
			else
			{
				cout << matrixToTheLeftOfThePuzzle[i][j] << " ";
			}
		}
		for (size_t j = 0; j < sizeOfPuzzle; j++)
		{
			if ((puzzle[i][j] != 'x') && (puzzle[i][j] != 'o'))
			{
				cout << "(" << " " << ") ";
			}
			else
			{
				cout << "(" << puzzle[i][j] << ") ";
			}
		}
		cout << endl << endl;
	}
}

bool CheckForValidUserInput(size_t x_CoordinateOfMatrix, size_t y_CoordinateOfMatrix, char symbol, size_t sizeOfPuzzle)
{
	if (x_CoordinateOfMatrix >= 0 && x_CoordinateOfMatrix < sizeOfPuzzle && y_CoordinateOfMatrix >= 0 && y_CoordinateOfMatrix < sizeOfPuzzle && (symbol == 'o' || symbol == 'x'))
	{
		return true;
	}
	else return false;
}

bool IsEmptyField(char** puzzle, size_t x_CoordinateOfMatrix, size_t y_CoordinateOfMatrix)
{
	return (puzzle[x_CoordinateOfMatrix][y_CoordinateOfMatrix] != '*' && puzzle[x_CoordinateOfMatrix][y_CoordinateOfMatrix] != '-');
}

void GetCurrentUsersInput(char** puzzle, int& x_Coordinate, int& y_Coordinate, char& currentSym, size_t sizeOfPuzzle)
{
	cout << "Prease, enter x-Coordinate, y-Coordinate and symbol(\"x\" to fill the field, \"o\" to mark as empty field): ";
	cin >> x_Coordinate >> y_Coordinate >> currentSym;
	while (!CheckForValidUserInput(x_Coordinate, y_Coordinate, currentSym, sizeOfPuzzle) || !IsEmptyField(puzzle, x_Coordinate, y_Coordinate))
	{
		cout << "This cell is already opened! Try again: ";
		cin >> x_Coordinate >> y_Coordinate >> currentSym;
	}
}

bool AreOpendAllFilledFieldsFromTheCurrentRow(char** puzzle, int row, size_t sizeOfPuzzle)
{
	for (size_t j = 0; j < sizeOfPuzzle; j++)
	{
		if (puzzle[row][j] == '1')
		{
			return false;
		}
	}
	return true;
}

bool AreOpendAllFilledFieldsFromTheCurrentCol(char** puzzle, int col, size_t sizeOfPuzzle)
{
	for (size_t i = 0; i < sizeOfPuzzle; i++)
	{
		if (puzzle[i][col] == '1')
		{
			return false;
		}
	}
	return true;
}

void OpenRowField(char** puzzle, size_t row, size_t sizeOfPuzzle)
{
	for (size_t i = 0; i < sizeOfPuzzle; i++)
	{
		if (puzzle[row][i] == '0') puzzle[row][i] = 'o';
	}
}

void OpenColField(char** puzzle, size_t col, size_t sizeOfPuzzle)
{
	for (size_t i = 0; i < sizeOfPuzzle; i++)
	{
		if (puzzle[i][col] == '0') puzzle[i][col] = 'o';
	}
}

void OpenTheRemainingNonFilledFieldsInEntireNonogramPuzzle(char** puzzle, size_t row, size_t col, size_t sizeOfPuzzle)
{
	if (AreOpendAllFilledFieldsFromTheCurrentRow(puzzle, row, sizeOfPuzzle))
	{
		OpenRowField(puzzle, row, sizeOfPuzzle);
	}
	if (AreOpendAllFilledFieldsFromTheCurrentCol(puzzle, col, sizeOfPuzzle))
	{
		OpenColField(puzzle, col, sizeOfPuzzle);
	}
}

bool isTheHoleNonogramPuzzleSolved(char** puzzle, size_t x_CoordinateOfMatrix, size_t y_CoordinateOfMatrix,
	size_t& currentMistakes, char userGivenSymbol, size_t sizeOfPuzzle)
{
	switch (userGivenSymbol)
	{
		case 'x':
			if (puzzle[x_CoordinateOfMatrix][y_CoordinateOfMatrix] == '0')
			{
				puzzle[x_CoordinateOfMatrix][y_CoordinateOfMatrix] = 'o';
				currentMistakes++;
			}
			else
			{
				puzzle[x_CoordinateOfMatrix][y_CoordinateOfMatrix] = 'x';
			}
			break;
		case 'o':
			if (puzzle[x_CoordinateOfMatrix][y_CoordinateOfMatrix] == '1')
			{
				puzzle[x_CoordinateOfMatrix][y_CoordinateOfMatrix] = 'x';
				currentMistakes++;
			}
			else
			{
				puzzle[x_CoordinateOfMatrix][y_CoordinateOfMatrix] = 'o';
			}
			break;
		default:
			break;
	}
	OpenTheRemainingNonFilledFieldsInEntireNonogramPuzzle(puzzle, x_CoordinateOfMatrix, y_CoordinateOfMatrix, sizeOfPuzzle);
	for (size_t i = 0; i < sizeOfPuzzle; i++)
	{
		for (size_t j = 0; j < sizeOfPuzzle; j++)
		{
			if (puzzle[i][j] == '1') return false;
		}
	}
	return true;
}

void InitializeMatrixAccordingToTheSizeAndLevel(int level, char**& puzzle, size_t& sizeOfPuzzel)
{
	if (level == 1)
	{
		sizeOfPuzzel = 5;
		puzzle = CreateMatrix(sizeOfPuzzel);
	}
	else if (level == 2)
	{
		sizeOfPuzzel = 7;
		puzzle = CreateMatrix(sizeOfPuzzel);
	}
	else if (level == 3)
	{
		sizeOfPuzzel = 9;
		puzzle = CreateMatrix(sizeOfPuzzel);
	}
}

// position the console as if the content had been deleted
void artificialDeletionOfTheConsole() {
	// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
	std::cout << "\x1B[2J\x1B[H";
}

void PlayNonogramPuzzle()
{
	size_t level = 1; //first level by default
	string username = "";
	string password = "";

	HasAPersonAlreadyAccountOrWillCreateANewOne();
	UsersChoiceOfLevel(level);

	string filledFieldsOfMatrixReadFromFile;
	char** puzzle;
	size_t sizeOfPuzzle = 0;
	int rows = 0;
	int maxRows = 0;
	int cols = 0;
	int maxCols = 0;

	InitializeMatrixAccordingToTheSizeAndLevel(level, puzzle, sizeOfPuzzle);
	SelectAndLoadLevel(level, filledFieldsOfMatrixReadFromFile, sizeOfPuzzle);
	for (size_t i = 0; i < sizeOfPuzzle; i++)
	{
		for (size_t j = 0; j < sizeOfPuzzle; j++)
		{
			puzzle[i][j] = filledFieldsOfMatrixReadFromFile[j + i * sizeOfPuzzle];
		}
	}

	int x_Coordinate, y_Coordinate;
	size_t mistakes = 0;
	char currentUserSymbol;
	int** arraysWithFilledFieldsInRows = CreateMatrix(sizeOfPuzzle, sizeOfPuzzle);
	int** arraysWithFilledFieldsInCols = CreateMatrix(sizeOfPuzzle, sizeOfPuzzle);
	CountOfConsecutivelyOccupiedFieldsInRows(puzzle, sizeOfPuzzle, arraysWithFilledFieldsInRows, rows, maxCols);
	CountOfConsecutivelyOccupiedFieldsInColumns(puzzle, sizeOfPuzzle, maxCols, arraysWithFilledFieldsInCols, rows, cols, maxRows);

	VisualizeTheEntireNonogramPuzzle(puzzle, sizeOfPuzzle, arraysWithFilledFieldsInRows, arraysWithFilledFieldsInCols, rows, maxCols, maxRows, cols);
	while (true)
	{
		GetCurrentUsersInput(puzzle, x_Coordinate, y_Coordinate, currentUserSymbol, sizeOfPuzzle);
		if (isTheHoleNonogramPuzzleSolved(puzzle, x_Coordinate, y_Coordinate, mistakes, currentUserSymbol, sizeOfPuzzle))
		{
			cout << "Congratulations, you won the game!";
			break;
		}
		if (mistakes == countOfPossibleMistakesAccordingToTheCurrentLevel)
		{
			cout << "Sorry, you lost! But you can try again!";
			break;
		}
		artificialDeletionOfTheConsole();
		VisualizeTheEntireNonogramPuzzle(puzzle, sizeOfPuzzle, arraysWithFilledFieldsInRows, arraysWithFilledFieldsInCols, rows, maxCols, maxRows, cols);
		cout << "Mistakes: " << mistakes << "   ( " << "Maximum number of mistakes: "<< countOfPossibleMistakesAccordingToTheCurrentLevel << " )" << endl;
	}
}

int main()
{
	PlayNonogramPuzzle();
}