#include "bcpch.h"
#include "BackupEngine/Renderer/RenderCommand.h"

namespace BackupEngine {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}