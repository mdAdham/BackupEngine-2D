#include "bcpch.h"
#include "Entity.h"

BackupEngine::Entity::Entity(entt::entity handle, Scene* scene)
	:m_EntityHandle(handle), m_Scene(scene)
{
}
