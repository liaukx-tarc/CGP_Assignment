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
	projectileRect.top = 0;
	projectileRect.left = 0;
	projectileRect.bottom = projectileRect.top + 32;
	projectileRect.right = projectileRect.left + 32;

	isComplete = true;
	timer = 0;
	tDistance = 0;
	cDistance = 0;
}

void Physics::update()
{
	for (int i = 0; i < projectilePositionList.size(); i++)
	{
		totalDistance = enemyPositionList[i] - towerPositionList[i];
		tDistance = sqrt((totalDistance.x*totalDistance.x) + (totalDistance.y*totalDistance.y));
		printf("%.2f %.2f\n", tDistance, cDistance);
		if (!isComplete)
		{
			projectilePositionList[i].x += totalDistance.x * 0.05;
			projectilePositionList[i].y += totalDistance.y * 0.05;
			cDistance += tDistance * 0.05;
		}
		if (cDistance > tDistance)
		{
			isComplete = true;
			cDistance = 0;
			projectilePositionList.erase(projectilePositionList.begin() + i);
			enemyPositionList.erase(enemyPositionList.begin() + i);
			towerPositionList.erase(towerPositionList.begin() + i);
		}
		else
		{
			isComplete = false;
		}
	}
}

void Physics::projectile(D3DXVECTOR3 towerPosition, D3DXVECTOR3 enemyPosition)
{
	/*towerPosition.x -= 5;*/
	towerPositionList.push_back(towerPosition);
	enemyPositionList.push_back(enemyPosition);
	projectilePosition.x = towerPosition.x;
	projectilePosition.y = towerPosition.y - 5;
	projectilePositionList.push_back(projectilePosition);
}

void Physics::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	for (int i = 0; i < projectilePositionList.size(); i++)
	{
		printf("%.2f %.2f %.2f\n", towerPositionList[i].x, towerPositionList[i].y, towerPositionList[i].z);
		printf("%.2f %.2f %.2f\n", enemyPositionList[i].x, enemyPositionList[i].y, enemyPositionList[i].z);
		printf("%.2f %.2f %.2f\n", projectilePositionList[i].x, projectilePositionList[i].y, projectilePositionList[i].z);
		drawPosition.x = projectilePositionList[i].x / 2.0f;
		drawPosition.y = projectilePositionList[i].y / 2.2f;
		drawPosition.z = 0;
		sprite->Draw(projectileTexture, &projectileRect, &D3DXVECTOR3(16, 16, 0), &drawPosition, D3DCOLOR_XRGB(255, 255, 255));
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
