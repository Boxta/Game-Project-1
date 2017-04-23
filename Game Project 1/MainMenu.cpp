#include "MainMenu.h"
#include "Game.h"

void MainMenu::Initiate()
{
	/*Only Initiate Once*/
	if (mInitiated)
		return;
	else
		mInitiated = true;

	/*Setup Music*/
	mMenuMusic.openFromFile("Media/MenuMusic.wav");
	mMenuMusic.setLoop(true);

	/*Setup Sprites*/
	mBackgroundImage.setTexture(mCommonTextureStore.GetTextureRef("MenuBackground"));
	mBackgroundImage.setPosition(sf::Vector2f(0, 0));

	mStartGame_Button.Initiate((mWindow.getSize().x / 2) - (UIButton::WIDTH / 2), 
		mWindow.getSize().y / 2, 
		"Start");
	mLoadGame_Button.Initiate((mWindow.getSize().x / 2) - (UIButton::WIDTH / 2), 
		mWindow.getSize().y / 2 + (mButtonSpacing + UIButton::HEIGHT),
		"Load");
	mTutorialGame_Button.Initiate((mWindow.getSize().x / 2) - (UIButton::WIDTH / 2), 
		mWindow.getSize().y / 2 + ((mButtonSpacing + UIButton::HEIGHT) * 2),
		"Tutorial");
}

void MainMenu::HandleInput()
{

}

void MainMenu::Update(float dt)
{
	if (!mMusicIsPlaying)
	{
		mMusicIsPlaying = true;
		mMenuMusic.play();
	}
	else
	{ }
}

void MainMenu::Draw()
{
	mWindow.clear();
	mWindow.draw(mBackgroundFill);
	mWindow.draw(mBackgroundImage);
	mStartGame_Button.Draw(mWindow);
	mLoadGame_Button.Draw(mWindow);
	mTutorialGame_Button.Draw(mWindow);
}

void MainMenu::HandleEvents(sf::Event& ev)
{
	/*Process Left Mouse Click Event*/
	if (ev.type == sf::Event::MouseButtonPressed &&
		ev.mouseButton.button == sf::Mouse::Left)
	{
		/*Capture Mouse Coords*/
		const int xX = sf::Mouse::getPosition(mWindow).x;
		const int yY = sf::Mouse::getPosition(mWindow).y;

		/*If Press Was Inside 'Start Game' Button*/
		if (mStartGame_Button.CheckIfClicked(xX, yY))
		{
			if (mStartGame_Button.GetPressedState())
			{
				mStartGame_Button.SetPressedState(false);
			}
			else
			{
				mStartGame_Button.SetPressedState(true);
				mExit_StartNewGame();
			}
		}
		/*If Press Was Inside 'Load Game' Button*/
		if (mLoadGame_Button.CheckIfClicked(xX, yY))
		{
			if (mLoadGame_Button.GetPressedState())
				mLoadGame_Button.SetPressedState(false);
			else
				mLoadGame_Button.SetPressedState(true);
		}
		/*If Press Was Inside 'Tutorial Game' Button*/
		if (mTutorialGame_Button.CheckIfClicked(xX, yY))
		{
			if (mTutorialGame_Button.GetPressedState())
				mTutorialGame_Button.SetPressedState(false);
			else
				mTutorialGame_Button.SetPressedState(true);
		}
	}
}

void MainMenu::mExit_StartNewGame()
{
	GameState& ref = mStateManager.mGameReference.mState_Board;
	Game& gme = mStateManager.mGameReference;
	mMenuMusic.stop();
	gme.ChangeGameState(ref);
}

MainMenu::MainMenu(StateManager& stmgr,
	sf::RenderWindow& wnd)
	:
	mStateManager(stmgr),
	mCommonTextureStore(stmgr.mGameReference.mCommonTextureStore),
	mStartGame_Button(stmgr.mGameReference.mCommonTextureStore),
	mLoadGame_Button(stmgr.mGameReference.mCommonTextureStore),
	mTutorialGame_Button(stmgr.mGameReference.mCommonTextureStore),
	mWindow(wnd)
{
}


MainMenu::~MainMenu()
{
}
