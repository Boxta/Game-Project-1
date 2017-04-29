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
	mBackgroundImage.setTexture(mGameReference.GetCommonStore().GetTextureRef("MenuBackground"));
	mBackgroundImage.setPosition(sf::Vector2f(0, 0));

	mStartGame_Button.Initiate((mGameReference.GetWindow().getSize().x / 2) - (UIButton::WIDTH / 2),
		mGameReference.GetWindow().getSize().y / 2,
		"Start");
	mLoadGame_Button.Initiate((mGameReference.GetWindow().getSize().x / 2) - (UIButton::WIDTH / 2),
		mGameReference.GetWindow().getSize().y / 2 + (mButtonSpacing + UIButton::HEIGHT),
		"Load");
	mTutorialGame_Button.Initiate((mGameReference.GetWindow().getSize().x / 2) - (UIButton::WIDTH / 2),
		mGameReference.GetWindow().getSize().y / 2 + ((mButtonSpacing + UIButton::HEIGHT) * 2),
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
	mGameReference.GetWindow().clear();
	mGameReference.GetWindow().draw(mBackgroundFill);
	mGameReference.GetWindow().draw(mBackgroundImage);
	mStartGame_Button.Draw(mGameReference.GetWindow());
	mLoadGame_Button.Draw(mGameReference.GetWindow());
	mTutorialGame_Button.Draw(mGameReference.GetWindow());
}

void MainMenu::HandleEvents(sf::Event& ev)
{
	/*Process Left Mouse Click Event*/
	if (ev.type == sf::Event::MouseButtonPressed &&
		ev.mouseButton.button == sf::Mouse::Left)
	{
		/*Capture Mouse Coords*/
		const int xX = sf::Mouse::getPosition(mGameReference.GetWindow()).x;
		const int yY = sf::Mouse::getPosition(mGameReference.GetWindow()).y;

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
	/*Initiate Player*/
	mGameReference.GetPlayer().Initiate(50.0f, 700.0f, "CMDR Ayna P", 133.0f, 721.0f);
	mMenuMusic.stop();
	mMenuMusic.setLoop(false);
	mGameReference.ChangeGameState(mGameReference.GetState_Board());
}

MainMenu::MainMenu(Game& ref)
	:
	mGameReference(ref),
	mStartGame_Button(ref.GetCommonStore()),
	mLoadGame_Button(ref.GetCommonStore()),
	mTutorialGame_Button(ref.GetCommonStore())
{
}


MainMenu::~MainMenu()
{
}
