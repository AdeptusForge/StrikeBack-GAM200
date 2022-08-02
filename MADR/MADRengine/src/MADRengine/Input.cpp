#include "Input.h"
#include "Events.h"
#include "glfw3.h"

std::vector<InputFrame> priorFrames;
std::vector<InputFrame>::iterator ptr;
MouseMode currMouseMode;

InputFrame currFrame;
bool isSelecting;
EVENT inputEvent;

//Defines when the player can input.
bool canInput;
void BlockAllInputs() { canInput = false; };
void UnblockAllInputs() { canInput = true; };


static void cursorPoitionCallback(GLFWwindow* window, double xPos, double yPos)
{
	//WriteDebug(vecToStr(glm::vec2(xPos, yPos)));
}
static void cursorClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	if (action == GLFW_PRESS)
	{
		//WriteDebug("Clicked at location: " + vecToStr(glm::vec2(xPos, yPos)));
		inputEvent = EVENT(EventType::Input_Event, "Mouse Click Input");
		inputEvent.data.SetVector2("MousePos", glm::vec2(xPos, yPos));
		if (button == GLFW_MOUSE_BUTTON_LEFT)
			inputEvent.data.SetInt("LeftClick", 1);
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
			inputEvent.data.SetInt("LeftClick", 0);

	}
}

//sets the key event callback to CollectInputs() and fills the inputframe list with empty data so no input errors can occur.
void InputControlStartup(GLFWwindow** window)
{
	//glfwSetKeyCallback(window, CollectInputs);
	//glfwSetCursorPosCallback(window, cursorPoitionCallback);
	glfwSetMouseButtonCallback(*window, cursorClickCallback);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(*window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	for (int i = 1; i <= MAX_SAVED_INPUTFRAMES; i++)
	{
		ptr = priorFrames.begin();
		ptr = priorFrames.insert(ptr, InputFrame());
	}

	UnblockAllInputs();
}

InputFrame CollectInputs(GLFWwindow* window) {
	InputFrame newFrame = InputFrame();
	glm::bvec4 dirs = currFrame.RAW_DIRECTIONS();
	glm::bvec4 buttons = currFrame.RAW_BUTTONS();
	glm::bvec4 buttons2 = currFrame.RAW_BUTTONS2();

	if (canInput)
	{
		if (glfwJoystickPresent(GLFW_JOYSTICK_1)) 
		{

		}
		else 
		{
#pragma region Press
			if (glfwGetKey(window, GLFW_KEY_W))
			{
				dirs.w = true;
			}
			if (glfwGetKey(window, GLFW_KEY_D))
			{
				dirs.x = true;
			}
			if (glfwGetKey(window, GLFW_KEY_S))
			{
				dirs.y = true;
			}
			if (glfwGetKey(window, GLFW_KEY_A))
			{
				dirs.z = true;
			}
			if (glfwGetKey(window, GLFW_KEY_U))
			{
				buttons.w = true;
			}
			if (glfwGetKey(window, GLFW_KEY_I))
			{
				buttons.x = true;
			}
			if (glfwGetKey(window, GLFW_KEY_O))
			{
				buttons.y = true;
			}
			if (glfwGetKey(window, GLFW_KEY_P))
			{
				buttons.z = true;
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			{
				buttons2.x = true;
			}
#pragma endregion

#pragma region Release
			if (glfwGetKey(window, GLFW_KEY_W) == 0)
			{
				dirs.w = false;
			}
			if (glfwGetKey(window, GLFW_KEY_D) == 0)
			{
				dirs.x = false;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == 0)
			{
				dirs.y = false;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == 0)
			{
				dirs.z = false;
			}

			if (glfwGetKey(window, GLFW_KEY_U) == 0)
			{
				buttons.w = false;
			}
			if (glfwGetKey(window, GLFW_KEY_I) == 0)
			{
				buttons.x = false;
			}
			if (glfwGetKey(window, GLFW_KEY_O) == 0)
			{
				buttons.y = false;
			}
			if (glfwGetKey(window, GLFW_KEY_P) == 0)
			{
				buttons.z = false;
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == 0)
			{
				buttons2.x = false;
			}
#pragma endregion
		}

		newFrame = InputFrame(dirs, buttons, buttons2);
		return newFrame;
	}
	else return InputFrame(dirs, buttons, buttons2);
}

//Moves the inputFrame list forward to the current frame and erases the oldest one.
void SaveInputs(GLFWwindow* window)
{
	ptr = priorFrames.begin();
	ptr = priorFrames.insert(ptr, currFrame);
	currFrame = CollectInputs(window);
	priorFrames.pop_back();
}

//Runs inputs. Called once every frame to prevent input errors in a singleplayer environment.
//If you wanted to handle multiplayer or an update-based framework, you'd need to change this to compensate.
void RunInputs()
{
	inputEvent.data.SetInputs(currFrame);
	inputEvent.triggeredBy = "InputChange";
	inputEvent.Etype = EventType::Input_Event;
	QueueEvent(inputEvent);
	
}