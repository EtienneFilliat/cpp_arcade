/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Created by hexa,
*/

#include <iostream>
#include "Exception.hpp"

arc::Exception::Exception(const std::string &errorMessage,
	const std::string &project,
	const std::string &parentClass) throw()
	: _errorMessage("[" + project + "] " + "[" + parentClass + "] " +
	errorMessage)
{}

const char* arc::Exception::what() const throw()
{
	return (this->_errorMessage.c_str());
}