#pragma once

#include "TaskManager.hpp"


class UserInterface
{
private:
	TaskManager m_task_manager;

public:
	UserInterface()
	{
		setlocale(0, "");
	}

	void run()
	{
		m_task_manager.task_control();
	}

};