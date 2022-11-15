#pragma once

namespace sf 
{
	class CommandReceiver;

	//Command class, segit multiplayerben es replayben
	class Command
	{
	public:
		virtual ~Command() {};
		virtual void execute() = 0;
	};

	//move command, loketet adunk a hajoknak 
	//melyik hajo, es mely iranyba kap loketet
	class MoveCommand : public Command
	{
	public:
		MoveCommand(sf::MoveDirectionCommandReceiver* receiver, sf::CommandTypes commandType) :
			receiver_(receiver),
			commandType_(commandType)
		{}

		void execute()
		{
			receiver_->SetAction(commandType_);
			receiver_->MoveDirectionCommandReceiver::execute();
		}


	protected:
		sf::MoveDirectionCommandReceiver* receiver_;
		sf::CommandTypes commandType_;
	};
}
