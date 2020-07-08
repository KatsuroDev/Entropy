#include "RenderCommand.h"

namespace Entropy {

	// Creates the rendering API
	RenderingAPI* RenderCommand::s_RenderingAPI = RenderingAPI::Create();
}
