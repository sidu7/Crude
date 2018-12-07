/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Application.h
Purpose:		Main Game Loop 
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include <GL/glew.h>
#include <SDL.h>
#include "windows.h"

#include <iostream>

#include "OpenGL/Renderer.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture.h"
#include "Maths/Matrix2D.h"

#include <cstdio>
#include "Managers/InputManager.h"
#include "Managers/Frame Rate Controller.h"
#include "Managers/ResourceManager.h"
#include "Managers/GameObject.h"
#include "Managers/GameObjectManager.h"
#include "Managers/ObjectFactory.h"
#include "Managers/CollisionManager.h"
#include "Managers/PhysicsManager.h"
#include "Components/Component.h"
#include "Managers/EventManager.h"
#include "Components/Spawner.h"
#include "Components/Transform.h" 
#include "Components/Sprite.h"
#include "Managers/GameStateManager.h"

#include "Components/Body.h"

#include "Defines.h"

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")


Input_Manager *gpInputManager;
FrameRateController *gpFrameRateController;
ResourceManager *gpResourceManager;
GameObjectManager *gpGameObjectManager;
ObjectFactory *gpObjectFactory;
CollisionManager *gpCollisionManager;
PhysicsManager *gpPhysicsManager;
EventManager *gpEventManager;
GameStateManager *gpGameStateManager;

bool PlayerIsDead;
bool Debug;
int GrenadeCount;
bool Start;
bool ShowHelp;
bool GodMode;

Shader *gpShader;
Shader *gdShader;
Matrix3D* gpProj;
int Tombstones;

float Spawner::mStatic;

bool appIsRunning = true;
int main(int argc, char* args[])
{
	//-----SDL

	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle("SDL 2.0 Test");
	}

	SDL_Window *pWindow;
	int error = 0;
	int posX = 0, posY = 0;
	
	// Initialize SDL
	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	pWindow = SDL_CreateWindow("Gunter",			// window title
		SDL_WINDOWPOS_CENTERED,						// initial x position
		SDL_WINDOWPOS_CENTERED,						// initial y position
		SCREEN_WIDTH,								// width, in pixels
		SCREEN_HEIGHT,								// height, in pixels
		SDL_WINDOW_OPENGL);

	// Check that the window was successfully made
	if (NULL == pWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	
	SDL_GLContext gContext = SDL_GL_CreateContext(pWindow); 
	if (gContext == NULL) 
	{ 
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError()); 
	}
	else { 
		//Initialize GLEW
		glewExperimental = true;
		if(glewInit() != GLEW_OK )
		{
			printf( "Error initializing GLEW!\n"); 
		}
	}

	if (!GLEW_VERSION_4_3)
		printf("OpenGL 4.3 is not supported\n");

	//------ SDL End
	
	gpInputManager = new Input_Manager();
	gpFrameRateController = new FrameRateController(60);
	gpGameObjectManager = new GameObjectManager();
	gpResourceManager = new ResourceManager();
	gpObjectFactory = new ObjectFactory();
	gpCollisionManager = new CollisionManager();
	gpPhysicsManager = new PhysicsManager();
	gpEventManager = new EventManager();
	gpGameStateManager = new GameStateManager();

	//-----
	printf("%s\n",glGetString(GL_VERSION));
	{
		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};
		
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		float circle[] = {
			   0.5f,    0.0f,
			 0.433f,   0.25f,
			 0.353f,  0.353f,
			  0.25f,  0.433f,
			   0.0f,    0.5f,
			 -0.25f,  0.433f,
			-0.353f,  0.353f,
			-0.433f,   0.25f,
			  -0.5f,    0.0f,
			-0.433f,  -0.25f,
			-0.353f, -0.353f,
			 -0.25f, -0.433f,
			   0.0f,   -0.5f,
			  0.25f, -0.433f,
			 0.353f, -0.353f,
			 0.433f,  -0.25f
		};

		float line[] = {
			0.0f, 0.0f,
			0.75f, 0.0f,
		};

		//Quad
		VertexArray va;

		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		va.AddBuffer(vb);
		va.Push(2, GL_FLOAT, sizeof(float));
		va.Push(2, GL_FLOAT, sizeof(float));
		va.AddLayout();

		IndexBuffer ib(indices, 6);

		//Circle
		VertexArray vc;

		VertexBuffer vbc(circle, 2 * 16 * sizeof(float));
		vc.AddBuffer(vbc);
		vc.Push(2, GL_FLOAT, sizeof(float));
		vc.AddLayout();

		//Line
		VertexArray vl;

		VertexBuffer vbl(line, 2 * 2 * sizeof(float));
		vl.AddBuffer(vbl);
		vl.Push(2, GL_FLOAT, sizeof(float));
		vl.AddLayout();


		gpProj = new Matrix3D();
		Matrix3DOrtho(gpProj, 0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -1.0f, 1.0f);
	//-----
		
		
		gpShader = new Shader("res/shaders/shader.vertex", "res/shaders/shader.fragment");
		gpShader->Bind();

		gdShader = new Shader("res/shaders/debug.vertex", "res/shaders/debug.fragment");


	//---- Background -----
		GameObject background(NO_OBJECT);
		Component *pNewComponent = nullptr;

		pNewComponent = background.AddComponent(TRANSFORM);
		pNewComponent = background.AddComponent(SPRITE);

		background.SetTransform(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		background.SetSprite("res/textures/background.png");

	//----- GodMode icon ----
		GameObject god(NO_OBJECT);
		pNewComponent = god.AddComponent(TRANSFORM);
		pNewComponent = god.AddComponent(SPRITE);

		god.SetTransform(800, 680, 50, 50, 0.0f);
		god.SetSprite("res/textures/godmode.png");

	//------ Pause Screen -----
		GameObject pause(NO_OBJECT);
		
		pNewComponent = pause.AddComponent(TRANSFORM);
		pNewComponent = pause.AddComponent(SPRITE);

		pause.SetTransform(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pause.SetSprite("res/textures/pause.png");
		
	//------ Help Screen -----

		GameObject help(NO_OBJECT);
		pNewComponent = help.AddComponent(TRANSFORM);
		pNewComponent = help.AddComponent(SPRITE);

		help.SetTransform(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		help.SetSprite("res/textures/ingamehelp.png");

	//------ Grenades counter ----

		GameObject* CurrGrenade[5];

		for (int i = 0; i < 5; ++i)
		{
			CurrGrenade[i] = new GameObject(NO_OBJECT);
			pNewComponent = CurrGrenade[i]->AddComponent(TRANSFORM);
			pNewComponent = CurrGrenade[i]->AddComponent(SPRITE);

			CurrGrenade[i]->SetSprite("res/textures/grenade.png");
		}

	//-----
	//----- Load Level -----


		gpObjectFactory->LoadArchetypes("Archetypes.json");
		gpGameStateManager->PrecacheLevels("Levels.json");
		gpGameStateManager->LoadLevel(MAINMENU);
	//------
		Renderer renderer;
		bool Pause = false;
		Start = false;
		ShowHelp = false;
		PlayerIsDead = false;
		GodMode = false;
		Debug = false;
		GrenadeCount = 5;
		Tombstones = 2;
		
		/* Loop until the user closes the window */
		while (true == appIsRunning)
		{
			gpFrameRateController->FrameStart();
			//printf("Frame time = %f\n", gpFrameRateController->GetFrameTime());
			
			gpInputManager->Update();
			
			if (gpInputManager->IsTriggered(SDL_SCANCODE_O))
			{
				Debug = !Debug;
			}
			
			gpShader->Bind();

			/* Render here */
			renderer.Clear();

			
			if (Start) 
			{
				if (gpInputManager->IsTriggered(SDL_SCANCODE_P) && !ShowHelp)
				{
					Pause = !Pause;
				}
				if (gpInputManager->IsTriggered(SDL_SCANCODE_H))
				{
					ShowHelp = !ShowHelp;
					Pause = ShowHelp;
				}
				if (gpInputManager->IsTriggered(SDL_SCANCODE_G))
				{
					GodMode = !GodMode;
					
				}
				if (Pause)
				background.SetSprite("res/textures/pause_background.png");
				else
				background.SetSprite("res/textures/background.png");

				background.Update();
				renderer.Draw(va, ib, *gpShader);
				
				if (GodMode)
				{
					god.Update();
					renderer.Draw(va, ib, *gpShader);
				}

				//Current Greande Count
				for (int i = 0; i < GrenadeCount; ++i)
				{
					CurrGrenade[i]->SetTransform(300.0f + (i * 30), SCREEN_HEIGHT - 30.0f, 30.0f, 30.0f, 0.0f);
					CurrGrenade[i]->Update();
					renderer.Draw(va, ib, *gpShader);
				}
			}
			if (!PlayerIsDead && !Pause)
			{
				//--- Draw static dead objects
				for (unsigned int i = 0; i < gpGameObjectManager->mStaticDeadObjects.size(); ++i)
				{
					if(gpGameObjectManager->mStaticDeadObjects[i]->mType != TOMBSTONE)
						gpGameObjectManager->mStaticDeadObjects[i]->mDeathDelay -= gpFrameRateController->GetFrameTime();
					if (gpGameObjectManager->mStaticDeadObjects[i]->mDeathDelay < 0.0f)
					{
						gpGameObjectManager->mDeleteObjects.push_back(gpGameObjectManager->mStaticDeadObjects[i]);
						gpGameObjectManager->mStaticDeadObjects.erase(gpGameObjectManager->mStaticDeadObjects.begin() + i);
					}
					else
					{	
						gpGameObjectManager->mStaticDeadObjects[i]->Update();
						renderer.Draw(va, ib, *gpShader);
					}

				}

				for (unsigned int i = 0; i < gpGameObjectManager->mGameObjects.size(); ++i)
				{
					bool destroyed = gpGameObjectManager->mGameObjects[i]->Update();
					
					/* Draw call*/
					renderer.Draw(va, ib, *gpShader);

					//Debug drawing calls
 					if (Debug && !destroyed)
					{
						Body* pBody = static_cast<Body*>(gpGameObjectManager->mGameObjects[i]->GetComponent(BODY));
						if (pBody == nullptr)
							continue;
					
						Transform* pTr = static_cast<Transform*>(gpGameObjectManager->mGameObjects[i]->GetComponent(TRANSFORM));
						pTr->UpdateDebug();
						if (pBody->mpShape->mType == Shape::CIRCLE)
						{
							renderer.DrawDebugCircle(vc, *gdShader);
						}
						else
						{
							renderer.DebugDraw(va, ib, *gdShader);
						}
							
						//Direction vector
						if (gpGameObjectManager->mGameObjects[i]->mType == PLAYER)
						{
							pTr->UpdateLine();
							renderer.DrawDebugLine(vl, *gdShader);
						}
						
					}
				}
				
				gpPhysicsManager->Update(gpFrameRateController->GetFrameTime());
				gpEventManager->Update(gpFrameRateController->GetFrameTime());
			}
			else
			{
				//Paused state
				for (unsigned int i = 0; i < gpGameObjectManager->mGameObjects.size(); ++i)
				{
					Transform* pT = static_cast<Transform*>(gpGameObjectManager->mGameObjects[i]->GetComponent(TRANSFORM));
					Sprite* pSp = static_cast<Sprite*>(gpGameObjectManager->mGameObjects[i]->GetComponent(SPRITE));
					if (PlayerIsDead)
					{
						Body* pBody = static_cast<Body*>(gpGameObjectManager->mGameObjects[i]->GetComponent(BODY));
						if(pBody != nullptr)
							pBody->Update();
					}
					pT->Update();
					pSp->Update();

					/* Draw call*/
					renderer.Draw(va, ib, *gpShader);
				}
				if (Pause && !ShowHelp)
				{
					pause.Update();
				}
				if (ShowHelp)
				{
					help.Update();
				}
				renderer.Draw(va, ib, *gpShader);
			}
			if (Tombstones == 0)
			{
				Start = false;
				gpGameStateManager->LoadLevel(WINSCREEN);
			}
			if (PlayerIsDead)
			{
				Start = false;
				gpGameStateManager->LoadLevel(LOSESCREEN);
			}

			SDL_GL_SwapWindow(pWindow);
			gpGameObjectManager->Update();
			gpFrameRateController->FrameEnd();
		}
	}


	free(gpInputManager);
	free(gpFrameRateController);
	free(gpResourceManager);
	free(gpGameObjectManager);
	free(gpCollisionManager);
	free(gpObjectFactory);
	free(gpPhysicsManager);
	free(gpEventManager);

	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}