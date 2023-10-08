#include "bcpch.h"
#include "BackupEngine/Renderer/VertexArray.h"

#include"BackupEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlVertexArray.h"

namespace BackupEngine {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    BC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		BC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}