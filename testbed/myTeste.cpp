#include "test.h"
#include <iostream>


class MyTest : public Test //voc� cria a sua classe derivada da classe base Test
{
	int boxRestituion = 0;
	bool isfirstBox = true;
	b2Body* firstBox;
public:
	MyTest() {
		// Aqui no construtor voc� inicializa a cena
		b2World* world;
		b2Vec2 gravity(0.0f, -9.8f);
		world = new b2World(gravity);


		CreateWall(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
		CreateWall(b2Vec2(-40.0f, 40.0f), b2Vec2(40.0f, 40.0f));
		CreateWall(b2Vec2(40.0f, 00.0f), b2Vec2(40.0f, 40.0f));
		CreateWall(b2Vec2(-40.0f, 00.0f), b2Vec2(-40.0f, 40.0f));


		int posX = -30;

		for (int i = 0; i < 10; i++)
		{
			posX += 5;
			CreateBox(1, 1, 6, 1, 0, b2Vec2(posX, 1));
		}

		b2Vec2 pos((0, 0), 30);
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

	void CreateBox(int density, float height, float width, float friction, float restitution, b2Vec2 position)
	{
		b2BodyDef boxObj;
		boxObj.type = b2_dynamicBody;
		boxObj.position = position;
		b2Body* body = m_world->CreateBody(&boxObj);

		if (isfirstBox)
		{
			firstBox = body;
			isfirstBox = false;
		}

		b2PolygonShape box;

		box.SetAsBox(height, width);
		b2FixtureDef fd;
		fd.shape = &box;
		fd.density = density;
		fd.friction = friction;
		fd.restitution = restitution;

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

		if (glfwGetKey(g_mainWindow, GLFW_KEY_W) == GLFW_PRESS)
		{
			b2Vec2 f = firstBox->GetWorldVector(b2Vec2(100.0f, 0));
			b2Vec2 p = firstBox->GetWorldPoint(b2Vec2(0.0f, 3.0f));
			firstBox->ApplyForce(f, p, true);
		}

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Exercicio 1 - CLIQUE W PARA APLICAR FORÇA");
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
static int testIndex = RegisterTest("Examples", "MyTeste", MyTest::Create);
