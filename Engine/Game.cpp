#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd)
{
	GameCamera::Instance().Initalise(wnd);

	LevelBuilder::InitaliseGameplayValues("C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Engine\\Levels\\Prefabs.xml"); //BROKEN

	mCurrentLevel = 1;
	mTotalScore = 0;
	mGameState = GameState::eStartScreen;

	mGameStartScreen = make_unique<GameStartScreen>();
}

void Game::Update()
{
	GameCamera::Instance().BeginFrame();

	// If game is playing
	if (mGameState == GameState::ePlayingGame || mGameState == GameState::eWaitingOnGUIInput)
	{
		UpdateLevel();
		DrawLevel();
	}
	else
	{
		UpdateStartScreen();
	}

	GameCamera::Instance().EndFrame();

	Audio::Instance().Update();
}

Game::~Game()
{
	mGameLevel = nullptr;
}

void Game::CreateLevel()
{
	// Delete old level
	if (mCurrentLevel != 1) // HARDCODED 
	{
		mTotalScore += mGameLevel->GetScore();
		mGameLevel = nullptr;
	}
		
	stringstream stream;
	stream << "C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Engine\\Levels\\Level" << mCurrentLevel << ".xml";
	string levelPath = stream.str();

	mGameLevel = LevelBuilder::BuildGameLevel(levelPath, mTotalScore);
	mGameGUI->ResetGUI(mGameLevel, mCurrentLevel);
}

void Game::CheckLevelOver()
{
	if (mGameState != GameState::eWaitingOnGUIInput)
	{
		if (mGameLevel->GetLevelState() == LevelState::eDead)
		{
			mGameGUI->EnableCentreButton("RESTART");
			mGameState = GameState::eWaitingOnGUIInput;
		}
		else if (mGameLevel->GetLevelState() == LevelState::eWon)
		{
			mGameGUI->EnableCentreButton("LEVELUP");
			mCurrentLevel++; // Increase level
			mGameState = GameState::eWaitingOnGUIInput;
		}
	}
	else
	{
		if (mGameGUI->GetCentreButtonClicked())
		{
			mGameState = GameState::ePlayingGame;
			CreateLevel();
		}
	}
}

void Game::UpdateLevel()
{
	float deltaTime = mFrameTimer.Mark();

	GameCamera::Instance().Update(deltaTime);

	mGameLevel->Update(deltaTime);
	mGameGUI->UpdateGUI(deltaTime);

	CheckLevelOver();
}

void Game::DrawLevel()
{
	mGameLevel->Draw();
	mGameGUI->DrawGUI();
}

void Game::UpdateStartScreen()
{
	mGameStartScreen->UpdateGUI(mFrameTimer.Mark());
	mGameStartScreen->DrawGUI();

	if (mGameStartScreen->GetCentreButtonClicked())
	{
		mGameStartScreen = nullptr;

		mGameState = GameState::ePlayingGame;
		mGameGUI = make_unique<GameGUI>();
		CreateLevel();
	}
}