#pragma once

#include "BackupEngine/Renderer/PerspectiveCamera.h"

#include "BackupEngine/Renderer/Texture.h"

#include "BackupEngine/Renderer/Camera.h"
#include "BackupEngine/Renderer/EditorCamera.h"

#include "BackupEngine/Scene/Components.h"

namespace BackupEngine {

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();
		static void Flush();

		//Primitives
		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture, float tilingfactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawCube(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
		static void DrawCube(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f), int entityID = -1);

		//Stats
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();

	private:
		static void StartBatch();
		static void NextBatch();
	};
}