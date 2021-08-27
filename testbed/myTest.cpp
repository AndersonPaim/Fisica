#include "test.h"
#include "myTest.h"
#include <iostream>
#include "..\..\testbed\myTest.h"

class myTest : public Test //voc� cria a sua classe derivada da classe base Test
{
public:
	MyTest() {
		// Aqui no construtor voc� inicializa a cena
		b2World* world;
		b2Vec2 gravity(0.0f, -9.8f);
		world = new b2World(gravity);

		for (int i = 0; i < 10; i++)
		{
			b2Vec2 pos(RandomFloat(-15.0f, 15.0f), 30.0f);
			int density(RandomFloat(0.0f, 35.0f));
			float radius(RandomFloat(0.1f, 5.0f));

			CreateCircle(density, radius, pos);
		}

	}

	void CreateCircle(int density, int radius, b2Vec2 position)
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
		fd.restitution = 0.0f;

		circleObj->CreateFixture(&fd);
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

