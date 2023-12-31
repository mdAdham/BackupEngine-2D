#include "bcpch.h"
#include "UUID.h"

namespace BackupEngine {

	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

	BackupEngine::UUID::UUID()
		: m_UUID(s_UniformDistribution(s_Engine))
	{
	}
	
	BackupEngine::UUID::UUID(uint64_t uuid)
		: m_UUID(uuid)
	{
	}

}