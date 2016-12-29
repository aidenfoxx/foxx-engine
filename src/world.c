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

		worldSetAutoDisable(world, WORLD_AUTO_DISABLE);
		worldSetGravity(world, vec3(WORLD_GRAVITY_X, WORLD_GRAVITY_Y, WORLD_GRAVITY_Z));
		worldSetSurfaceLayer(world, WORLD_SURFACE_LAYER);
		worldSetERP(world, WORLD_ERP);
		worldSetCFM(world, WORLD_CFM);

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
		dJointGroupDestroy(world->contactGroup);
		arrayFree(world->bodies);
		arrayFree(world->joints);
		free(world);

		if (!odeInit)
		{
			dCloseODE();
		}	
	}
}

int worldAddObject(World *world, Object *object)
{
	ModelBuffer *modelBuffer;

	if (modelBuffer = objectGetModelBuffer(object))
	{
		Model *model = modelBufferGetModel(modelBuffer);
		Vec3 position = objectGetTranslation(object);
		Vec4 rotation = objectGetRotation(object);
		Vec3 boundingBox = objectGetBoundingBox(object);

		dBodyID body = dBodyCreate(world->world);


		dTriMeshDataID data = dGeomTriMeshDataCreate();
		dGeomTriMeshDataBuildSimple(data, (dReal*)model->vertices, model->verticesLength, model->indices, model->indicesLength);

		dGeomID geometry = dCreateTriMesh(world->space, data, NULL, NULL, NULL);
		dGeomSetBody(geometry, body);

		dMass mass;
		float massValue;

		if ((massValue = objectGetParameterFloat(object, "mass")) == 0.0f)
		{
			massValue = 1.0f;
		}

		dMassSetBox(&mass, 1.0f, boundingBox.x, boundingBox.y, boundingBox.z);
		dMassAdjust(&mass, massValue);

		dBodySetMass(body, &mass);
		dBodySetGravityMode(body, objectGetParameterInt(object, "gravity"));
		dBodySetPosition(body, position.x, position.y, position.z);
		dBodySetQuaternion(body, (const dReal*)&rotation);
		dBodySetData(body, (void*)object);

		arrayPush(world->bodies, body);

		return arrayLength(world->bodies);
	}

	return -1;
}

void worldRemoveObject(World *world, int objectID)
{
	dBodyID body;

	if ((body = (dBodyID)arrayGet(world->bodies, objectID - 1)) != NULL)
	{
		arrayRemove(world->bodies, objectID - 1);
		dBodyDestroy(body);
	}
}

void worldSetAutoDisable(World *world, int disable)
{
	dWorldSetAutoDisableFlag(world->world, disable);
}

void worldSetGravity(World *world, Vec3 gravity)
{
	dWorldSetGravity(world->world, gravity.x, gravity.y, gravity.z);
}

void worldSetSurfaceLayer(World *world, float surfaceLayer)
{
	dWorldSetContactSurfaceLayer(world->world, surfaceLayer);
}

void worldSetERP(World *world, float erp)
{
	dWorldSetERP(world->world, erp);
}

void worldSetCFM(World *world, float cfm)
{
	dWorldSetCFM(world->world, cfm);
}

int worldGetAutoDisable(World *world)
{
	return dWorldGetAutoDisableFlag(world->world);
}

Vec3 worldGetGravity(World *world)
{
	dVector3 gravity;
	dWorldGetGravity(world->world, gravity);
	return vec3(gravity[0], gravity[1], gravity[2]);
}

float worldGetSurfaceLayer(World *world)
{
	return (float)dWorldGetContactSurfaceLayer(world->world);
}

float worldGetERP(World *world)
{
	return (float)dWorldGetERP(world->world);
}

float worldGetCFM(World *world)
{
	return (float)dWorldGetCFM(world->world);
}

void worldStep(World *world, float stepSize)
{
	dSpaceCollide(world->space, 0, &worldCollision);
	dWorldQuickStep(world->world, 0.01);
	dJointGroupEmpty(world->contactGroup);

	int bodiesLength = arrayLength(world->bodies);

	for (int i = 0; i < bodiesLength; i++)
	{
		dBodyID body = (dBodyID)arrayGet(world->bodies, i);
		dReal *position = (dReal*)dBodyGetPosition(body);
		dReal *rotation = (dReal*)dBodyGetQuaternion(body);

		Object *object = (Object*)dBodyGetData(body);

		objectSetTranslation(object, vec3(position[0], position[1], position[2]));
		objectSetRotation(object, vec4(rotation[0], rotation[1], rotation[2], rotation[3]));
	}
}

void worldCollision(void *data, dGeomID objectOne, dGeomID objectTwo)
{
	dWorldID worldID;
	dBodyID bodyOne = dGeomGetBody(objectOne);
	dBodyID bodyTwo = dGeomGetBody(objectTwo);

	/**
	 * If the objects are connected by
	 * joints, do nothing.
	 */
	if(bodyOne && bodyTwo && dAreConnected(bodyOne, bodyTwo))
	{
		return;
	}

	if ((bodyOne != 0 && (worldID = dBodyGetWorld(bodyOne))) || 
		(bodyTwo != 0 && (worldID = dBodyGetWorld(bodyTwo))))
	{
		World *world = dWorldGetData(worldID);

		dContact contact[WORLD_MAX_CONTACTS];

		for (int i = 0; i < WORLD_MAX_CONTACTS; i++)
		{
			contact[i].surface.mode = dContactApprox1 | dContactSoftCFM;
			contact[i].surface.mu = 0.9f;
			contact[i].surface.soft_cfm = 0.05f;
		}

		int collide;

		if ((collide = dCollide(objectOne, objectTwo, WORLD_MAX_CONTACTS, &contact[0].geom, sizeof(dContact))) > 0)
		{
			for (int i = 0; i < collide; i++)
			{
				dJointID joint = dJointCreateContact(world->world, world->contactGroup, &contact[i]);
				dJointAttach(joint, bodyOne, bodyTwo);
			}
		}
	}
}