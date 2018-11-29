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
#include "Managers/Components/Component.h"
#include "Managers/EventManager.h"
#include "Managers/Components/Spawner.h"
#include "Managers/Components/Transform.h" //to remove
#include "Managers/Components/Sprite.h"

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

bool PlayerIsDead;
bool Debug;
int GrenadeCount;
bool MouseEnabled;

Shader *gpShader;
Matrix3D* gpProj;

float Spawner::mStatic = 0.0f;

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
	bool appIsRunning = true;
	
	// Initialize SDL
	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); 
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
	//------ SDL End
	
	gpInputManager = new Input_Manager();
	gpFrameRateController = new FrameRateController(60);
	gpGameObjectManager = new GameObjectManager();
	gpResourceManager = new ResourceManager();
	gpObjectFactory = new ObjectFactory();
	gpCollisionManager = new CollisionManager();
	gpPhysicsManager = new PhysicsManager();
	gpEventManager = new EventManager();

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

		VertexArray va;

		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		va.AddBuffer(vb);
		va.Push(2, GL_FLOAT, sizeof(float));
		va.Push(2, GL_FLOAT, sizeof(float));
		va.AddLayout();

		IndexBuffer ib(indices, 6);

		gpProj = new Matrix3D();
		Matrix3DOrtho(gpProj, 0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -1.0f, 1.0f);
	//-----
		
		
		gpShader = new Shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
		gpShader->Bind();


	//---- Background -----
		GameObject background(NO_OBJECT);
		Component *pNewComponent = nullptr;

		pNewComponent = background.AddComponent(TRANSFORM);
		pNewComponent = background.AddComponent(SPRITE);

		background.SetTransform(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 150.0f, 0.0f);
		background.SetSprite("res/textures/background.png");

	//------ Pause Screen -----
		GameObject pause(NO_OBJECT);
		
		pNewComponent = pause.AddComponent(TRANSFORM);
		pNewComponent = pause.AddComponent(SPRITE);

		pause.SetTransform(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pause.SetSprite("res/textures/pause.png");


	//-----

	//----- Health Bar ------

		GameObject HP(HPBAR);

		pNewComponent = HP.AddComponent(TRANSFORM);
		pNewComponent = HP.AddComponent(SPRITE);
		gpEventManager->Subscribe(PLAYERHP, &HP);

		HP.SetTransform(190.0f, SCREEN_HEIGHT - 30.0f, 155.0f, 20.0f, 0.0f);
		HP.SetSprite("res/textures/hp.png");

		gpGameObjectManager->mGameObjects.push_back(&HP);

		GameObject Tomb1HP(TOMB1HP);

		pNewComponent = Tomb1HP.AddComponent(TRANSFORM);
		pNewComponent = Tomb1HP.AddComponent(SPRITE);
		gpEventManager->Subscribe(TOMBHIT, &Tomb1HP);

		Tomb1HP.SetTransform(200.0f, 145.0f, 90.0f, 10.0f, 0.0f);
		Tomb1HP.SetSprite("res/textures/hp.png");

		gpGameObjectManager->mGameObjects.push_back(&Tomb1HP);

		GameObject Tomb2HP(TOMB2HP);

		pNewComponent = Tomb2HP.AddComponent(TRANSFORM);
		pNewComponent = Tomb2HP.AddComponent(SPRITE);
		gpEventManager->Subscribe(TOMBHIT, &Tomb2HP);

		Tomb2HP.SetTransform(760.0f, 580.0f, 90.0f, 10.0f, 0.0f);
		Tomb2HP.SetSprite("res/textures/hp.png");

		gpGameObjectManager->mGameObjects.push_back(&Tomb2HP);
	//-----

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

		gpObjectFactory->LoadLevel("level.json");

	//------
		Renderer renderer;
		bool Pause = false;
		PlayerIsDead = false;
		Debug = false;
		GrenadeCount = 5;
		MouseEnabled = true;

		/* Loop until the user closes the window */
		while (true == appIsRunning)
		{
			gpFrameRateController->FrameStart();
			//printf("Frame time = %f\n", gpFrameRateController->GetFrameTime());
			
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					appIsRunning = false;
				}
			}

			gpInputManager->Update();
			
			if (gpInputManager->IsPressed(SDL_SCANCODE_ESCAPE))
			{
				appIsRunning = false;
			}
			if (gpInputManager->IsTriggered(SDL_SCANCODE_P))
			{
				Pause = !Pause;
			}
			if (gpInputManager->IsTriggered(SDL_SCANCODE_O))
			{
				Debug = !Debug;
			}
			if (gpInputManager->IsTriggered(SDL_SCANCODE_M))
			{
				MouseEnabled = !MouseEnabled;
			}
			
			gpShader->Bind();

			/* Render here */
			renderer.Clear();

			background.Update();
			renderer.Draw(va, ib, *gpShader);


			//Current Greande Count
			for (unsigned int i = 0; i < GrenadeCount; ++i)
			{
				CurrGrenade[i]->SetTransform(300.0f + (i*30), SCREEN_HEIGHT - 30.0f, 30.0f, 30.0f, 0.0f);
				CurrGrenade[i]->Update();
				renderer.Draw(va, ib, *gpShader);
			}
			
			if (!PlayerIsDead && !Pause)
			{
				//--- Draw static dead objects
				for (unsigned int i = 0; i < gpGameObjectManager->mStaticDeadObjects.size(); ++i)
				{
					if(gpGameObjectManager->mStaticDeadObjects[i]->mType != TOMBSTONE)
						gpGameObjectManager->mStaticDeadObjects[i]->mDeathDelay -= gpFrameRateController->GetFrameTime();
					if (gpGameObjectManager->mStaticDeadObjects[i]->mDeathDelay < 0.0f)
						gpGameObjectManager->mStaticDeadObjects.erase(gpGameObjectManager->mStaticDeadObjects.begin() + i);
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
					if (Debug && !destroyed)
					{
						Component* pBody = gpGameObjectManager->mGameObjects[i]->GetComponent(BODY);
						if (pBody == nullptr)
							continue;
						gpGameObjectManager->mGameObjects[i]->ScaleToBody();
						renderer.DebugDraw(va, ib, *gpShader);
						gpGameObjectManager->mGameObjects[i]->ResetScale();
					}
				}

				gpPhysicsManager->Update(gpFrameRateController->GetFrameTime());
				gpEventManager->Update(gpFrameRateController->GetFrameTime());
			}
			else
			{
				for (unsigned int i = 0; i < gpGameObjectManager->mGameObjects.size(); ++i)
				{
					Transform* pT = static_cast<Transform*>(gpGameObjectManager->mGameObjects[i]->GetComponent(TRANSFORM));
					Sprite* pSp = static_cast<Sprite*>(gpGameObjectManager->mGameObjects[i]->GetComponent(SPRITE));
					pT->Update();
					pSp->Update();

					/* Draw call*/
					renderer.Draw(va, ib, *gpShader);
				}
				pause.Update();
				renderer.Draw(va, ib, *gpShader);
			}
			SDL_GL_SwapWindow(pWindow);

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