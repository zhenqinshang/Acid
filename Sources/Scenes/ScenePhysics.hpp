#pragma once

#include <BulletCollision/BroadphaseCollision/btBroadphaseInterface.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include "Maths/Vector3.hpp"

namespace acid
{
	class ACID_EXPORT ScenePhysics
	{
	private:
		btCollisionConfiguration *m_collisionConfiguration;
		btBroadphaseInterface *m_broadphase;
		btCollisionDispatcher *m_dispatcher;
		btSequentialImpulseConstraintSolver *m_solver;
		btDiscreteDynamicsWorld *m_dynamicsWorld;
	public:
		ScenePhysics();

		~ScenePhysics();

		void Update();

		Vector3 GetGravity() const;

		void SetGravity(const Vector3 &gravity);

		float GetAirDensity() const;

		void SetAirDensity(const float &airDensity);

		btDiscreteDynamicsWorld *GetDynamicsWorld() { return m_dynamicsWorld; }
	};
}
