/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Exception,
*/

#ifndef EXCEPTION_HPP
	#define EXCEPTION_HPP
	#include <string>
	#include <exception>
namespace arc
{
	class Exception : public std::exception
	{
	public:
		Exception(const std::string &errorMessage = "Error",
			const std::string &project = "CPP_ARCADE",
			const std::string &parentClass = "Unknown") throw();
		~Exception() throw() = default;
		virtual const char *what() const throw();
	private:
		std::string _errorMessage;
	};
}
#endif /* !EXCEPTION_HPP */
