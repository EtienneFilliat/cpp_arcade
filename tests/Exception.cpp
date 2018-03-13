/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Created by hexa,
*/

#include <string>
#include <criterion/criterion.h>
#include "Exception.hpp"

static int division(int x, int y)
{
	if (y == 0)
		throw arc::Exception();
	return (x / y);
}

static int division_custom_error(int x, int y)
{
	if (y == 0)
		throw arc::Exception("Cannot divide by 0");
	return (x / y);
}

static int division_custom_error_parent(int x, int y)
{
	if (y == 0)
		throw arc::Exception("Cannot divide by 0", "Test");
	return (x / y);
}

static int division_full_custom(int x, int y)
{
	if (y == 0)
		throw arc::Exception("Cannot divide by 0", "Test", "TEST");
	return (x / y);
}

Test(utils, no_exception)
{
	try {
		division(1, 2);
	}
	catch (const arc::Exception &e) {
		cr_assert_eq(e.what(), "");
	}
}

Test(utils, basic_exception_no_param)
{
	try {
		division(1, 0);
	}
	catch (const arc::Exception &e) {
		cr_assert_eq(std::string(e.what()), "[CPP_ARCADE] [Unknown] Error");
	}
}

Test(utils, custom_error_exception)
{
	try {
		division_custom_error(1, 0);
	}
	catch (const arc::Exception &e) {
		cr_assert_eq(std::string(e.what()), "[CPP_ARCADE] [Unknown] Cannot divide by 0");
	}
}

Test(utils, custom_error_exception_and_parent)
{
	try {
		division_custom_error_parent(1, 0);
	}
	catch (const arc::Exception &e) {
		cr_assert_eq(std::string(e.what()), "[CPP_ARCADE] [Test] Cannot divide by 0");
	}
}

Test(utils, custom_exception)
{
	try {
		division_full_custom(1, 0);
	}
	catch (const arc::Exception &e) {
		cr_assert_eq(std::string(e.what()), "[TEST] [Test] Cannot divide by 0");
	}
}
