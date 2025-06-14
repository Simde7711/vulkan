#include "ECS/fs.entityManager.hpp"

namespace fs
{
    FsEntityManager::FsEntityManager()
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			mAvailableEntities.push(entity);
		}
    }

    Entity FsEntityManager::CreateEntity()
    {
        assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

		Entity id = mAvailableEntities.front();
		mAvailableEntities.pop();
		++mLivingEntityCount;

		return id;
    }

    void FsEntityManager::DestroyEntity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

		mSignatures[entity].reset();
		mAvailableEntities.push(entity);
		--mLivingEntityCount;
    }

    void FsEntityManager::SetSignature(Entity entity, Signature signature)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

		mSignatures[entity] = signature;
    }

    Signature FsEntityManager::GetSignature(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

		return mSignatures[entity];
    }
}