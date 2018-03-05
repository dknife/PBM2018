#include "BulletWorld.h"

void CBulletWorld::initialize() {
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;

	mWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	mWorld->setGravity(btVector3(0, -10, 0));

	groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	ballShape = new btSphereShape(1);

	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	groundRigidBody->setRestitution(1.0);
	mWorld->addRigidBody(groundRigidBody);


	ballMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 ballInertia(0, 0, 0);
	ballShape->calculateLocalInertia(mass, ballInertia);
	btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(mass, ballMotionState, ballShape, ballInertia);
	ballRigidBody = new btRigidBody(ballRigidBodyCI);
	ballRigidBody->setRestitution(1.0);
	mWorld->addRigidBody(ballRigidBody);

}

void CBulletWorld::step(float dt) {
	mWorld->stepSimulation(1/30.0, 10, 1.0/60.0);
}

void CBulletWorld::draw() {
	btTransform trans;
	ballRigidBody->getMotionState()->getWorldTransform(trans);
	glPushMatrix();
	btVector3 loc = trans.getOrigin();
	glTranslatef(loc[0], loc[1], loc[2]);
	glutWireSphere(1.0, 10, 10);
	glPopMatrix();
}


void CBulletWorld::release() {
	mWorld->removeRigidBody(ballRigidBody);
	delete ballRigidBody->getMotionState();
	delete ballRigidBody;

	mWorld->removeRigidBody(groundRigidBody);
	delete groundRigidBody->getMotionState();
	delete groundRigidBody;


	delete ballShape;

	delete groundShape;


	delete mWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
}