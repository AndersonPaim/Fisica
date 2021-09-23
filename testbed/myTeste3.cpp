#include "test.h"
#include <iostream>
#include <string>


class MyTest3 : public Test, b2ContactListener //voc� cria a sua classe derivada da classe base Test
{
	int boxRestituion = 0;
	bool isfirstBox = true;
	b2Body* player;
	bool isGrounded = true;

public:
	MyTest3() {
		// Aqui no construtor voc� inicializa a cena
		b2World* world;
		b2Vec2 gravity(0.0f, -9.8f);
		world = new b2World(gravity);

		CreateWall(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
		CreateWall(b2Vec2(-5.0f, 10.0f), b2Vec2(5.0f, 10.0f));
		CreateWall(b2Vec2(-30.0f, 7.0f), b2Vec2(-15.0f, 7.0f));
		CreateWall(b2Vec2(10.0f, 15.0f), b2Vec2(20.0f, 15.0f));

		int posX = -30;

		CreatePlayer(5, 1.5f, 3, 1, 0, b2Vec2(posX, 4));
	}

	void BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();
		b2Body* body1 = fixtureA->GetBody();
		b2Body* body2 = fixtureB->GetBody();
		isGrounded = true;
	}

	void EndContact(b2Contact* contact)
	{
		isGrounded = false;
	}

	void CreateWall(b2Vec2 pos1, b2Vec2 pos2)
	{
		b2Body* wall = NULL;
		{
			b2BodyDef bd;
			wall = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(pos1, pos2);

			b2FixtureDef fd;
			fd.shape = &shape;

			wall->CreateFixture(&fd);
		}
	}


	void CreatePlayer(int density, float height, float width, float friction, float restitution, b2Vec2 position)
	{
		b2BodyDef boxObj;
		boxObj.type = b2_dynamicBody;
		boxObj.position = position;
		b2Body* body = m_world->CreateBody(&boxObj);
		player = body;
		b2PolygonShape box;
		player->SetFixedRotation(true);
		box.SetAsBox(height, width);
		b2FixtureDef fd;
		fd.shape = &box;
		fd.density = density;
		fd.friction = friction;
		fd.restitution = restitution;
	

		body->CreateFixture(&fd);
	}

	void Keyboard(int key) override
	{
		switch (key)
		{
			case GLFW_KEY_SPACE:
				if (isGrounded)
				{
					b2Vec2 f = b2Vec2(player->GetWorldVector(b2Vec2(0, 70000.0f)));
					player->ApplyForceToCenter(f, true);
				}
				break;
		}
	}


	void Step(Settings& settings) override
	{
		//Chama o passo da simula��o e o algoritmo de rendering
		Test::Step(settings);

		if (glfwGetKey(g_mainWindow, GLFW_KEY_D) == GLFW_PRESS)
		{
			if (isGrounded)
			{
				b2Vec2 f = player->GetWorldVector(b2Vec2(20.0f, 0));
				b2Vec2 v = player->GetLinearVelocity();
				player->SetLinearVelocity(b2Vec2(20, v.y));
			}
		}
		if (glfwGetKey(g_mainWindow, GLFW_KEY_D) == GLFW_RELEASE)
		{
			if (isGrounded)
			{
				b2Vec2 v = player->GetLinearVelocity();
				player->SetLinearVelocity(b2Vec2(0, v.y));
			}
		}
		if (glfwGetKey(g_mainWindow, GLFW_KEY_A) == GLFW_PRESS)
		{
			if (isGrounded)
			{
				b2Vec2 f = player->GetWorldVector(b2Vec2(-20.0f, 0));
				b2Vec2 v = player->GetLinearVelocity();
				player->SetLinearVelocity(b2Vec2(-20, v.y));
			}
		}
		if (glfwGetKey(g_mainWindow, GLFW_KEY_A) == GLFW_RELEASE)
		{
			if (isGrounded)
			{
				b2Vec2 v = player->GetLinearVelocity();
				player->SetLinearVelocity(b2Vec2(0, v.y));
			}
		}

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Exercicio 3 - MOVER A e S, PULAR ESPAÇO");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padr�o de projeto chamado Factory
						   //para sua arquitetura de classes
	{


		return new MyTest3;
	}
};
//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "MyTeste", MyTest3::Create);
