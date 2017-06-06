#include "MainMenu.h"
#include "Game.h"

void MainMenu::Initiate()
{
	/*Only Initiate Once*/
	if (mInitiated)
		return;
	else
		mInitiated = true;

	mMusic.openFromFile("Media/MenuMusic.wav");
	mMusic.play();

	/*Setup Sprites*/
	mBackgroundImage.setTexture(mGameReference.GetCommonStore().GetTextureRef("MenuBackground"));
	mBackgroundImage.setPosition(sf::Vector2f(0, 0));

	mLogoImage.setTexture(mGameReference.GetCommonStore().GetTextureRef("Logo"));
	mLogoImage.setPosition(float(mGameReference.GetWindow().getSize().x / 2 - 333),
		float(mGameReference.GetWindow().getSize().y / 2 - 350));

	mStartGame_Button.Initiate((mGameReference.GetWindow().getSize().x / 2) - 125,
		mGameReference.GetWindow().getSize().y / 2,
		"Start", 30 , "BaseButtons", 1, 250, 80);
	mStartGame_Button.AnimationToggle(false);
	mLoadGame_Button.Initiate((mGameReference.GetWindow().getSize().x / 2) - 125,
		mGameReference.GetWindow().getSize().y / 2 + (mButtonSpacing + 80),
		"Load", 30 , "BaseButtons", 1, 250, 80);
	mLoadGame_Button.AnimationToggle(false);
	mTutorialGame_Button.Initiate((mGameReference.GetWindow().getSize().x / 2) - 125,
		mGameReference.GetWindow().getSize().y / 2 + (mButtonSpacing * 2) + 160,
		"Tutorial", 30 , "BaseButtons", 1, 250, 80);
	mTutorialGame_Button.AnimationToggle(false);
}

void MainMenu::HandleInput()
{
}

void MainMenu::Update(float dt)
{
}

void MainMenu::Draw()
{
	mGameReference.GetWindow().clear();
	mGameReference.GetWindow().draw(mBackgroundFill);
	mGameReference.GetWindow().draw(mBackgroundImage);
	mGameReference.GetWindow().draw(mLogoImage);
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
	mGameReference.GetPlayer().Initiate(30.0f, 265.0f, "CMDR Ayna P");
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
