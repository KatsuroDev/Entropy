#include "RenderCommand.h"

namespace Entropy {

	// Creates the rendering API
	Scope<RenderingAPI> RenderCommand::s_RenderingAPI = RenderingAPI::Create();
}
