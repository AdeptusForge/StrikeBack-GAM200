/*!
	\file Errors.h
	this header file declares the error handling system.
*/

#pragma once
#include "MADRpch.h"
#include "TimeKeeping.h"
#include <stdarg.h>

#define ERRORFILE "Errors.txt"

#define ERROR(a, b ) Errors::ErrorData Error(__func__, __FILE__, Errors::ErrorType::a,b)


namespace Errors {

	

	enum class ErrorType {
	UNHANDLED,
	HALTING,
	NULLPTR,
	ASSET,
	EVENT,
	};
	
	std::ofstream errorFile;

	class ErrorData {
	
		public:
			ErrorData()
			{
				_notes = "no information at all was passed to this error.";
				_type = ErrorType::UNHANDLED;
				_func = "no function was passed with this error.";
				_file = "no file was passed with this error.";
				//not enough information passed to error.
			}

			ErrorData(std::string func, std::string file, ErrorType type, std::string notes): _func(func), _file(file), _type(type), _notes(notes)
			{
				handleError();
			}
			ErrorData(std::string func, std::string file, ErrorType type): _func(func), _file(file), _type(type)
			{
				_notes = "No notes given for this error.";
				handleError();
			}
			ErrorData(std::string func, std::string file) : _func(func), _file(file)
			{
				_notes = "No notes or type were passed for this error.";
				_type = ErrorType::UNHANDLED;
				handleError();
			}

		private:
			std::string _func;
			std::string _file;
			ErrorType _type; 
			std::string _notes;

			/*!
				decides what to do with the error once it is created.
			*/
			void handleError() const
			{
				
				if (_type != ErrorType::HALTING)
				{
					writeError();
				}
				else
				{
					programHalt();
				}


			}
			void writeError()const 
			{
				errorFile.open(ERRORFILE, std::ios_base::app);
				if (errorFile.good())
				{
					switch (_type)
					{
					case ErrorType::UNHANDLED:
					{
						errorFile << "\nError of type UNHANDLED in file " << _file << " in function " << _func << " \n notes: \n"
							<< _notes;
						break;
					}
					case ErrorType::ASSET:
					{
						errorFile << "\nError of type ASSET in file " << _file << " in function " << _func << " \n notes: \n"
							<< _notes;
						break;
					}
					case ErrorType::HALTING:
					{
						errorFile << "\nError of type HALTING in file " << _file << " in function " << _func << " \n notes: \n"
							<< _notes;
						break;
					}
					case ErrorType::NULLPTR:
					{
						errorFile << "\nError of type NULLPTR in file " << _file << " in function " << _func << " \n notes: \n"
							<< _notes;
						break;
					}
					case ErrorType::EVENT:
					{
						errorFile << "\nError of type EVENT in file " << _file << " in function " << _func << " \n notes: \n"
							<< _notes;
						break;
					}
					}

					errorFile.close();
				}
			}
			void programHalt() const
			{
				writeError();
				errorFile.open(ERRORFILE);
				if (errorFile.good())
				{
					errorFile << "Program was halted because of the above error.";
					errorFile.close();
				}

				//make program halt.
			}
	};
	
	
	

}