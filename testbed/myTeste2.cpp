#include "test.h"
#include <iostream>
#include <string>
#include <math.h>

class MyTest2 : public Test //voc� cria a sua classe derivada da classe base Test
{
	int boxFriction = 0;
	int force;
	int angle;
	b2Body* lastBody;
public:
	MyTest2() {
		// Aqui no construtor voc� inicializa a cena
		force = 3000;
		angle = 0;
		b2World* world;
		b2Vec2 gravity(0.0f, -9.8f);
		world = new b2World(gravity);

		CreateWall(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
		CreateWall(b2Vec2(-40.0f, 40.0f), b2Vec2(40.0f, 40.0f));
		CreateWall(b2Vec2(40.0f, 00.0f), b2Vec2(40.0f, 40.0f));
		CreateWall(b2Vec2(-40.0f, 00.0f), b2Vec2(-40.0f, 40.0f));
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

		double pi = 3.14159265359;
		int newAngle = (angle * (pi / 180));

		bd.angle = newAngle;
		circleObj = m_world->CreateBody(&bd);

		b2CircleShape circle;
		circle.m_radius = radius;

		b2FixtureDef fd;
		fd.shape = &circle;
		fd.density = density;
		fd.friction = friction;
		fd.restitution = restitution;


		b2Vec2 f = circleObj->GetWorldVector(b2Vec2(force, 0));
		b2Vec2 p = circleObj->GetWorldPoint(b2Vec2(0.0f, 3.0f));
		circleObj->ApplyForce(f, p, true);
		lastBody = circleObj;

		circleObj->CreateFixture(&fd);
	}


	void Step(Settings& settings) override
	{
		//Chama o passo da simula��o e o algoritmo de rendering
		Test::Step(settings);

		if (glfwGetKey(g_mainWindow, GLFW_KEY_UP) == GLFW_PRESS)
		{
			force += 100;
			std::cout << "FORCE: " << force << std::endl;
		}
		if (glfwGetKey(g_mainWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			if (force > 100)
			{
				force -= 100;
				std::cout << "FORCE: " << force << std::endl;
			}
		}
	
		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Exercicios 2 - CRIAR OBJETO COM ESPAÇO");
		g_debugDraw.DrawString(5, m_textLine + 10, "MUDAR FORÇA COM UP, DOWN");
		g_debugDraw.DrawString(5, m_textLine + 20, "MUDAR ANGULO COM W, S");

		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padr�o de projeto chamado Factory
						   //para sua arquitetura de classes
	{


		return new MyTest2;
	}

	void Keyboard(int key) override
	{
		switch (key)
		{
			case GLFW_KEY_SPACE:
			{
				b2Vec2 pos(-35, 1);
				CreateCircle(1, 1, 1, 0, pos);
				break;
			}
			case GLFW_KEY_W:
			{
				if (angle < 360)
				{
					angle += 15;
					std::cout << "ANGLE: " << angle << std::endl;
				}
				break;
			}
			case GLFW_KEY_S:
			{
				if (angle > 0)
				{
					angle -= 15;
					std::cout << "ANGLE: " << angle << std::endl;
				}
				break;
			}
		}

	}
};
//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "MyTeste2", MyTest2::Create);
