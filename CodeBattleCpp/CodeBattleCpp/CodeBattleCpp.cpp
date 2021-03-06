#include <iostream>
#include <random>

#include "GameClientLibrary.h"

std::string solve(uint32_t level, std::string question) {
	switch (level)
	{
	case 0: {
		if (std::string{ "hello" }.compare(question) == 0)
		{
			return "world";
		}
		else if (std::string{ "world" }.compare(question) == 0)
		{
			return "hello";

		}
		return question;
	}
	default:
		return "TODO: solve quiz";
	}
}

void main()
{
	GameClientLibrary *gcb = new GameClientLibrary("localhost:8080", "e@mail.org", "00000000000000000000");
	gcb->Run([&]()
	{		
		uint32_t level = gcb->GetLevel();
		std::list<std::string> questions = gcb->GetQuestions();

		if (questions.empty())
		{
			gcb->StartNextLevel();
		}
		else
		{
			std::list<std::string> answers;
			for (std::string q : questions)
			{
				answers.push_back(solve(level, q));
			}
			gcb->SendAnswers(answers);
		}
	});

	getchar();
}
