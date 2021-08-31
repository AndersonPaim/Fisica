#include "MyTeste.h"
#include "test.h"
#include <iostream>

class MyTest : public Test //voc� cria a sua classe derivada da classe base Test
{
public:
	MyTest() {
		// Aqui no construtor voc� inicializa a cena
		b2World* world;
		b2Vec2 gravity(0.0f, -9.8f);
		world = new b2World(gravity);

		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));

			b2FixtureDef fd;
			fd.shape = &shape;

			ground->CreateFixture(&fd);
		}

		for (int i = 0; i < 3; i++)
		{
			b2Vec2 pos(RandomFloat(-15.0f, 15.0f), 30.0f);
			float density(RandomFloat(0.1f, 1.0f));
			float radius(RandomFloat(0.1f, 5.0f));
			float restitution(RandomFloat(0.0f, 1.0f));
			float friction(RandomFloat(0.0f, 1.0f)); 

			CreateCircle(density, radius, friction, restitution, pos);
		}

		for (int i = 0; i < 3; i++)
		{
			b2Vec2 pos(RandomFloat(-15.0f, 15.0f), 30.0f);
			float density(RandomFloat(0.1f, 35.0f));
			float height(RandomFloat(0.1f, 1.0f));
			float width(RandomFloat(1.0f, 5.0f));
			float restitution(RandomFloat(0.0f, 1.0f));
			float friction(RandomFloat(0.0f, 1.0f));

			CreateBox(density, height, width, friction, restitution, pos);
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


	void Step(Settings& settings) override
	{
		//Chama o passo da simula��o e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Este e' um template para os exercicios!! :)");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padr�o de projeto chamado Factory
						   //para sua arquitetura de classes
	{


		return new MyTest;
	}
};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "MyTest", MyTest::Create);
