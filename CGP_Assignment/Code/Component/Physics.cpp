#include "Physics.h"
#include "Graphic.h"

//singleton
Physics* Physics::sInstance = NULL;

Physics* Physics::getInstance()
{
	if (Physics::sInstance == NULL)
	{
		sInstance = new Physics;
	}

	return sInstance;
}

void Physics::releaseInstance()
{
	delete sInstance;
	sInstance = NULL;
}

Physics::Physics()
{

}

Physics::~Physics()
{
	
}

void Physics::init()
{
	hr[0] = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);
	hr[1] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/bullet.png", &projectileTexture);

	for (int i = 0; i < sizeof(hr); i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		projectileRect[i].top = 0;
		projectileRect[i].left = 32 * i;
		projectileRect[i].bottom = projectileRect[i].top + 32;
		projectileRect[i].right = projectileRect[i].left + 32;
	}

	isComplete = true;
	timer = 0;
	tDistance = 0;
}

void Physics::update()
{
	for (int i = 0; i < projectilePositionList.size(); i++)
	{
		enemy = EnemyController::getInstance()->enemyList;
		enemyPosition = enemy[enemyCountList[i]]->objPosition;
		totalDistance = enemyPosition - projectilePositionList[i];
		tDistance = sqrt((totalDistance.x*totalDistance.x) + (totalDistance.y*totalDistance.y));
		if (!isComplete)
		{
			projectilePositionList[i].x += totalDistance.x / tDistance * 10;
			projectilePositionList[i].y += totalDistance.y / tDistance * 10;
		}
		if (tDistance <= 5)
		{
			isComplete = true;
			switch (tower[i])
			{
			case 0:
				enemy[enemyCountList[i]]->health -= 2;
				enemy[enemyCountList[i]]->r = 123;
				enemy[enemyCountList[i]]->g = 125;
				enemy[enemyCountList[i]]->b = 110;
				switch(enemy[enemyCountList[i]]->directionState)
				{
				case 'l':
					enemy[enemyCountList[i]]->objPosition.x += 10;
					break;
				case 'r':
					enemy[enemyCountList[i]]->objPosition.x -= 10;
					break;
				case 't':
					enemy[enemyCountList[i]]->objPosition.y += 10;
					break;
				case 'b':
					enemy[enemyCountList[i]]->objPosition.y -= 10;
					break;
					
				}
				break;
			case 1:
				enemy[enemyCountList[i]]->health -= 3;
				enemy[enemyCountList[i]]->r = 207;
				enemy[enemyCountList[i]]->g = 180;
				enemy[enemyCountList[i]]->b = 17;
				break;
			case 2:
				enemy[enemyCountList[i]]->health -= 2;
				enemy[enemyCountList[i]]->r = 10;
				enemy[enemyCountList[i]]->g = 150;
				enemy[enemyCountList[i]]->b = 245;
				enemy[enemyCountList[i]]->isSlow = true;
				break;
			case 3:
				enemy[enemyCountList[i]]->health -= 5;
				enemy[enemyCountList[i]]->r = 252;
				enemy[enemyCountList[i]]->g = 100;
				enemy[enemyCountList[i]]->b = 100;
				break;
			}
			enemy[enemyCountList[i]]->isHit = true;

			printf("%.2f\n", enemy[enemyCountList[i]]->health);
			projectilePositionList.erase(projectilePositionList.begin() + i);
			enemyCountList.erase(enemyCountList.begin() + i);
			towerPositionList.erase(towerPositionList.begin() + i);
			tower.erase(tower.begin() + i);
		}
		else
		{
			isComplete = false;
		}
	}
}

void Physics::projectile(D3DXVECTOR3 towerPosition, int enemyCount, int towerNo)
{
	towerPositionList.push_back(towerPosition);
	enemyCountList.push_back(enemyCount);
	projectilePosition.x = towerPosition.x;
	projectilePosition.y = towerPosition.y - 5;
	projectilePositionList.push_back(projectilePosition);
	tower.push_back(towerNo);
}

void Physics::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	for (int i = 0; i < projectilePositionList.size(); i++)
	{
		drawPosition.x = projectilePositionList[i].x / 2.0f;
		drawPosition.y = projectilePositionList[i].y / 2.1f;
		drawPosition.z = 0;
		sprite->Draw(projectileTexture, &projectileRect[tower[i]], &D3DXVECTOR3(16, 16, 0), &drawPosition, D3DCOLOR_XRGB(255, 255, 255));
		scaling.x = scaling.y = 2.0f;
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
		sprite->SetTransform(&mat);
	}
	sprite->End();
}


void Physics::release()
{
	sprite->Release();
	sprite = NULL;

	projectileTexture->Release();
	projectileTexture = NULL;
}
