#include "World.h"
#include "Graphics.h"
#include "EntityBackground.h"
#include "EntityEnemy.h"
#include "EntityPlayer.h"
#include "EntityBullet.h"
#include "EntityExplosions.h"
#include "Sound.h"

#include <cassert>

World::World()
{
}

World::~World()
{
	delete m_gfx;
	delete SE_shoot;
	delete SE_explode;

	for (auto p : m_entityVector) {
		delete p;
	}
}

bool World::LoadLevel()
{
	//Creating Sprites
	if (!m_gfx->CreateSprite("Data/Background.png", "Background"))
		return false;
	if (!m_gfx->CreateSprite("Data/Lightning.png", "Player",32 , 32, 4, 10))
		return false;
	if (!m_gfx->CreateSprite("Data/Saboteur.png", "Enemy", 32, 32, 4, 10))
		return false;
	if (!m_gfx->CreateSprite("Data/Bullet.png", "Bullet"))
		return false;
	for (int i = 1; i < m_numExplosions + 1; i++) 
	{
		if (!m_gfx->CreateSprite("Data/Explosion2.png", "Explosion" + std::to_string(i), 32, 32, 16, 10, 1, false))
			return false;
	}

	//loading sound
	SE_shoot->LoadSound("Data/laser2.wav");
	SE_explode->LoadSound("Data/explodify4.wav");
	
	//Creating two background entities for scrolling background
	EntityBackground* newBackground = new EntityBackground("Background", m_gfx->getSpriteSize("Background"), m_gfx->getScreenSize());
	m_entityVector.push_back(newBackground);

	newBackground->SetPosition(Vector2(0, 0));

	EntityBackground* newBackground2 = new EntityBackground("Background", m_gfx->getSpriteSize("Background"), m_gfx->getScreenSize());
	m_entityVector.push_back(newBackground2);

	newBackground2->SetPosition(Vector2(0, -1000));

	//Creating player entity
	m_playerVectorStartIndex = (int)m_entityVector.size();
	EntityPlayer* newPlayer = new EntityPlayer("Player", m_gfx->getSpriteSize("Player"), m_gfx->getScreenSize());
	m_entityVector.push_back(newPlayer);

	newPlayer->SetPosition(Vector2(218, 650));
	newPlayer->SetSpeed(10.0f);
	newPlayer->SetHealth(m_playerHealth);

	//Creating enemy entities
	m_enemyVectorStartIndex = (int)m_entityVector.size();
	Vector2 oldPos, enemyPos;
	Rectangle oldRect, enemyRect;
	int oldShoot{ 0 }, newShoot{ 0 };
	for (int i = 0; i < m_numEnemy; i++) 
	{
		EntityEnemy* newEnemy = new EntityEnemy("Enemy", m_gfx->getSpriteSize("Enemy"), m_gfx->getScreenSize());

		//Randomizing enemy position
		do 
		{
			srand(HAPI.GetTime() + i);
			enemyPos.x = rand() % (m_gfx->getScreenSize().right - (int)m_gfx->getSpriteSize("Enemy").w);
			enemyPos.y = -(rand() % 100 + (int)m_gfx->getSpriteSize("Enemy").h);

			enemyRect = Rectangle(m_gfx->getSpriteSize("Enemy").w, m_gfx->getSpriteSize("Enemy").h, enemyPos);
			oldRect = Rectangle(m_gfx->getSpriteSize("Enemy").w, m_gfx->getSpriteSize("Enemy").h, oldPos);
		} 
		while (!(oldRect.right < enemyRect.left || enemyRect.right < oldRect.left));

		newEnemy->SetPosition(enemyPos);
		oldPos = enemyPos;
		newEnemy->SetHealth(2);

		do 
		{
			srand(HAPI.GetTime() + i);
			newShoot = rand() % 5000 + 4000;
		} 
		while (newShoot == oldShoot);

		newEnemy->SetShootTime(newShoot);
		oldShoot = newShoot;

		m_entityVector.push_back(newEnemy);
		
	}

	//Creating explosion entites
	m_explVectorStartIndex = (int)m_entityVector.size();
	for (int i = 0; i < m_numExplosions; i++)
	{
		EntityExplosions* newExplosion = new EntityExplosions("Explosion" + std::to_string(i+1), m_gfx->getSpriteSize("Explosion" + std::to_string(i + 1)), m_gfx->getScreenSize());

		newExplosion->SetAlive(false);

		m_entityVector.push_back(newExplosion);
	}
	
	//Creating bullet entities
	m_bulletsVectorStartIndex = (int)m_entityVector.size();
	for (int i = 0; i < m_numBullets; i++) 
	{
		EntityBullet* newBullet = new EntityBullet("Bullet", m_gfx->getSpriteSize("Bullet"), m_gfx->getScreenSize());

		newBullet->SetHealth(1);
		newBullet->SetAlive(false);
		newBullet->SetSpeed(15.0f);
		m_entityVector.push_back(newBullet);
	}

	return true;
}

void World::Reset()
{
	//resetting player
	m_entityVector[m_playerVectorStartIndex]->SetPosition(Vector2(218, 650));
	m_entityVector[m_playerVectorStartIndex]->SetSpeed(10.0f);
	m_entityVector[m_playerVectorStartIndex]->SetHealth(m_playerHealth);
	m_entityVector[m_playerVectorStartIndex]->SetAlive(true);

	//resetting enemy
	Vector2 oldPos, enemyPos;
	Rectangle oldRect, enemyRect;
	int oldShoot{ 0 }, newShoot{ 0 };
	for (int i = m_enemyVectorStartIndex; i < m_enemyVectorStartIndex + m_numEnemy; i++)
	{
		do 
		{
			srand(HAPI.GetTime() + i);
			enemyPos.x = rand() % (m_gfx->getScreenSize().right - (int)m_gfx->getSpriteSize("Enemy").w);
			enemyPos.y = -(rand() % 100 + (int)m_gfx->getSpriteSize("Enemy").h);

			enemyRect = Rectangle(m_gfx->getSpriteSize("Enemy").w, m_gfx->getSpriteSize("Enemy").h, enemyPos);
			oldRect = Rectangle(m_gfx->getSpriteSize("Enemy").w, m_gfx->getSpriteSize("Enemy").h, oldPos);
		} 
		while (!(oldRect.right < enemyRect.left || enemyRect.right < oldRect.left));

		m_entityVector[i]->SetPosition(enemyPos);
		oldPos = enemyPos;
		m_entityVector[i]->SetHealth(2);

		do 
		{
			srand(HAPI.GetTime() + i);
			newShoot = rand() % 5000 + 4000;
		} 
		while (newShoot == oldShoot);

		m_entityVector[i]->SetShootTime(newShoot);
		oldShoot = newShoot;

		m_entityVector[i]->SetAlive(true);
	}

	//resetting explosion entities
	for (int i = m_explVectorStartIndex; i < m_explVectorStartIndex + m_numExplosions; i++)
		m_entityVector[i]->SetAlive(false);

	//resetting explosion sprites currentFrame
	for (int i = 1; i < m_numExplosions + 1; i++)
	{
		m_gfx->resetFrame("Explosion" + std::to_string(i));
	}

	//resetting bullet entities
	for (int i = m_explVectorStartIndex; i < m_explVectorStartIndex + m_numExplosions; i++) 
	{
		m_entityVector[i]->SetHealth(1);
		m_entityVector[i]->SetAlive(false);
		m_entityVector[i]->SetSpeed(15.0f);
	}
		
}

void World::Update()
{
	DWORD lastTimeTicked{ 0 };

	while (HAPI.Update())
	{
		DWORD timeSinceLastTick{ HAPI.GetTime() - lastTimeTicked };

		if (!gameOver) 
			//Update all entities
			if ((int)timeSinceLastTick >= m_delay)
			{
				for (auto p : m_entityVector)
				{
					if (p->isAlive())
					{
						p->Update();

						//Firing
						if (p->GetSide() != ESide::eNeutral)
						{
							p->SetCurrentTime(p->getCurrentTime() + (int)timeSinceLastTick);
							if (p->isFire)
							{
								p->isFire = false;

								for (int i = m_bulletsVectorStartIndex; i < m_bulletsVectorStartIndex + m_numBullets; i++)
								{
									if (!m_entityVector[i]->isAlive() && m_entityVector[i]->getHealth() >= 1)
									{
										m_entityVector[i]->SetAlive(true); //Set bullet to alive

										Vector2 bulletPos; //Bullet positiion

										bulletPos.x = p->getPosition().x + (p->getEntityRect().Width() / 2) - (m_entityVector[i]->getEntityRect().Width() / 2);
										bulletPos.y = p->getPosition().y + (p->getEntityRect().Height() / 2) - m_entityVector[i]->getEntityRect().Height();

										m_entityVector[i]->SetPosition(bulletPos); //Set it's position
										m_entityVector[i]->SetSide(p->GetSide()); //Set it's side to the same as the entity that is firing it

										SE_shoot->PlaySound();
										break;
									}
									else if (i == m_bulletsVectorStartIndex + m_numBullets - 1 && m_entityVector[i]->isAlive())
										HAPI.UserMessage("Out of Bullets!", "ERROR");
								}
							}
						}

						//Checking for collision
						if (p->GetSide() != ESide::eNeutral)
						{
							for (auto q : m_entityVector)
							{
								if (q->GetSide() != ESide::eNeutral)
									if (q != p)
										if (q->GetSide() != p->GetSide())
											if (q->isAlive())
												if (q->getEntityRect().isCollide(p->getEntityRect()))
												{
													p->damaged(q->getDamage());
													q->damaged(p->getDamage());

													if (!p->isAlive())
													{
														for (int i = m_explVectorStartIndex; i < m_explVectorStartIndex + m_numExplosions; i++)
														{
															if (!m_entityVector[i]->isAlive())
															{
      															m_entityVector[i]->SetAlive(true); //Set explosion to alive

																Vector2 explPos; //Explosion positiion

																explPos.x = p->getPosition().x + (p->getEntityRect().Width() / 2) - (m_entityVector[i]->getEntityRect().Width() / 2);
																explPos.y = p->getPosition().y + (p->getEntityRect().Height() / 2) - m_entityVector[i]->getEntityRect().Height();

																m_entityVector[i]->SetPosition(explPos); //Set it's position

																SE_explode->PlaySound();

																break;
															}
															else if (i == m_explVectorStartIndex + m_numExplosions - 1 && m_entityVector[i]->isAlive())
																HAPI.UserMessage("Out of Bullets!", "ERROR");
														}

														if (p->GetSide() == ESide::eEnemy && p->getName() != "Bullet")
														{
															deadEnemies++;
															m_currentScore += 100;
														}
													}

													if (!q->isAlive())
													{
														for (int i = m_explVectorStartIndex; i < m_explVectorStartIndex + m_numExplosions; i++)
														{
															if (!m_entityVector[i]->isAlive())
															{
																m_entityVector[i]->SetAlive(true); //Set explosion to alive

																Vector2 explPos; //Explosion positiion

																explPos.x = q->getPosition().x + (q->getEntityRect().Width() / 2) - (m_entityVector[i]->getEntityRect().Width() / 2);
																explPos.y = q->getPosition().y + (q->getEntityRect().Height() / 2) - m_entityVector[i]->getEntityRect().Height();

																m_entityVector[i]->SetPosition(explPos); //Set it's position

																SE_explode->PlaySound();

																break;
															}
															else if (i == m_explVectorStartIndex + m_numExplosions - 1 && m_entityVector[i]->isAlive())
																HAPI.UserMessage("Out of Bullets!", "ERROR");
														}
														if (q->GetSide() == ESide::eEnemy && q->getName() != "Bullet")
														{
															deadEnemies++;
															m_currentScore += 100;
														}
													}
												}

							}
						}

						if (p->GetSide() == ESide::eEnemy)
							if (!p->getEntityRect().CompletelyOutside(m_gfx->getScreenSize()))
								p->SetCurrentTime(p->getCurrentTime() + (int)timeSinceLastTick);

					}
					else if (p->GetSide() == ESide::ePlayer && p->getName() != "Bullet")
						gameOver = true;
					else if (deadEnemies == m_numEnemy)
					{
						gameOver = true;
						win = true;
					}
				}
				lastTimeTicked = HAPI.GetTime();
				timeSinceLastTick = 0;
			} 

		//Draw all the entities
		for (auto p : m_entityVector) 
		{
			if (p->isAlive()) 
			{
				p->Render(*m_gfx);

				if (p->GetSide() == ESide::ePlayer && !gameOver)
					m_gfx->updateUI(p->getHealth(), m_currentScore);
			}
		}

		if (gameOver)
		{
			HAPI_TKeyboardData keyData = HAPI.GetKeyboardData();

			m_gfx->gameOverUI(m_currentScore, win);

			if (keyData.scanCode[HK_RETURN]) 
			{
				//resetting to level start settings
				deadEnemies = 0;
				m_currentScore = 0;
				Reset();
				gameOver = false;
				win = false;
			}

			if (keyData.scanCode[HK_ESCAPE])
				HAPI.Close();
		}

		
	}
}

void World::Run()
{
	m_gfx = new Graphics;
	if (!m_gfx->Initialise(500, 800))
		return;

	if (!LoadLevel())
		return;

	Update();
}
