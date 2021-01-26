#pragma once

#include <functional>
#include <vector>


namespace test
{
	class Test
	{
	public:
		Test() {};
		virtual ~Test() {};
		virtual void OnUpdate(float deltatime) {}
		virtual void OnRender() {}
		virtual void OnImguiRender() {}

	};

	class TestMenu:public Test
	{
	public:
		TestMenu(Test* &m_CurrentTestPointer);
	

		
		void OnImguiRender() override;

		template <typename T>
		void RegisterTest(const std::string &name)
		{
			std::cout << "Registering Test" << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	private:
		Test* &m_Current_Test;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;

	};
}