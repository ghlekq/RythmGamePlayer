#include <stdio.h>

#include "GameSystem.h"
#include "Sprite.h"
#include "Note.h"
#include "Track.h"

Note::Note(float sec, int judgeLineDelta,int x_width)
{
	_sprite = NULL;
	_startTick = GameSystem::GetInstance()->GetGameTimeTick() - (sec * 1000);
	_judgeLineDelta = judgeLineDelta;
	GameSystem::GetInstance()->SetWidth(x_width);
	_isPass = false;
	
}

Note::~Note()
{
	Deinit();
}

void Note::Init()
{
	_sprite = new Sprite("notespr.csv", true);
	_updateDuration = 0;
	_x = GameSystem::GetInstance()->Width();
		
	_updateDuration = _startTick;
	_isLive = true;

	UpdatePosition(0);
}

void Note::Deinit()
{
	if (NULL != _sprite)
	{
		delete _sprite;
		_sprite = NULL;
	}
}

void Note::Update(int deltaTime)
{
	_sprite->Update(deltaTime);
		
	int totalMoveTick = 8000;
	int totalHeight = GameSystem::GetInstance()->GetWindowHeight() * 4;
	
	UpdatePosition(deltaTime);
}

void Note::Render()
{
	_sprite->Render();
}

void Note::UpdatePosition(int deltaTime)
{
	_updateDuration += deltaTime;
	if (_updateDuration < GameSystem::GetInstance()->GetGameTimeTick() + 500)
	{
		float positionRate = (float)_updateDuration / (float)GameSystem::GetInstance()->GetGameTimeTick();
		float positonInSec = GameSystem::GetInstance()->GetTrackHeight() * positionRate;
		_y = positonInSec - (GameSystem::GetInstance()->GetTrackHeight() - GameSystem::GetInstance()->GetWindowHeight() + _judgeLineDelta);

		_sprite->SetPosition(_x, _y);
	}
	else
	{
		_isLive = false;
	}
}

void Note::Pass()
{
	_isPass = true;
}

bool Note::IsPass()
{
	return _isPass;
}

bool Note::IsLive()
{
	return _isLive;
}

int Note::GetNoteTime()
{
	return _updateDuration;
}

