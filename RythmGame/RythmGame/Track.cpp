#include <stdio.h>
#include <stdlib.h>

#include "GameSystem.h"
#include "Sprite.h"
#include "Note.h"
#include "Track.h"

Track::Track(int x,int y)
{
	_isKeyDown = false;
	_judge = eJudge::NONE;
	_effectList = NULL;
	GameSystem::GetInstance()->SetWidth(x);
	y_height = y;
}

Track::~Track()
{

}

void Track::Init()
{
	Sprite* backgroundSprite = new Sprite("trackbackgroundspr.csv", true);
	backgroundSprite->SetPosition(GameSystem::GetInstance()->Width(), y_height);
	_backgroundSpriteList.Append(backgroundSprite);

	_judgeLineDeltaPos = 100;

	Sprite* judgeLineSprite = new Sprite("trackjudgeline.csv", true);
	judgeLineSprite->SetPosition(GameSystem::GetInstance()->Width(), y_height*2- _judgeLineDeltaPos);
	_backgroundSpriteList.Append(judgeLineSprite);

	Sprite* explosionSprite = new Sprite("explosionspr.csv", false);
	explosionSprite->SetPosition(GameSystem::GetInstance()->Width(), y_height * 2 - _judgeLineDeltaPos);

	Sprite* failSprite = new Sprite("failjudgespr.csv", false);
	failSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2, GameSystem::GetInstance()->GetWindowHeight() / 2);

	_effectList = new Array<Sprite*>(2);
	_effectList->Set(eEffect::EXPLOSION, explosionSprite);
	_effectList->Set(eEffect::FAIL, failSprite);

	int totalTick = GameSystem::GetInstance()->GetGameTimeTick();
	int deltaTick = 0;
	for (int noteTick = 0; noteTick < totalTick; )
	{
		int randValue = rand() % 3;
		switch (randValue)
		{
		case 0:
			deltaTick = 250;
			break;
		case 1:
			deltaTick = 500;
			break;
		case 2:
			deltaTick = 750;
			break;
		default:
			deltaTick = 1000;
			break;
		}

		noteTick += deltaTick;

		float sec = (float)noteTick / 1000.0f;
		Note* note = new Note(sec, _judgeLineDeltaPos,GameSystem::GetInstance()->Width());
		note->Init();
		_noteList.Append(note);
	}
}

void Track::Deinit()
{
	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		itr.Item()->Deinit();
		delete itr.Item();
		_noteList.Remove(itr);
	}

	DLinkedListIterator<Sprite*> backItr = _backgroundSpriteList.GetIterator();
	for (backItr.Start(); backItr.Valid(); backItr.Forth())
	{
		if (NULL != backItr.Item())
		{
			delete backItr.Item();
		}
		_backgroundSpriteList.Remove(backItr);
	}

	if (NULL != _effectList)
	{
		for (int i = 0; i < _effectList->Size(); i++)
		{
			delete _effectList->Get(i);
		}
		delete _effectList;
		_effectList = NULL;
	}
}

void Track::Update(int deltaTime)
{
	DLinkedListIterator<Sprite*> backItr = _backgroundSpriteList.GetIterator();
	for (backItr.Start(); backItr.Valid(); backItr.Forth())
	{
		backItr.Item()->Update(deltaTime);
	}

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		if (itr.Item()->IsLive())
		{
			itr.Item()->Update(deltaTime);
		}
		else
		{
			delete itr.Item();
			_noteList.Remove(itr);
		}

		int judgeTick = GameSystem::GetInstance()->GetGameTimeTick();

		_judgeStartTick = judgeTick - 100;
		_judgeEndTick = judgeTick + 100;
		if (_judgeEndTick < itr.Item()->GetNoteTime() && false == itr.Item()->IsPass())
		{
			itr.Item()->Pass();
			_judge = eJudge::FAIL;			
			_effectList->Get(eEffect::FAIL)->Play();
		}
	}

	for (int i = 0; i < _effectList->Size(); i++)
	{
		_effectList->Get(i)->Update(deltaTime);
	}
}

void Track::Render()
{

	DLinkedListIterator<Sprite*> backItr = _backgroundSpriteList.GetIterator();
	for (backItr.Start(); backItr.Valid(); backItr.Forth())
	{
		backItr.Item()->Render();
	}

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		itr.Item()->Render();
	}

	for (int i = 0; i < _effectList->Size(); i++)
	{
		_effectList->Get(i)->Render();
	}
}


void Track::KeyDown()
{
	if (_isKeyDown)
		return;
	_isKeyDown = true;


	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		if (itr.Item()->GetNoteTime() < _judgeStartTick)
		{
			break;
		}

		if (_judgeStartTick <= itr.Item()->GetNoteTime() && itr.Item()->GetNoteTime() <= _judgeEndTick)
		{
			_judge = eJudge::JUDGE;
			break;
		}
		if (_judgeEndTick < itr.Item()->GetNoteTime() && false == itr.Item()->IsPass())
		{
			_judge = eJudge::FAIL;
			break;
		}
	}

	switch (_judge)
	{
	case eJudge::JUDGE:
		_effectList->Get(eEffect::EXPLOSION)->Play();
		GameSystem::GetInstance()->SetScore((GameSystem::GetInstance()->Score())+ 50);
		_noteList.Remove(itr);
		break;
	case eJudge::FAIL:
		_effectList->Get(eEffect::FAIL)->Play();
		GameSystem::GetInstance()->SetScore((GameSystem::GetInstance()->Score()) -10);
		_noteList.Remove(itr);
		break;
	}
}

void Track::KeyUp()
{
	_judge = eJudge::NONE;
	_isKeyDown = false;
}
