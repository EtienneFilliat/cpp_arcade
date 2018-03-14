//
// EPITECH PROJECT, 2018
// arcade
// File description:
// lib opening hpp
//

#ifndef DYNAMICLIB_HPP_
	#define DYNAMICLIB_HPP_
	#include <dlfcn.h>
	#include <string>
	#include "Exception.hpp"

namespace arc {

	template <class T>
	class DynamicLib {
	public:
		using fptrCreate = std::unique_ptr<T> (*)();
		DynamicLib()
			: _handle(nullptr)
		{}
		~DynamicLib()
		{
			if (_handle)
				dlclose(_handle);
		}
		void open(const std::string &libName)
		{
			std::string err = "Cannot open \'";

			_libName = libName;
			err += _libName;
			err += "\' library!";
			if (_handle)
				dlclose(_handle);
			_handle = dlopen(_libName.c_str(), RTLD_LAZY);
			if (!_handle)
				throw Exception(err, "DynamicLib");
		}
		void instantiate()
		{
			std::string err = "Missing \'create_object\'";

			err +=" symbol in \'";
			err += _libName;
			err += "\'!";
			if (!dlsym(_handle, "create_object"))
				throw Exception(err, "DynamicLib");
			_create = (fptrCreate) dlsym(_handle, "create_object");
		}
		std::unique_ptr<T> load() { return _create(); }
		void close() { dlclose(_handle); }
	private:
		std::string _libName;
		void *_handle;
		fptrCreate _create;
	};
}

#endif /* !DYNAMICLIB_HPP_ */
