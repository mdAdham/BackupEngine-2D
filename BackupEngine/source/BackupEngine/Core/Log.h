#pragma once

#include "BackupEngine/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace BackupEngine {

	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

// Core log macros
#define BC_CORE_TRACE(...)    ::BackupEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BC_CORE_INFO(...)     ::BackupEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BC_CORE_WARN(...)     ::BackupEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BC_CORE_ERROR(...)    ::BackupEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BC_CORE_CRITICAL(...) ::BackupEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define BC_TRACE(...)         ::BackupEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BC_INFO(...)          ::BackupEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define BC_WARN(...)          ::BackupEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BC_ERROR(...)         ::BackupEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define BC_CRITICAL(...)      ::BackupEngine::Log::GetClientLogger()->critical(__VA_ARGS__)
