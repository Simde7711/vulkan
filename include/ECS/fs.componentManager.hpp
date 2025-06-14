#pragma once

#include "ECS/fs.componentArray.hpp"
#include "ECS/components/fs.components.hpp"
#include "ECS/fs.types.hpp"

// std
#include <any>
#include <memory>
#include <unordered_map>
#include <iostream>

namespace fs
{
    class FsComponentManager
    {
        public:

        template<typename T>
        void RegisterComponent()
        {
            const char* typeName = typeid(T).name();

            assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");

            mComponentTypes.insert({typeName, mNextComponentType});
            mComponentArrays.insert({typeName, std::make_shared<FsComponentArray<T>>()});

            ++mNextComponentType;
        }

        template<typename T>
        ComponentType GetComponentType()
        {
            const char* typeName = typeid(T).name();

            assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

            return mComponentTypes[typeName];
        }

        template<typename T>
        void AddComponent(Entity entity, T &&component)
        {
            GetComponentArray<T>()->InsertData(entity, std::forward<T>(component));
        }

        template<typename T>
        void RemoveComponent(Entity entity)
        {
            GetComponentArray<T>()->RemoveData(entity);
        }

        template<typename T>
        T& GetComponent(Entity entity)
        {
            return GetComponentArray<T>()->GetData(entity);
        }

        template<typename T>
        bool HasComponent(Entity entity) const
        {
            const char* typeName = typeid(T).name();

            // Ensure the component is registered
            assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

            auto componentArray = std::static_pointer_cast<FsComponentArray<T>>(mComponentArrays.at(typeName));
            return componentArray->HasEntity(entity);
        }

        void EntityDestroyed(Entity entity)
	    {
            std::cout << "[FsComponentManager] Entity destroyed: " << entity << std::endl;

            for (auto const& pair : mComponentArrays)
            {
                auto const& component = pair.second;

                component->EntityDestroyed(entity);
            }
	    }

        private:

        std::unordered_map<const char*, ComponentType> mComponentTypes{};
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};
        ComponentType mNextComponentType{};

        template<typename T>
        std::shared_ptr<FsComponentArray<T>> GetComponentArray()
        {
            const char* typeName = typeid(T).name();

            assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

            return std::static_pointer_cast<FsComponentArray<T>>(mComponentArrays[typeName]);
        }
    };
}

