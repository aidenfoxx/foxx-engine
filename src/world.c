#include "world.h"

static void worldCollision(void*, dGeomID, dGeomID);

static int odeInit = 0;

World *worldNew()
{
	World *world;

	if ((world = malloc(sizeof(World))) != NULL)
	{
		if (!odeInit)
		{
			dInitODE();
		}

		odeInit++;

		world->world = dWorldCreate();
		world->space = dHashSpaceCreate(0);
		world->contactGroup = dJointGroupCreate(0);
		world->bodies = arrayNew();
		world->joints = arrayNew();

		dCreatePlane(world->space, 0, 1, 0, 0);

		dWorldSetAutoDisableFlag(world->world, 0);
		dWorldSetGravity(world->world, WORLD_GRAVITY_X, WORLD_GRAVITY_Y, WORLD_GRAVITY_Z);
		dWorldSetContactSurfaceLayer(world->world, WORLD_SURFACE_LAYER);
		dWorldSetERP(world->world, WORLD_ERROR_CORRECTION);
		dWorldSetCFM(world->world, WORLD_CONSTRAINT_FORCE);
		dWorldSetData(world->world, world);
	}

	return world;
}

void worldFree(World *world)
{
	if (world)
	{
		odeInit--;

		dSpaceDestroy(world->space);
		dWorldDestroy(world->world);
		arrayFree(world->bodies);
		arrayFree(world->joints);
		free(world);

		if (!odeInit)
		{
			dCloseODE();
		}	
	}
}

void worldSetGravity(World *world, Vec3 gravity)
{
	dWorldSetGravity(world->world, gravity.x, gravity.y, gravity.z);
}

int worldAddObject(World *world, Object *object)
{
	Model *model = objectGetModel(object);
	Vec3 position = objectGetTranslation(object);
	Vec3 center = objectGetCenter(object);
	Vec3 boundingBox = objectGetBoundingBox(object);

	dMass mass;
	dBodyID bodyID = dBodyCreate(world->world);
	dTriMeshDataID dataID = dGeomTriMeshDataCreate();
	dGeomID geometryID = dCreateTriMesh(world->space, dataID, NULL, NULL, NULL);

	dGeomTriMeshDataBuildSimple(dataID, (dReal*)model->vertices, model->verticesLength, (const int*)model->indices, model->indicesLength);
	dGeomSetPosition(geometryID, position.x, position.y, position.z);

	float massValue;

	if ((massValue = objectGetParameterFloat(object, "mass")) == 0.0f)
	{
		massValue = 1.0f;
	}

	dMassSetBox(&mass, 1.0f, boundingBox.x, boundingBox.y, boundingBox.z);
	dMassAdjust(&mass, massValue);

	dBodySetGravityMode(bodyID, objectGetParameterInt(object, "gravity"));

	dBodySetMass(bodyID, &mass);
	dBodySetPosition(bodyID, position.x, position.y, position.z);
	dBodySetData(bodyID, (void*)object);

	dGeomSetBody(geometryID, bodyID);
	
	arrayPush(world->bodies, bodyID);

	return arrayLength(world->bodies);
}

void worldRemoveObject(World *world, int objectID)
{
	dBodyID bodyID;

	if ((bodyID = (dBodyID)arrayGet(world->bodies, objectID - 1)) != NULL)
	{
		/**
		 * TODO: Implement.
		 */
	}
}

void worldStep(World *world, float stepSize)
{
	dSpaceCollide(world->space, 0, &worldCollision);
	dWorldQuickStep(world->world, 0.01);
	dJointGroupEmpty(world->contactGroup);

	for (int i = 0; i < arrayLength(world->bodies); i++)
	{
		dBodyID bodyID = (dBodyID)arrayGet(world->bodies, i);
		dReal *position = (dReal*)dBodyGetPosition(bodyID);
		dReal *rotation = (dReal*)dBodyGetRotation(bodyID);

		Object *object = (Object*)dBodyGetData(bodyID);

		objectSetTranslation(object, vec3(position[0], position[1], position[2]));
		objectSetRotation(object, vec4(rotation[0], rotation[1], rotation[2], rotation[3]));
	}
}

void worldCollision(void *data, dGeomID objectOne, dGeomID objectTwo)
{
	dWorldID worldID;
	dBodyID bodyOne = dGeomGetBody(objectOne);
	dBodyID bodyTwo = dGeomGetBody(objectTwo);

	if ((bodyOne != 0 && (worldID = dBodyGetWorld(bodyOne))) || 
		(bodyTwo != 0 && (worldID = dBodyGetWorld(bodyTwo))))
	{		
		World *world = dWorldGetData(worldID);

		dContact contact;

		contact.surface.mode = dContactBounce | dContactSoftCFM;
		contact.surface.mu = 1.0f;
		contact.surface.bounce = 0.0f;
		contact.surface.bounce_vel = 0.0f;
		contact.surface.soft_cfm = 0.001f;

		if (dCollide(objectOne, objectTwo, 1, &contact.geom, sizeof(dContact)))
		{
			dJointID joint = dJointCreateContact(world->world, world->contactGroup, &contact);
			dJointAttach(joint, bodyOne, bodyTwo);
		}
	}
}