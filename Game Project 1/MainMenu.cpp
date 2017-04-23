#include "MainMenu.h"

void MainMenu::Initiate()
{
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
	mMenuMusic.stop();
	mStateManager.PushState(mNextStateRef);
}

MainMenu::MainMenu(StateManager& stmgr,
	CmnTextureStore& str,
	sf::RenderWindow& wnd,
	GameState& nxt)
	:
	mStateManager(stmgr),
	mCommonTextureStore(str),
	mStartGame_Button(str),
	mLoadGame_Button(str),
	mTutorialGame_Button(str),
	mWindow(wnd),
	mNextStateRef(nxt)
{
}


MainMenu::~MainMenu()
{
}
