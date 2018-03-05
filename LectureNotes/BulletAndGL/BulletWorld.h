#ifndef BULLETWORLD_HH_
#define BULLETWORLD_HH_
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

#include "../../src/btBulletDynamicsCommon.h"

class CBulletWorld {
	
	btBroadphaseInterface* broadphase;	
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btCollisionShape* groundShape;
	btCollisionShape* ballShape;
	btRigidBody* groundRigidBody;
	btRigidBody* ballRigidBody;
	
public:

	btDiscreteDynamicsWorld* mWorld;
	btDefaultMotionState* groundMotionState;
	btDefaultMotionState* ballMotionState;

public:
	void initialize();
	void draw();
	void step(float dt);

	void release();

};

#endif