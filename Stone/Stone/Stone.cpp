
#include <iostream>
#include <cstdlib>
#include<string>
using namespace std;

enum enChoices
{
	enStone = 1, enScissor = 2, enPaper = 3
};

enum enWinner
{
	enDraw = 0, enPlayer = 1, enComputer = 2
};

struct stRoundInfo
{
	short RoundNumber = 0;
	enChoices PlayerChoice;
	enChoices ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameInfo{
	short GameRounds = 0;
	short PlayerScore = 0;
	short ComputerScore = 0;
	short Draws = 0;
	enWinner GameWinner;
	string GameWinnerName  = "";
};

short ReadHowManyRounds(string line = "How Many Round you want to play : ")
{
	short number;
	cout << line << endl;
	cin >> number;
	while (number > 10 || number < 1)
	{
		cout << "Enter Number Between 1 to 10 : \n";
		cin >> number;
	}
	return number;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

enChoices ReadPlayerChoice()
{
	short choice = 1;
	do
	{
		cout << "\nYour Choice: [1]:Stone , [2]:Paper , [3]:Scissors ? ";
		cin >> choice;
	} while (choice < 1 || choice > 3);

	return enChoices(choice);
}

short RandomNumber(short From, short To) {
	short RandNum = (rand() % (To - From + 1)) + From;
	return RandNum;
}

enChoices GetComputerChoice()
{
	return enChoices(RandomNumber(1,3));
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
		return enWinner::enDraw;
	else if ((RoundInfo.PlayerChoice == enChoices::enPaper && RoundInfo.ComputerChoice == enChoices::enStone) ||
		(RoundInfo.PlayerChoice == enChoices::enStone && RoundInfo.ComputerChoice == enChoices::enScissor) ||
		(RoundInfo.PlayerChoice == enChoices::enScissor && RoundInfo.ComputerChoice == enChoices::enPaper))
		return enWinner::enPlayer;
	else
		return enWinner::enComputer;
}

string WinnerName(enWinner Winner)
{
	string WinnerName[3] = { "NoWinner", "Player", "Pc" };
	return WinnerName[Winner];
}

string ChoiceName(enChoices Choice)
{
	string AnyThing[3] = { "Stone" , "Scissor" , "Paper" };
	return AnyThing[Choice - 1];
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n___________Round [" << RoundInfo.RoundNumber << "]_____________\n\n";
	cout << "Player Choice : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "PC Choice     : " << ChoiceName(RoundInfo.ComputerChoice) << endl ;
	cout << "Round Winner  : [ " << RoundInfo.WinnerName << " ] \n";
	cout << "\n___________________________________\n\n";

}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::enPlayer;
	else if (ComputerWinTimes > PlayerWinTimes)
		return enWinner::enComputer;
	else
		return enWinner::enDraw;
}

stGameInfo FillGameResults(int GameRounds , short PlayerWinTimes , short ComputerWinTimes , short DrawTimes )
{
	stGameInfo GameInfo;
	GameInfo.GameRounds = GameRounds;
	GameInfo.PlayerScore = PlayerWinTimes;
	GameInfo.ComputerScore = ComputerWinTimes;
	GameInfo.Draws = DrawTimes;
	GameInfo.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
	GameInfo.GameWinnerName = WinnerName(GameInfo.GameWinner);

	return GameInfo;
}

stGameInfo PlayGame(short Rounds)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawsTimes = 0;
	for (short i = 1; i <= Rounds; i++)
	{
		cout << "\nRound " << i << " Start Now \n";
		RoundInfo.RoundNumber = i;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::enPlayer)
			PlayerWinTimes++;
		else if
			(RoundInfo.Winner == enWinner::enComputer)
			ComputerWinTimes++;
		else
			DrawsTimes++;
		
		PrintRoundResults(RoundInfo);
	}
	return FillGameResults(Rounds, PlayerWinTimes, ComputerWinTimes, DrawsTimes);
}


string Tabs(int Count)
{
	string t= "";
	for (int i = 0; i < Count; i++) {
		t += "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "________________________________________________________________\n\n";
	cout << Tabs(2) << "                          +++ G a m e O v e r +++\n";
	cout << Tabs(2) << "________________________________________________________________\n\n";

}

void SetWinnerScreenColor(enWinner Winner)
{
	if (Winner == enWinner::enPlayer) {
		system("color 2F");
	}
	else if (Winner == enWinner::enComputer) {
		system("color 4F");
		cout << "\a";
	}
	else
		system("color 6F");
}

void ShowGameResults(stGameInfo GameInfo)
{
	cout << Tabs(2) << "_________________________________ [Game Results] _____________________\n";
	cout << Tabs(2) << "Total Rounds Played   : " << GameInfo.GameRounds << endl;
	cout << Tabs(2) << "Player Score          : " << GameInfo.PlayerScore << endl;
	cout << Tabs(2) << "Computer Score        : " << GameInfo.ComputerScore << endl;
	cout << Tabs(2) << "Draws                 : " << GameInfo.Draws << endl;
	cout << Tabs(2) << "Game Winner           : " << GameInfo.GameWinnerName << endl;
	cout << Tabs(2) << "________________________________________________________________\n\n";

	SetWinnerScreenColor(GameInfo.GameWinner);
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameInfo GameInfo = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowGameResults(GameInfo);

		 cout << endl << Tabs(3) << "Do you want to play Again ? ";
		 cin >> PlayAgain;
	
	} while (PlayAgain =='y' || PlayAgain == 'Y');
}

int main()
{
	srand(time(0));
	
	StartGame();

}

