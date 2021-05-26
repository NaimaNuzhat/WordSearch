#include <iostream>
#include <fstream>
using namespace std;

void DeallocateMemory(char** matrix, const int& rows)
{
	//Deletes the memorry after the use.

	for (int i = 0; i < rows; i++)
		if (matrix[i])
			delete[] matrix[i];
	if (matrix)
		delete[] matrix;
}

int StringLenght(char* mystr)
{
	int lenght = 0;
	for (char* j = mystr; *j != '\0'; j++, lenght++);

	return lenght;

}

void AllCaps(char* Word)
{
	//Converts the LowerCase Letters into UpperCase
	int strLen = StringLenght(Word);
	for (int i = 0; i < strLen; i++)
	{
		if (Word[i] >= 97 && Word[i] <= 122)
			Word[i] = Word[i] - 32;
	}

}

void RemoveSpaces(char* Word)
{
	int strLen = StringLenght((Word)), k = 0;

	for (int j = 0, i = 0; *(Word + j) != '\0'; j++)
	{
		if (*(Word + j) == ' ')
		{
			for (int i = j; i < strLen - 1; i++)
			{
				Word[i] = Word[i + 1];
			}

			Word[strLen - 1] = '\0';
		}
	}
}

void OutputFile(int Matrix[][4], char** Wordlist, const int& rows, int Cols, int Control,string FileName)
{
	// Saves the result in the output file.
	ofstream coutF(FileName.c_str());
	for (int i = 0; i < rows; i++)
	{
		coutF << Wordlist[i] << "\t { ";
		cout << Wordlist[i] << "\t { ";
		for (int j = 0; j < Cols; j++)
		{
			if (j == 2)
			{
				coutF << " } to { ";
				cout << " } to { ";
			}
			if (Matrix[i][0] == Control)
			{
				coutF << "Not Found  ";
				cout << "Not Found  ";
				break;

			}
			coutF << Matrix[i][j] << " ";
			cout << Matrix[i][j] << " ";


		}

		coutF << "}" << endl;
		cout << "}" << endl;
	}

	coutF << endl << endl;

	cout << endl << endl;

}

void DisplayMatrix(char** matrix, const int& rows)
{
	// in this function nested loop is started to display the matrix in the right order.

	for (int i = 0; i < rows; i++)
	{

		cout << matrix[i] << " ";
		cout << endl;
	}

	cout << endl << endl;

}

char* GetStringFromBuffer(char* buffer)
{
	//converts charecter array into pointer
	int strLen = StringLenght(buffer);
	char* str = 0;

	if (strLen > 0)
	{
		str = new char[strLen + 1];
		char* tempDest = str;
		for (char* tempSrc = buffer; *tempSrc != '\0'; tempSrc++, tempDest++)
		{
			*tempDest = *tempSrc;
		}
		*tempDest = '\0';
	}

	return str;

}

char** InputFileQ2(ifstream& cinF, int& Rows, int Cols)
{
	//takes the name in the form of char and then convert it to pointer then save it in the Array.
	char** WordList = new char* [Rows];

	char tempBuffer[80];
	for (int i = 0; i < Rows; i++)
	{
		cinF.getline(tempBuffer, 80);

		if (Cols == 0)
		{
			int StrLen = StringLenght(tempBuffer);
			WordList[i] = new char[StrLen];
		}
		else
			WordList[i] = new char[Cols];


		char* Word = 0;


		Word = GetStringFromBuffer(tempBuffer);
		RemoveSpaces(Word);

		*(WordList + i) = Word;
	}
	cinF.close();
	return WordList;
}
char** InputFileQ1(int& size, string File_Name)
{
	//takes the name in the form of char and then convert it to pointer then save it in the Array.
	ifstream cinF(File_Name.c_str());
	if (cinF.is_open())
	{
		int  StrLen = 0;
		char** WordList = new char* [size];
		char tempBuffer[80];
		for (int i = 0; i < size; i++)
		{
			StrLen = 0;

			char* Word = 0;

			cinF.getline(tempBuffer, 80);
			RemoveSpaces(tempBuffer);
			AllCaps(tempBuffer);
			StrLen = StringLenght(tempBuffer);
			Word = GetStringFromBuffer(tempBuffer);

			WordList[i] = new char[StrLen];

			*(WordList + i) = Word;
		}
		cinF.close();
		return WordList;
	}
	return 0;

}

void OutputFile(char** grid, int rows,int cols, string Filename)
{
	//creates the Output file and saves the data in it.
	ofstream coutF(Filename.c_str());
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			coutF << grid[i][j] << " ";
		}
		coutF << endl;

	}

	cout << endl << endl;

}

int LongestWord(char** WordList, const int size)
{
	//Finding the Length of the logest word in the whole list
	int Max = StringLenght(*(WordList + 0));

	for (int i = 0; i < size; i++) {

		int strLen = StringLenght(*(WordList + i));

		for (int j = 0; *(*(WordList + i) + j) != '\0'; j++)
		{
			if (*(*(WordList + i) + j) == ' ')
				strLen--;
		}

		if (strLen >= Max)
		{
			Max = strLen;

		}
	}

	return Max;
}

int DecendinOrderSort(char** WordList, int size)
{
	//Sorts the list in Descending  order with respect to size.
	//it also sort the array containing their size.f
	int sizeOfStr[20],TotalLetters=0;

	for (int i = 0; i < size; i++)
	{
		sizeOfStr[i] = StringLenght(WordList[i]);
		TotalLetters += sizeOfStr[i];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (sizeOfStr[i] <= sizeOfStr[j])
			{
				swap(WordList[i], WordList[j]);
				swap(sizeOfStr[i], sizeOfStr[j]);
			}
		}
	}
	return TotalLetters;
}

bool IsItAvailable(char** Grid, char* Word, int Row, int Column, int r, int c, int size)
{
	//This function checks whether the word can fit in the desried area or not. 
	for (int i = Row, j = Column, l = 0; l < size; i += r, j += c, l++)
	{
		if (Word[l] != Grid[i][j] && Grid[i][j] != '-')
			return false;
	}
	return true;
}

bool SettingWordsIntoTheGrid(char** Grid, char* Word, int r, int c, int rows,int cols)
{
	//First the row amd column is randomized and checked that wheather it can fit into the grid or not
	// then we check the availability of space for the word. 
	// then we set the word into the grid.
	int strLen = StringLenght(Word);
	int Row = (rand() % rows);
	int Column = rand() % cols;

	if (c != 0)
	{
		if (c == 1)
		{
			if (strLen != cols) {
				while (Column + strLen >= cols)
					Column = rand() % cols;
			}
			else
				Column = 0;
		}

		else
		{
			if (strLen != cols)
			{
				while (Column - strLen < 0)
					Column = rand() % cols + 0;
			}
			else
				Column = cols - 1;
		}
	}
	if (r != 0)
	{
		if (r == 1)
		{
			if (strLen != rows) {
				while (Row + strLen >=rows)
					Row = rand() % rows;
			}
			else
				Row = 0;
		}

		else
		{
			if (strLen != rows) {
				while (Row - strLen < 0)
					Row = rand() % rows;
			}
			else
				Row = rows - 1;
		}
	}

	bool Availability = IsItAvailable(Grid, Word, Row, Column, r, c, strLen);

	if (Availability == true)
	{
		for (int i = Row, j = Column, l = 0; l < strLen; i += r, j += c, l++)
		{
			Grid[i][j] = Word[l];
		}
		return true;
	}
	return false;
}

void RandomWords(char** Grid, int rows, int cols)
{
	//This sets random words on the remaining empty spaces after the words are set.
	srand(time(0));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (Grid[i][j] == '-')
			{
				Grid[i][j] = (char)((rand() % 26) + 65);
			}
		}
	}
}

char** GridGenerator(char** WordList, const int size, const int rows,const int cols)
{
	//This functionn creates a grid then sets the words from list and then fills it with random words.
	char** Grid = new char* [rows];
	//in these 2 loops we firs create a memmory and then set '-' as a control varriable.
	for (int i = 0; i < rows; i++)
	{
		Grid[i] = new char[cols + 1];
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			Grid[i][j] = '-';
		Grid[i][cols] = '\0';
	}

	//srand is used to produce diffferent results everytime.
	srand(time(0));
	for (int i = 0, count = 0; i < size; i++)
	{
		//this varriable takes a random number and then sets the word to on the grid with the pattern set for that umber. 
		int pattern = rand() % 8 + 1;
		// We call the function settingWordsIntoTheGrid then if the word can fit into the grid it sets it 
		// if not the loop is started to set the word into the grid.
		// if the word is not able to fit into the grid then we skip the word to prevent infinite laop
		// 
		if (count == 500)
		{
			cout << "Word ' " << WordList[i] << " ' is Skipped Because it cant fit into the grid!" << endl;
			count = 0;
			i++;
		}
		//left to right
		if (pattern == 1)
		{
			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], 0, +1, rows,cols);

			if (Availability == false)
			{
				count++;
				i--;
			}

		}
		//Right to Left
		else if (pattern == 2)
		{
			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], 0, -1, rows, cols);;

			if (Availability == false)
			{
				count++;
				i--;
			}
		}

		//Top to bottom
		else if (pattern == 3)
		{

			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], 1, 0, rows, cols);

			if (Availability == false)
			{
				count++;
				i--;
			}
		}

		//Bottom to Top	
		else if (pattern == 4)
		{
			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], -1, 0, rows, cols);;

			if (Availability == false)
			{
				count++;
				i--;
			}

		}

		//Top left to Bottom right
		else if (pattern == 5)
		{

			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], 1, 1, rows, cols);;

			if (Availability == false)
			{
				count++;
				i--;
			}

		}

		//Bottom Right to Top Left
		else if (pattern == 6)
		{

			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], -1, -1, rows, cols);;

			if (Availability == false)
			{
				count++;
				i--;
			}
		}

		//Top Right to Bottom left
		else if (pattern == 7)
		{

			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], 1, -1, rows, cols);;

			if (Availability == false)
			{
				count++;
				i--;
			}
		}

		//Bottom Left to Top Right
		else if (pattern == 8)
		{

			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], -1, 1, rows, cols);;

			if (Availability == false)
			{
				count++;
				i--;
			}
		}

		// if the word is not able to set into the grid and the loop is inititated 500 times then we skip the word.

	}
	//Setting Random WOrds on the remaining space left
	RandomWords(Grid, rows,cols);

	return Grid;
}


bool SearchWord(char** Grid, char* Word, int Row, int Column, int r, int c, int size, int cols)
{
	//this function search the word from the starting letter which same as the first letter of the desired word.
	if (c != 0)
	{
		if (c == 1)
		{
			if (Column + size >= cols)
				return false;
		}
		else if (Column - size < 0)
			return false;
	}
	if (r != 0)
	{

		if (r == 1)
		{
			if (Row + size >= cols)
				return false;
		}

		else if (Row - size < 0)
			return false;
	}

	for (int i = Row, j = Column, l = 0; l < size; i += r, j += c, l++)
	{
		if (Word[l] != Grid[i][j])
			return false;

	}
	return true;
}

void CoordinatesForWords(int Coordinates[][4], char** Grid, char** WordList, int Rows, int Cols, int Entries)
{
	//this function consits of multiple if statements.
	//if the first letter is same than the desired word then then we set the parameters one by one to find 
	//the word in all eight directions. if that is not possible we again find the fist letter.
	//if the word is found then the loop is broken and then the coordinates are set into the Coordinates array
	//Depending to its direction.
	for (int i = 0; i < Entries; i++)
	{
		bool Found = false;

		for (int j = 0; j < Rows; j++)
		{
			for (int l = 0; l < Cols; l++)
			{
				int count = 0;
				if (Grid[j][l] == WordList[i][0])
				{
					int StrLen = StringLenght(WordList[i]);
					int a = j;

					for (; count < 8 && Found == false; count++)
					{
						int r = 0, c = 0;

						//Right to Left
						if (count == 0)
						{
							c = 1;
						}

						//Left to Right
						else if (count == 1)
						{
							c = -1;
						}

						//Top to Bottom
						else if (count == 2)
						{
							r = 1;
						}

						//Bottom to Top
						else if (count == 3)
						{
							r = -1;
						}

						//Top Left to Bottom RIght
						else if (count == 4)
						{
							r = 1;
							c = 1;
						}

						//Bottom RIght to Top Left
						else if (count == 5)
						{
							r = -1;
							c = -1;
						}

						//Bottom Left to Top Right
						else if (count == 6)
						{
							r = -1;
							c = 1;
						}

						//Top Right to Bottom Left
						else if (count == 7)
						{
							r = 1;
							c = -1;

						}

						Found = SearchWord(Grid, WordList[i], j, l, r, c, StrLen, Cols);
						if (Found == true)
							break;
					}

					if (Found == true)
					{
						//Stating Coordinates
						Coordinates[i][0] = j;
						Coordinates[i][1] = l;

						//Right to Left
						if (count == 0)
						{
							Coordinates[i][2] = j;
							Coordinates[i][3] = l + StrLen - 1;
						}

						//Left to Right
						else if (count == 1)
						{
							Coordinates[i][2] = j;
							Coordinates[i][3] = l - StrLen + 1;
						}

						//Top to Bottom
						else if (count == 2)
						{
							Coordinates[i][2] = j + StrLen - 1;
							Coordinates[i][3] = l;
						}

						//Bottom to Top
						else if (count == 3)
						{
							Coordinates[i][2] = j - StrLen + 1;
							Coordinates[i][3] = l;
						}

						//Top Left to Bottom RIght
						else if (count == 4)
						{
							Coordinates[i][2] = j + StrLen - 1;
							Coordinates[i][3] = l + StrLen - 1;
						}

						//Bottom RIght to Top Left
						else if (count == 5)
						{
							Coordinates[i][2] = j - StrLen + 1;
							Coordinates[i][3] = l - StrLen + 1;
						}

						//Bottom Left to Top Right
						else if (count == 6)
						{
							Coordinates[i][2] = j - StrLen + 1;
							Coordinates[i][3] = l + StrLen - 1;
						}

						//Top Right to Bottom Left
						else if (count == 7)
						{
							Coordinates[i][2] = j + StrLen - 1;
							Coordinates[i][3] = l - StrLen + 1;
						}

						break;
					}

					if (Found == false && count == 8)
					{
						Coordinates[i][0] = Cols + Rows;
					}
				}
			}

			if (Found == true)
				break;
		}
	}
	return;
}

bool Question1()
{
	int size = 0, rows = 0, cols = 0;
	char** WordList, ** Grid;
	string FileName;
	cout << "Please enter the following details\n1) Name of the input file: ";
	cin >> FileName;
	cout << "2) Number of words in the file: ";
	cin >> size;
	cout << "3) Number of rows in the grid: ";
	cin >> rows;
	cout << "4) Number of columns in the grid: ";
	cin >> cols;

	if (size > 0)
	{
		WordList = InputFileQ1(size, FileName);
		if (WordList != 0)
		{
			int Max = LongestWord(WordList, size);
			if (Max <= rows || Max <= cols)
			{
				int TotalLetters=DecendinOrderSort(WordList, size);
				//cout << TotalLetters;
				Grid = GridGenerator(WordList, size, rows, cols);
				cout << "Please enter the Name of the output file: ";
				string Filename;
				cin >> Filename;
				OutputFile(Grid, rows, cols, Filename);
				cout << "Results saved into the file " << Filename << " Successfully! \nHope you got all of them Correct!" << endl;
				DeallocateMemory(Grid, Max);
				DeallocateMemory(WordList, size);
			}
			else
			{
				DeallocateMemory(WordList, size);
				cout << "Grid cannot be formed, press any key to return to the home screen" << endl;
				char exit;
				cin >> exit;
				return false;
			}
		}
		else
		{
			cout << "Grid cannot be formed, press any key to return to the home screen" << endl;
			char exit;
			cin >> exit;
			return false;
		}


	}
	else
	{

		cout << "Grid cannot be formed, press any key to return to the home screen" << endl;
		return false;
	}
	return true;

}

bool Question2()
{
	char** Grid;
	int Rows, Cols, Entries = 0, Coordinates[100][4];
	char** WordList;
	string FileName, FileName2,FileOutput;
	cout << "Please enter the following details\n1) Name of the input file with grid: ";
	cin >> FileName;
	cout << "2) Name of the file with words: ";
	cin >> FileName2;
	cout << "3) Name of the Output File: ";
	cin >> FileOutput;
	ifstream cinF(FileName.c_str());
	ifstream cinF2(FileName2.c_str());
	if (cinF.is_open() && cinF2.is_open())
	{
		cinF2 >> Rows;
		cinF2 >> Cols;
		Grid = InputFileQ2(cinF, Rows, Cols);
		cinF2 >> Entries;
		cinF2.ignore();
		WordList = InputFileQ2(cinF2, Entries, 0);

		for (int i = 0; i < Entries; i++)
		{
			AllCaps(WordList[i]);
			RemoveSpaces(WordList[i]);
		}

		CoordinatesForWords(Coordinates, Grid, WordList, Rows, Cols, Entries);
		OutputFile(Coordinates, WordList, Entries, 4, (Cols + Rows),FileOutput);

		cout << "Results saved into the file Output.txt Successfully! \nHope you got all of them Correct!" << endl;
		DeallocateMemory(Grid, Rows);
		DeallocateMemory(WordList, Entries);
		return true;
	}
	else if(!cinF.is_open())
	{
		cout << "Error! File "<<FileName <<" Doesnt exist!"<< endl;
		WordList = 0;
		Grid = 0;
		Rows = 0;
		Entries = 0;
		DeallocateMemory(Grid, Rows);
		DeallocateMemory(WordList, Entries);
	}
	else if (!cinF2.is_open())
	{
		cout << "Error! File " << FileName2 << " Doesnt exist!" << endl;
		WordList = 0;
		Grid = 0;
		Rows = 0;
		Entries = 0;
		DeallocateMemory(Grid, Rows);
		DeallocateMemory(WordList, Entries);
	}
	return false;

}

int main()
{
	bool Success = false;
	char A=' ';
	while (A!='Q')
	{
		cout << "Hello Word!\nWelcome to The World of Word Search Puzzle" << endl;
		char A=0;
		while (A != 'C' && A != 'S' && A != 'Q')
		{

			cout << "What do you Want to do!\nPlease enter the first letter of Your choice!" << endl
				<<"1) Create Grid\n2) Search Words from Grid\n3) Quit\n";
			cin >> A;
			if (A != 'C' && A != 'S' && A != 'Q')
			{
				cout << "Error! Wrong input" << endl;
			}
		}
		if (A == 'C')
		{
			Success = Question1();
		}
		if (A == 'S')
		{
			Success = Question2();
		}
		if (A == 'Q')
		{
			cout << "\nIts Understandable\nHave a Nice Day\nShutting Down!\n";
			break;
		}
	}

	return 0;
}