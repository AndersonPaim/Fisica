#include "MyTeste.h"
#include "test.h"
#include <iostream>


class MyTest3 : public Test //voc� cria a sua classe derivada da classe base Test
{
	int boxRestituion = 0;
public:
	MyTest3() {
		// Aqui no construtor voc� inicializa a cena
		b2World* world;
		b2Vec2 gravity(0.0f, -9.8f);
		world = new b2World(gravity);


		CreateGround(30, 1, b2Vec2(0, 0));

		//box stack
		CreateBox(10, 1, 1, 1, 0, b2Vec2(-20, 1));
		CreateBox(10, 1, 1, 1, 0, b2Vec2(-20, 3));
		CreateBox(10, 1, 1, 1, 0, b2Vec2(-20, 5));
		CreateBox(10, 1, 1, 1, 0, b2Vec2(-20, 7));
		CreateBox(10, 1, 1, 1, 0, b2Vec2(-20, 9));
		CreateBox(10, 1, 1, 1, 0, b2Vec2(-20, 11));
		//circle stack
		CreateCircle(10, 1, 1, 0, b2Vec2(-10, 1));
		CreateCircle(10, 1, 1, 0, b2Vec2(-10, 3));
		CreateCircle(10, 1, 1, 0, b2Vec2(-10, 5));
		CreateCircle(10, 1, 1, 0, b2Vec2(-10, 7));
		CreateCircle(10, 1, 1, 0, b2Vec2(-10, 9));
		CreateCircle(10, 1, 1, 0, b2Vec2(-10, 11));
		//box wall
		float x = -5;
		float y = 0;
		for (int i = 0; i < 10; i++)
		{
			y = 1;
			x += 2.1f;
			for (int j = 0; j < 10; j++)
			{
				CreateBox(10, 1, 1, 1, 0, b2Vec2(x, y));
				y += 3;
			}

		}

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

	void CreateCircle(float density, int radius, float friction, float restitution, b2Vec2 position)
	{
		b2Body* circleObj;

		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position = position;
		circleObj = m_world->CreateBody(&bd);

		b2CircleShape circle;
		circle.m_radius = radius;

		b2FixtureDef fd;
		fd.shape = &circle;
		fd.density = density;
		fd.friction = friction;
		fd.restitution = restitution;

		circleObj->CreateFixture(&fd);
	}

	void CreateBox(int density, float height, float width, float friction, float restitution, b2Vec2 position)
	{
		b2BodyDef boxObj;
		boxObj.type = b2_dynamicBody;
		boxObj.position = position;
		b2Body* body = m_world->CreateBody(&boxObj);

		b2PolygonShape box;

		box.SetAsBox(height, width);
		b2FixtureDef fd;
		fd.shape = &box;
		fd.density = density;
		fd.friction = friction;
		fd.restitution = restitution;

		body->CreateFixture(&fd);
	}

	void CreateGround(float height, float width, b2Vec2 position)
	{
		b2BodyDef boxObj;
		boxObj.type = b2_staticBody;
		boxObj.position = position;
		b2Body* body = m_world->CreateBody(&boxObj);

		b2PolygonShape box;

		box.SetAsBox(height, width);
		b2FixtureDef fd;
		fd.shape = &box;

		body->CreateFixture(&fd);
	}

	void CreateEdge(int density, float height, float width, float friction, float restitution, b2Vec2 position, b2Vec2 pos1, b2Vec2 pos2)
	{
		b2Body* edge;

		b2BodyDef bt;
		bt.type = b2_dynamicBody;
		bt.position = position;
		edge = m_world->CreateBody(&bt);
		b2EdgeShape shape;
		shape.SetTwoSided(b2Vec2(-pos1), b2Vec2(pos2));
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = density;
		fd.restitution = restitution;

		edge->CreateFixture(&fd);
	}


	void Step(Settings& settings) override
	{
		//Chama o passo da simula��o e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Exercicios 11, 12");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padr�o de projeto chamado Factory
						   //para sua arquitetura de classes
	{


		return new MyTest3;
	}

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_C:
		{
			b2Vec2 pos(RandomFloat(-15.0f, 15.0f), 30.0f);
			float density(RandomFloat(0.1f, 1.0f));
			float radius(RandomFloat(0.1f, 5.0f));
			float restitution(RandomFloat(0.0f, 1.0f));
			float friction(RandomFloat(0.0f, 1.0f));
			CreateCircle(density, radius, friction, restitution, pos);

			break;
		}
		case GLFW_KEY_B:
		{
			b2Vec2 pos(RandomFloat(-15.0f, 15.0f), 30.0f);

			float density(RandomFloat(0.1f, 35.0f));
			float height(RandomFloat(0.1f, 1.0f));
			float width(RandomFloat(1.0f, 5.0f));
			float friction(RandomFloat(0.0f, 1.0f));
			CreateBox(density, height, width, friction, boxRestituion, pos);

			if (boxRestituion < 1)
			{
				boxRestituion++;
			}

			break;
		}
		case GLFW_KEY_L:
		{
			b2Vec2 position(RandomFloat(5.0f, 15.0f), RandomFloat(5.0f, 15.0f));
			b2Vec2 pos1(RandomFloat(5.0f, 15.0f), RandomFloat(5.0f, 15.0f));
			b2Vec2 pos2(RandomFloat(5.0f, 15.0f), RandomFloat(5.0f, 15.0f));

			float density(RandomFloat(0.1f, 35.0f));
			float height(RandomFloat(0.1f, 1.0f));
			float width(RandomFloat(1.0f, 5.0f));
			float restitution(RandomFloat(0.0f, 1.0f));
			float friction(RandomFloat(0.0f, 1.0f));

			CreateEdge(density, height, width, friction, restitution, position, pos1, pos2);
			break;
		}
		}

	}
};
//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "MyTeste3", MyTest3::Create);
