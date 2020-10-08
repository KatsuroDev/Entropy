// This file is included by the client
// This only file is required in order to use Entropy Engine

// Core
#include "src/Entropy/Core/Core.h"
#include "src/Entropy/Core/Application.h"
#include "src/Entropy/Core/Input.h"

// Rendering
#include "src/Entropy/Renderer/Renderer.h"
#include "src/Entropy/Renderer/Camera.h"
#include "src/Entropy/Renderer/CameraController.h"
#include "src/Entropy/Renderer/Shader.h"
#include "src/Entropy/Renderer/Texture.h"

// Events
#include "src/Entropy/Events/ApplicationEvent.h"
#include "src/Entropy/Events/KeyEvent.h"
#include "src/Entropy/Events/MouseEvent.h"

// Utils
#include "src/Entropy/Tools/Colorimetry.h"
#include "src/Entropy/Tools/Noise.h"

using namespace Entropy;
