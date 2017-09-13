#include <stdio.h>
#include <string.h>

#include "DLinkedList.h"
#include "GameSystem.h"
#include "Texture.h"
#include "Sprite.h"


Sprite::Sprite(const char* fileName, bool isLoop)
{
	DLinkedList<Texture*> linkedList;
		
	char filePath[256];
	sprintf(filePath, "../Resources/%s", fileName);
	FILE* fp = fopen(filePath, "r");
	if (NULL == fp)
	{
		printf("File Open Error %s\n", fileName);
	}

	char* textureName;
	float scaleWidth;
	float scaleHeight;

	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);
	while (true)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		{
			char* token = strtok(record, ",");
			textureName = token;

			token = strtok(NULL, ",");
			scaleWidth = atof(token);

			token = strtok(NULL, ",");
			scaleHeight = atof(token);

			Texture* texture = new Texture(textureName);
			texture->SetScale(scaleWidth, scaleHeight);
			linkedList.Append(texture);
		}
	}

	fclose(fp);
		
	_frames = linkedList.Count();
	_textureFrames = new Array<Texture*>(_frames);

	int frame = 0;
	DLinkedListIterator<Texture*> itr = linkedList.GetIterator();
	for(itr.Start() ; itr.Valid() ; itr.Forth())
	{
		Texture* texture = itr.Item();
		_textureFrames->Set(frame, texture);
		frame++;
	}

	_frame = 0;

	_animationSpeed = 1000 / _frames;
	_frameDuration = 0;

	_isLoop = isLoop;
	if (_isLoop)
	{
		_isPlay = true;
	}
	else
	{
		_isPlay = false;
	}
}

Sprite::~Sprite()
{
}

void Sprite::Update(int deltaTime)
{
	if (false == _isPlay)
		return;

	_frameDuration += deltaTime;
	
	if (_animationSpeed <= _frameDuration)
	{
		_frameDuration = 0;
		_frame = (_frame + 1) % _frames;

		if (false == _isLoop)
		{
			if (0 == _frame)
			{
				_isPlay = false;
			}
		}
	}

	Texture* texture = _textureFrames->Get(_frame);
	texture->SetPosition(_x, _y);
}

void Sprite::Render()
{
	if (false == _isPlay)
		return;

	_textureFrames->Get(_frame)->Render();
}

void Sprite::SetPosition(int x, int y)
{
	_x = x;
	_y = y;

	Texture* texture = _textureFrames->Get(_frame);
	texture->SetPosition(x, y);
}

void Sprite::Play()
{
	_frame = 0;
	_isPlay = true;
}